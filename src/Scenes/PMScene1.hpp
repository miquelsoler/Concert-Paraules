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

    void dragEvent(ofDragInfo dragInfo); // Just in case we need it for poem selection (drag text file to scene)

    int setupGUIPoem(int originX, int originY);
    int setupGUIAudio(int originX, int originY);
    int setupGUIRenderer(int originX, int originY);
    void setupGUIMainButtons();

    void handleEventInputDevices(ofxUIEventArgs &e);
    void handleEventMainButtons(ofxUIEventArgs &e);

    void disableAllChannelsForDevice(ofxUIToggle *deviceToggle);
    void disableDeviceIfNoChannels(ofxUIToggle *channelToggle);

    ofxUISuperCanvas        *guiPoemSelector;
    ofxUISuperCanvas        *guiAudioSettings;
    ofxUISuperCanvas        *guiRendererSettings;
    ofxUISuperCanvas        *guiMainButtons;

    int                     guiX, guiY;

    ofColor                 canvasBgColor;
    ofColor                 canvasTitleColor;
    ofColor                 deviceLabelColor;
};

#endif /* PMScene1_hpp */
