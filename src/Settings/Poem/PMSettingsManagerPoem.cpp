//
// Created by Miquel Àngel Soler on 29/10/15.
//

#include "PMSettingsManagerPoem.h"

static const string FILENAME                = "settings/poem.json";
static const string FOLDER_PATH             = "poems";

static const string STR_POEM_FILE           = "Poem File";
static const string STR_POEM_VALID          = "Valid File";
static const string STR_POEM_FILE_DEFAULT   = "<None>";


PMSettingsManagerPoem::PMSettingsManagerPoem() : PMSettingsManager()
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

bool PMSettingsManagerPoem::load(string filename)
{
    if (!fileExists(FILENAME))
        createJSONSettings();

    bool result = PMSettingsManager::load(filename);
    return result;
}

void PMSettingsManagerPoem::createJSONSettings()
{
    json[STR_POEM_FILE] = STR_POEM_FILE_DEFAULT;
    json[STR_POEM_VALID] = false;
    json.save(FILENAME, true);
}

string PMSettingsManagerPoem::getPoemFilename()
{
    return json[STR_POEM_FILE].asString();
}

bool PMSettingsManagerPoem::getPoemValidity()
{
    return json[STR_POEM_VALID].asBool();
}

void PMSettingsManagerPoem::setPoem(string filePath)
{
    json[STR_POEM_FILE] = filePath;
    json[STR_POEM_VALID] = true;
    json.save(FILENAME, true);
}

string PMSettingsManagerPoem::getFolderPath()
{
    return FOLDER_PATH;
}
