//
//  PMScene1.cpp
//  PMConcertParaules
//
//  Created by Miquel Àngel Soler on 7/10/15.
//
//

#include "PMScene1.hpp"


#pragma mark - UI building

PMScene1::PMScene1()
{
    // Settings
    {
        backgroundColor = ofColor(230, 230, 230);
        canvasBgColor = ofColor(100, 100, 100, 255);
    }

    // GUI
    {
        int panelPosX = panelMargin;
        int panelPosY = panelMargin;

        int lastWidth;

        // Poem selector
        guiPoemSelector = new PMUICanvasPoem("POEM", OFX_UI_FONT_MEDIUM);
        guiPoemSelector->init(panelPosX, panelPosY, false, 500, 70);
        guiPoemSelector->setBackgroundColor(canvasBgColor);
        guiPoemSelector->setVisible(false);

        // Audio settings
        panelPosY += guiPoemSelector->getHeight() + panelMargin;
        guiAudioSettings = new PMUICanvasAudioDevices("INPUT DEVICES", OFX_UI_FONT_MEDIUM);
        guiAudioSettings->init(panelPosX, panelPosY);
        guiAudioSettings->setBackgroundColor(canvasBgColor);
        guiAudioSettings->setVisible(false);
        lastWidth = int(guiAudioSettings->getWidth());

        // Renderer settings
        panelPosX += lastWidth + panelMargin;
        guiRendererSettings = new PMUICanvasRenderers("RENDER MODE", OFX_UI_FONT_MEDIUM);
        guiRendererSettings->init(panelPosX, panelPosY);
        guiRendererSettings->setBackgroundColor(canvasBgColor);
        guiRendererSettings->setVisible(false);

        // Navigation
        guiNavigation = new PMUICanvasNavigation("NAVIGATION", OFX_UI_FONT_MEDIUM);
        guiNavigation->init(ofGetWidth() - 300, ofGetHeight() - 300);
        guiNavigation->setBackgroundColor(canvasBgColor);
        guiNavigation->setVisible(false);
    }
}

PMScene1::~PMScene1()
{
    delete guiPoemSelector;
    delete guiAudioSettings;
    delete guiRendererSettings;
    delete guiNavigation;
}

void PMScene1::setup()
{
}

void PMScene1::update()
{
}

void PMScene1::draw()
{
    PMBaseScene::draw();
}

void PMScene1::willDraw()
{
    guiPoemSelector->loadSettings("settings/gui/pome1.xml");
    guiAudioSettings->loadSettings("settings/gui/audioDevices1.xml");
    guiRendererSettings->loadSettings("settings/gui/renderers1.xml");
    guiNavigation->loadSettings("settings/gui/navigation1.xml");

    guiPoemSelector->setVisible(true);
    guiAudioSettings->setVisible(true);
    guiRendererSettings->setVisible(true);
    guiNavigation->setVisible(true);
}

void PMScene1::willExit()
{
    exit();
}

void PMScene1::exit()
{
    guiPoemSelector->saveSettings("settings/gui/pome1.xml");
    guiAudioSettings->saveSettings("settings/gui/audioDevices1.xml");
    guiRendererSettings->saveSettings("settings/gui/renderers1.xml");
    guiNavigation->saveSettings("settings/gui/navigation1.xml");

    guiPoemSelector->setVisible(false);
    guiAudioSettings->setVisible(false);
    guiRendererSettings->setVisible(false);
    guiNavigation->setVisible(false);
}
