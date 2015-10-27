//
//  PMSettingsManager.h
//  ConductrEnter
//
//  Created by Miquel �ngel Soler on 25/5/15.
//
//

#pragma once

#ifndef __ConductrEnter__SettingsManager__
#define __ConductrEnter__SettingsManager__

#include <stdio.h>
#include "ofxJSON.h"

// Debug/release string settings
static const string STR_DEBUG_MODE          = "Debug Mode";
static const string STR_RELEASE_MODE        = "Release Mode";
static const string STR_SHOW_GUI            = "Show GUI";
static const string STR_SHOW_FPS            = "Show FPS";

// Audio device settings
static const string STR_APP_SETTINGS        = "App Settings";
static const string STR_DEVICES             = "Devices";
static const string STR_DEVICE_ID           = "1. Id";
static const string STR_DEVICE_ENABLED      = "2. Enabled";
static const string STR_CHANNELS            = "3. Channels";
static const string STR_CHANNEL_ID          = "1. Id";
static const string STR_CHANNEL_ENABLED     = "2. Enabled";

struct DeviceChannel
{
    int ID;
    bool enabled;
};

class PMSettingsManager
{
public:
    static PMSettingsManager &getInstance()
    {
        static PMSettingsManager instance;
        return instance;
    }

    // General
    bool getDebugShowGUI();
    bool getDebugShowFPS();
    bool getReleaseShowGUI();
    bool getReleaseShowFPS();

    // Audio devices
    void enableDevice(bool enable, unsigned int deviceID);
    void enableDeviceChannel(bool enable, unsigned int deviceID, unsigned int channelID);

    // Debug Mode
    bool                                debugShowGUI;
    bool                                debugShowFPS;

    // Release Mode
    bool                                releaseShowGUI;
    bool                                releaseShowFPS;

    // Input devices (map of deviceID + array of channels per device)
    map<int, vector<DeviceChannel>>     deviceSettings;

    void writeAudioDevicesSettings();

private:

    PMSettingsManager();
    bool loadGeneralSettings();
    bool loadAudioDevicesSettings();

    void buildAudioDevicesVectorFromJSON();

    void createAudioDeviceJSONSettings();

    int findDeviceWithID(int deviceID);
    int findChannelWithID(int channelID, int deviceID);

    ofxJSONElement jsonGeneral;
    ofxJSONElement jsonAudioDevices;
};

#endif /* defined(__ConductrEnter__SettingsManager__) */
