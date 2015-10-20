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
#include "ofxScene.h"

class PMBaseScene : public ofxScene
{
public:

    virtual void setup() = 0;
    virtual void update() = 0;
    virtual void draw() = 0;

    virtual void willExit() = 0;

protected:

};

#endif /* PMBaseScene_hpp */
