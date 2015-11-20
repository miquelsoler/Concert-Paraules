//
// Created by Miquel Àngel Soler on 16/11/15.
//

#ifndef PMCONCERTPARAULES_PMLETTERCONTAINER_H
#define PMCONCERTPARAULES_PMLETTERCONTAINER_H

#include "PMBaseRenderer.h"


class PMLetterContainer
{
public:

    PMLetterContainer(string fontName, string letter);

    void setPosition(float normalizedX, float normalizedY);
    void setPositionX(float normalizedX);
    void setPositionY(float normalizedY);
    void setSize(float normalizedSize);

    void draw();

private:

    float x, y;
    int size;
    float angle;

    ofTrueTypeFont letterFont;
    string letter;
};


#endif //PMCONCERTPARAULES_PMLETTERCONTAINER_H
