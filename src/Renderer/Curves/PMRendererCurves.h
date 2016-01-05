//
// Created by Miquel Àngel Soler on 16/12/15.
//

#ifndef PMCONCERTPARAULES_PMRENDERERCURVES_H
#define PMCONCERTPARAULES_PMRENDERERCURVES_H

#pragma once

#include "PMBaseRenderer.h"
#include "PMCurvesPainter.h"
#include "PMUICanvasCurvesRenderer.h"


class PMRendererCurves : public PMBaseRenderer
{
public:

    PMRendererCurves();

    virtual void setup();
    virtual void update();
    virtual void drawIntoFBO();

    virtual void pitchChanged(pitchParams pitchParams);
    virtual void energyChanged(energyParams energyParams);
    virtual void silenceStateChanged(silenceParams &silenceParams);

    void mouseDragged(int x, int y, int button);
    void mousePressed(int x, int y, int button);
    void mouseReleased(int x, int y, int button);

    virtual void switchStateOnOff();

private:

    float gradientPosition;
    bool gradientReverse;
    int offsetSign;

    PMUICanvasCurvesRenderer *myGUI;

    vector<PMCurvesPainter> painters;
};


#endif //PMCONCERTPARAULES_PMRENDERERCURVES_H
