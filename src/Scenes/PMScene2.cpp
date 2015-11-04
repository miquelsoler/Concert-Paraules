//
//  PMScene2.cpp
//  PMConcertParaules
//
//  Created by Miquel Àngel Soler on 7/10/15.
//
//

#include "PMScene2.hpp"
#include "PMSceneManager.hpp"

///--------------------------------------------------------------
PMScene2::PMScene2()
{
    backgroundColor = ofColor::white;

    guiRendererSettings = new PMUICanvasRenderers("RENDER MODE", OFX_UI_FONT_LARGE);
    guiRendererSettings->init(200, 200);
    guiRendererSettings->setBackgroundColor(ofColor(100, 100, 100, 255));
    guiRendererSettings->setVisible(false);
}


PMScene2::~PMScene2()
{
    delete guiRendererSettings;
}

void PMScene2::setup()
{
    cout << "S2 setup" << endl;
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
    guiRendererSettings->loadSettings("settings/gui/renderers2.xml");
    guiRendererSettings->setVisible(true);
}

void PMScene2::willExit()
{
    exit();
}

void PMScene2::exit()
{
    guiRendererSettings->saveSettings("settings/gui/renderers2.xml");
    guiRendererSettings->setVisible(false);
}

void PMScene2::keyReleased(int key)
{
    switch(key)
    {
        case 'g':
        case 'G':
        {
            guiRendererSettings->setVisible(!guiRendererSettings->isVisible());
            break;
        }
    }
    cout << "Scene2 key released" << endl;
}
