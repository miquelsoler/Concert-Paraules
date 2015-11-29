//
// Created by Miquel Àngel Soler on 30/10/15.
//

#ifndef PMCONCERTPARAULES_PMUICANVASAUDIODEVICES_H
#define PMCONCERTPARAULES_PMUICANVASAUDIODEVICES_H

#pragma once

#include "PMBaseUICanvas.h"

#include "PMSettingsManagerAudioDevices.h"


class PMUICanvasAudioDevices : public PMBaseUICanvas
{
public:

    PMUICanvasAudioDevices(string title, int headerFontSize) : PMBaseUICanvas(title, headerFontSize) {}

    virtual void init(int posX, int posY, bool autosize = true, int width = 0, int height = 0);

    virtual void handleEvents(ofxUIEventArgs &e);

private:

    void disableAllChannelsForDevice(ofxUIToggle *deviceToggle);
    void disableDeviceIfNoChannels(ofxUIToggle *channelToggle);
    void disableAllDevicesExcept(ofxUIToggle *deviceToggle);

    ofColor deviceLabelColor = ofColor(255, 255, 200);
    PMSettingsManagerAudioDevices *settings;
};


#endif //PMCONCERTPARAULES_PMUICANVASAUDIODEVICES_H
