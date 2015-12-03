//
// Created by Miquel Àngel Soler on 3/12/15.
//

#ifndef PMCONCERTPARAULES_PMBRUSHCONTAINER2_H
#define PMCONCERTPARAULES_PMBRUSHCONTAINER2_H

#include "PMBaseRenderer.h"
#include "PMUICanvasBrushRenderer.h"

typedef enum
{
    LEFT = 0,
    RIGHT = 1,
    UP = 2,
    DOWN = 3,
    NUM_ORIGINS
} PMBrushContainerOrigin;

class PMBrushContainer2
{
public:

    PMBrushContainer2();

    void update();
    void draw();

    void setOrigin(PMBrushContainerOrigin);

    void setPosition(float normalizedX, float normalizedY);
    void setPositionX(float normalizedX);
    void setPositionY(float normalizedY);

    void setOffset(float normalizedOffset);

    void setSize(float normalizedSize);
    void setMinSize(float _minSize) { minSize = _minSize; };
    void setMaxSize(float _maxSize) { maxSize = _maxSize; };

    void setSpeed(int _speed) { speed = _speed; };

    void setBounces(bool _bounces) { bounces = _bounces; };
    void setColor(ofColor _color) { color=_color; };

private:

    float x, y;
    float oldX, oldY;
    float offset;
    float size, minSize, maxSize;
    int speed;

    PMBrushContainerOrigin direction;
    bool shouldChangeDirection;

    ofColor color;
    bool bounces;

    void changeDirection();
};


#endif //PMCONCERTPARAULES_PMBRUSHCONTAINER2_H
