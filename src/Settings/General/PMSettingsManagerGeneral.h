//
// Created by Miquel Àngel Soler on 29/10/15.
//

#pragma once

#ifndef PMCONCERTPARAULES_PMSETTINGSMANAGERGENERAL_H
#define PMCONCERTPARAULES_PMSETTINGSMANAGERGENERAL_H

#include "PMSettingsManager.h"

class PMSettingsManagerGeneral : public PMSettingsManager
{
public:

    static PMSettingsManagerGeneral &getInstance()
    {
        static PMSettingsManagerGeneral instance;
        return instance;
    }

    PMSettingsManagerGeneral();
    void createJSONSettings() {};

    bool getDebugShowFPS();
    bool getDebugShowGUIScene2();
    bool getReleaseShowFPS();
    bool getReleaseShowGUIScene2();
};

#endif //PMCONCERTPARAULES_PMSETTINGSMANAGERGENERAL_H
