//
// Created by Miquel Àngel Soler on 28/10/15.
//

#pragma once

#ifndef PMCONCERTPARAULES_PMSETTINGSDEVICE_H
#define PMCONCERTPARAULES_PMSETTINGSDEVICE_H

#include "PMSettingsDeviceChannel.h"

class PMSettingsDevice
{
public:
    unsigned int ID;
    string name;
    bool enabled;
    int inChannels;
    int outChannels;
    vector<PMSettingsDeviceChannel> channels;
};


#endif //PMCONCERTPARAULES_PMSETTINGSDEVICE_H
