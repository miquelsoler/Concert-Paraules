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

    void setLetterSize(float normalizedSize);
    void setYVelocity(float normalizedVelocity);

    void keyPressed ( ofKeyEventArgs& eventArgs );

private:

    PMUICanvasTypoRenderer* canvasTypoRenderer;
    
    string                                  charset;
    vector<ofTrueTypeFont *>                fontCharset;
    list<shared_ptr<PMLetterContainer>>     activeLetters;

    float                                   letterSize;
    float                                   letterYVelocity;

    mutex                                   mutexActiveLetters;

    ofxBox2d                                box2d;
    mutex                                   mutexAddLetter;

    void buildCharsetFromPoem();

};


#endif //PMCONCERTPARAULES_PMRENDERERTYPOGRAPHY_H
