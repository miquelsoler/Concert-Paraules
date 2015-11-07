//
// Created by Miquel Àngel Soler on 28/10/15.
//

#ifndef PMCONCERTPARAULES_PMBASERENDERER_H
#define PMCONCERTPARAULES_PMBASERENDERER_H

#pragma once

#include "ofMain.h"

class PMBaseRenderer
{
public:

    PMBaseRenderer();

    virtual void setup();
    virtual void update();
    virtual void draw();

    virtual void drawIntoFBO() = 0;

protected:

    ofFbo       fbo;
    ofColor     clearColor;
};


#endif //PMCONCERTPARAULES_PMBASERENDERER_H
