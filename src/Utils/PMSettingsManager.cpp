//
//  PMSettingsManager.cpp
//  ConductrEnter
//
//  Created by Miquel Angel Soler on 25/5/15.
//
//

#include "PMSettingsManager.h"
#include "PMAudioAnalyzer.hpp"

static const string FILENAME_GENERAL        = "settings/general.json";
static const string FILENAME_AUDIODEVICES   = "settings/audioDevices.json";
static const string FILENAME_POEM           = "settings/poem.json";

// Debug/release string settings
static const string STR_DEBUG_MODE          = "Debug Mode";
static const string STR_RELEASE_MODE        = "Release Mode";
static const string STR_SHOW_FPS            = "Show FPS";

// Audio device settings
static const string STR_DEVICES             = "Devices";
static const string STR_DEVICE_NAME         = "1. Name";
static const string STR_DEVICE_ID           = "2. Id";
static const string STR_DEVICE_ENABLED      = "3. Enabled";
static const string STR_CHANNELS            = "4. Channels";
static const string STR_CHANNEL_ID          = "1. Id";
static const string STR_CHANNEL_ENABLED     = "2. Enabled";

// Poem settings
static const string STR_POEM_FILE           = "Poem File";
static const string STR_POEM_VALID          = "Valid File";
static const string STR_POEM_FILE_DEFAULT   = "<None>";

#pragma mark - Internal setup

///--------------------------------------------------------------
PMSettingsManager::PMSettingsManager()
{
    bool parserResult = loadGeneralSettings();
    if (!parserResult)
    {
        string msg = "BAD FORMAT IN " + FILENAME_GENERAL + ". Now quitting...";
        ofLog(OF_LOG_ERROR, msg);
        std::exit(EXIT_FAILURE);
    }

    parserResult = loadAudioDevicesSettings();
    if (!parserResult)
    {
        string msg = "BAD FORMAT IN " + FILENAME_AUDIODEVICES + ". Now quitting...";
        ofLog(OF_LOG_ERROR, msg);
        std::exit(EXIT_FAILURE);
    }

    parserResult = loadPoemSettings();
    if (!parserResult)
    {
        string msg = "BAD FORMAT IN " + FILENAME_POEM + ". Now quitting...";
        ofLog(OF_LOG_ERROR, msg);
        std::exit(EXIT_FAILURE);
    }
}

#pragma mark - Getters and setters

bool PMSettingsManager::getDebugShowFPS()
{
    return jsonGeneral[STR_DEBUG_MODE][STR_SHOW_FPS].asBool();
}

bool PMSettingsManager::getReleaseShowFPS()
{
    return jsonGeneral[STR_RELEASE_MODE][STR_SHOW_FPS].asBool();
}

vector<PMSettingsDevice> *PMSettingsManager::getAudioDevices()
{
    return &deviceSettings;
};

void PMSettingsManager::enableAudioDevice(unsigned int deviceID, bool enable)
{
    bool found = false;
    int deviceIndex = 0;
    for (int i = 0; i < jsonAudioDevices[STR_DEVICES].size() && !found; ++i)  {
        found = jsonAudioDevices[STR_DEVICES][i][STR_DEVICE_ID].asInt() == deviceID;
        if (found) deviceIndex = i;
    }

    if (found) {
        jsonAudioDevices[STR_DEVICES][deviceIndex][STR_DEVICE_ENABLED] = enable;
    }
}

void PMSettingsManager::enableAudioDeviceChannel(unsigned int deviceID, unsigned int channelID, bool enable)
{
    bool found = false;
    int deviceIndex = 0;
    for (int i = 0; i < jsonAudioDevices[STR_DEVICES].size() && !found; ++i)  {
        found = jsonAudioDevices[STR_DEVICES][i][STR_DEVICE_ID].asInt() == deviceID;
        if (found) deviceIndex = i;
    }

    if (found) {
        jsonAudioDevices[STR_DEVICES][deviceIndex][STR_CHANNELS][channelID][STR_CHANNEL_ENABLED] = enable;
    }
}

string PMSettingsManager::getPoemFilename()
{
    return jsonPoem[STR_POEM_FILE].asString();
}

