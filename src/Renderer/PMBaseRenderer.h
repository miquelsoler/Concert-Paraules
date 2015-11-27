//
// Created by Miquel Àngel Soler on 28/10/15.
//

#ifndef PMCONCERTPARAULES_PMBASERENDERER_H
#define PMCONCERTPARAULES_PMBASERENDERER_H

#pragma once

#include "ofMain.h"
#include "PMUICanvasBaseRenderer.h"
#include "PMAudioAnalyzer.hpp"


typedef enum
{
    RENDERERTYPE_PAINTBRUSH = 0,
    RENDERERTYPE_TYPOGRAPHY = 1,
    RENDERERTYPE_COLOR = 2
} PMRendererType;

class PMBaseRenderer
{
public:

    PMBaseRenderer(PMRendererType type, unsigned int numInputs);

    virtual void setup();
    virtual void update();
    virtual void draw();
    virtual void clear();

    virtual void drawIntoFBO() = 0;

    // SETTERS
    void setShouldPaint(unsigned int inputIndex, bool shouldPaint);
    void setNeedsToBeCleared(bool _b);
    
    // GETTERS
    ofFbo*          getFbo(){return &fbo;};
    PMRendererType  getType() { return type; };
    bool            getNeedsToBeCleared();
    
    void showGUI(bool show);
    
    // changed ...
    virtual void pitchChanged(pitchParams pitchParams);
    virtual void energyChanged(energyParams energyParams);
    virtual void silenceStateChanged(silenceParams &silenceParams);
    virtual void pauseStateChanged(pauseParams &pauseParams);


protected:

    PMRendererType          type;

    unsigned int            numInputs;  // Number of microphones
    vector<bool>            isActive;   // Enable/disable painting per input

    ofFbo                   fbo;

    PMUICanvasBaseRenderer* gui;
    
    bool                    needsToBeCleared;
    
    // audio smoothing
    float                   oldPitch;
    float                   oldEnergy;
    
    bool                    isSilent;
    bool                    isPaused;
};


#endif //PMCONCERTPARAULES_PMBASERENDERER_H
