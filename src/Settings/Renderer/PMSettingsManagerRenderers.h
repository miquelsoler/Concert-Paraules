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
    PMSRENDERER_PAINTBRUSH = 0,
    PMSRENDERER_TYPOGRAPHY = 1,
    PMSRENDERER_COLORS = 2,
    PMSRENDERER_RIBBON = 3,
    PMSRENDERER_CURVES = 4
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