void PMSettingsManager::addPoem(string filePath)
{
    jsonPoem[STR_POEM_FILE] = filePath;
    jsonPoem[STR_POEM_VALID] = true;
    jsonPoem.save(FILENAME_POEM, true);
}

#pragma mark - General settings

bool PMSettingsManager::loadGeneralSettings()
{
    return jsonGeneral.open(FILENAME_GENERAL);
}

#pragma mark - Audio settings

bool PMSettingsManager::loadAudioDevicesSettings()
{
    ofFile audioDevicesFile(FILENAME_AUDIODEVICES);
    bool fileExists = audioDevicesFile.exists();
    audioDevicesFile.close();

    if (!fileExists) createAudioDeviceJSONSettings();

    bool result = jsonAudioDevices.open(FILENAME_AUDIODEVICES);
    if (result) buildAudioDevicesVectorFromJSON();

    return result;
}

void PMSettingsManager::createAudioDeviceJSONSettings()
{
    vector<ofSoundDevice> devices = PMAudioAnalyzer::getInstance().getInputDevices();

    jsonAudioDevices[STR_DEVICES] = Json::arrayValue;

    for (int i=0; i<devices.size(); ++i)
    {
        Json::Value jsonDevice;
        jsonDevice[STR_DEVICE_ID] = devices[i].deviceID;
        jsonDevice[STR_DEVICE_ENABLED] = false;
        jsonDevice[STR_DEVICE_NAME] = devices[i].name;

        jsonDevice[STR_CHANNELS] = Json::arrayValue;
        for (int j=0; j<devices[i].inputChannels; ++j)
        {
            Json::Value jsonDeviceChannel;
            jsonDeviceChannel[STR_CHANNEL_ID] = j;
            jsonDeviceChannel[STR_CHANNEL_ENABLED] = false;

            jsonDevice[STR_CHANNELS].append(jsonDeviceChannel);
        }

        jsonAudioDevices[STR_DEVICES].append(jsonDevice);
    }

    writeAudioDevicesSettings();
}

void PMSettingsManager::writeAudioDevicesSettings()
{
    jsonAudioDevices.save(FILENAME_AUDIODEVICES, true);
}

#pragma mark - Poem settings

bool PMSettingsManager::loadPoemSettings()
{
    ofFile poemFile(FILENAME_POEM);
    bool fileExists = poemFile.exists();
    poemFile.close();

    if (!fileExists) createPoemJSONSettings();

    bool result = jsonPoem.open(FILENAME_POEM);
    return result;
}

void PMSettingsManager::createPoemJSONSettings()
{
    jsonPoem[STR_POEM_FILE] = STR_POEM_FILE_DEFAULT;
    jsonPoem[STR_POEM_VALID] = false;
    jsonPoem.save(FILENAME_POEM, true);
}

void PMSettingsManager::writePoemSettings()
{
    jsonPoem.save(FILENAME_POEM, true);
}

#pragma mark - Convenience methods

///--------------------------------------------------------------
void PMSettingsManager::buildAudioDevicesVectorFromJSON()
{
    for (int i = 0; i < jsonAudioDevices[STR_DEVICES].size(); ++i)
    {
        Json::Value jsonDevice = jsonAudioDevices[STR_DEVICES][i];

        PMSettingsDevice device;
        device.name = jsonDevice[STR_DEVICE_NAME].asString();
        device.ID = jsonDevice[STR_DEVICE_ID].asInt();
        device.enabled = jsonDevice[STR_DEVICE_ENABLED].asBool();

        Json::Value jsonDeviceChannels = jsonDevice[STR_CHANNELS];
        vector<PMSettingsDeviceChannel> deviceChannels;

        for (int j = 0; j < jsonDeviceChannels.size(); ++j) {
            Json::Value jsonDeviceChannel = jsonDeviceChannels[j];

            PMSettingsDeviceChannel channel;
            channel.ID = jsonDeviceChannel[STR_CHANNEL_ID].asInt();
            channel.enabled = jsonDeviceChannel[STR_CHANNEL_ENABLED].asBool();

            deviceChannels.push_back(channel);
        }

        device.channels = deviceChannels;

        deviceSettings.push_back(device);
    }
}
