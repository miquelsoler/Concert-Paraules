//
// Created by Miquel Àngel Soler on 10/11/15.
//

#include "PMBrushContainer.h"

PMBrushContainer::PMBrushContainer(string filename)
{
    brush = ofImage(filename);
}

void PMBrushContainer::setPosition(float normalizedX, float normalizedY)
{
    setPositionX(normalizedX);
    setPositionY(normalizedY);
}

void PMBrushContainer::setPositionX(float normalizedX)
{
    x = int(float(ofGetWidth()) * normalizedX);
}

void PMBrushContainer::setPositionY(float normalizedY)
{
    y = int(float(ofGetHeight()) * normalizedY);
}

void PMBrushContainer::setSize(float normalizedSize)
{
    if (normalizedSize > 1) normalizedSize = 1;
    if (normalizedSize < 0.1) normalizedSize = 0.1;
    size = int(brush.getWidth() * normalizedSize);
}

void PMBrushContainer::draw()
{
    int halfSize = size >> 1;
    brush.draw(x - halfSize, y - halfSize, size, size);
}
