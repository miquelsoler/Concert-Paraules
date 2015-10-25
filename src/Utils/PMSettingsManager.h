//
//  PMSettingsManager.h
//  ConductrEnter
//
//  Created by Miquel Ëngel Soler on 25/5/15.
//
//

#pragma once

#ifndef __ConductrEnter__SettingsManager__
#define __ConductrEnter__SettingsManager__

#include <stdio.h>
#include "ofxJSON.h"

// Debug/release string settings
static const string     STR_DEBUG_MODE      = "Debug Mode";
static const string     STR_RELEASE_MODE    = "Release Mode";
static const string     STR_SHOW_GUI        = "Show GUI";
static const string     STR_SHOW_FPS        = "Show FPS";

// "Concert de les paraules" string settings
static const string     STR_APP_SETTINGS    = "App Settings";
static const string     STR_AS_DEVICES      = "Devices";
static const string     STR_AS_CHANNELS     = "Channels";
static const string     STR_AS_CHANNEL_ID   = "Id";

class PMSettingsManager
{
public:
    static PMSettingsManager &getInstance()
    {
        static PMSettingsManager instance;
        return instance;
    }

    // Debug Mode
    bool                                debugShowGUI;
    bool                                debugShowFPS;

    // Release Mode
    bool                                releaseShowGUI;
    bool                                releaseShowFPS;

    // Input devices (map of deviceID + array of channels per device)
    map<int, vector<int>>               deviceSettings;


    void writeToFile();

private:

    PMSettingsManager();
    bool loadSettings();

    ofxJSONElement  json;
};

#endif /* defined(__ConductrEnter__SettingsManager__) */
