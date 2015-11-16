//
// Created by Miquel Àngel Soler on 16/11/15.
//

#ifndef PMCONCERTPARAULES_PMRENDERERTYPOGRAPHY_H
#define PMCONCERTPARAULES_PMRENDERERTYPOGRAPHY_H

#pragma once

#include "PMBaseRenderer.h"


class PMRendererTypography : public PMBaseRenderer
{
    PMRendererTypography(unsigned int numInputs);

    virtual void setup();
    virtual void update();
    virtual void drawIntoFBO();
};


#endif //PMCONCERTPARAULES_PMRENDERERTYPOGRAPHY_H
