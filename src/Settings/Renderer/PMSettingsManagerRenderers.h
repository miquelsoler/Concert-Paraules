//
// Created by Miquel Àngel Soler on 30/10/15.
//

#pragma once

#ifndef PMCONCERTPARAULES_PMSETTINGSMANAGERRENDERERS_H
#define PMCONCERTPARAULES_PMSETTINGSMANAGERRENDERERS_H

#include "PMSettingsManager.h"
#include "PMSettingsRenderer.h"

typedef enum
{
    PMSRENDERER_TYPOGRAPHY = 0,
    PMSRENDERER_COLORS = 1,
    PMSRENDERER_CURVES = 2
} PMS_RendererMode;



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
    Json::Value buildRenderer(string name, PMS_RendererMode id);

    vector<PMSettingsRenderer> renderersSettings;
};


#endif //PMCONCERTPARAULES_PMSETTINGSMANAGERRENDERERS_H
