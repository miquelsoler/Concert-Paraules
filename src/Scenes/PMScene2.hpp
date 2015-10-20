//
//  PMScene2.hpp
//  PMConcertParaules
//
//  Created by Miquel Àngel Soler on 7/10/15.
//
//

#ifndef PMScene2_hpp
#define PMScene2_hpp

#pragma once

#include <stdio.h>
#include "PMBaseScene.hpp"

class PMScene2 : public PMBaseScene
{
public:

    PMScene2() : PMBaseScene() {};

    void setup();
    void update();
    void draw();
    
    void willExit();

protected:

private:

};

#endif /* PMScene2_hpp */
