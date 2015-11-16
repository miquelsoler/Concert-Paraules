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

    PMBaseRenderer(unsigned int numInputs);

    virtual void setup();
    virtual void update();
    virtual void draw();

    virtual void drawIntoFBO() = 0;

    virtual void setPosition(unsigned int inputIndex, float normalizedX, float normalizedY) = 0;
    virtual void setPositionX(unsigned int inputIndex, float normalizedX) = 0;
    virtual void setPositionY(unsigned int inputIndex, float normalizedY) = 0;
    virtual void setSize(unsigned int inputIndex, float normalizedSize) = 0;
    void setShouldPaint(unsigned int inputIndex, bool shouldPaint);

protected:

    ofFbo           fbo;

    unsigned int    numInputs;     // Number of microphones
    vector<bool>    shouldPaint;   // Enable/disable painting per input
};


#endif //PMCONCERTPARAULES_PMBASERENDERER_H
