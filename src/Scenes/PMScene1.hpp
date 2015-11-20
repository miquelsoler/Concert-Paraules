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
#include "PMSettingsManagerPoem.h"
#include "PMSettingsManagerAudioDevices.h"
#include "PMSettingsManagerRenderers.h"

#include "PMUICanvasPoem.h"
#include "PMUICanvasAudioDevices.h"
#include "PMUICanvasRenderers.h"
#include "PMUICanvasAudioSettings.h"

class PMScene1 : public PMBaseScene
{
public:

    PMScene1();
    ~PMScene1();

    void setup();
    void update();
    void updateEnter();
    void updateExit();
    void draw();

    void saveSettings();

private:

    PMUICanvasPoem                  *guiPoemSelector;
    PMUICanvasAudioDevices          *guiAudioDevices;
    PMUICanvasRenderers             *guiRendererSettings;
    PMUICanvasAudioSettings         *guiAudioSettings;

    ofColor                         canvasBgColor;
    int                             panelMargin = 5;
};

#endif /* PMScene1_hpp */
