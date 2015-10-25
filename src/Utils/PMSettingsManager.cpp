//
//  PMSettingsManager.cpp
//  ConductrEnter
//
//  Created by Miquel Ëngel Soler on 25/5/15.
//
//

#include "PMSettingsManager.h"
#include "ofUtils.h"

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

    // Debug mode
    {
        debugShowGUI = json[STR_DEBUG_MODE][STR_SHOW_GUI].asBool();
        debugShowFPS = json[STR_DEBUG_MODE][STR_SHOW_FPS].asBool();
    }

    // Release mode
    {
        releaseShowGUI = json[STR_RELEASE_MODE][STR_SHOW_GUI].asBool();
        releaseShowFPS = json[STR_RELEASE_MODE][STR_SHOW_FPS].asBool();
    }

    // App Settings
    {
        deviceSettings.clear();

        // Traverse devices and fill the deviceSettings map

        Json::Value devices = json[STR_APP_SETTINGS][STR_AS_DEVICES];
        for (int iDevice=0; iDevice<devices.size(); ++iDevice)
        {
            Json::Value device = devices[iDevice];
            int deviceID = devices[iDevice][STR_AS_CHANNEL_ID].asInt();

            // For each device, traverse channels
            vector<int> deviceChannelsIDs;
            Json::Value channels = devices[iDevice][STR_AS_CHANNELS];
            for (int iChannel=0; iChannel<channels.size(); ++iChannel)
                deviceChannelsIDs.push_back(channels[iChannel][STR_AS_CHANNEL_ID].asInt());

            deviceSettings[deviceID] = deviceChannelsIDs;
        }

    }

    return parsingSuccessful;
}

///--------------------------------------------------------------
void PMSettingsManager::writeToFile()
{
    // TO BE DONE (maybe move to ofxXmlSettings...)

    ofxJSONElement data;

    // Debug mode
    {
        data[STR_DEBUG_MODE][STR_SHOW_GUI] = debugShowGUI;
    }

    ofFile outputFile(ofToDataPath("json/country_data.json"), ofFile::WriteOnly);
    outputFile << data;
}
