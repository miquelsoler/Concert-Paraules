//
// Created by Miquel Àngel Soler on 16/11/15.
//

#ifndef PMCONCERTPARAULES_PMLETTERCONTAINER_H
#define PMCONCERTPARAULES_PMLETTERCONTAINER_H

#include "PMBaseRenderer.h"


class PMLetterContainer
{
public:

    PMLetterContainer(string fontName);

    void setPosition(float normalizedX, float normalizedY);
    void setPositionX(float normalizedX);
    void setPositionY(float normalizedY);
    void setSize(float normalizedSize);

    void draw();

private:

    int x, y;
    int size;

    ofTrueTypeFont letterFont;
};


#endif //PMCONCERTPARAULES_PMLETTERCONTAINER_H
