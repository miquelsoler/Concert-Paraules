//
//  PMSettingsManager.cpp
//  ConductrEnter
//
//  Created by Miquel Angel Soler on 25/5/15.
//
//

#include "PMSettingsManager.h"
#include "PMAudioAnalyzer.hpp"


const string FILENAME_GENERAL = "settings/general.json";
const string FILENAME_AUDIODEVICES = "settings/audioDevices.json";

#pragma mark - Internal setup

///--------------------------------------------------------------
PMSettingsManager::PMSettingsManager()
{
    bool parserResult = loadGeneralSettings();
    if (!parserResult)
    {
        ofLog(OF_LOG_ERROR, "BAD FORMAT IN general.json. Now quitting...");
        std::exit(EXIT_FAILURE);
    }

    parserResult = loadAudioDevicesSettings();
    if (!parserResult)
    {
        ofLog(OF_LOG_ERROR, "BAD FORMAT IN audioDevices.json. Now quitting...");
        std::exit(EXIT_FAILURE);
    }
}

#pragma mark - Getters and setters

///--------------------------------------------------------------
bool PMSettingsManager::getDebugShowFPS()
{
    return jsonGeneral[STR_DEBUG_MODE][STR_SHOW_FPS].asBool();
}

///--------------------------------------------------------------
bool PMSettingsManager::getReleaseShowFPS()
{
    return jsonGeneral[STR_RELEASE_MODE][STR_SHOW_FPS].asBool();
}

///--------------------------------------------------------------
vector<PMSettingsDevice> *PMSettingsManager::getAudioDevices()
{
    return &deviceSettings;
};

///--------------------------------------------------------------
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

///--------------------------------------------------------------
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

#pragma mark - Read/write JSON file

///--------------------------------------------------------------
bool PMSettingsManager::loadGeneralSettings()
{
    // JSON parse

    bool parsingSuccessful = jsonGeneral.open(FILENAME_GENERAL);

#ifdef OF_DEBUG
    cout << "PARSING RESULT: " << parsingSuccessful << endl;
#endif

    return parsingSuccessful;
}

///--------------------------------------------------------------
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

///--------------------------------------------------------------
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

///--------------------------------------------------------------
void PMSettingsManager::writeAudioDevicesSettings()
{
    jsonAudioDevices.save(FILENAME_AUDIODEVICES, true);
}
