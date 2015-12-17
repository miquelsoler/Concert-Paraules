//
// Created by Miquel Ëngel Soler on 15/12/15.
//

#include "PMRibbonPainter.h"

PMRibbonPainter::PMRibbonPainter(ofColor _color, float _dx, float _dy, float _ax, float _ay, float _div, float _ease)
{
    color = ofColor(_color.r, _color.g, _color.b, _color.a);

    // FIXME: Why adding a color that is not black (color = ofColor(1,1,1,255)) tends to set alpha to zero???
    color = ofColor(0,0,0);
    dx = _dx; dy = _dy;
    ax = _ax; ay = _ay;
    div = _div;
    ease = _ease;

    path.setMode(ofPath::POLYLINES);
    path.setStrokeColor(color);
    path.setFilled(false);
    path.setStrokeWidth(1);

    isNewPath = true;
}

void PMRibbonPainter::setup()
{
    isNewPath = true;
}

void PMRibbonPainter::update()
{
    if ((dx != targetPos.x) && (dy != targetPos.y))
    {
        path.moveTo(dx, dy);
        if (isNewPath) return;

        dx -= ax = (ax + (dx - targetPos.x) * div) * ease;
        dy -= ay = (ay + (dy - targetPos.y) * div) * ease;

        path.lineTo(dx, dy);
    }
}

void PMRibbonPainter::draw()
{
    if (isNewPath) return;

    ofEnableBlendMode(OF_BLENDMODE_ADD);
    path.draw();
    ofDisableBlendMode();
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

void PMRibbonPainter::setColor(ofColor _color)
{
    color = ofColor(_color.r, _color.g, _color.b, _color.a);
    path.setStrokeColor(color);
}

void PMRibbonPainter::clear()
{
    path.clear();

    path = ofPath();

    path.setMode(ofPath::POLYLINES);
    path.setStrokeColor(color);
    path.setFilled(false);
    path.setStrokeWidth(1);

    isNewPath = true;
}
