//
// Created by Miquel �ngel Soler on 15/12/15.
//

#ifndef HARMONYFOROF_PMRIBBONPAINTER_H
#define HARMONYFOROF_PMRIBBONPAINTER_H

#include "ofMain.h"
#include "PMUICanvasRibbonRenderer.h"

typedef enum
{
    PAINTER_LEFT = 0,
    PAINTER_RIGHT = 1,
    PAINTER_UP = 2,
    PAINTER_DOWN = 3,
    PAINTER_NUM_ORIGINS
} PMPainterOrigin;

class PMRibbonPainter
{
public:

    PMRibbonPainter(ofColor color, float dx, float dy, float div, float ease, unsigned int size, PMUICanvasRibbonRenderer *gui);

    void setup();
    void update();
    void draw();

    void setOrigin(PMPainterOrigin origin);
    void setPosition(int x, int y);
    void setX(int x);
    void setY(int y);
    void addOffsetToPosition(float xOffset, float yOffset);
    void setColor(ofColor color);
    void setSize(unsigned int size);
    void clear();

private:

    float dx, dy;
    float ax, ay;
    float div;
    float ease;
    unsigned int size;

    ofPoint targetPos;

    ofPolyline path;
    ofColor color;

    bool isNewPath;

    PMUICanvasRibbonRenderer *gui;
};

#endif //HARMONYFOROF_PMRIBBONPAINTER_H
