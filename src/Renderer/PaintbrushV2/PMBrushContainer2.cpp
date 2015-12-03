//
// Created by Miquel Àngel Soler on 3/12/15.
//

#include "PMBrushContainer2.h"

static const float MIN_ORIGIN = 0.3f;
static const float MAX_ORIGIN = 0.7f;


PMBrushContainer2::PMBrushContainer2()
{
    setSize(1);
    setSpeed(1);
    shouldChangeDirection = false;

    offset = 0.0f;
}

void PMBrushContainer2::update()
{
    switch(direction)
    {
        case RIGHT:     x += speed; break;
        case LEFT:      x -= speed; break;
        case UP:        y -= speed; break;
        case DOWN:      y += speed; break;
        default:        break;
    }

    if (x >= ofGetWidth()) {
        x = ofGetWidth() - 1;
        shouldChangeDirection = true;
    }
    if (x < 0) {
        x = 0;
        shouldChangeDirection = true;
    }
    if (y >= ofGetHeight()) {
        y = ofGetHeight() - 1;
        shouldChangeDirection = true;
    }
    if (y < 0) {
        y = 0;
        shouldChangeDirection = true;
    }
}

void PMBrushContainer2::draw()
{
//    cout << "Offset: " << offset << endl;

    ofSetColor(color);
    ofSetCircleResolution(32);

    // Interpolate brush positions

    float offsetX=0.0f, offsetY=0.0f;
    if ((direction==LEFT) || (direction==RIGHT)) offsetY = offset;
    else offsetX = offset;

    double deltaX = (x - oldX) / double(speed);
    double deltaY = (y - oldY) / double(speed);

    for (int i=0; i<speed; ++i)
    {
        oldX += deltaX + offsetX;
        oldY += deltaY + offsetY;
        ofDrawCircle(oldX, oldY, size / 2.0f);
    }

    if (shouldChangeDirection) changeDirection();

//    cout << "Pos: " << x << ", " << y << endl;
}

void PMBrushContainer2::setOrigin(PMBrushContainerOrigin origin)
{
    ofSeedRandom(rand());
    float randomNormalizedPos = ofRandom(MIN_ORIGIN, MAX_ORIGIN);
    randomNormalizedPos = 0.5f;

    switch (origin)
    {
        case LEFT:
        default: // TODO: Check why sometimes origin is a weird number (it's not initialized)
        {
            setPositionX(0);
            setPositionY(randomNormalizedPos);
            direction = RIGHT;
            break;
        }
        case RIGHT:
        {
            setPositionX(1);
            setPositionY(randomNormalizedPos);
            direction = LEFT;
            break;
        }
        case UP:
        {
            setPositionY(0);
            setPositionX(randomNormalizedPos);
            direction = DOWN;
            break;
        }
        case DOWN:
        {
            setPositionY(1);
            setPositionX(randomNormalizedPos);
            direction = UP;
            break;
        }
    }

    cout << "--------------------------------" << endl;
    cout << "setOrigin " << origin << endl;
    cout << "Pos: " << x << ", " << y << endl;
    cout << "--------------------------------" << endl;
}

void PMBrushContainer2::setPosition(float normalizedX, float normalizedY)
{
    setPositionX(normalizedX);
    setPositionY(normalizedY);
}

void PMBrushContainer2::setPositionX(float normalizedX)
{
    x = int(float(ofGetWidth()) * normalizedX);
    oldX = x;
}

void PMBrushContainer2::setPositionY(float normalizedY)
{
    y = int(float(ofGetHeight()) * normalizedY);
    oldY = y;
}

void PMBrushContainer2::setOffset(float normalizedOffset)
{
    float minNormalizedOffset = -1.0f;
    float maxNormalizedOffset = 1.0f;

    if (normalizedOffset > maxNormalizedOffset) normalizedOffset = maxNormalizedOffset;
    if (normalizedOffset < minNormalizedOffset) normalizedOffset = minNormalizedOffset;

    float minOffset = -30.0f;
    float maxOffset = 30.0f;
    offset = ofMap(normalizedOffset, minNormalizedOffset, maxNormalizedOffset, minOffset, maxOffset);
}

void PMBrushContainer2::setSize(float normalizedSize)
{
    float minNormalizedSize = 0.001;
    float maxNormalizedSize = 1.0;

    if (normalizedSize > maxNormalizedSize) normalizedSize = maxNormalizedSize;
    if (normalizedSize < minNormalizedSize) normalizedSize = minNormalizedSize;

    size = ofMap(normalizedSize, minNormalizedSize, maxNormalizedSize, minSize, maxSize);
}

void PMBrushContainer2::changeDirection()
{
    switch (direction)
    {
        case RIGHT:     direction = LEFT; break;
        case LEFT:      direction = RIGHT; break;
        case UP:        direction = DOWN; break;
        case DOWN:      direction = UP; break;
        default:        break;
    }

    shouldChangeDirection = false;
}
