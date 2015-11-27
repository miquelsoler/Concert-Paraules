//
// Created by Miquel Àngel Soler on 28/10/15.
//

#ifndef PMCONCERTPARAULES_PMRENDERERPAINTBRUSH_H
#define PMCONCERTPARAULES_PMRENDERERPAINTBRUSH_H

#pragma once

#include "PMBaseRenderer.h"
#include "PMBrushContainer.h"
#include "PMUICanvasBrushRenderer.h"
#include "PMParticle.h"


class PMRendererPaintbrush : public PMBaseRenderer
{
public:

//    PMRendererPaintbrush(unsigned int numInputs);
    PMRendererPaintbrush();

    virtual void setup();
    virtual void update();
    virtual void drawIntoFBO();

    void changeBaseAngle();
    void setOffset(float offset);

    void setPosition(float normalizedX, float normalizedY);
    void setPositionX(float normalizedX);
    void setPositionY(float normalizedY);
    void setSize(float normalizedSize);
    void changeDirection(float direction);
    void vibrate(float hasToVibrate);

    virtual void pitchChanged(pitchParams pitchParams);
    virtual void energyChanged(energyParams energyParams);

private:

//    vector<PMBrushContainer *> brushes;
    PMBrushContainer *brush;
    deque<PMParticle> particles;
};


#endif //PMCONCERTPARAULES_PMRENDERERPAINTBRUSH_H
