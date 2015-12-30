//
// Created by Miquel Àngel Soler on 16/12/15.
//

#ifndef PMCONCERTPARAULES_PMRENDERERRIBBON_H
#define PMCONCERTPARAULES_PMRENDERERRIBBON_H

#pragma once

#include "PMBaseRenderer.h"
#include "PMRibbonPainter.h"
#include "PMUICanvasRibbonRenderer.h"


class PMRendererRibbon : public PMBaseRenderer
{
public:

    PMRendererRibbon();

    virtual void setup();
    virtual void update();
    virtual void drawIntoFBO();

    void rebuildPainters();

    virtual void pitchChanged(pitchParams pitchParams);
    virtual void energyChanged(energyParams energyParams);
    virtual void silenceStateChanged(silenceParams &silenceParams);

    void setPosition(int x, int y);
    void setX(int x);
    void setY(int y);

    void strokeStarted();
    void strokeEnded();

    void mouseDragged(int x, int y, int button);
    void mousePressed(int x, int y, int button);
    void mouseReleased(int x, int y, int button);

    virtual void switchStateOnOff();

private:

    PMUICanvasRibbonRenderer *myGUI;

    vector<PMRibbonPainter> painters;

    int mode;

    // Painter positioning
    ofPoint position;
    int xMin, xMax, yMin, yMax;
    bool didReachBorder;
    int offsetSign;

    // Ease
    float lastEase;

    // Colors
    unsigned int numPainters;
    unsigned int strokeWidth;
    unsigned int ribbonColorR, ribbonColorG, ribbonColorB;
    float gradientPosition;
    bool gradientReverse;

    // Mode 3
    float pitchLastTime;
    float lastPitch;
    float m3offsetX, m3offsetY;

    // Others
    float divisions;
    bool isInStroke;
    bool isSilent;

    void addOffsetToPosition(float xOffset, float yOffset);
    void getGUIData();
};


#endif //PMCONCERTPARAULES_PMRENDERERRIBBON_H
