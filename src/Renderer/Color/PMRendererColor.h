//
// Created by Miquel Àngel Soler on 16/11/15.
//

#ifndef PMCONCERTPARAULES_PMRENDERERCOLOR_H
#define PMCONCERTPARAULES_PMRENDERERCOLOR_H

#pragma once

#include "PMBaseRenderer.h"


class PMRendererColor : public PMBaseRenderer
{
    PMRendererColor(unsigned int numInputs);

    virtual void setup();
    virtual void update();
    virtual void drawIntoFBO();
};


#endif //PMCONCERTPARAULES_PMRENDERERCOLOR_H
