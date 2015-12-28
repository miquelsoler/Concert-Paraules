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
    virtual void keyPressed ( ofKeyEventArgs& eventArgs );
    virtual void keyReleased ( ofKeyEventArgs& eventArgs );

    virtual void setup();
    virtual void update();
    virtual void drawIntoFBO();
    virtual void pitchChanged(pitchParams pitchParams);
    virtual void energyChanged(energyParams energyParams);
    virtual void silenceStateChanged(silenceParams &silenceParams);

    void addLetter();
    void setLetterSize(float normalizedSize);
    void setYVelocity(float normalizedVelocity);
    

protected:

    virtual void clear();

private:

    PMUICanvasTypoRenderer                  *myGUI;

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
    
    
    /// ELOI
    int                                 oldMode;
    ofVec2f                             oldGravity;
    bool                                addALetter;
    bool                                firstTimeInMode;

    float                               timeForNextLetter;
    float                               lastPitchReceived;
    
};


#endif //PMCONCERTPARAULES_PMRENDERERTYPOGRAPHY_H
