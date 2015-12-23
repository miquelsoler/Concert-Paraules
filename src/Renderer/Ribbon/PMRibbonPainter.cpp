//
// Created by Miquel �ngel Soler on 15/12/15.
//

#include "PMRibbonPainter.h"

static const float MIN_ORIGIN = 0.2f;
static const float MAX_ORIGIN = 0.8f;
static const float PAINTER_SPEED = 5.0;

PMRibbonPainter::PMRibbonPainter(ofColor _color, float _dx, float _dy, float _div, float _ease, unsigned int size)
{
    // FIXME: Why adding a color that is not black (color = ofColor(1,1,1,255)) tends to set alpha to zero???
    color = ofColor(_color.r, _color.g, _color.b, _color.a);

    dx = _dx; dy = _dy;
    ax = ay = 0.0f;
    div = _div;
    ease = _ease;
    setSize(size);

//    path.setStrokeColor(color);
//    path.setFilled(false);
//    path.setMode(ofPath::POLYLINES);

    isNewPath = true;
}

void PMRibbonPainter::setup()
{
    isNewPath = true;
}

void PMRibbonPainter::update()
{
    int newX = int(targetPos.x + PAINTER_SPEED);
    if (newX > ofGetWidth() - 2)
    {
        clear();
        newX = 1;
    }
    setX(newX);

    cout << "newX=" << newX << endl;

    if ((dx != targetPos.x) && (dy != targetPos.y))
    {
        if (isNewPath) return;

        dx -= ax = (ax + (dx - targetPos.x) * div) * ease;
        dy -= ay = (ay + (dy - targetPos.y) * div) * ease;

        path.curveTo(dx, dy);
    }
}

void PMRibbonPainter::draw()
{
    if (isNewPath) return;

    ofEnableBlendMode(OF_BLENDMODE_ALPHA);
    ofSetColor(color);
    ofSetLineWidth(size);
    path.draw();
    ofDisableBlendMode();
}

void PMRibbonPainter::setOrigin(PMPainterOrigin origin)
{
    ofSeedRandom(rand());
    float randomNormalizedPos = ofRandom(MIN_ORIGIN, MAX_ORIGIN);

    switch (origin)
    {
        case PAINTER_LEFT:
        {
            setX(1);
            setY(int(randomNormalizedPos * float(ofGetHeight())));
            break;
        }
        case PAINTER_RIGHT:
        {
            setX(ofGetWidth()-2);
            setY(int(randomNormalizedPos * float(ofGetHeight())));
            break;
        }
        case PAINTER_UP:
        {
            setX(int(randomNormalizedPos * float(ofGetWidth())));
            setY(1);
            break;
        }
        case PAINTER_DOWN:
        {
            setX(int(randomNormalizedPos * float(ofGetWidth())));
            setY(ofGetHeight()-2);
            break;
        }
        default: break;
    }
}

void PMRibbonPainter::setPosition(int x, int y)
{
    targetPos = ofPoint(x, y);

    if (isNewPath)
    {
        dx = targetPos.x;
        dy = targetPos.y;
        isNewPath = false;
        return;
    }
}

void PMRibbonPainter::setX(int x)
{
    setPosition(x, int(targetPos.y));
}

void PMRibbonPainter::setY(int y)
{
    setPosition(int(targetPos.x), y);
}

void PMRibbonPainter::setColor(ofColor _color)
{
    color = ofColor(_color.r, _color.g, _color.b, _color.a);
//    path.setStrokeColor(color);
}

void PMRibbonPainter::setSize(unsigned int _size)
{
    size = _size;
//    path.setStrokeWidth(size);
}

void PMRibbonPainter::clear()
{
    path.clear();

    path = ofPolyline();

//    path = ofPath();
//
//    path.setMode(ofPath::POLYLINES);
//    path.setStrokeColor(color);
//    path.setFilled(false);
//    path.setStrokeWidth(size);

    isNewPath = true;
}
