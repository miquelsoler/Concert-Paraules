//
//  PMScene2.cpp
//  PMConcertParaules
//
//  Created by Miquel Àngel Soler on 7/10/15.
//
//

#include "PMScene2.hpp"
#include "PMSettingsManagerGeneral.h"

///--------------------------------------------------------------
PMScene2::PMScene2()
{
#ifdef OF_DEBUG
    showGUI= PMSettingsManagerGeneral::getInstance().getDebugShowGUIScene2();
#else
    showGUI = PMSettingsManagerGeneral::getInstance().getReleaseShowGUIScene2();
#endif

    backgroundColor = ofColor::white;
    canvasBgColor = ofColor(100, 100, 100, 200);

    guiRenderer = new PMUICanvasRenderers("RENDER MODE", OFX_UI_FONT_LARGE);
    guiRenderer->init(200, 200);
    guiRenderer->setBackgroundColor(canvasBgColor);
    guiRenderer->setVisible(false);

    guiNavigation = new PMUICanvasNavigation("NAVIGATION", OFX_UI_FONT_MEDIUM);
    guiNavigation->init(ofGetWidth() - 300, ofGetHeight() - 300);
    guiNavigation->setBackgroundColor(canvasBgColor);
    guiNavigation->setVisible(false);
}


PMScene2::~PMScene2()
{
    delete guiRenderer;
    delete guiNavigation;
}

void PMScene2::setup()
{
}

void PMScene2::update()
{

}

void PMScene2::draw()
{
    PMBaseScene::draw();

    ofSetColor(ofColor::red);
    ofDrawCircle(ofGetWidth()/2, ofGetHeight()/2, 300);
}

void PMScene2::willDraw()
{
    guiRenderer->loadSettings("settings/gui/renderers2.xml");
    guiNavigation->loadSettings("settings/gui/navigation2.xml");

    guiRenderer->setVisible(showGUI);
    guiNavigation->setVisible(showGUI);
}

void PMScene2::willExit()
{
    exit();
}

void PMScene2::exit()
{
    guiRenderer->saveSettings("settings/gui/renderers2.xml");
    guiNavigation->saveSettings("settings/gui/navigation2.xml");

    guiRenderer->setVisible(false);
    guiNavigation->setVisible(false);
}

void PMScene2::keyReleased(int key)
{
    switch(key)
    {
        case 'g':
        case 'G':
        {
            showGUI = !showGUI;
            guiRenderer->setVisible(showGUI);
            guiNavigation->setVisible(showGUI);
            break;
        }
        default: break;
    }
}
