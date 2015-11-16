//
// Created by Miquel Àngel Soler on 30/10/15.
//

#pragma once

#ifndef PMCONCERTPARAULES_PMSETTINGSMANAGERRENDERERS_H
#define PMCONCERTPARAULES_PMSETTINGSMANAGERRENDERERS_H

#include "PMSettingsManager.h"
#include "PMSettingsRenderer.h"


class PMSettingsManagerRenderers : public PMSettingsManager
{
public:

    static PMSettingsManagerRenderers &getInstance()
    {
        static PMSettingsManagerRenderers instance;
        return instance;
    }

    PMSettingsManagerRenderers();
    virtual bool load(string filename);

    void createJSONSettings();

    vector<PMSettingsRenderer> *getRenderers();
    PMSettingsRenderer getSelectedRenderer();

    void enableRenderer(unsigned int rendererID);

private:

    void buildRenderersVectorFromJSON();
    vector<PMSettingsRenderer> renderersSettings;
};


#endif //PMCONCERTPARAULES_PMSETTINGSMANAGERRENDERERS_H
