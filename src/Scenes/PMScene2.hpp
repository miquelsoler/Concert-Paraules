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
#include "PMRendererPaintbrush.h"
#include "PMUICanvasRenderers.h"
#include "PMUICanvasNavigation.h"

class PMScene2 : public PMBaseScene
{
public:

    PMScene2();
    ~PMScene2();

    void setup();
    void update();
    void updateEnter();
    void updateExit();
    void draw();

    void saveSettings();

    void keyReleased(int key);

private:

    PMBaseRenderer          *renderer;

    PMUICanvasRenderers     *guiRenderers;

    ofColor                 canvasBgColor;

    bool                    showGUI;
};

#endif /* PMScene2_hpp */
