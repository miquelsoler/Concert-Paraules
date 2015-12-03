//
// Created by Miquel Àngel Soler on 3/12/15.
//

#include "PMBrushContainer2.h"

static const float MIN_ORIGIN = 0.2f;
static const float MAX_ORIGIN = 0.8f;
static const float PAINTING_MARGIN_PCT = 0.00;


PMBrushContainer2::PMBrushContainer2()
{
    bounces = true;

    // TODO: Move it to UI canvas
    {
        setOrigin(LEFT);
        setMinSize(2.0);
        setMaxSize(10.0);
        setSize(1);
    }
}

void PMBrushContainer2::update()
{
    x += 3;
}

void PMBrushContainer2::draw()
{
    ofSetColor(color);
    ofSetCircleResolution(32);
    ofDrawCircle(x, y, size/2.0f);
}

void PMBrushContainer2::setOrigin(PMBrushContainerOrigin origin)
{
    ofSeedRandom(rand());
    float randomNormalizedPos = ofRandom(MIN_ORIGIN, MAX_ORIGIN);

    switch (origin)
    {
        case LEFT:
        {
            baseAngle = 0;
            setPositionX(PAINTING_MARGIN_PCT);
            setPositionY(randomNormalizedPos);
            break;
        }
        case RIGHT:
        {
            baseAngle = 180;
            setPositionX(1 - PAINTING_MARGIN_PCT);
            setPositionY(randomNormalizedPos);
            break;
        }
        case UP:
        {
            baseAngle = 270;
            setPositionY(PAINTING_MARGIN_PCT);
            setPositionX(randomNormalizedPos);
            break;
        }
        case DOWN:
        {
            baseAngle = 90;
            setPositionY(1 - PAINTING_MARGIN_PCT);
            setPositionX(randomNormalizedPos);
            break;
        }
        default: break;
    }
}

void PMBrushContainer2::setPosition(float normalizedX, float normalizedY)
{
    setPositionX(normalizedX);
    setPositionY(normalizedY);
}

void PMBrushContainer2::setPositionX(float normalizedX)
{
    x = int(float(ofGetWidth()) * normalizedX);
}

void PMBrushContainer2::setPositionY(float normalizedY)
{
    y = int(float(ofGetHeight()) * normalizedY);
}

void PMBrushContainer2::setSize(float normalizedSize)
{
    float minNormalizedSize = 0.001;
    float maxNormalizedSize = 1.0;

    if (normalizedSize > maxNormalizedSize) normalizedSize = maxNormalizedSize;
    if (normalizedSize < minNormalizedSize) normalizedSize = minNormalizedSize;

    size = ofMap(normalizedSize, minNormalizedSize, maxNormalizedSize, minSize, maxSize);
}
