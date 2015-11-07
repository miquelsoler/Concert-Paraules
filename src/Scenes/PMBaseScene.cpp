//
//  PMBaseScene.cpp
//  PMConcertParaules
//
//  Created by Miquel Àngel Soler on 20/10/15.
//
//

#include "PMBaseScene.hpp"

PMBaseScene::PMBaseScene(const string &name) : ofxFadeScene(name)
{
    baseFont.load(OF_TTF_SANS, 20, true, true, false, 0.3, 72);

    backgroundColor = ofColor::black;

    setSingleSetup(false); // call setup each time the scene is loaded
}

void PMBaseScene::draw()
{
}

void PMBaseScene::updateEnter()
{
    ofxFadeScene::updateEnter();
}

void PMBaseScene::updateExit()
{
    ofxFadeScene::updateExit();
}