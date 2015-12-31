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
    PAINTER_CENTER = 4,
    PAINTER_NUM_ORIGINS
} PMPainterOrigin;

class PMRibbonPainter
{
public:

    PMRibbonPainter(ofColor color, float dx, float dy, float div, float ease, float easeRandom, unsigned int size, PMUICanvasRibbonRenderer *gui);

    void setup();
    void update();
    void draw();

    void setOrigin(PMPainterOrigin origin);
    void setPosition(int x, int y);
    void setX(int x);
    void setY(int y);
    void setColor(ofColor color);
    void setSize(unsigned int size);
    void setEase(float _ease) {ease = ofRandom(0.0f, 1.0f) * easeRandomness + _ease;};//{ ease = _ease + ofRandomuf()*easeRandomness; }
    void setEaseRandomness(float _randomnes) { easeRandomness = _randomnes; }
    void clear();

    ofPoint *getTargetPos() { return &targetPos; }
    vector<ofPoint> getVertices() {return vertices;};
    ofPolyline getPath()    {return path;};

private:

    float dx, dy;
    float ax, ay;
    float div;
    float ease;
    float easeRandomness;
    unsigned int size;

    ofPolyline path;

    ofPoint targetPos;
    int xMin, xMax, yMin, yMax;
    ofColor color;
    PMPainterOrigin origin;

    bool isNewPath;
    vector<ofPoint> vertices;
    vector<ofPoint> lastVertices;

    PMUICanvasRibbonRenderer *gui;
};

#endif //HARMONYFOROF_PMRIBBONPAINTER_H
