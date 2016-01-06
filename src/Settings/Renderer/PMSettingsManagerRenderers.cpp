//
// Created by Miquel Àngel Soler on 30/10/15.
//

//#include <xpc/xpc.h>
#include "PMSettingsManagerRenderers.h"

static const string FILENAME = "settings/renderers.json";

static const string STR_RENDERERS           = "Renderers";
static const string STR_RENDERER_NAME       = "1. Name";
static const string STR_RENDERER_ID         = "2. Id";
static const string STR_RENDERER_ENABLED    = "3. Enabled";

static const string STR_RENDERER_PAINTBRUSH = "Paint Brush";
static const string STR_RENDERER_TYPOGRAPHY = "Typography";
static const string STR_RENDERER_COLORS     = "Colors";
static const string STR_RENDERER_RIBBON     = "Ribbon";
static const string STR_RENDERER_CURVES     = "Curves";


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

    Json::Value jsonPaintbrush = buildRenderer(STR_RENDERER_PAINTBRUSH, PMSRENDERER_PAINTBRUSH);
    json[STR_RENDERERS].append(jsonPaintbrush);

    Json::Value jsonTypo = buildRenderer(STR_RENDERER_TYPOGRAPHY, PMSRENDERER_TYPOGRAPHY);
    json[STR_RENDERERS].append(jsonTypo);

    Json::Value jsonColors = buildRenderer(STR_RENDERER_COLORS, PMSRENDERER_COLORS);
    json[STR_RENDERERS].append(jsonColors);

    Json::Value jsonRibbon = buildRenderer(STR_RENDERER_RIBBON, PMSRENDERER_RIBBON);
    json[STR_RENDERERS].append(jsonRibbon);

    Json::Value jsonCurves = buildRenderer(STR_RENDERER_CURVES, PMSRENDERER_CURVES);
    json[STR_RENDERERS].append(jsonCurves);

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

Json::Value PMSettingsManagerRenderers::buildRenderer(string name, PMS_RendererMode id)
{
    Json::Value jsonRenderer;
    jsonRenderer[STR_RENDERER_NAME] = name;
    jsonRenderer[STR_RENDERER_ID] = id;
    jsonRenderer[STR_RENDERER_ENABLED] = false;
    return jsonRenderer;
}
