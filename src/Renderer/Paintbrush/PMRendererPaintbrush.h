//
// Created by Miquel Àngel Soler on 28/10/15.
//

#ifndef PMCONCERTPARAULES_PMRENDERERPAINTBRUSH_H
#define PMCONCERTPARAULES_PMRENDERERPAINTBRUSH_H

#pragma once

#include "PMBaseRenderer.h"
#include "PMBrushContainer.h"
#include "PMUICanvasBrushRenderer.h"


class PMRendererPaintbrush : public PMBaseRenderer
{
public:

    PMRendererPaintbrush(unsigned int numInputs);

    virtual void setup();
    virtual void update();
    virtual void drawIntoFBO();

    void changeBaseAngle(unsigned int inputIndex);
    void setOffset(unsigned int inputIndex, float offset);

    void setPosition(unsigned int inputIndex, float normalizedX, float normalizedY);
    void setPositionX(unsigned int inputIndex, float normalizedX);
    void setPositionY(unsigned int inputIndex, float normalizedY);
    void setSize(unsigned int inputIndex, float normalizedSize);

private:

    PMUICanvasBrushRenderer* canvasBrushRenderer;

    vector<PMBrushContainer *> brushes;
};


#endif //PMCONCERTPARAULES_PMRENDERERPAINTBRUSH_H
