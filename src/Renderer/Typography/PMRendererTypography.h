//
// Created by Miquel Àngel Soler on 16/11/15.
//

#ifndef PMCONCERTPARAULES_PMRENDERERTYPOGRAPHY_H
#define PMCONCERTPARAULES_PMRENDERERTYPOGRAPHY_H

#pragma once

#include "PMBaseRenderer.h"

#include "PMLetterContainer.h"


class PMRendererTypography : public PMBaseRenderer
{
public:

    PMRendererTypography(unsigned int numInputs);

    virtual void setup();
    virtual void update();
    virtual void drawIntoFBO();

    void addLetter();

private:

    list<PMLetterContainer> letters;
};


#endif //PMCONCERTPARAULES_PMRENDERERTYPOGRAPHY_H