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
bool PMSettingsManager::getDebugShowGUI()
{
    return debugShowGUI;
}

///--------------------------------------------------------------
bool PMSettingsManager::getDebugShowFPS()
{
    return debugShowFPS;
}

///--------------------------------------------------------------
bool PMSettingsManager::getReleaseShowGUI()
{
    return releaseShowGUI;
}

///--------------------------------------------------------------
bool PMSettingsManager::getReleaseShowFPS()
{
    return releaseShowFPS;
}

///--------------------------------------------------------------
vector<SettingsDevice> *PMSettingsManager::getAudioDevices()
{
    return &deviceSettings;
};

///--------------------------------------------------------------
void PMSettingsManager::enableAudioDevice(bool enable, unsigned int deviceID)
{

}

///--------------------------------------------------------------
void PMSettingsManager::enableAudioDeviceChannel(bool enable, unsigned int deviceID, unsigned int channelID)
{

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

    // Debug mode
    {
        debugShowGUI = jsonGeneral[STR_DEBUG_MODE][STR_SHOW_GUI].asBool();
        debugShowFPS = jsonGeneral[STR_DEBUG_MODE][STR_SHOW_FPS].asBool();
    }

    // Release mode
    {
        releaseShowGUI = jsonGeneral[STR_RELEASE_MODE][STR_SHOW_GUI].asBool();
        releaseShowFPS = jsonGeneral[STR_RELEASE_MODE][STR_SHOW_FPS].asBool();
    }

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

        SettingsDevice device;
        device.name = jsonDevice[STR_DEVICE_NAME].asString();
        device.ID = jsonDevice[STR_DEVICE_ID].asInt();
        device.enabled = jsonDevice[STR_DEVICE_ENABLED].asBool();

        Json::Value jsonDeviceChannels = jsonDevice[STR_CHANNELS];
        vector<SettingsDeviceChannel> deviceChannels;

        for (int j = 0; j < jsonDeviceChannels.size(); ++j) {
            Json::Value jsonDeviceChannel = jsonDeviceChannels[j];

            SettingsDeviceChannel channel;
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

///--------------------------------------------------------------
int PMSettingsManager::findDeviceWithID(int _deviceID)
{
    // Returns the index in the array of devices inside the JSON file
    // -1 means not found

    int result = -1;

    bool found = false;
    Json::Value defaultValue = -1;
    int numDevices = jsonGeneral[STR_APP_SETTINGS][STR_DEVICES].size();

    for (int i=0; i<numDevices && !found; ++i)
    {
        Json::Value deviceID = jsonGeneral[STR_APP_SETTINGS][STR_DEVICES][i].get(STR_DEVICE_ID, &defaultValue);
        found = deviceID == _deviceID;
        if (found) result = i;
    }

    return result;
}

///--------------------------------------------------------------
int PMSettingsManager::findChannelWithID(int _channelID, int _deviceID)
{
    // Returns the index in the array of device channels inside the JSON file
    // -1 means not found

    int result = -1;

    int deviceIndex = findDeviceWithID(_deviceID);
    if (deviceIndex == -1)
        return result;

    Json::Value device = jsonGeneral[STR_APP_SETTINGS][STR_DEVICES][deviceIndex];

    bool found = false;
    Json::Value defaultValue = -1;
    int numChannels = device.size();

    for (int i=0; i<numChannels; ++i)
    {
        Json::Value channelId = device[STR_CHANNELS];
    }
}
