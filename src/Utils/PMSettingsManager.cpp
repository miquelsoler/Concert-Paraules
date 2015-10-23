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

    string prefix, subprefix;

    // Debug Mode
    {
        prefix = "Debug Mode";
        debugShowGUI = json[prefix]["Show GUI"].asBool();
        debugShowFPS = json[prefix]["Show FPS"].asBool();
    }

    // Release mode
    {
        prefix = "Release Mode";
        releaseShowGUI = json[prefix]["Show GUI"].asBool();
        releaseShowFPS = json[prefix]["Show FPS"].asBool();
    }

    // App Settings
    {
        deviceSettings.clear();

        prefix = "App Settings";

        // Traverse devices
        Json::Value devices = json[prefix]["Devices"];
        for (int iDevice=0; iDevice<devices.size(); ++iDevice)
        {
            Json::Value device = devices[iDevice];
            int deviceID = devices[iDevice]["Id"].asInt();

            // For each device, traverse channels
            vector<int> deviceChannelsIDs;
            Json::Value channels = devices[iDevice]["Channels"];
            for (int iChannel=0; iChannel<channels.size(); ++iChannel)
                deviceChannelsIDs.push_back(channels[iChannel]["Id"].asInt());

            deviceSettings.push_back(pair<int, vector<int>>(deviceID, deviceChannelsIDs));
        }
    }

    return parsingSuccessful;
}

///--------------------------------------------------------------
void PMSettingsManager::writeToFile()
{
    // TO BE DONE (maybe move to ofxXmlSettings...)
}
