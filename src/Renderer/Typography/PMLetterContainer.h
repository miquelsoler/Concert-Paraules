//
// Created by Miquel Àngel Soler on 16/11/15.
//

#ifndef PMCONCERTPARAULES_PMLETTERCONTAINER_H
#define PMCONCERTPARAULES_PMLETTERCONTAINER_H

#include "PMBaseRenderer.h"

#include "Defaults.h"
#include "ofxBox2d.h"

class PMLetterContainer : public ofxBox2dRect
{
public:

    PMLetterContainer(string letter, ofTrueTypeFont *font, ofxBox2d *box2d);
    ~PMLetterContainer();

    void setPosition(float normalizedX, float normalizedY);
    void setPositionX(float normalizedX);
    void setPositionY(float normalizedY);
    void setSize(float normalizedSize);

    void draw();

    uint64_t getAge();

private:

    float           x, y;
    int             size;
    float           angle;

    ofTrueTypeFont  *letterFont;
    string          letter;

    ofxBox2d        *box2d;
    uint64_t        timeCreated;
};


#endif //PMCONCERTPARAULES_PMLETTERCONTAINER_H
