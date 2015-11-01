//
//  PMSettingsManager.cpp
//  ConductrEnter
//
//  Created by Miquel Angel Soler on 25/5/15.
//
//

#include "PMSettingsManager.h"

#pragma mark - Internal setup

bool PMSettingsManager::load(string filename)
{
    return json.open(filename);
}

void PMSettingsManager::write()
{
    json.save(filename, true);
}

#pragma mark - Convenience methods

bool PMSettingsManager::fileExists(string filename)
{
    ofFile file(filename);
    bool fileExists = file.exists();
    file.close();

    return fileExists;
}
