//
// Created by Miquel Àngel Soler on 28/10/15.
//

#pragma once

#ifndef PMCONCERTPARAULES_PMSETTINGSDEVICE_H
#define PMCONCERTPARAULES_PMSETTINGSDEVICE_H

#include <stdio.h>
#include "PMSettingsDeviceChannel.h"

class PMSettingsDevice
{
public:
    string name;
    int ID;
    bool enabled;
    vector<PMSettingsDeviceChannel> channels;
};


#endif //PMCONCERTPARAULES_PMSETTINGSDEVICE_H
