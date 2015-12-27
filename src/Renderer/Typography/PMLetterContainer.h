//
// Created by Miquel Àngel Soler on 16/11/15.
//

#ifndef PMCONCERTPARAULES_PMLETTERCONTAINER_H
#define PMCONCERTPARAULES_PMLETTERCONTAINER_H

#include "PMBaseRenderer.h"

#include "Defaults.h"
#include "ofxBox2d.h"
#include "PMUICanvasTypoRenderer.h"

class PMLetterContainer : public ofxBox2dRect
{
public:

    PMLetterContainer(string letter, ofTrueTypeFont *font, ofPoint pos, float letterSize, float letterVelocity, ofxBox2d *box2d, PMUICanvasTypoRenderer* gui);
    ~PMLetterContainer();

    void draw();

    uint64_t getAge();
    void setNeedsToBeRemoved() { needsToBeRemoved = true; };
    bool getNeedsToBeRemoved() { return needsToBeRemoved; };

private:

    float           x, y;
    int             size;
    float           angle;

    ofxBox2d        *box2d;

    ofTrueTypeFont  *letterFont;
    string          letter;
    float           letterSize;

    uint64_t        timeCreated;

    bool            needsToBeRemoved;
};


#endif //PMCONCERTPARAULES_PMLETTERCONTAINER_H
