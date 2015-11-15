//
// Created by Miquel Àngel Soler on 7/11/15.
//

#ifndef PMCONCERTPARAULES_PMUICANVASAUDIOANALYZER_H
#define PMCONCERTPARAULES_PMUICANVASAUDIOANALYZER_H

#include "PMBaseUICanvas.h"

#include "PMAudioInParams.h"
#include "PMAudioAnalyzer.hpp"
#include "PMSettingsManagerAudioAnalyzers.h"

class PMUICanvasAudioAnalyzer : public PMBaseUICanvas
{
public:

    PMUICanvasAudioAnalyzer(string title, int headerFontSize, unsigned int audioInputIndex);

    virtual void init(int posX, int posY, bool autosize = true, int width = 0, int height = 0);
    virtual void clear();

    virtual void handleEvents(ofxUIEventArgs &e);

private:

    unsigned int audioInputIndex;

    vector<PMDeviceAudioAnalyzer *> *audioAnalyzers;

    // Pitch ------------------------------------

    void pitchChanged(pitchParams &pitchParams);

    ofxUIRangeSlider    *pitchRangedSlider;
    ofxUISlider         *pitchSlider;
    float               pitchMinFreq, pitchMaxFreq;
    float               pitchCurrentFreq;

    // Energy -----------------------------------

    void energyChanged(energyParams &energyParams);

    ofxUISlider         *energySilder;
    float               energyCurrent;

    // Silence ----------------------------------

    void silenceStateChanged(silenceParams &silenceParams);

    ofxUILabelToggle    *silenceToggle;
    bool                silenceOn;

    // Settings

    PMSettingsManagerAudioAnalyzers *settings;
};


#endif //PMCONCERTPARAULES_PMUICANVASAUDIOANALYZER_H
