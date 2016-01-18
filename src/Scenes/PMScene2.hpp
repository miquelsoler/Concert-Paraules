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

#include "PMRendererPaintbrush2.h"
#include "PMRendererTypography.h"
#include "PMRendererColor.h"
#include "PMRendererRibbon.h"
#include "PMRendererTextBox.h"
#include "PMRendererStillImage.h"
#include "PMRendererCurves.h"

#include "PMRecorder.hpp"

#include "PMUICanvasRenderers.h"
#include "PMUICanvasAudioAnalyzer.h"

#include "PMAudioAnalyzer.hpp"

#include "PMSettingsManagerAudioDevices.h"

typedef enum
{
    RECORDING_NORMAL = 0,
    RECORDING_ADDPOEM = 1,
    RECORDING_ADDTITLE = 2
} PMRecordingState;


class PMScene2 : public PMBaseScene
{
public:

    PMScene2();
    ~PMScene2();

    void setup();
    void goToRenderer(int rendererID);
    void update();
    void updateEnter();
    void updateExit();
    void draw();

    void saveSettings();
    void keyReleased(int key);
    void recorderSetup();

    // Audio events
    void pitchChanged(pitchParams &pitchParams);
    void energyChanged(energyParams &energyParams);
    void silenceStateChanged(silenceParams &silenceParams);
    void pauseStateChanged(pauseParams &pauseParams);
    void onsetDetected(onsetParams &onsetParams);
    void shtDetected(shtParams &shtParams);
    void melodyDirection(melodyDirectionParams &melodyDirectionParams);

    // Mouse events
    void mouseDragged(int x, int y, int button);
    void mousePressed(int x, int y, int button);
    void mouseReleased(int x, int y, int button);

    // Window Resize
    void windowResized(int x, int y);
    
private:

    void takeSnapshot();
    
    PMBaseRenderer                      *renderer;
    PMRendererStillImage                stillImagePoem;
    PMRendererStillImage                stillImageTitle;

    bool                                rendererAlreadyCreated;
    int                                 currentRenderer;
    
    PMRecorder                          *recorder;
    PMRecordingState                    recState;
    float                               startTimeRecordingText;
    float                               durationRecordingText;

    vector<PMUICanvasAudioAnalyzer *>   guiAudioAnalyzers;
    bool                                guiAudioAnalyzerCreated;

    ofColor                             canvasBgColor;

    bool                                showGUI;

    vector<PMSettingsDevice>            *enabledAudioDevices;
};

#endif /* PMScene2_hpp */
