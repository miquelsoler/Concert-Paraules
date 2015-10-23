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

    // Input devices (pair of deviceID + array of channels per device
    vector<pair<int, vector<int>>>      deviceSettings;

    void writeToFile();

private:

    PMSettingsManager();
    bool loadSettings();

    ofxJSONElement  json;
};

#endif /* defined(__ConductrEnter__SettingsManager__) */
