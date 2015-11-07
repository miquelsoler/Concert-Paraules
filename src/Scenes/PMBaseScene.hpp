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
#include "ofMain.h"
#include "ofxSceneManager.h"
#include "ofxScene.h"

class PMBaseScene : public ofxScene
{
public:

    PMBaseScene(const string &name);

    virtual void setup() = 0;
    virtual void update() = 0;
    virtual void updateEnter();
    virtual void updateExit() = 0;
    virtual void draw() = 0;

    virtual void exit() = 0;

protected:

    ofColor backgroundColor;
    ofTrueTypeFont baseFont;
};

#endif /* PMBaseScene_hpp */
