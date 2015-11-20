//
// Created by Miquel Àngel Soler on 20/11/15.
//

#ifndef PMCONCERTPARAULES_PMUICANVASAUDIOSETTINGS_H
#define PMCONCERTPARAULES_PMUICANVASAUDIOSETTINGS_H

#include "PMBaseUICanvas.h"
#include "PMSettingsManagerAudioAnalyzers.h"

class PMUICanvasAudioSettings : public PMBaseUICanvas
{
public:

    PMUICanvasAudioSettings(string title, int headerFontSize);

    virtual void init(int posX, int posY, bool autosize = true, int width = 0, int height = 0);
    virtual void clear();

    virtual void handleEvents(ofxUIEventArgs &e);

private:

    float minMidiValue, maxMidiValue;
    ofxUISlider *minMidiSlider;
    ofxUISlider *maxMidiSlider;

    float minEnergyValue, maxEnergyValue;
    ofxUISlider *minEnergySlider;
    ofxUISlider *maxEnergySlider;

    int silenceThresholdValue;
    int silenceQueueValue;
    ofxUIIntSlider *silenceThresholdSlider;
    ofxUIIntSlider *silenceQueueSlider;

    float onsetThresholdValue;
    float onsetAlphaValue;
    ofxUISlider *onsetThresholdSlider;
    ofxUISlider *onsetAlphaSlider;

    float smoothingDeltaValue;
    ofxUISlider *smoothingDeltaSlider;

    int numMelBandsValue;
    ofxUIIntSlider *numMelBandsSlider;

    // Settings

    PMSettingsManagerAudioAnalyzers *settings;
};


#endif //PMCONCERTPARAULES_PMUICANVASAUDIOSETTINGS_H
