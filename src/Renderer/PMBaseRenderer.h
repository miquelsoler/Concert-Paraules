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
    RENDERERTYPE_COLOR = 2,
    RENDERERTYPE_RIBBON = 3,
    RENDERERTYPE_TEXTBOX = 4
} PMRendererType;

typedef enum
{
    RENDERERSTATE_ON = 0,       // Listening to audio events and rendering
    RENDERERSTATE_PAUSED = 1,   // Listening to audio events but not rendering
    RENDERERSTATE_OFF = 2       // Screen is cleared and nothing is rendered
} PMRendererState;

class PMBaseRenderer
{
public:

    PMBaseRenderer(PMRendererType type);

    virtual void setup();
    virtual void update();
    virtual void draw();
    virtual void drawIntoFBO() = 0;
    // Audio events
    virtual void pitchChanged(pitchParams pitchParams);
    virtual void energyChanged(energyParams energyParams);
    virtual void silenceStateChanged(silenceParams &silenceParams);
    virtual void pauseStateChanged(pauseParams &pauseParams);
    // Mouse events (only to be implemented in subclasses when really needed)
    virtual void mouseDragged(int x, int y, int button) {};
    virtual void mousePressed(int x, int y, int button) {};
    virtual void mouseReleased(int x, int y, int button) {};
    
    virtual void keyPressed ( ofKeyEventArgs& eventArgs );

    
    // SETTERS
    void setState(PMRendererState newState);
    virtual void switchStateOnOff();
    void setNeedsToBeCleared(bool _needsToBeCleared) { needsToBeCleared = _needsToBeCleared; };
    
    // GETTERS
    ofFbo*          getFbo() { return &fbo; };
    PMRendererState getState() { return state; };
    PMRendererType  getType() { return type; };
    bool            getNeedsToBeCleared() { return needsToBeCleared; };
    ofColor         getBackgroundColor();
    
    void showGUI(bool show);
    void clearFBOBackground(float r,float g,float b,float a);

protected:

    virtual void clear();

    PMRendererType          type;
    PMRendererState         state;

    ofFbo                   fbo;

    PMUICanvasBaseRenderer* gui;
    
    bool                    needsToBeCleared;
    
    // audio smoothing
    float                   oldPitch;
    float                   oldEnergy;
    
    bool                    isSilent;
};


#endif //PMCONCERTPARAULES_PMBASERENDERER_H
