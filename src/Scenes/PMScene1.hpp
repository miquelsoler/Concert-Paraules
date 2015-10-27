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

    int setupGUIPoem(float originX, float originY);
    int setupGUIAudioSettings(float originX, float originY);
    void setupGUIMainButtons();

    void handleEventInputDevices(ofxUIEventArgs &e);
    void handleEventMainButtons(ofxUIEventArgs &e);

    void enableDevice(unsigned int deviceIndex);

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
