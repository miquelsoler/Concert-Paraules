//
// Created by Miquel �ngel Soler on 15/12/15.
//

#ifndef HARMONYFOROF_PMRIBBONPAINTER_H
#define HARMONYFOROF_PMRIBBONPAINTER_H

#include "ofMain.h"


class PMRibbonPainter
{
public:

    PMRibbonPainter(ofColor color, float dx, float dy, float div, float ease, unsigned int size);

    void setup();
    void update();
    void draw();

    void setPosition(int x, int y);
    void setX(int x);
    void setY(int y);
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

    ofPath path;
    ofColor color;

    bool isNewPath;
};

#endif //HARMONYFOROF_PMRIBBONPAINTER_H
