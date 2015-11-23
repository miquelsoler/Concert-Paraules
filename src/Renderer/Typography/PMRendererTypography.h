//
// Created by Miquel Àngel Soler on 16/11/15.
//

#ifndef PMCONCERTPARAULES_PMRENDERERTYPOGRAPHY_H
#define PMCONCERTPARAULES_PMRENDERERTYPOGRAPHY_H

#pragma once

#include "PMBaseRenderer.h"

#include "PMLetterContainer.h"
#include "PMUICanvasTypoRenderer.h"


class PMRendererTypography : public PMBaseRenderer
{
public:

    PMRendererTypography(unsigned int numInputs);

    virtual void setup();
    virtual void update();
    virtual void drawIntoFBO();

    void addLetter();

    void keyPressed ( ofKeyEventArgs& eventArgs );

private:
    PMUICanvasTypoRenderer* canvasTypoRenderer;
    
    string charset;
    vector<ofTrueTypeFont *> fontCharset;

    list<PMLetterContainer *> activeLetters;

    void buildCharsetFromPoem();

    mutex mutexLetters;
};


#endif //PMCONCERTPARAULES_PMRENDERERTYPOGRAPHY_H
