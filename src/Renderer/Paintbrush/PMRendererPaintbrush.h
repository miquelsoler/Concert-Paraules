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

    PMRendererPaintbrush() : PMBaseRenderer() {};

    virtual void setup();
    virtual void update();
    virtual void drawIntoFBO();

    void setPosition(float normalizedX, float normalizedY);
    void setPositionX(float normalizedX);
    void setPositionY(float normalizedY);
    void setSize(float normalizedSize);

private:

    PMBrushContainer *brush;
};


#endif //PMCONCERTPARAULES_PMRENDERERPAINTBRUSH_H
