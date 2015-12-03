//
// Created by Miquel Àngel Soler on 7/11/15.
//

#ifndef PMCONCERTPARAULES_PMUICANVASAUDIOANALYZER_H
#define PMCONCERTPARAULES_PMUICANVASAUDIOANALYZER_H

#include "PMBaseUICanvas.h"

#include "PMAudioInParams.h"
#include "PMAudioAnalyzer.hpp"
//#include "PMSettingsManagerAudioAnalyzers.h"

class PMUICanvasAudioAnalyzer : public PMBaseUICanvas
{
public:

    PMUICanvasAudioAnalyzer(string title, int headerFontSize, unsigned int audioInputIndex);

    virtual void init(int posX, int posY, bool autosize = true, int width = 0, int height = 0);
    virtual void clear();

    virtual void handleEvents(ofxUIEventArgs &e);

protected:
    
    void            loadPreset(int presetNumber = 0);
    void            savePreset(int presetNumber = 0);

private:

    unsigned int audioInputIndex;

    vector<PMDeviceAudioAnalyzer *> *audioAnalyzers;

    // Matrix --------------------------------
    
    ofxUIToggleMatrix       *presetsMatrix;
    int                     getActivePreset();
    bool                    savingPreset;

    // Pitch ------------------------------------

    void pitchChanged(pitchParams &pitchParams);

    ofxUISlider         *pitchSlider;
    float               pitchMinMidiNote, pitchMaxMidiNote;
    float pitchCurrentMidiNote;

    // Energy -----------------------------------

    void energyChanged(energyParams &energyParams);

    ofxUISlider         *energyGainSlider;
    float               energyGainCurrent;
    ofxUISlider         *energySilder;
    float               energyCurrent;

    // Silence ----------------------------------

    void silenceStateChanged(silenceParams &silenceParams);

    ofxUILabelToggle    *silenceToggle;
    bool                silenceOn;
    float               silenceThreshold;
    float               silenceQueueLength;
    
    // Pause ------------------------------------

    void pauseStateChanged(pauseParams &pauseParams);

    ofxUILabelToggle    *pauseToggle;
    bool                pauseOn;
    float               pauseQueueLength;

    // Onset ------------------------------------

    void onsetStateChanged(onsetParams &onsetParams);

    ofxUILabelToggle    *onsetToggle;
    bool                onsetOn;

    // Sht ------------------------------------
    
    void shtStateChanged(shtParams &_shtParams);
    
    ofxUILabelToggle    *shtToggle;
    bool                shtOn;
    
    void            keyPressed(int key);
    void            keyReleased(int key);

    // Settings

    //PMSettingsManagerAudioAnalyzers *settings;
};


#endif //PMCONCERTPARAULES_PMUICANVASAUDIOANALYZER_H
