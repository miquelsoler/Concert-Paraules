//
// Created by Miquel Àngel Soler on 28/10/15.
//

#ifndef PMCONCERTPARAULES_PMRENDERERPAINTBRUSH_H
#define PMCONCERTPARAULES_PMRENDERERPAINTBRUSH_H

#pragma once

#include "PMBaseRenderer.h"
#include "PMBrushContainer.h"


class PMRendererPaintbrush : public PMBaseRenderer
{
public:

    PMRendererPaintbrush(unsigned int numInputs);

    virtual void setup();
    virtual void update();
    virtual void drawIntoFBO();

    void setPosition(unsigned int inputId, float normalizedX, float normalizedY);
    void setPositionX(unsigned int inputId, float normalizedX);
    void setPositionY(unsigned int inputId, float normalizedY);
    void setSize(unsigned int inputId, float normalizedSize);

private:

    PMBrushContainer *brush;
};


#endif //PMCONCERTPARAULES_PMRENDERERPAINTBRUSH_H
