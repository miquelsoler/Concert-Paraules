//
// Created by Miquel Àngel Soler on 29/10/15.
//

#include "PMSettingsManagerGeneral.h"

static const string FILENAME            = "settings/general.json";

static const string STR_DEBUG_MODE      = "Debug Mode";
static const string STR_RELEASE_MODE    = "Release Mode";
static const string STR_SHOW_FPS        = "Show FPS";


PMSettingsManagerGeneral::PMSettingsManagerGeneral() : PMSettingsManager()
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

bool PMSettingsManagerGeneral::getDebugShowFPS()
{
    return json[STR_DEBUG_MODE][STR_SHOW_FPS].asBool();
}

bool PMSettingsManagerGeneral::getReleaseShowFPS()
{
    return json[STR_RELEASE_MODE][STR_SHOW_FPS].asBool();
}
