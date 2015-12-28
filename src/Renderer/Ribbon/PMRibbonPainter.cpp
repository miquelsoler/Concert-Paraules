//
// Created by Miquel �ngel Soler on 15/12/15.
//

#include "PMRibbonPainter.h"

static const int POS_MARGIN = 1;

#define DRAW_PATH false

PMRibbonPainter::PMRibbonPainter(ofColor _color, float _dx, float _dy, float _div, float _ease, unsigned int size, PMUICanvasRibbonRenderer *_gui)
{
    
    // FIXME: Why adding a color that is not black (color = ofColor(1,1,1,255)) tends to set alpha to zero???
    color = ofColor(_color.r, _color.g, _color.b, _color.a);

    dx = _dx; dy = _dy;
    ax = ay = 0.0f;
    div = _div;
    ease = _ease;
    setSize(size);

    isNewPath = true;

    gui = _gui;

    xMin = POS_MARGIN;
    xMax = ofGetWidth() - POS_MARGIN - 1;
    yMin = POS_MARGIN;
    yMax = ofGetHeight() - POS_MARGIN - 1;
}

void PMRibbonPainter::setup()
{
    isNewPath = true;
    offsetSign = 1;
}

void PMRibbonPainter::update()
{
    if ((dx != targetPos.x) && (dy != targetPos.y))
    {
        if (isNewPath) return;

        dx -= ax = (ax + (dx - targetPos.x) * div) * ease;
        dy -= ay = (ay + (dy - targetPos.y) * div) * ease;

        // Clean-up path vertices in case its size is higher than the allowed maximum.
        {
            int maxNumVertices = gui->getPathNumVertices();
            vector<ofPoint> vertices = path.getVertices();
            if (vertices.size() > maxNumVertices)
            {
                path.clear();
                path.addVertex(vertices[vertices.size()-1]);
            }
        }

        path.curveTo(dx, dy);
    }
}

void PMRibbonPainter::draw()
{
    if (isNewPath) return;

    ofEnableBlendMode(OF_BLENDMODE_ALPHA);
    ofSetColor(color);
    ofSetLineWidth(size);

#if (DRAW_PATH == true)
    path.draw();
#else
    vector<ofPoint> vertices = path.getVertices();
    if (vertices.size() > 1)
    {
        for (int i=0; i<vertices.size()-1; ++i)
        {
            ofSetColor(color);
//            ofColor color = gui->getGradientColor(gui->getGradientId(), )
//            ofSetColor(color);
            ofDrawLine(vertices[i], vertices[i+1]);
        }
    }
#endif
    ofDisableBlendMode();
     
}

void PMRibbonPainter::setOrigin(PMPainterOrigin _origin)
{
    origin = _origin;

    switch (origin)
    {
        case PAINTER_LEFT:
        {
            setX(xMin);
            setY(ofGetHeight() / 2);
            break;
        }
        case PAINTER_RIGHT:
        {
            setX(xMax);
            setY(ofGetHeight() / 2);
            break;
        }
        case PAINTER_UP:
        {
            setX(ofGetWidth() / 2);
            setY(yMin);
            break;
        }
        case PAINTER_DOWN:
        {
            setX(ofGetWidth() / 2);
            setY(yMax);
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

void PMRibbonPainter::addOffsetToPosition(float xOffset, float yOffset)
{
    bool bounces = gui->getBounceEnabled();

    // X offset
    {
        int newX = int(targetPos.x + (xOffset * offsetSign));
        if (newX > xMax)
        {
            if (!bounces) {
                clear();
                newX = xMin;
            } else {
                offsetSign = -1;
                newX = xMax;
            }
        }
        else if (newX < xMin)
        {
            if (!bounces) {
                clear();
                newX = xMax;
            } else {
                offsetSign = 1;
                newX = xMin;
            }
        }

        setX(newX);
    }

    // Y offset
    {
        int newY = int(targetPos.y + (yOffset * offsetSign));
        if (newY > yMax)
        {
            if (!bounces) {
                clear();
                newY = yMin;
            } else {
                offsetSign = -1;
                newY = yMax;
            }
        }
        else if (newY < 1)
        {
            if (!bounces) {
                clear();
                newY = yMax;
            } else {
                offsetSign = 1;
                newY = yMin;
            }
        }

        setY(newY);
    }
}

void PMRibbonPainter::setColor(ofColor _color)
{
    color = ofColor(_color.r, _color.g, _color.b, _color.a);
}

void PMRibbonPainter::setSize(unsigned int _size)
{
    size = _size;
}

void PMRibbonPainter::clear()
{
    path.clear();
    path = ofPolyline();

    isNewPath = true;
}
