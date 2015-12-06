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

//#include "PMRendererPaintbrush.h"
#include "PMRendererPaintbrush2.h"
#include "PMRendererTypography.h"
#include "PMRendererColor.h"
#include "PMRendererTextBox.h"

#include "PMRecorder.hpp"

#include "PMUICanvasRenderers.h"
#include "PMUICanvasAudioAnalyzer.h"

#include "PMAudioAnalyzer.hpp"

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
    void pauseStateChanged(pauseParams &pauseParams);
    void onsetDetected(onsetParams &onsetParams);
    void shtDetected(shtParams &shtParams);
    void melodyDirection(melodyDirectionParams &melodyDirectionParams);

private:

    PMBaseRenderer                      *renderer;
    PMRendererTextBox                   textBox;

    PMRecorder                          *recorder;
    int                                 recState; // 0 : normal 1 : record textBox !!
    float                               startTimeRecordingText;
    float                               durationRecordingText;

    vector<PMUICanvasAudioAnalyzer *>   guiAudioAnalyzers;
    bool                                guiAudioAnalyzerCreated;

    ofColor                             canvasBgColor;

    bool                                showGUI;

    vector<PMSettingsDevice>            *enabledAudioDevices;
};

#endif /* PMScene2_hpp */
