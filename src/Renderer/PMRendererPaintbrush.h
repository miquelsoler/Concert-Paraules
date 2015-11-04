//
// Created by Miquel Àngel Soler on 28/10/15.
//

#ifndef PMCONCERTPARAULES_PMRENDERERPAINTBRUSH_H
#define PMCONCERTPARAULES_PMRENDERERPAINTBRUSH_H

#pragma once

#include "PMBaseRenderer.h"

class PMRendererPaintbrush : public PMBaseRenderer
{
public:

    virtual void setup();
    virtual void update();
    virtual void drawIntoFBO();

private:

    ofImage brush;
};


#endif //PMCONCERTPARAULES_PMRENDERERPAINTBRUSH_H
