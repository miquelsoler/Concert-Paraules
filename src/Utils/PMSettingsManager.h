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

    // Poem
    void addPoem(string filePath);

private:

    PMSettingsManager();
    bool loadGeneralSettings();
    bool loadAudioDevicesSettings();
    bool loadPoemSettings();

    void createAudioDeviceJSONSettings();
    void createPoemJSONSettings();

    void buildAudioDevicesVectorFromJSON();

    vector<PMSettingsDevice> deviceSettings;

    ofxJSONElement jsonGeneral;
    ofxJSONElement jsonAudioDevices;
    ofxJSONElement jsonPoem;
};

#endif /* defined(__ConductrEnter__SettingsManager__) */
