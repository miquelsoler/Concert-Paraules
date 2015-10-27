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
static const string     STR_MAIN_IGNORE     = "IGNORE & CONTINUE";

#pragma mark - UI building

///--------------------------------------------------------------
PMScene1::PMScene1()
{
    // Settings
    {
        // Load sound devices and erase those with no input channels

        soundDevices = PMAudioAnalyzer::getInputDevices();

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

        float panelOriginX, panelOriginY;
        float panelMarginX = 20;

        ofxUIColor bgColor = ofColor(50,70,20);
        
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
int PMScene1::setupGUIPoem(float originX, float originY)
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
int PMScene1::setupGUIAudioSettings(float originX, float originY)
{
    guiAudioSettings = new ofxUISuperCanvas("INPUT DEVICES", OFX_UI_FONT_LARGE);
    guiAudioSettings->setColorBack(canvasBgColor);
    guiAudioSettings->getCanvasTitle()->setColorFill(canvasTitleColor);

    // Add devices and per-device channels
    {
        unsigned long numDevices = soundDevices.size();

        for (int iDevice=0; iDevice<numDevices; ++iDevice)
            soundDevicesNames.push_back(buildStringForSoundDevice(&soundDevices[iDevice]));

        for (unsigned int iDevice=0; iDevice<numDevices; ++iDevice)
        {
            int numChannels = soundDevices[iDevice].inputChannels;
            if (numChannels <= 0) continue; // Skip devices without input channels

            bool isDeviceEnabled = addDevice(iDevice);
            if (isDeviceEnabled)
                addDeviceChannels(iDevice);
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
    guiMainButtons->addLabelButton(STR_MAIN_IGNORE, false);

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
    selectedSoundDevices[toggle->getID()] = toggle->getValue();
    cout << widgetName << "\t value: " << toggle->getValue() << "\t id: " << toggle->getID() << endl;
}

void PMScene1::handleEventMainButtons(ofxUIEventArgs &e)
{
    string widgetName = e.widget->getName();

    if (e.getKind() != OFX_UI_WIDGET_LABELBUTTON) return;

    ofxUILabelButton *button = (ofxUILabelButton *)e.widget;
    if (!button->getValue()) return; // Ignore releases

    if (widgetName == STR_MAIN_SAVE)
    {
        cout << "Save" << endl;
        PMSceneManager::getInstance().changeScene();
    }
    else if (widgetName == STR_MAIN_IGNORE)
    {
        cout << "Ignore" << endl;
        PMSceneManager::getInstance().changeScene();
    }
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
