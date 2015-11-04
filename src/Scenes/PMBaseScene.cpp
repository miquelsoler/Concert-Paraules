//
//  PMBaseScene.cpp
//  PMConcertParaules
//
//  Created by Miquel Àngel Soler on 20/10/15.
//
//

#include "PMBaseScene.hpp"
#include "PMSceneManager.hpp"

PMBaseScene::PMBaseScene()
{
    baseFont.load(OF_TTF_SANS, 20, true, true, false, 0.3, 72);

    // Disable fades
    this->setSceneDuration(0, 0);

    backgroundColor = ofColor::black;
}

void PMBaseScene::draw()
{
    ofClear(backgroundColor);
}

void PMBaseScene::keyReleased(int key)
{
    switch(key)
    {
        case OF_KEY_LEFT:
        case OF_KEY_RIGHT:
        {
            PMSceneManager::getInstance().changeScene();
            break;
        }
        default: break;
    }
}
