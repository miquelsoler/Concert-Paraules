//
// Created by Miquel Àngel Soler on 20/11/15.
//

#ifndef PMCONCERTPARAULES_PMUICANVASAUDIOSETTINGS_H
#define PMCONCERTPARAULES_PMUICANVASAUDIOSETTINGS_H

#include "PMBaseUICanvas.h"
#include "PMSettingsManagerAudioAnalyzers.h"

typedef enum
{
    PRESET_LOAD = 0,
    PRESET_SAVE = 1
} PRESET_MODE;

class PMUICanvasAudioSettings : public PMBaseUICanvas
{
public:

    PMUICanvasAudioSettings(string title, int headerFontSize);

    virtual void init(int posX, int posY, bool autosize = true, int width = 0, int height = 0);
    virtual void clear();

    virtual void handleEvents(ofxUIEventArgs &e);

private:

    ofxUIToggleMatrix *presetsMatrix;
    PRESET_MODE presetsMode;

    float minMidiValue, maxMidiValue;
    ofxUISlider *minMidiSlider;
    ofxUISlider *maxMidiSlider;

    float minEnergyValue, maxEnergyValue;
    ofxUISlider *minEnergySlider;
    ofxUISlider *maxEnergySlider;

    float silenceThresholdValue;
    int silenceQueueValue;
    ofxUISlider *silenceThresholdSlider;
    ofxUIIntSlider *silenceQueueSlider;

    float onsetThresholdValue;
    float onsetAlphaValue;
    ofxUISlider *onsetThresholdSlider;
    ofxUISlider *onsetAlphaSlider;

    float smoothingDeltaValue;
    ofxUISlider *smoothingDeltaSlider;

    int numMelBandsValue;
    ofxUIIntSlider *numMelBandsSlider;

    PMSettingsManagerAudioAnalyzers *settings;

    void keyPressed(int key);
    void keyReleased(int key);

    void updateExternalSettings();

    int getActivePreset();
};


#endif //PMCONCERTPARAULES_PMUICANVASAUDIOSETTINGS_H
