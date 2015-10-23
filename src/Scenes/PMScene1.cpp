//
//  PMScene1.cpp
//  PMConcertParaules
//
//  Created by Miquel Àngel Soler on 7/10/15.
//
//

#include "PMScene1.hpp"
#include "PMSettingsManager.h"

#pragma mark - UI building

///--------------------------------------------------------------
PMScene1::PMScene1() : PMBaseScene()
{
    // Settings
    {
        // Load sound devices and erase those with no input channels

        soundDevices = PMAudioAnalyzer::getDevices();

        selectedSoundDevices.push_back(0);
        selectedChannels.push_back(0);

        backgroundColor = ofColor(64, 73, 47);
        canvasBgColor = ofColor(0, 0, 0, 50);
        canvasTitleColor = ofColor(252, 239, 157);
        deviceLabelColor = ofColor(255, 255, 200);
        channelsLabelColor = ofColor(180, 180, 100);
    }

    // GUI
    {
        guiX = 20;
        guiY = 20;
        guiPanelWidth = 500;

        float panelOriginX;
        float panelMarginX = 20;

        ofxUIColor bgColor = ofColor(50,70,20);
        
        int lastWidth;

        // Poem selector
        panelOriginX = guiX;
        lastWidth = this->setupGUIPoem(panelOriginX);

        // Audio settings
        panelOriginX += lastWidth + panelMarginX;
        lastWidth = this->setupGUIAudioSettings(panelOriginX);
    }
}

///--------------------------------------------------------------
PMScene1::~PMScene1()
{
    delete guiPoemSelector;
    delete guiAudioSettings;
}

///--------------------------------------------------------------
void PMScene1::setup()
{
    cout << "S1 setup" << endl;
}

///--------------------------------------------------------------
void PMScene1::update()
{
}

///--------------------------------------------------------------
void PMScene1::draw()
{
//    cout << "SC1 draw" << endl;

    PMBaseScene::draw();
}

///--------------------------------------------------------------
void PMScene1::willDraw()
{
    guiPoemSelector->setVisible(true);
    guiAudioSettings->setVisible(true);
}

///--------------------------------------------------------------
void PMScene1::willExit()
{
    guiPoemSelector->setVisible(false);
    guiAudioSettings->setVisible(false);
}

///--------------------------------------------------------------
float PMScene1::setupGUIPoem(float originX)
{
    guiPoemSelector = new ofxUISuperCanvas("POEM", OFX_UI_FONT_LARGE);
    guiPoemSelector->setColorBack(canvasBgColor);
    guiPoemSelector->getCanvasTitle()->setColorFill(canvasTitleColor);
    guiPoemSelector->addSpacer();

    guiPoemSelector->setPosition(originX, guiY);
    guiPoemSelector->autoSizeToFitWidgets();
    
    return guiPoemSelector->getRect()->getWidth();
}

///--------------------------------------------------------------
float PMScene1::setupGUIAudioSettings(float originX)
{
    guiAudioSettings = new ofxUISuperCanvas("INPUT DEVICES", OFX_UI_FONT_LARGE);
    guiAudioSettings->setColorBack(canvasBgColor);
    guiAudioSettings->getCanvasTitle()->setColorFill(canvasTitleColor);

    // Add devices and per-device channels
    {
        int numChannels;
        int numDevices = soundDevices.size();

        for (int iDevice=0; iDevice<numDevices; ++iDevice)
            soundDevicesNames.push_back(buildStringForSoundDevice(&soundDevices[iDevice]));

        for (unsigned int iDevice=0; iDevice<numDevices; ++iDevice)
        {
            numChannels = soundDevices[iDevice].inputChannels;
            if (numChannels <= 0) continue; // Skip devices without input channels

            bool isDeviceEnabled = addDevice(iDevice);
            if (!isDeviceEnabled) continue;

            addDeviceChannels(iDevice);
        }
    }

    guiAudioSettings->setPosition(originX, guiY);
    guiAudioSettings->autoSizeToFitWidgets();

    ofAddListener(guiAudioSettings->newGUIEvent, this, &PMScene1::handleEventInputDevices);

    return guiAudioSettings->getRect()->getWidth();
}

#pragma mark - Event management

///--------------------------------------------------------------
void PMScene1::handleEventInputDevices(ofxUIEventArgs &e)
{
    string name = e.widget->getName();
    int kind = e.widget->getKind();

    if (kind != OFX_UI_WIDGET_TOGGLE) return;

    ofxUIToggle *toggle = (ofxUIToggle *)e.widget;
    selectedSoundDevices[toggle->getID()] = toggle->getValue();
    cout << name << "\t value: " << toggle->getValue() << "\t id: " << toggle->getID() << endl;
}

#pragma mark - Build scene 2 from settings

///--------------------------------------------------------------
void PMScene1::buildAudioAnalyzersFromSetup()
{
}

#pragma mark - Convenience methods

///--------------------------------------------------------------
bool PMScene1::addDevice(unsigned int deviceIndex)
{
    // Device list + enabling/disabling devices

    guiAudioSettings->addSpacer();

    ofxUIToggle* deviceToggle = guiAudioSettings->addToggle(soundDevicesNames[deviceIndex], selectedSoundDevices[deviceIndex]);
    deviceToggle->setID(deviceIndex);
    deviceToggle->getLabelWidget()->setColorFill(deviceLabelColor);

    bool isDeviceEnabled = PMSettingsManager::getInstance().deviceSettings.count(deviceIndex) == 1;
    deviceToggle->setValue(isDeviceEnabled);

    return isDeviceEnabled;
}

///--------------------------------------------------------------
void PMScene1::addDeviceChannels(unsigned int deviceIndex)
{
    guiAudioSettings->addLabel("Input channels:",OFX_UI_FONT_SMALL)->setColorFill(channelsLabelColor);

    int maxChannelCols = 16;
    int numChannels = soundDevices[deviceIndex].inputChannels;

    int numRows = 1;
    int numCols = numChannels;

    if (numChannels > maxChannelCols) {
        numRows = numChannels / maxChannelCols;
        numCols = maxChannelCols;
    }

    ofxUIToggleMatrix *channelMatrix = guiAudioSettings->addToggleMatrix(soundDevicesNames[deviceIndex], numRows, numCols, 20, 20);
    vector<ofxUIToggle *> channelToggles = channelMatrix->getToggles();

    for (int iToggle=0; iToggle<numChannels; ++iToggle)
    {
        vector<int> &enabledDeviceChannels = PMSettingsManager::getInstance().deviceSettings[deviceIndex];

        bool isChannelEnabled = std::find(enabledDeviceChannels.begin(), enabledDeviceChannels.end(), iToggle) != enabledDeviceChannels.end();

        // Widged channels now have and IDs with format [DxxC] where D is the device ID and xxC is the channel index
        // E.g.: ID 4058 matches device with ID 4 and channel number 58

        ofxUIToggle *currentTogle = channelToggles[iToggle];
        currentTogle->setID((deviceIndex * 1000) + iToggle);
        currentTogle->setValue(isChannelEnabled);
    }
}

///--------------------------------------------------------------
string PMScene1::buildStringForSoundDevice(ofSoundDevice *soundDevice)
{
    string result = "  <" + ofToString(soundDevice->deviceID) + "> " +
        ofToUpper(soundDevice->name) +
        " (in:" + ofToString(soundDevice->inputChannels) + " out:" + ofToString(soundDevice->outputChannels) + ")";
    return result;
}
