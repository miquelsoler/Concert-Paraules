//
//  PMBaseScene.cpp
//  PMConcertParaules
//
//  Created by Miquel Àngel Soler on 20/10/15.
//
//

#include "PMBaseScene.hpp"

PMBaseScene::PMBaseScene()
{
    baseFont.load(OF_TTF_SANS, 14, true, true, false, 0.0, 0);
}

void PMBaseScene::draw()
{
    ofClear(ofColor::black);
}
