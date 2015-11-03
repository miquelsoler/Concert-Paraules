//
//  PMScene1.cpp
//  PMConcertParaules
//
//  Created by Miquel Àngel Soler on 7/10/15.
//
//

#include "PMScene1.hpp"
#include "PMSceneManager.hpp"

static const string     STR_MAINBUTTONS_SAVE    = "CONTINUE";


#pragma mark - UI building

PMScene1::PMScene1()
{
    // Settings
    {
        backgroundColor = ofColor(64, 73, 47);
        canvasBgColor = ofColor(0, 0, 0, 50);
    }

    // GUI
    {
        int panelPosX = panelMargin;
        int panelPosY = panelMargin;

        int lastWidth;

        // Poem selector
        guiPoemSelector = new PMUICanvasPoem("POEM", OFX_UI_FONT_LARGE);
        guiPoemSelector->init(panelPosX, panelPosY, false, 500, 70);
        guiPoemSelector->setVisible(false);

        // Audio settings
        panelPosY += guiPoemSelector->getHeight() + panelMargin;
        guiAudioSettings = new PMUICanvasAudioDevices("INPUT DEVICES", OFX_UI_FONT_LARGE);
        guiAudioSettings->init(panelPosX, panelPosY);
        guiAudioSettings->setVisible(false);
        lastWidth = int(guiAudioSettings->getWidth());

        // Renderer settings
        panelPosX += lastWidth + panelMargin;
        guiRendererSettings = new PMUICanvasRenderers("RENDER MODE", OFX_UI_FONT_LARGE);
        guiRendererSettings->init(panelPosX, panelPosY);
        guiRendererSettings->setVisible(false);

        // Continue buttons
        this->setupGUIMainButtons();
    }
}

PMScene1::~PMScene1()
{
    delete guiPoemSelector;
    delete guiAudioSettings;
    delete guiRendererSettings;
    delete guiMainButtons;
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
    guiPoemSelector->setVisible(true);
    guiAudioSettings->setVisible(true);
    guiRendererSettings->setVisible(true);
    guiMainButtons->setVisible(true);
}

void PMScene1::willExit()
{
    exit();
}

void PMScene1::exit()
{
    guiPoemSelector->setVisible(false);
    guiAudioSettings->setVisible(false);
    guiRendererSettings->setVisible(false);
    guiMainButtons->setVisible(false);
}

#pragma mark - Panels

void PMScene1::setupGUIMainButtons()
{
    guiMainButtons = new ofxUICanvas();
    guiMainButtons->setColorBack(canvasBgColor);

    guiMainButtons->addLabelButton(STR_MAINBUTTONS_SAVE, false);

    guiMainButtons->autoSizeToFitWidgets();

    ofxUIRectangle *widgetRect = guiMainButtons->getRect();

    guiMainButtons->setPosition(int(ofGetWidth() - widgetRect->getWidth() - panelMargin),
                                int(ofGetHeight() - widgetRect->getHeight() - panelMargin));

    ofAddListener(guiMainButtons->newGUIEvent, this, &PMScene1::handleEventMainButtons);
}

#pragma mark - Event management

void PMScene1::handleEventMainButtons(ofxUIEventArgs &e)
{
    if (e.getKind() != OFX_UI_WIDGET_LABELBUTTON) return;

    ofxUILabelButton *button = (ofxUILabelButton *)e.widget;
    if (!button->getValue()) return; // Ignore releases

    PMSceneManager::getInstance().changeScene();
}
