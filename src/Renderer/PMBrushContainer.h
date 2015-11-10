//
// Created by Miquel Àngel Soler on 10/11/15.
//

#ifndef PMCONCERTPARAULES_PMBRUSHCONTAINER_H
#define PMCONCERTPARAULES_PMBRUSHCONTAINER_H

#include "ofMain.h"


class PMBrushContainer
{
public:

    PMBrushContainer(string filename);

    void setPosition(float normalizedX, float normalizedY);
    void setPositionX(float normalizedX);
    void setPositionY(float normalizedY);
    void setSize(float normalizedSize);

    void draw();

private:

    int x, y;
    int size;

    ofImage brush;
};


#endif //PMCONCERTPARAULES_PMBRUSHCONTAINER_H
