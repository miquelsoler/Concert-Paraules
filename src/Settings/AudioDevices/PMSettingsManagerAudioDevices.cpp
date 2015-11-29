//
// Created by Miquel Àngel Soler on 29/10/15.
//

#include "PMSettingsManagerAudioDevices.h"
#include "PMAudioAnalyzer.hpp"

static const string FILENAME                = "settings/audioDevices.json";

static const string STR_DEVICES             = "Devices";
static const string STR_DEVICE_NAME         = "1. Name";
static const string STR_DEVICE_ID           = "2. Id";
static const string STR_DEVICE_ENABLED      = "3. Enabled";
static const string STR_DEVICE_INCHANNELS   = "4. Input Channels";
static const string STR_DEVICE_OUTCHANNELS  = "5. Output Channels";
static const string STR_CHANNELS            = "6. Channels";
static const string STR_CHANNEL_ID          = "1. Id";
static const string STR_CHANNEL_ENABLED     = "2. Enabled";


PMSettingsManagerAudioDevices::PMSettingsManagerAudioDevices() : PMSettingsManager()
{
    filename = FILENAME;

    bool parserResult = load(filename);
    if (!parserResult)
    {
        string msg = "BAD FORMAT IN " + FILENAME + ". Now quitting...";
        ofLog(OF_LOG_ERROR, msg);
        std::exit(EXIT_FAILURE);
    }
}

bool PMSettingsManagerAudioDevices::load(string filename)
{
    if (!fileExists(FILENAME))
        createJSONSettings();

    bool result = PMSettingsManager::load(filename);
    if (result)
    {
//        if (!JSONmatchesCurrentAudioDevices())
//            createJSONSettings();

        buildAllAudioDevicesVectorFromJSON();
    }

    return result;
}

void PMSettingsManagerAudioDevices::createJSONSettings()
{
    if (fileExists(FILENAME))
    {
        ofFile file(filename);
        file.remove(false);
        file.close();
    }

    json.clear();

    vector<ofSoundDevice> devices = PMAudioAnalyzer::getInstance().getInputDevices();

    json[STR_DEVICES] = Json::arrayValue;

    for (int i=0; i<devices.size(); ++i)
    {
        Json::Value jsonDevice;
        jsonDevice[STR_DEVICE_ID] = devices[i].deviceID;
        jsonDevice[STR_DEVICE_ENABLED] = false;
        jsonDevice[STR_DEVICE_NAME] = devices[i].name;
        jsonDevice[STR_DEVICE_INCHANNELS] = devices[i].inputChannels;
        jsonDevice[STR_DEVICE_OUTCHANNELS] = devices[i].outputChannels;

        jsonDevice[STR_CHANNELS] = Json::arrayValue;
        for (int j=0; j<devices[i].inputChannels; ++j)
        {
            Json::Value jsonDeviceChannel;
            jsonDeviceChannel[STR_CHANNEL_ID] = j;
            jsonDeviceChannel[STR_CHANNEL_ENABLED] = false;

            jsonDevice[STR_CHANNELS].append(jsonDeviceChannel);
        }

        json[STR_DEVICES].append(jsonDevice);
    }

    write();
}

bool PMSettingsManagerAudioDevices::JSONmatchesCurrentAudioDevices()
{
    // TODO: Compare actual audio devices with JSON settings.
    return true;
}

void PMSettingsManagerAudioDevices::buildAllAudioDevicesVectorFromJSON()
{
    devicesSettings.clear();

    unsigned int inputIndex = 0;

    for (int i = 0; i < json[STR_DEVICES].size(); ++i)
    {
        Json::Value jsonDevice = json[STR_DEVICES][i];

        PMSettingsDevice device;
        device.name = jsonDevice[STR_DEVICE_NAME].asString();
        device.ID = jsonDevice[STR_DEVICE_ID].asUInt();
        device.enabled = jsonDevice[STR_DEVICE_ENABLED].asBool();
        device.inChannels = jsonDevice[STR_DEVICE_INCHANNELS].asInt();
        device.outChannels = jsonDevice[STR_DEVICE_OUTCHANNELS].asInt();

        Json::Value jsonDeviceChannels = jsonDevice[STR_CHANNELS];
        vector<PMSettingsDeviceChannel> deviceChannels;

        for (int j = 0; j < jsonDeviceChannels.size(); ++j)
        {
            Json::Value jsonDeviceChannel = jsonDeviceChannels[j];

            PMSettingsDeviceChannel channel;
            channel.ID = jsonDeviceChannel[STR_CHANNEL_ID].asUInt();
            channel.enabled = jsonDeviceChannel[STR_CHANNEL_ENABLED].asBool();

            deviceChannels.push_back(channel);

            inputIndex++;
        }

        device.channels = deviceChannels;

        devicesSettings.push_back(device);
    }
}

