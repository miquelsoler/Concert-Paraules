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
        // Load sound devices and erase those with no input channels

        soundDevices = PMAudioAnalyzer::getDevices();
        vector<int> devicesWithNoInputChannels;
        for (int i=0; i<soundDevices.size(); i++)
        {
            if (soundDevices[i].inputChannels == 0)
                devicesWithNoInputChannels.push_back(i);
        }
        for (int i=devicesWithNoInputChannels.size()-1; i>=0; i--)
        {
            soundDevices.erase(soundDevices.begin() + devicesWithNoInputChannels[i]);
        }

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

    // Device
    {
        int maxChannelCols = 16;

        int numDevices = soundDevices.size();

        vector<string> soundDevicesList;
        for (int i=0; i<numDevices; i++)
            soundDevicesList.push_back(buildStringForSoundDevice(&soundDevices[i]));

        int numRows, numCols;
        int numChannels;

        for (int i=0; i<numDevices; i++)
        {
            guiAudioSettings->addSpacer();
            ofxUIToggle* deviceToggle = guiAudioSettings->addToggle(soundDevicesList[i], selectedSoundDevices[i]);
            deviceToggle->setID(i);
            deviceToggle->getLabelWidget()->setColorFill(deviceLabelColor);

            // Channel matrix

            guiAudioSettings->addLabel("Input channels:",OFX_UI_FONT_SMALL)->setColorFill(channelsLabelColor);

            int numChannels = soundDevices[i].inputChannels;
            if (numChannels <= maxChannelCols) {
                numRows = 1;
                numCols = numChannels;
            } else {
                numRows = numChannels / maxChannelCols;
                numCols = maxChannelCols;
            }

            ofxUIToggleMatrix *channelMatrix = guiAudioSettings->addToggleMatrix(soundDevicesList[i], numRows, numCols, 20, 20);

            vector<ofxUIToggle *> toggles = channelMatrix->getToggles();
        }
    }

    guiAudioSettings->setPosition(originX, guiY);
    guiAudioSettings->autoSizeToFitWidgets();

    ofAddListener(guiAudioSettings->newGUIEvent, this, &PMScene1::handleEventInputDevices);

    return guiAudioSettings->getRect()->getWidth();
}

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


///--------------------------------------------------------------
string PMScene1::buildStringForSoundDevice(ofSoundDevice *soundDevice)
{
    string result = soundDevice->name + " (In:" + ofToString(soundDevice->inputChannels) + " Out:" + ofToString(soundDevice->outputChannels) + ")";
    return ofToUpper(result);
}
