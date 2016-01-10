//
// Created by Miquel Àngel Soler on 7/11/15.
//

#ifndef PMCONCERTPARAULES_PMUICANVASAUDIOANALYZER_H
#define PMCONCERTPARAULES_PMUICANVASAUDIOANALYZER_H

#include "PMBaseUICanvas.h"

#include "PMAudioInParams.h"
#include "PMAudioAnalyzer.hpp"

class PMUICanvasAudioAnalyzer : public PMBaseUICanvas
{
public:

    PMUICanvasAudioAnalyzer(string title, int headerFontSize, unsigned int audioInputIndex);

    virtual void init(int posX, int posY, bool autosize = true, int width = 0, int height = 0);
    virtual void clear();

    virtual void update();
    
    virtual void handleEvents(ofxUIEventArgs &e);
    virtual void windowResized(ofResizeEventArgs& data);
protected:
    
    void            loadPreset(int presetNumber = 0);
    void            savePreset(int presetNumber = 0);

private:

    unsigned int audioInputIndex;

    vector<PMDeviceAudioAnalyzer *> *audioAnalyzers;

    // Presets --------------------------------
    ofxUIToggleMatrix   *presetsMatrix;
    bool                savingPreset;
    int getActivePreset();

    // Pitch ------------------------------------
    float               pitchCurrentMidiNote;
    void pitchChanged(pitchParams &pitchParams);
    float               minPitch;
    float               maxPitch;
    float               deltaPitch;
    float               smoothedPitch;
    float               oldPitch;

    // Energy -----------------------------------
    float               energyGainCurrent;
    float               energyCurrent;
    float               minEnergy;
    float               maxEnergy;
    float               deltaEnergy;
    float               smoothedEnergy;
    float               oldEnergy;

    void energyChanged(energyParams &energyParams);

    // Silence ----------------------------------
    bool                silenceOn;
    float               silenceThreshold;
    float               silenceQueueLength;
    void silenceStateChanged(silenceParams &silenceParams);

    // Pause ------------------------------------
    bool                pauseOn;
    float               pauseQueueLength;
    void pauseStateChanged(pauseParams &pauseParams);

    // Onset ------------------------------------
    bool                onsetOn;
    float               onsetThreshold;
    void onsetStateChanged(onsetParams &onsetParams);

    // Sht ------------------------------------
    bool                shtOn;
    void shtStateChanged(shtParams &_shtParams);

    // Event handling ----------------------------
    void keyPressed(int key);
    void keyReleased(int key);

    void resetGUIPosition();
    
    void updateAudioParams();
};


#endif //PMCONCERTPARAULES_PMUICANVASAUDIOANALYZER_H
