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
#include "PMSceneManager.hpp"
#include "PMBaseScene.hpp"
#include "PMSettingsManagerPoem.h"
#include "PMSettingsManagerAudioDevices.h"
#include "PMSettingsManagerRenderers.h"

#include "PMUICanvasPoem.h"
#include "PMUICanvasAudioDevices.h"
#include "PMUICanvasRenderers.h"


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

    void setupGUIMainButtons();

    void handleEventMainButtons(ofxUIEventArgs &e);

    ofxUISuperCanvas                *guiMainButtons;

    PMUICanvasPoem                  *guiPoemSelector;
    PMUICanvasAudioDevices          *guiAudioSettings;
    PMUICanvasRenderers             *guiRendererSettings;

    int                             guiX, guiY;

    ofColor                         canvasBgColor;
    ofColor                         canvasTitleColor;
};

#endif /* PMScene1_hpp */
