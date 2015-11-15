//
// Created by Miquel Àngel Soler on 29/10/15.
//

#pragma once

#ifndef PMCONCERTPARAULES_PMSETTINGSMANAGERAUDIODEVICES_H
#define PMCONCERTPARAULES_PMSETTINGSMANAGERAUDIODEVICES_H

#include "PMSettingsManager.h"
#include "PMSettingsDevice.h"
#include "PMSettingsDeviceChannel.h"


class PMSettingsManagerAudioDevices : public PMSettingsManager
{
public:

    static PMSettingsManagerAudioDevices &getInstance()
    {
        static PMSettingsManagerAudioDevices instance;
        return instance;
    }

    PMSettingsManagerAudioDevices();
    virtual bool load(string filename);

    void createJSONSettings();

    vector<PMSettingsDevice> *getAudioDevices();
    vector<PMSettingsDevice> *getEnabledAudioDevices();
    void enableAudioDevice(unsigned int deviceID, bool enable);
    void enableAudioDeviceChannel(unsigned int deviceID, unsigned int channelID, bool enable);

private:

    bool JSONmatchesCurrentAudioDevices();

    void buildAllAudioDevicesVectorFromJSON();
    void buildEnabledAudioDevicesVectorFromJSON();

    unsigned int getNumEnabledChannelsForDevice(PMSettingsDevice *device);

    vector<PMSettingsDevice> devicesSettings;
    vector<PMSettingsDevice> enabledDevices;
};


#endif //PMCONCERTPARAULES_PMSETTINGSMANAGERAUDIODEVICES_H
