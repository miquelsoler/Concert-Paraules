//
// Created by Miquel Àngel Soler on 30/10/15.
//

#include "PMUICanvasAudioDevices.h"

static const int MAX_CHANNELS_COLS = 8;


void PMUICanvasAudioDevices::init(int posX, int posY, bool autosize, int width, int height)
{
    PMBaseUICanvas::init(posX, posY, autosize, width, height);

    settings = &PMSettingsManagerAudioDevices::getInstance();

    // Add devices and per-device channels
    {
        vector<PMSettingsDevice> *devices = settings->getAudioDevices();

        for (int iDevice=0; iDevice < devices->size(); ++iDevice) {
            PMSettingsDevice device = (*devices)[iDevice];

            ofxUIToggle *deviceToggle = addToggle(device.name, device.enabled);
            deviceToggle->setID(device.ID);
            deviceToggle->getLabelWidget()->setColorFill(deviceLabelColor);

            int numChannels = int(device.channels.size());
            int numRows = 1;
            int numCols = numChannels;

            if (numChannels > MAX_CHANNELS_COLS) {
                numRows = int(ceilf(float(numChannels) / float(MAX_CHANNELS_COLS)));
                numCols = MAX_CHANNELS_COLS;
            }

            ofxUIToggleMatrix *channelMatrix = addToggleMatrix(device.name, numRows, numCols, 20, 20);
            channelMatrix->setID(device.ID);
            channelMatrix->setParent(deviceToggle);

            vector<ofxUIToggle *> channelToggles = channelMatrix->getToggles();
            for (int iChannel=0; iChannel < device.channels.size(); ++iChannel)
            {
                bool isChannelEnabled = device.channels[iChannel].enabled;
                ofxUIToggle *currentToggle = channelToggles[iChannel];
                currentToggle->setID(iChannel);
                currentToggle->setValue(isChannelEnabled);
            }

            if (iDevice != devices->size()-1)
                addSpacer();
        }
    }

    if (autosize) autoSizeToFitWidgets();

    ofAddListener(newGUIEvent, this, &PMUICanvasAudioDevices::handleEvents);
}

void PMUICanvasAudioDevices::handleEvents(ofxUIEventArgs &e)
{
    if (e.widget->getKind() != OFX_UI_WIDGET_TOGGLE) return;

    ofxUIToggle *toggle = (ofxUIToggle *)e.widget;

    bool toggleValue = toggle->getValue();

    unsigned int deviceID, channelID;
    if (toggle->getParent()->getKind() != OFX_UI_WIDGET_TOGGLEMATRIX)
    {
        // It's a device toggle

        if (!toggleValue) {
            // Device is disabled -> disable all of its channels
            disableAllChannelsForDevice(toggle);
        } else {
            // Device is enabled -> disable all the other devices and its channels
            disableAllDevicesExcept(toggle);
        }
    }
    else
    {
        // It's a channel toggle

        deviceID = (unsigned int)(toggle->getParent()->getID());
        channelID = (unsigned int)(toggle->getID());
        settings->enableAudioDeviceChannel(deviceID, channelID, toggleValue);

        if (toggleValue) {
            // If channel is enabled, enabled its device if it wasn't
            disableAllDevicesExcept((ofxUIToggle *)(toggle->getParent()->getParent()));
            settings->enableAudioDevice(deviceID, true);
        } else {
            // If channel is disabled and all of them are, disable its device
            disableDeviceIfNoChannels(toggle);
        }
    }

    settings->write();
}

void PMUICanvasAudioDevices::disableAllChannelsForDevice(ofxUIToggle *deviceToggle)
{
    vector<ofxUIWidget *> allWidgets = getWidgets();
    ofxUIWidget *channelToggles = NULL;
    bool found = false;
    for (int i=0; i<allWidgets.size() && !found; ++i)
    {
        found = (allWidgets[i]->getParent() == deviceToggle) && (allWidgets[i]->getKind() == OFX_UI_WIDGET_TOGGLEMATRIX);
        if (found)
            channelToggles = allWidgets[i];
    }
    if (found)
    {
        ofxUIToggleMatrix *toggleMatrix = dynamic_cast<ofxUIToggleMatrix *>(channelToggles);
        toggleMatrix->setAllToggles(false);

        int matrixSize = int(toggleMatrix->getToggles().size());
        for (unsigned int i=0; i<matrixSize; i++)
            settings->enableAudioDeviceChannel((unsigned int)(deviceToggle->getID()), i, false);
    }
}

void PMUICanvasAudioDevices::disableDeviceIfNoChannels(ofxUIToggle *channelToggle)
{
    ofxUIToggleMatrix *toggleMatrix = (ofxUIToggleMatrix *) (channelToggle->getParent());
    vector<ofxUIToggle *> allToggles = toggleMatrix->getToggles();

    bool allDisabled = true;
    for (int i = 0; i < allToggles.size() && allDisabled; ++i)
    {
        if (allToggles[i]->getValue())
            allDisabled = false;
    }

    if (allDisabled)
    {
        ofxUIToggle *deviceToggle = (ofxUIToggle *) (channelToggle->getParent()->getParent());
        deviceToggle->setValue(false);

        settings->enableAudioDevice((unsigned int)(deviceToggle->getID()), false);
    }
}

void PMUICanvasAudioDevices::disableAllDevicesExcept(ofxUIToggle *deviceToggle)
{
    vector<ofxUIWidget *> allWidgets = getWidgets();
    for (int i = 0; i < allWidgets.size(); ++i)
    {
        ofxUIWidget *widget = allWidgets[i];
        if (widget->getParent()->getKind() != OFX_UI_WIDGET_TOGGLEMATRIX) continue;

        ofxUIToggleMatrix *toggleMatrix = dynamic_cast<ofxUIToggleMatrix *>(widget->getParent());
        ofxUIToggle *currentDeviceToggle = dynamic_cast<ofxUIToggle *>(toggleMatrix->getParent());
        int currentDeviceId = currentDeviceToggle->getID();

        if (currentDeviceId != deviceToggle->getID())
        {
            // Disable current device
            currentDeviceToggle->setValue(false);
            settings->enableAudioDevice(currentDeviceId, false);

            // Disable all channels for the current device
            toggleMatrix->setAllToggles(false, false);
            vector <ofxUIToggle *> channelToggles = toggleMatrix->getToggles();
            for (int j=0; j<channelToggles.size(); ++j)
                settings->enableAudioDeviceChannel(currentDeviceId, channelToggles[j]->getID(), false);
        }
    }

    deviceToggle->setValue(true);
}
