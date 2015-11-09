//
// Created by Miquel Àngel Soler on 7/11/15.
//

#ifndef PMCONCERTPARAULES_PMUICANVASAUDIOANALYZER_H
#define PMCONCERTPARAULES_PMUICANVASAUDIOANALYZER_H

#include "PMBaseUICanvas.h"

#include "PMAudioOutParams.h"
#include "PMAudioAnalyzer.hpp"

class PMUICanvasAudioAnalyzer : public PMBaseUICanvas
{
public:

    PMUICanvasAudioAnalyzer(string title, int headerFontSize) : PMBaseUICanvas(title, headerFontSize) {}

    virtual void init(int posX, int posY, bool autosize = true, int width = 0, int height = 0);
    virtual void clear();

    virtual void handleEvents(ofxUIEventArgs &e);

    vector<PMDeviceAudioAnalyzer *> *audioAnalyzers;

    // Pitch ----------------------------------

    void pitchChanged(pitchParams &pitchParams);

    ofxUIRangeSlider    *pitchRangedSlider0;
    ofxUISlider         *pitchSlider0;
    ofxUIRangeSlider    *pitchRangedSlider1;
    ofxUISlider         *pitchSlider1;

    float pitchMinFreq0, pitchMaxFreq0;
    float currentPitchFreq0;
    float pitchMinFreq1, pitchMaxFreq1;
    float currentPitchFreq1;

    // Silence

    void silenceStateChanged(silenceParams &silenceParams);

    ofxUILabelToggle    *silenceToggle0;
    ofxUILabelToggle    *silenceToggle1;

    bool silenceOn0;
    bool silenceOn1;
};


#endif //PMCONCERTPARAULES_PMUICANVASAUDIOANALYZER_H