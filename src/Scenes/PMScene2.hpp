//
//  PMScene2.hpp
//  PMConcertParaules
//
//  Created by Miquel Àngel Soler on 7/10/15.
//
//

#ifndef PMScene2_hpp
#define PMScene2_hpp

#pragma once

#include <stdio.h>

#include "PMBaseScene.hpp"

#include "PMRendererPaintbrush.h"
#include "PMRendererTypography.h"
#include "PMRendererColor.h"

#include "PMUICanvasRenderers.h"
#include "PMUICanvasAudioAnalyzer.h"

#include "PMAudioAnalyzer.hpp"

#include "PMSettingsManagerAudioAnalyzers.h"
#include "PMSettingsManagerAudioDevices.h"


class PMScene2 : public PMBaseScene
{
public:

    PMScene2();
    ~PMScene2();

    void setup();
    void update();
    void updateEnter();
    void updateExit();
    void draw();

    void saveSettings();

    void keyReleased(int key);

    void pitchChanged(pitchParams &pitchParams);
    void energyChanged(energyParams &energyParams);
    void silenceStateChanged(silenceParams &silenceParams);
    void onsetDetected(onsetParams &onsetParams);

private:

    PMBaseRenderer                      *renderer;

    vector<PMUICanvasAudioAnalyzer *>   guiAudioAnalyzers;
    bool                                guiAudioAnalyzerCreated;

    ofColor                             canvasBgColor;

    bool                                showGUI;

    PMSettingsManagerAudioAnalyzers     *audioAnalyzersSettings;

    vector<PMSettingsDevice>            *enabledAudioDevices;
};

#endif /* PMScene2_hpp */
