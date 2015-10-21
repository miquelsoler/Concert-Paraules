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
#include "PMBaseScene.hpp"
#include "ofxUI.h"

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

    void setupGUIPoem(float originX, ofxUIColor bgColor);
    void setupGUIAudioSettings(float originX, ofxUIColor bgColor);

    // UI
    ofxUISuperCanvas    *guiPoemSelector;
    ofxUISuperCanvas    *guiAudioSettings;
    float               guiX, guiY;
    float               guiPanelWidth;
};

#endif /* PMScene1_hpp */
