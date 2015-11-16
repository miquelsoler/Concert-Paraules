//
// Created by Miquel Àngel Soler on 30/10/15.
//

#include "PMSettingsManagerRenderers.h"

static const string FILENAME = "settings/renderers.json";

static const string STR_RENDERERS           = "Renderers";
static const string STR_RENDERER_NAME       = "1. Name";
static const string STR_RENDERER_ID         = "2. Id";
static const string STR_RENDERER_ENABLED    = "3. Enabled";
static const string STR_RENDERER_SETTINGS   = "4. Settings";

static const string STR_RENDERER_PAINTBRUSH = "Paint Brush";
static const string STR_RENDERER_TYPOGRAPHY = "Typography";
static const string STR_RENDERER_COLORS     = "Colors";

typedef enum
{
    PMSRENDERER_PAINTBRUSH = 0,
    PMSRENDERER_TYPOGRAPHY = 1,
    PMSRENDERER_COLORS = 2
} PMS_RendererMode;


PMSettingsManagerRenderers::PMSettingsManagerRenderers() : PMSettingsManager()
{
    filename = FILENAME;

    bool parserResult = load(filename);
    if (!parserResult)
    {
        string msg = "BAD FORMAT IN " + FILENAME + ". Now quitting...";
        ofLog(OF_LOG_ERROR, msg);
        std::exit(EXIT_FAILURE);
    }
}

bool PMSettingsManagerRenderers::load(string filename)
{
    if (!fileExists(FILENAME))
        createJSONSettings();

    bool result = PMSettingsManager::load(filename);
    if (result) buildRenderersVectorFromJSON();

    return result;
}

void PMSettingsManagerRenderers::createJSONSettings()
{
    json[STR_RENDERERS] = Json::arrayValue;

    {
        Json::Value jsonRenderer;
        jsonRenderer.clear();
        jsonRenderer[STR_RENDERER_NAME] = STR_RENDERER_PAINTBRUSH;
        jsonRenderer[STR_RENDERER_ID] = PMSRENDERER_PAINTBRUSH;
        jsonRenderer[STR_RENDERER_ENABLED] = true;
        jsonRenderer[STR_RENDERER_SETTINGS] = Json::arrayValue;
        json[STR_RENDERERS].append(jsonRenderer);
    }

    {
        Json::Value jsonRenderer;
        jsonRenderer[STR_RENDERER_NAME] = STR_RENDERER_TYPOGRAPHY;
        jsonRenderer[STR_RENDERER_ID] = PMSRENDERER_TYPOGRAPHY;
        jsonRenderer[STR_RENDERER_ENABLED] = false;
        jsonRenderer[STR_RENDERER_SETTINGS] = Json::arrayValue;
        json[STR_RENDERERS].append(jsonRenderer);
    }

    {
        Json::Value jsonRenderer;
        jsonRenderer[STR_RENDERER_NAME] = STR_RENDERER_COLORS;
        jsonRenderer[STR_RENDERER_ID] = PMSRENDERER_COLORS;
        jsonRenderer[STR_RENDERER_ENABLED] = false;
        jsonRenderer[STR_RENDERER_SETTINGS] = Json::arrayValue;
        json[STR_RENDERERS].append(jsonRenderer);
    }

    write();
}

void PMSettingsManagerRenderers::buildRenderersVectorFromJSON()
{
    renderersSettings.clear();

    for (int i=0; i<json[STR_RENDERERS].size(); ++i)
    {
        Json::Value jsonRenderer = json[STR_RENDERERS][i];

        PMSettingsRenderer renderer;
        renderer.ID = jsonRenderer[STR_RENDERER_ID].asInt();
        renderer.name = jsonRenderer[STR_RENDERER_NAME].asString();
        renderer.enabled = jsonRenderer[STR_RENDERER_ENABLED].asBool();

        switch(jsonRenderer[STR_RENDERER_ID].asInt())
        {
            case PMSRENDERER_PAINTBRUSH:
            {
                PMSettingsRendererPaintbrush rendererPaintbrush;
                rendererPaintbrush.size = 10;
                renderer.specificSettings = rendererPaintbrush;
                break;
            }
            case PMSRENDERER_TYPOGRAPHY:
            {
                PMSettingsRendererTypography rendererTypography;
                renderer.specificSettings = rendererTypography;
                break;
            }
            case PMSRENDERER_COLORS:
            {
                PMSettingsRendererColors rendererColors;
                renderer.specificSettings = rendererColors;
                break;
            }
            default: break;
        }

        renderersSettings.push_back(renderer);
    }
}

vector<PMSettingsRenderer> *PMSettingsManagerRenderers::getRenderers()
{
    return &renderersSettings;
}

PMSettingsRenderer PMSettingsManagerRenderers::getSelectedRenderer()
{
    buildRenderersVectorFromJSON();

    bool found = false;
    int index = 0;

    for (int i=0; i<renderersSettings.size() && !found; ++i)
    {
        found = renderersSettings[i].enabled;
        if (found) index = i;
    }

    if (found) return renderersSettings[index];
    else return PMSettingsRenderer();
}

void PMSettingsManagerRenderers::enableRenderer(unsigned int rendererID)
{
    for (int i=0; i<json[STR_RENDERERS].size(); ++i)
    {
        bool enabled = (json[STR_RENDERERS][i][STR_RENDERER_ID].asInt() == rendererID);
        json[STR_RENDERERS][i][STR_RENDERER_ENABLED] = enabled;
    }
}
