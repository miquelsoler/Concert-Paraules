//
//  PMSettingsManager.cpp
//  ConductrEnter
//
//  Created by Miquel Ëngel Soler on 25/5/15.
//
//

#include "PMSettingsManager.h"

const std::string FILENAME = "settings/settings.json";

///--------------------------------------------------------------
PMSettingsManager::PMSettingsManager()
{
    bool parserResult = loadSettings();
    if (!parserResult)
    {
        ofLog(OF_LOG_ERROR, "BAD FORMAT IN settings.json. Now quitting...");
        std::exit(EXIT_FAILURE);
    }
}

///--------------------------------------------------------------
bool PMSettingsManager::loadSettings()
{
    // JSON parse

    bool parsingSuccessful = json.open(FILENAME);
#ifdef OF_DEBUG
    cout << "PARSING RESULT: " << parsingSuccessful << endl;
#endif

    string prefix;

    // Debug Mode
    prefix = "Debug Mode";
    debugShowGUI = json[prefix]["Show GUI"].asBool();
    debugShowFPS = json[prefix]["Show FPS"].asBool();

    // Release mode
    prefix = "Release Mode";
    releaseShowGUI = json[prefix]["Show GUI"].asBool();
    releaseShowFPS = json[prefix]["Show FPS"].asBool();

    return parsingSuccessful;
}
