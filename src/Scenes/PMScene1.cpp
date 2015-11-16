//
//  PMScene1.cpp
//  PMConcertParaules
//
//  Created by Miquel Àngel Soler on 7/10/15.
//
//

#include "PMScene1.hpp"

#pragma mark - UI building

static const string STR_CANVAS_BASEPATH = "settings/gui/";

PMScene1::PMScene1() : PMBaseScene("Scene 1")
{
    // Settings
    {
        backgroundColor = ofColor(230, 230, 230);
        canvasBgColor = ofColor(100, 100, 100, 255);
    }

    // GUI
    {
        // Poem selector
        guiPoemSelector = new PMUICanvasPoem("POEM", OFX_UI_FONT_MEDIUM);
        guiPoemSelector->init(5, 5, false, 500, 70);
        guiPoemSelector->setBackgroundColor(canvasBgColor);
        guiPoemSelector->setVisible(false);

        // Audio settings
        guiAudioSettings = new PMUICanvasAudioDevices("INPUT DEVICES", OFX_UI_FONT_MEDIUM);
        guiAudioSettings->init(5, 80);
        guiAudioSettings->setBackgroundColor(canvasBgColor);
        guiAudioSettings->setVisible(false);

        // Renderer settings
        guiRendererSettings = new PMUICanvasRenderers("RENDER MODE", OFX_UI_FONT_MEDIUM);
        guiRendererSettings->init(310, 80);
        guiRendererSettings->setBackgroundColor(canvasBgColor);
        guiRendererSettings->setVisible(false);
    }
}

PMScene1::~PMScene1()
{
    delete guiPoemSelector;
    delete guiAudioSettings;
    delete guiRendererSettings;
}

void PMScene1::setup()
{
}

void PMScene1::update()
{
}

void PMScene1::updateEnter()
{
//    cout << "PMScene1::updateEnter()" << endl;
    if (isEnteringFirst())
    {
        guiPoemSelector->loadSettings(STR_CANVAS_BASEPATH + "poem1.xml");
        guiAudioSettings->loadSettings(STR_CANVAS_BASEPATH + "audioDevices1.xml");
        guiRendererSettings->loadSettings(STR_CANVAS_BASEPATH + "renderers1.xml");

        guiPoemSelector->setVisible(true);
        guiAudioSettings->setVisible(true);
        guiRendererSettings->setVisible(true);
    }

    PMBaseScene::updateEnter();
}

void PMScene1::updateExit()
{
    saveSettings();
    PMBaseScene::updateExit();
}

void PMScene1::draw()
{
    ofClear(backgroundColor);
}

void PMScene1::saveSettings()
{
    guiPoemSelector->saveSettings(STR_CANVAS_BASEPATH + "poem1.xml");
    guiAudioSettings->saveSettings(STR_CANVAS_BASEPATH + "audioDevices1.xml");
    guiRendererSettings->saveSettings(STR_CANVAS_BASEPATH + "renderers1.xml");

    guiPoemSelector->setVisible(false);
    guiAudioSettings->setVisible(false);
    guiRendererSettings->setVisible(false);
}
