//
// Created by Miquel Àngel Soler on 16/11/15.
//

#ifndef PMCONCERTPARAULES_PMRENDERERTYPOGRAPHY_H
#define PMCONCERTPARAULES_PMRENDERERTYPOGRAPHY_H

#pragma once

#include "PMBaseRenderer.h"

#include "PMLetterContainer.h"
#include "Defaults.h"

#include "ofxBox2d.h"


class PMRendererTypography : public PMBaseRenderer
{
public:

    PMRendererTypography();

    virtual void setup();
    virtual void update();
    virtual void drawIntoFBO();

    void addLetter();

    void setLetterSize(float normalizedSize);
    void setYVelocity(float normalizedVelocity);

    void keyPressed ( ofKeyEventArgs& eventArgs );
    
    virtual void pitchChanged(pitchParams pitchParams);
    virtual void energyChanged(energyParams energyParams);
    virtual void silenceStateChanged(silenceParams &silenceParams);

protected:

    virtual void clear();

private:

    string                                  charset;
    ofTrueTypeFont *                        font;
    list<shared_ptr<PMLetterContainer>>     activeLetters;

    float                                   letterSize;
    float                                   letterYVelocity;

    mutex                                   mutexActiveLetters;

    ofxBox2d                                box2d;
    mutex                                   mutexAddLetter;

    void buildCharsetFromPoem();
    
    float                               typoTimer;
    bool                                typoTimerEnabled;

    bool somethingInContact;
    void contactStart(ofxBox2dContactArgs &e);
    void contactEnd(ofxBox2dContactArgs &e);
};


#endif //PMCONCERTPARAULES_PMRENDERERTYPOGRAPHY_H
