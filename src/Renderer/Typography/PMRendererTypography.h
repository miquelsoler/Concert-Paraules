//
// Created by Miquel Àngel Soler on 16/11/15.
//

#ifndef PMCONCERTPARAULES_PMRENDERERTYPOGRAPHY_H
#define PMCONCERTPARAULES_PMRENDERERTYPOGRAPHY_H

#pragma once

#include "PMBaseRenderer.h"

#include "PMLetterContainer.h"
#include "PMUICanvasTypoRenderer.h"
#include "Defaults.h"

#include "ofxBox2d.h"


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
    
    string                                  charset;
    vector<ofTrueTypeFont *>                fontCharset;
#ifdef WITH_BOX2D
    list<shared_ptr<PMLetterContainer>>   activeLetters;
#else
    list<PMLetterContainer *>           activeLetters;
#endif

    mutex                                   mutexActiveLetters;

#ifdef WITH_BOX2D
    ofxBox2d                                box2d;
    mutex                                   mutexAddLetter;
#endif

    void buildCharsetFromPoem();

};


#endif //PMCONCERTPARAULES_PMRENDERERTYPOGRAPHY_H
