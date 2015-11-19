//
// Created by Miquel Àngel Soler on 10/11/15.
//

#include "PMBrushContainer.h"

static const float MIN_ORIGIN = 0.2f;
static const float MAX_ORIGIN = 0.8f;

static const float ANGLE_LARGE_VARIATION = 50;

static const float BRUSH_SPEED = 3.0;

#define degreesToRadians(angleDegrees) (angleDegrees * M_PI / 180.0)

PMBrushContainer::PMBrushContainer(string filename)
{
    brush = ofImage(filename);

    variationAngle = 0;

    ofSeedRandom();
}

void PMBrushContainer::update()
{
    double angleInRadians = degreesToRadians(baseAngle);
    x += BRUSH_SPEED * cos(angleInRadians);
    y += BRUSH_SPEED * sin(angleInRadians);

    int viewWidth = ofGetWidth();
    int viewHeight = ofGetHeight();

    if (x > viewWidth) x -= viewWidth;
    if (x < 0) x += viewWidth;
    if (y > viewHeight) y -= viewHeight;
    if (y < 0) y += viewHeight;
}

void PMBrushContainer::draw()
{
    int halfSize = size >> 1;
    brush.draw(x - halfSize, y - halfSize, size, size);
}

void PMBrushContainer::setOrigin(PMBrushContainerOrigin origin)
{
    ofSeedRandom(rand());
    float randomNormalizedPos = ofRandom(MIN_ORIGIN, MAX_ORIGIN);

    switch (origin)
    {
        case LEFT:
        {
            baseAngle = 0;
            setPositionX(0);
            setPositionY(randomNormalizedPos);
            break;
        }
        case RIGHT:
        {
            baseAngle = 180;
            setPositionX(1);
            setPositionY(randomNormalizedPos);
            break;
        }
        case UP:
        {
            baseAngle = 270;
            setPositionY(0);
            setPositionX(randomNormalizedPos);
            break;
        }
        case DOWN:
        {
            baseAngle = 90;
            setPositionY(1);
            setPositionX(randomNormalizedPos);
            break;
        }
        default: break;
    }
}

void PMBrushContainer::changeBaseAngle()
{
    int sign = ofSign(ofRandom(-1, 1));
    if (sign == 0) sign = 1;
    baseAngle += sign * ANGLE_LARGE_VARIATION;
    baseAngle = ofWrapDegrees(baseAngle, -360, 360);
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
