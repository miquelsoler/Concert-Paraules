//
//  PMScene1.hpp
//  PMConcertParaules
//
//  Created by Miquel Àngel Soler on 7/10/15.
//
//

#ifndef PMScene1_hpp
#define PMScene1_hpp

#pragma once

#include <stdio.h>
#include "PMBaseScene.hpp"

class PMScene1 : public PMBaseScene
{
public:

    PMScene1() : PMBaseScene() {};

    void setup();
    void update();
    void draw();
    
    void willExit();

private:

};

#endif /* PMScene1_hpp */
