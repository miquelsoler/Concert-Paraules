//
//  PMScene2.cpp
//  PMConcertParaules
//
//  Created by Miquel Àngel Soler on 7/10/15.
//
//

#include "PMScene2.hpp"
#include "PMSettingsManagerGeneral.h"

PMScene2::PMScene2() : PMBaseScene("Scene 2")
{
#ifdef OF_DEBUG
    showGUI= PMSettingsManagerGeneral::getInstance().getDebugShowGUIScene2();
#else
    showGUI = PMSettingsManagerGeneral::getInstance().getReleaseShowGUIScene2();
#endif

    backgroundColor = ofColor::white;

    // GUI
    {
        canvasBgColor = ofColor(50, 50, 50, 200);

        guiRenderers = new PMUICanvasRenderers("RENDER MODE", OFX_UI_FONT_LARGE);
        guiRenderers->init(200, 200);
        guiRenderers->setBackgroundColor(canvasBgColor);
        guiRenderers->setVisible(true);

        guiNavigation = new PMUICanvasNavigation("NAVIGATION", OFX_UI_FONT_MEDIUM);
        guiNavigation->init(ofGetWidth() - 300, ofGetHeight() - 300);
        guiNavigation->setBackgroundColor(canvasBgColor);
        guiNavigation->setVisible(true);
    }

    // Renderer
    {
        ofColor rendererClearColor = ofColor(255, 0, 0);
        renderer = new PMRendererPaintbrush(rendererClearColor);
    }
}


PMScene2::~PMScene2()
{
    delete guiRenderers;
    delete guiNavigation;
}

void PMScene2::setup()
{
    renderer->setup();
}

void PMScene2::update()
{
    renderer->update();
}

void PMScene2::updateEnter()
{
    if (isEnteringFirst())
    {
        guiRenderers->loadSettings("settings/gui/renderers2.xml");
        guiNavigation->loadSettings("settings/gui/navigation2.xml");

        guiRenderers->setVisible(showGUI);
        guiNavigation->setVisible(showGUI);
    }

    PMBaseScene::updateEnter();
}

void PMScene2::updateExit()
{
    exit();
}

void PMScene2::draw()
{
    ofClear(backgroundColor);
    ofSetColor(ofColor::red);
    ofDrawCircle(100, 100, 100);
//    PMBaseScene::draw();

    renderer->draw();
}

void PMScene2::exit()
{
    guiRenderers->saveSettings("settings/gui/renderers2.xml");
    guiNavigation->saveSettings("settings/gui/navigation2.xml");

    guiRenderers->setVisible(false);
    guiNavigation->setVisible(false);
}

void PMScene2::keyReleased(int key)
{
    PMBaseScene::keyReleased(key);

    switch(key)
    {
        case 'g':
        case 'G':
        {
            showGUI = !showGUI;
            guiRenderers->setVisible(showGUI);
            guiNavigation->setVisible(showGUI);
            break;
        }
        default: break;
    }
}

void PMScene2::changeScene()
{
    unsigned int nextSceneIndex = 0;
    ofNotifyEvent(eventChangeScene, nextSceneIndex, this);
}
