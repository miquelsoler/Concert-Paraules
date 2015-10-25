//
//  PMBaseScene.hpp
//  PMConcertParaules
//
//  Created by Miquel Àngel Soler on 20/10/15.
//
//

#ifndef PMBaseScene_hpp
#define PMBaseScene_hpp

#pragma once

#include <stdio.h>
#include "ofxSceneManager.h"
#include "ofxScene.h"

class PMBaseScene : public ofxScene
{
public:

    PMBaseScene();

    virtual void setup() = 0;
    virtual void update() = 0;
    virtual void draw();

    virtual void willExit() = 0;

protected:

    ofColor backgroundColor;

    ofTrueTypeFont baseFont;
};

#endif /* PMBaseScene_hpp */
