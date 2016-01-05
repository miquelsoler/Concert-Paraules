//
// Created by Miquel �ngel Soler on 15/12/15.
//

#ifndef HARMONYFOROF_PMCURVESPAINTER_H
#define HARMONYFOROF_PMCURVESPAINTER_H

#include "ofMain.h"
#include "PMUICanvasCurvesRenderer.h"
#include "ofxVectorGraphics.h"

class PMCurvesPainter
{
public:

    PMCurvesPainter(PMUICanvasCurvesRenderer *gui);

    void setup();
    void update();
    void draw();
    void clear();
    
    void setColor(ofColor _color);
    void setPosition(int x,int y);
    
private:

    // VARS
    ofxVectorGraphics vec;
    ofPoint lineDirection;
    ofPoint turnDirection;
    ofColor color;
    
    vector<ofPoint> points;
    
    int mode ;
    float posX;
    float posY;
    
    void controlBounds(ofPoint p);

    PMUICanvasCurvesRenderer *gui;
};

#endif //HARMONYFOROF_PMCURVESPAINTER_H
