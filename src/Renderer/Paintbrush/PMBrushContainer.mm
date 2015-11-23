//
// Created by Miquel Àngel Soler on 10/11/15.
//

#include "PMBrushContainer.h"

#define degreesToRadians(angleDegrees) (angleDegrees * M_PI / 180.0)

static const float MIN_ORIGIN = 0.2f;
static const float MAX_ORIGIN = 0.8f;
static const float ANGLE_VARIATION = 20;
static const float ANGLE_VARIATION_MAX_OFFSET = 30;
static const float BRUSH_SPEED = 5.0;
static const float OFFSET_SCALE = 1.5;

static const float PAINTING_MARGIN_PCT = 0.05;


PMBrushContainer::PMBrushContainer(string filename)
{
    brush = ofImage(filename);

    xOffset = 0;//-size*(brush.getWidth()/brush.getHeight())/2;
    yOffset = 0;//-size/2;
    generalOffset = 0;

    ofSeedRandom();
}

void PMBrushContainer::update()
{
    double angleInRadians = degreesToRadians(baseAngle);
    double cosAngle = cos(angleInRadians);
    double sinAngle = sin(angleInRadians);

    x += BRUSH_SPEED * cosAngle;
    y += BRUSH_SPEED * sinAngle;

    int viewWidth = ofGetWidth();
    int viewHeight = ofGetHeight();
    float margin = PAINTING_MARGIN_PCT * viewWidth;

    if (x > viewWidth - margin) x -= viewWidth - 2*margin;
    if (x < margin) x += (viewWidth - 2*margin);
    if (y > viewHeight - margin) y -= viewHeight - 2*margin;
    if (y < margin) y += viewHeight - 2*margin;

    xOffset = generalOffset * sinAngle * 100.0 * OFFSET_SCALE;
    yOffset = -generalOffset * cosAngle * 100.0 * OFFSET_SCALE;
}

void PMBrushContainer::draw()
{
    int halfSize = size >> 1;
//    ofPushMatrix();
//        ofTranslate(x , y);
//        ofRotate(baseAngle+90);
//        ofTranslate(halfSize, halfSize);
        brush.draw(x - halfSize + xOffset, y - halfSize + yOffset, size, size);
//        brush.draw(0,0, size, size);
//    ofPopMatrix();
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

void PMBrushContainer::changeBaseAngle()
{
    int sign = ofSign(ofRandom(-1, 1));
    if (sign == 0) sign = 1;
    baseAngle += sign * (ANGLE_VARIATION + ofRandom(ANGLE_VARIATION_MAX_OFFSET));
    baseAngle = ofWrapDegrees(baseAngle, -360, 360);
}

void PMBrushContainer::setOffset(float offset)
{
    generalOffset = offset;
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

void PMBrushContainer::changeDirection(float direction)
{
    baseAngle += direction*10;
    baseAngle = ofWrapDegrees(baseAngle, -360, 360);
}
