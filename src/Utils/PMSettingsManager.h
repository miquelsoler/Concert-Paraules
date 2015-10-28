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
#include "PMSettingsDevice.h"
#include "PMSettingsDeviceChannel.h"

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


class PMSettingsManager
{
public:
    static PMSettingsManager &getInstance()
    {
        static PMSettingsManager instance;
        return instance;
    }

    // General
    bool getDebugShowFPS();
    bool getReleaseShowFPS();

    // Audio devices
    vector<PMSettingsDevice> *getAudioDevices();
    void enableAudioDevice(unsigned int deviceID, bool enable);
    void enableAudioDeviceChannel(unsigned int deviceID, unsigned int channelID, bool enable);

    void writeAudioDevicesSettings();

private:

    PMSettingsManager();
    bool loadGeneralSettings();
    bool loadAudioDevicesSettings();

    void buildAudioDevicesVectorFromJSON();

    void createAudioDeviceJSONSettings();

    vector<PMSettingsDevice> deviceSettings;

    ofxJSONElement jsonGeneral;
    ofxJSONElement jsonAudioDevices;
};

#endif /* defined(__ConductrEnter__SettingsManager__) */
