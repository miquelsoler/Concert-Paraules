//
//  PMScene1.cpp
//  PMConcertParaules
//
//  Created by Miquel Àngel Soler on 7/10/15.
//
//

#include "PMScene1.hpp"

///--------------------------------------------------------------
PMScene1::PMScene1() : PMBaseScene()
{
    // Settings
    {
        selectedSoundDevice = 0;
        selectedChannelMode = PMDAA_CHANNEL_MULTI;
        selectedChannel = 0;
    }

    // GUI
    {
        guiX = 20;
        guiY = 50;
        guiPanelWidth = 500;

        float panelOriginX;
        float panelMarginX = 20;

        ofxUIColor bgColor = ofColor(30);
        int lastWidth;

        // Poem selector
        panelOriginX = guiX;
        lastWidth = this->setupGUIPoem(panelOriginX, bgColor);

        // Audio settings
        panelOriginX += lastWidth + panelMarginX;
        lastWidth = this->setupGUIAudioSettings(panelOriginX, bgColor);
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

#ifdef OF_DEBUG
    baseFont.drawString("CONCERT DE LES PARAULES - Configuració", 15, 30);
#endif
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
float PMScene1::setupGUIPoem(float originX, ofxUIColor bgColor)
{
    guiPoemSelector = new ofxUISuperCanvas("POEM");
    guiPoemSelector->setColorBack(bgColor);
    guiPoemSelector->addSpacer();

    guiPoemSelector->setPosition(originX, guiY);
    guiPoemSelector->autoSizeToFitWidgets();

    return guiPoemSelector->getRect()->getWidth();
}

///--------------------------------------------------------------
float PMScene1::setupGUIAudioSettings(float originX, ofxUIColor bgColor)
{
    soundDevices = PMDeviceAudioAnalyzer::getInstance().getDevices();

    guiAudioSettings = new ofxUISuperCanvas("AUDIO SETTINGS", OFX_UI_FONT_LARGE);

    guiAudioSettings->setColorBack(bgColor);
    guiAudioSettings->addSpacer();

    // Device
    {
        guiAudioSettings->addLabel("> DEVICE");

        vector<string> soundDevicesList;
        for (int i=0; i<soundDevices.size(); i++)
            soundDevicesList.push_back(buildStringForSoundDevice(&soundDevices[i]));

        ofxUIRadio *radioButtons = guiAudioSettings->addRadio("Sound Devices", soundDevicesList);
        radioButtons->activateToggle(buildStringForSoundDevice(&soundDevices[selectedSoundDevice]));
    }

    // Channel mode
    {
        guiAudioSettings->addSpacer();
        guiAudioSettings->addLabel("> CHANNEL MODE");

        vector<string> channelModesList;
        channelModesList.push_back("Multi");
        channelModesList.push_back("Mono");
        ofxUIRadio *radioButtons = guiAudioSettings->addRadio("Channel Mode", channelModesList);
        radioButtons->activateToggle(channelModesList[selectedChannelMode]);
    }

    guiAudioSettings->setPosition(originX, guiY);
    guiAudioSettings->autoSizeToFitWidgets();

    return guiAudioSettings->getRect()->getWidth();
}

///--------------------------------------------------------------
string PMScene1::buildStringForSoundDevice(ofSoundDevice *soundDevice)
{
    string result = soundDevice->name + " (In:" + ofToString(soundDevice->inputChannels) + " Out:" + ofToString(soundDevice->outputChannels) + ")";
    return result;
}
