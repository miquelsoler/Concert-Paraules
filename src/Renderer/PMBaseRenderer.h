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

    virtual void setPosition(float normalizedX, float normalizedY) = 0;
    virtual void setPositionX(float normalizedX) = 0;
    virtual void setPositionY(float normalizedY) = 0;
    virtual void setSize(float normalizedSize) = 0;
    void setShouldPaint(bool shouldPaint);

protected:

    ofFbo   fbo;
    bool    shouldPaint;
};


#endif //PMCONCERTPARAULES_PMBASERENDERER_H
