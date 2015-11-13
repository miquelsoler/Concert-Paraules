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

    float getMinPitchFreq();
    float getMaxPitchFreq();
    float getMinEnergy();
    float getMaxEnergy();
    bool getSilenceEnabled();
    int getSilenceThreshold();
    unsigned int getSilenceQueueLength();
    bool getMelBandsEnabled();
    unsigned int getNumMelBands();
    float getSmoothingDelta();
};

#endif //PMCONCERTPARAULES_PMSETTINGSMANAGERAUDIOANALYZER_H
