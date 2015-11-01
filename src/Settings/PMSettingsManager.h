//
//  PMSettingsManager.h
//  ConductrEnter
//
//  Created by Miquel �ngel Soler on 25/5/15.
//
//

#pragma once

#ifndef __ConductrEnter__SettingsManager__
#define __ConductrEnter__SettingsManager__

#include <stdio.h>
#include "ofxJSON.h"


class PMSettingsManager
{
public:
    virtual void write();

protected:

    PMSettingsManager() {};
    virtual bool load(string filename);
    virtual void createJSONSettings() = 0;

    bool fileExists(string filename);

    ofxJSONElement  json;
    string          filename;
};

#endif /* defined(__ConductrEnter__SettingsManager__) */
