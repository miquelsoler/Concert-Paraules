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
    guiX = 20;
    guiY = 50;
    guiPanelWidth = 300;

    float panelOriginX = guiX;
    float panelMarginX = 20;

    // GUI settings

    ofxUIColor bgColor = ofColor::darkGreen;

    // GUI
    {
        int panelNumber = 0;
        panelOriginX += (guiPanelWidth * panelNumber) + panelMarginX;

//        soundStream.printDeviceList();

        // Poem selector
        this->setupGUIPoem(panelOriginX, bgColor);

        // Audio settings
        panelNumber++;
        panelOriginX += (guiPanelWidth * panelNumber) + panelMarginX;
        this->setupGUIAudioSettings(panelOriginX, bgColor);
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
void PMScene1::setupGUIPoem(float originX, ofxUIColor bgColor)
{
    guiPoemSelector = new ofxUISuperCanvas("POEM", originX, guiY, guiPanelWidth, ofGetHeight());
    guiPoemSelector->setColorBack(bgColor);
    guiPoemSelector->addSpacer();
    guiPoemSelector->autoSizeToFitWidgets();
}

///--------------------------------------------------------------
void PMScene1::setupGUIAudioSettings(float originX, ofxUIColor bgColor)
{
    guiAudioSettings = new ofxUISuperCanvas("AUDIO SETTINGS", originX, guiY, guiPanelWidth, ofGetHeight());
    guiAudioSettings->setColorBack(bgColor);
    guiAudioSettings->addSpacer();

    guiAudioSettings->autoSizeToFitWidgets();
}
