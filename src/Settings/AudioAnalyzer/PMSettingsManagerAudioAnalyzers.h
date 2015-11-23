//
// Created by Miquel Àngel Soler on 13/11/15.
//

#ifndef PMCONCERTPARAULES_PMSETTINGSMANAGERAUDIOANALYZER_H
#define PMCONCERTPARAULES_PMSETTINGSMANAGERAUDIOANALYZER_H

#include "PMSettingsManager.h"

class PMSettingsManagerAudioAnalyzers : public PMSettingsManager
{
public:

    static PMSettingsManagerAudioAnalyzers &getInstance()
    {
        static PMSettingsManagerAudioAnalyzers instance;
        return instance;
    }

    PMSettingsManagerAudioAnalyzers();
    void createJSONSettings() {};

    float getMinPitchMidiNote();
    float getMaxPitchMidiNote();
    void setMinPitchMidiNote(float midiNote);
    void setMaxPitchMidiNote(float midiNote);

    float getMinEnergy();
    float getMaxEnergy();
    void setMinEnergy(float minEnergy);
    void setMaxEnergy(float maxEnergy);

    bool getSilenceEnabled();
    float getSilenceThreshold();
    unsigned int getSilenceQueueLength();
    void setSilenceThreshold(float threshold);
    void setSilenceQueueLength(unsigned int length);

    bool getMelBandsEnabled();
    unsigned int getNumMelBands();
    void setNumMelBands(unsigned int numBands);

    float getOnsetsThreshold();
    float getOnsetsAlpha();
    void setOnsetsThreshold(float threshold);
    void setOnsetsAlpha(float alpha);

    float getSmoothingDelta();
    void setSmoothingDelta(float delta);
    
    int getAscDescAnalysisSize();
    void setAscDescAnalysisSize(int size);
};

#endif //PMCONCERTPARAULES_PMSETTINGSMANAGERAUDIOANALYZER_H
