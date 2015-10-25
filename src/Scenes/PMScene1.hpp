//
//  PMScene1.hpp
//  PMConcertParaules
//
//  Created by Miquel Àngel Soler on 7/10/15.
//
//

#ifndef PMScene1_hpp
#define PMScene1_hpp

#pragma once

#include <stdio.h>
#include "ofxUI.h"
#include "PMBaseScene.hpp"
#include "PMAudioAnalyzer.hpp"

using namespace std;

class PMScene1 : public PMBaseScene
{
public:

    PMScene1();
    ~PMScene1();

    void setup();
    void update();
    void draw();

    void willDraw();
    void willExit();

private:

    float setupGUIPoem(float originX, float originY);
    float setupGUIAudioSettings(float originX, float originY);
    void setupGUIMainButtons();

    void handleEventInputDevices(ofxUIEventArgs &e);
    void handleEventMainButtons(ofxUIEventArgs &e);

    bool addDevice(unsigned int deviceIndex);
    void addDeviceChannels(unsigned int deviceIndex);
    string buildStringForSoundDevice(ofSoundDevice *soundDevice);

    // UI
    ofxUISuperCanvas        *guiPoemSelector;
    ofxUISuperCanvas        *guiAudioSettings;
    ofxUISuperCanvas        *guiMainButtons;

    float                   guiX, guiY;
    float                   guiPanelWidth;

    ofColor                 canvasBgColor;
    ofColor                 canvasTitleColor;
    ofColor                 deviceLabelColor;
    ofColor                 channelsLabelColor;

    // Convenience attributes
    vector <ofSoundDevice>  soundDevices;
    vector<string>          soundDevicesNames;

    // Settings
    vector<int>             selectedSoundDevices;
    vector<int>             selectedChannels;
};

#endif /* PMScene1_hpp */
