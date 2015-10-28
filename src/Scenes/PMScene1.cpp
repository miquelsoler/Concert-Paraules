//
//  PMScene1.cpp
//  PMConcertParaules
//
//  Created by Miquel Àngel Soler on 7/10/15.
//
//

#include "PMScene1.hpp"
#include "PMSceneManager.hpp"
#include "PMSettingsManager.h"


static const string     STR_MAIN_SAVE       = "SAVE & CONTINUE";
static const int        MAX_CHANNELS_COLS   = 16;

#pragma mark - UI building

///--------------------------------------------------------------
PMScene1::PMScene1()
{
    // Settings
    {
        backgroundColor = ofColor(64, 73, 47);

        canvasBgColor = ofColor(0, 0, 0, 50);
        canvasTitleColor = ofColor(252, 239, 157);
        deviceLabelColor = ofColor(255, 255, 200);
    }

    // GUI
    {
        guiX = 20;
        guiY = 20;

        int panelOriginX;
        int panelMarginX = 20;

        int lastWidth;

        // Poem selector
        panelOriginX = guiX;
        lastWidth = this->setupGUIPoem(panelOriginX, guiY);

        // Audio settings
        panelOriginX += lastWidth + panelMarginX;
        lastWidth = this->setupGUIAudioSettings(panelOriginX, guiY);

        // Continue buttons
        this->setupGUIMainButtons();
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
    guiMainButtons->setVisible(false);
}

#pragma mark - Panels

///--------------------------------------------------------------
int PMScene1::setupGUIPoem(int originX, int originY)
{
    guiPoemSelector = new ofxUISuperCanvas("POEM", OFX_UI_FONT_LARGE);
    guiPoemSelector->setColorBack(canvasBgColor);
    guiPoemSelector->getCanvasTitle()->setColorFill(canvasTitleColor);
    guiPoemSelector->addSpacer();

    guiPoemSelector->setPosition(originX, originY);
    guiPoemSelector->autoSizeToFitWidgets();
    
    return int(guiPoemSelector->getRect()->getWidth());
}

///--------------------------------------------------------------
int PMScene1::setupGUIAudioSettings(int originX, int originY)
{
    guiAudioSettings = new ofxUISuperCanvas("INPUT DEVICES", OFX_UI_FONT_LARGE);
    guiAudioSettings->setColorBack(canvasBgColor);
    guiAudioSettings->getCanvasTitle()->setColorFill(canvasTitleColor);

    // Add devices and per-device channels
    {
        vector<PMSettingsDevice> *devices = PMSettingsManager::getInstance().getAudioDevices();

        for (int iDevice=0; iDevice < devices->size(); ++iDevice) {
            PMSettingsDevice device = (*devices)[iDevice];

            guiAudioSettings->addSpacer();
            ofxUIToggle *deviceToggle = guiAudioSettings->addToggle(device.name, device.enabled);
            deviceToggle->setID(device.ID);
            deviceToggle->getLabelWidget()->setColorFill(deviceLabelColor);

            int numChannels = int(device.channels.size());
            int numRows = 1;
            int numCols = numChannels;

            if (numChannels > MAX_CHANNELS_COLS) {
                numRows = numChannels / MAX_CHANNELS_COLS;
                numCols = MAX_CHANNELS_COLS;
            }

            ofxUIToggleMatrix *channelMatrix = guiAudioSettings->addToggleMatrix(device.name, numRows, numCols, 20, 20);
            channelMatrix->setID(device.ID);

            vector<ofxUIToggle *> channelToggles = channelMatrix->getToggles();
            for (int iChannel=0; iChannel < device.channels.size(); ++iChannel)
            {
                PMSettingsDeviceChannel channel = device.channels[iChannel];
                bool isChannelEnabled = device.channels[iChannel].enabled;

                ofxUIToggle *currentToggle = channelToggles[iChannel];
                currentToggle->setID(iChannel);
                currentToggle->setValue(isChannelEnabled);
            }
        }
    }

    guiAudioSettings->setPosition(originX, originY);
    guiAudioSettings->autoSizeToFitWidgets();

    ofAddListener(guiAudioSettings->newGUIEvent, this, &PMScene1::handleEventInputDevices);

    return int(guiAudioSettings->getRect()->getWidth());
}

///--------------------------------------------------------------
void PMScene1::setupGUIMainButtons()
{
    guiMainButtons = new ofxUISuperCanvas("GO TO MAIN SCENE");
    guiMainButtons->setColorBack(canvasBgColor);
    guiMainButtons->getCanvasTitle()->setColorFill(canvasTitleColor);

    guiMainButtons->addLabelButton(STR_MAIN_SAVE, false);

    guiMainButtons->autoSizeToFitWidgets();

    ofxUIRectangle *widgetRect = guiMainButtons->getRect();

    float marginSize = 20;
    guiMainButtons->setPosition(int(ofGetWidth() - widgetRect->getWidth() - marginSize),
                                int(ofGetHeight() - widgetRect->getHeight() - marginSize));

    ofAddListener(guiMainButtons->newGUIEvent, this, &PMScene1::handleEventMainButtons);
}

#pragma mark - Event management

///--------------------------------------------------------------
void PMScene1::handleEventInputDevices(ofxUIEventArgs &e)
{
    string widgetName = e.widget->getName();

    if (e.widget->getKind() != OFX_UI_WIDGET_TOGGLE) return;

    ofxUIToggle *toggle = (ofxUIToggle *)e.widget;
    bool isEnabled = toggle->getValue();

    unsigned int deviceID, channelID;

    if (toggle->getParent()->getKind() != OFX_UI_WIDGET_TOGGLEMATRIX)
    {
        // It's a device toggle

        deviceID = (unsigned int)(toggle->getID());
        PMSettingsManager::getInstance().enableAudioDevice(deviceID, toggle->getValue());
    }
    else
    {
        // It's a channel toggle

        deviceID = (unsigned int)(toggle->getParent()->getID());
        channelID = (unsigned int)(toggle->getID());
        PMSettingsManager::getInstance().enableAudioDeviceChannel(deviceID, channelID, toggle->getValue());
    }

#ifdef OF_DEBUG
    cout << widgetName << "\t value: " << toggle->getValue() << "\t id: " << toggle->getID() << endl;
#endif
}

void PMScene1::handleEventMainButtons(ofxUIEventArgs &e)
{
    if (e.getKind() != OFX_UI_WIDGET_LABELBUTTON) return;

    ofxUILabelButton *button = (ofxUILabelButton *)e.widget;
    if (!button->getValue()) return; // Ignore releases

    PMSettingsManager::getInstance().writeAudioDevicesSettings();
    PMSceneManager::getInstance().changeScene();
}
