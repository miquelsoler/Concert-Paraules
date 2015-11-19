//
// Created by Miquel Àngel Soler on 10/11/15.
//

#ifndef PMCONCERTPARAULES_PMBRUSHCONTAINER_H
#define PMCONCERTPARAULES_PMBRUSHCONTAINER_H

#include "PMBaseRenderer.h"

typedef enum
{
    LEFT = 0,
    RIGHT = 1,
    UP = 2,
    DOWN = 3,
    NUM_ORIGINS
} PMBrushContainerOrigin;

class PMBrushContainer
{
public:

    PMBrushContainer(string filename);

    void update();
    void draw();

    void setOrigin(PMBrushContainerOrigin);
    void changeBaseAngle();
    void setOffset(float offset);

    void setPosition(float normalizedX, float normalizedY);
    void setPositionX(float normalizedX);
    void setPositionY(float normalizedY);
    void setSize(float normalizedSize);

private:

    float baseAngle;

    float x, y;
    float xOffset, yOffset, generalOffset;
    int size;

    ofImage brush;
};


#endif //PMCONCERTPARAULES_PMBRUSHCONTAINER_H
