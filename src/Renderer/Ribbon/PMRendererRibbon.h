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
    virtual void pitchChanged(pitchParams pitchParams);
    virtual void energyChanged(energyParams energyParams);
    virtual void silenceStateChanged(silenceParams &silenceParams);

    void setPosition(int x, int y);
    void setX(int x);
    void setY(int y);

    void strokeStarted();
    void strokeEnded();

    // TODO: Remove mouse events code once audio events are working
    void mouseDragged(int x, int y, int button);
    void mousePressed(int x, int y, int button);
    void mouseReleased(int x, int y, int button);

    virtual void switchStateOnOff();

private:

    PMUICanvasRibbonRenderer *myGUI;

    vector<PMRibbonPainter> painters;

    ofPoint position;

    int mode;
    unsigned int numPainters;
    unsigned int strokeWidth;
    unsigned int ribbonColorR, ribbonColorG, ribbonColorB;
    float divisions;

    bool isInStroke;

    bool isSilent;

    void buildPainters();
    void getGUIData();
};


#endif //PMCONCERTPARAULES_PMRENDERERRIBBON_H
