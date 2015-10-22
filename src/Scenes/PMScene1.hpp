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

    float setupGUIPoem(float originX, ofxUIColor bgColor);
    float setupGUIAudioSettings(float originX, ofxUIColor bgColor);

    string buildStringForSoundDevice(ofSoundDevice *soundDevice);

    // UI
    ofxUISuperCanvas        *guiPoemSelector;
    ofxUISuperCanvas        *guiAudioSettings;
    float                   guiX, guiY;
    float                   guiPanelWidth;

    // Convenience attributes
    vector <ofSoundDevice>  soundDevices;

    // Settings
    int                     selectedSoundDevice;
    PMDAA_ChannelMode       selectedChannelMode;
    int                     selectedChannel;
    
};

#endif /* PMScene1_hpp */
