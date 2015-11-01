//
// Created by Miquel Àngel Soler on 29/10/15.
//

#pragma once

#ifndef PMCONCERTPARAULES_PMSETTINGSMANAGERPOEM_H
#define PMCONCERTPARAULES_PMSETTINGSMANAGERPOEM_H

#include "PMSettingsManager.h"

class PMSettingsManagerPoem : public PMSettingsManager
{
public:

    static PMSettingsManagerPoem &getInstance()
    {
        static PMSettingsManagerPoem instance;
        return instance;
    }

    PMSettingsManagerPoem();
    virtual bool load(string filename);

    void createJSONSettings();

    string getPoemFilename();
    bool getPoemValidity();
    void setPoem(string filePath);

    string getFolderPath();
};

#endif //PMCONCERTPARAULES_PMSETTINGSMANAGERPOEM_H
