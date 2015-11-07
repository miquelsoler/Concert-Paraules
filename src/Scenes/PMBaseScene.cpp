//
//  PMBaseScene.cpp
//  PMConcertParaules
//
//  Created by Miquel Àngel Soler on 20/10/15.
//
//

#include "PMBaseScene.hpp"

PMBaseScene::PMBaseScene(const string &name) : ofxScene(name)
{
    baseFont.load(OF_TTF_SANS, 20, true, true, false, 0.3, 72);

    backgroundColor = ofColor::black;
}

void PMBaseScene::draw()
{
}

void PMBaseScene::updateEnter()
{
    ofxScene::updateEnter();
}

void PMBaseScene::updateExit()
{
    ofxScene::updateExit();
}