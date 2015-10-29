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
#include "PMSettingsRenderer.h"


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
    string getPoemFilename();
    void addPoem(string filePath);
    void writePoemSettings();

    // Renderers
    vector<PMSettingsRenderer> *getRenderers();
    void writeRenderersSettings();

private:

    PMSettingsManager();

    bool loadGeneralSettings();

    bool loadAudioDevicesSettings();
    void createAudioDeviceJSONSettings();
    void buildAudioDevicesVectorFromJSON();
    vector<PMSettingsDevice> devicesSettings;

    bool loadPoemSettings();
    void createPoemJSONSettings();

    bool loadRenderersSettings();
    void createRenderersJSONSettings();
    void buildRenderersVectorFromJSON();
    vector<PMSettingsRenderer> renderersSettings;

    bool fileExists(string filename);


    ofxJSONElement jsonGeneral;
    ofxJSONElement jsonAudioDevices;
    ofxJSONElement jsonPoem;
    ofxJSONElement jsonRenderers;
};

#endif /* defined(__ConductrEnter__SettingsManager__) */
