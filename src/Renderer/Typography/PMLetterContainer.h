//
// Created by Miquel Àngel Soler on 16/11/15.
//

#ifndef PMCONCERTPARAULES_PMLETTERCONTAINER_H
#define PMCONCERTPARAULES_PMLETTERCONTAINER_H

#include "PMBaseRenderer.h"

#include "Defaults.h"
#ifdef WITH_BOX2D
#   include "ofxBox2d.h"
#endif

#ifdef WITH_BOX2D
class PMLetterContainer : public ofxBox2dRect
#else
class PMLetterContainer
#endif
{
public:

#ifdef WITH_BOX2D
    PMLetterContainer(string letter, ofTrueTypeFont *font, ofxBox2d *box2d);
#else
    PMLetterContainer(string letter, ofTrueTypeFont *font);
#endif
    ~PMLetterContainer();

    void setPosition(float normalizedX, float normalizedY);
    void setPositionX(float normalizedX);
    void setPositionY(float normalizedY);
    void setSize(float normalizedSize);

    void draw();

#ifdef WITH_BOX2D
    uint64_t getAge();
#endif

private:

    float           x, y;
    int             size;
    float           angle;

    ofTrueTypeFont  *letterFont;
    string          letter;

#ifdef WITH_BOX2D
    ofxBox2d        *box2d;
    uint64_t        timeCreated;
#endif
};


#endif //PMCONCERTPARAULES_PMLETTERCONTAINER_H