void PMSettingsManagerAudioDevices::buildEnabledAudioDevicesVectorFromJSON()
{
    enabledDevices.clear();

    for (int i = 0; i < json[STR_DEVICES].size(); ++i)
    {
        Json::Value jsonDevice = json[STR_DEVICES][i];

        PMSettingsDevice device;
        device.name = jsonDevice[STR_DEVICE_NAME].asString();
        device.ID = jsonDevice[STR_DEVICE_ID].asUInt();
        device.enabled = jsonDevice[STR_DEVICE_ENABLED].asBool();
        device.inChannels = jsonDevice[STR_DEVICE_INCHANNELS].asInt();
        device.outChannels = jsonDevice[STR_DEVICE_OUTCHANNELS].asInt();

        if (device.inChannels <= 0) continue;
        if (!(device.enabled)) continue;

        Json::Value jsonDeviceChannels = jsonDevice[STR_CHANNELS];
        vector<PMSettingsDeviceChannel> deviceChannels;

        for (int j = 0; j < jsonDeviceChannels.size(); ++j)
        {
            Json::Value jsonDeviceChannel = jsonDeviceChannels[j];

            PMSettingsDeviceChannel channel;
            channel.ID = jsonDeviceChannel[STR_CHANNEL_ID].asUInt();
            channel.enabled = jsonDeviceChannel[STR_CHANNEL_ENABLED].asBool();

            if (!(channel.enabled)) continue;

            deviceChannels.push_back(channel);
        }

        device.channels = deviceChannels;

        if (device.channels.size() > 0)
            enabledDevices.push_back(device);
    }
}


vector<PMSettingsDevice> *PMSettingsManagerAudioDevices::getAudioDevices()
{
    buildAllAudioDevicesVectorFromJSON();
    return &devicesSettings;
};

vector<PMSettingsDevice> *PMSettingsManagerAudioDevices::getEnabledAudioDevices()
{
    buildEnabledAudioDevicesVectorFromJSON();
    return &enabledDevices;
}

void PMSettingsManagerAudioDevices::enableAudioDevice(unsigned int deviceID, bool enable)
{
    bool found = false;
    int deviceIndex = 0;
    for (int i = 0; i < json[STR_DEVICES].size() && !found; ++i)  {
        found = json[STR_DEVICES][i][STR_DEVICE_ID].asInt() == deviceID;
        if (found) deviceIndex = i;
    }

    if (found) {
        json[STR_DEVICES][deviceIndex][STR_DEVICE_ENABLED] = enable;
    }
}

void PMSettingsManagerAudioDevices::enableAudioDeviceChannel(unsigned int deviceID, unsigned int channelID, bool enable)
{
    bool found = false;
    int deviceIndex = 0;
    for (int i = 0; i < json[STR_DEVICES].size() && !found; ++i)  {
        found = json[STR_DEVICES][i][STR_DEVICE_ID].asInt() == deviceID;
        if (found) deviceIndex = i;
    }

    if (found) {
        json[STR_DEVICES][deviceIndex][STR_CHANNELS][channelID][STR_CHANNEL_ENABLED] = enable;
    }
}

unsigned int PMSettingsManagerAudioDevices::getNumEnabledChannelsForDevice(PMSettingsDevice *device)
{
    if (device->channels.size() == 0) return 0;

    unsigned int counter = 0;
    for (int i=0; i<device->channels.size(); ++i)
        if (device->channels[i].enabled) counter++;

    return counter;
}
