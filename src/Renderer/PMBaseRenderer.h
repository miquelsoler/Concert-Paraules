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
    RENDERERTYPE_UNDEFINED = -1,
    RENDERERTYPE_TYPOGRAPHY = 0,
    RENDERERTYPE_COLOR = 1,
    RENDERERTYPE_CURVES = 2,
    RENDERERTYPE_STILLIMAGE = 3,
    RENDERERTYPE_NUMRENDERERS = 3 // Still Image is not considerer a proper renderer
} PMRendererType;

typedef enum
{
    RENDERERSTATE_OFF = 0,       // Screen is cleared and nothing is rendered
    RENDERERSTATE_ON = 1,       // Listening to audio events and rendering
} PMRendererState;

class PMBaseRenderer
{
public:

    PMBaseRenderer(PMRendererType type);
    ~PMBaseRenderer();

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
    virtual void windowResized(ofResizeEventArgs& a);
    
    
    // SETTERS
    void setState(PMRendererState newState);
    virtual void switchStateOnOff();
    void setNeedsToBeCleared(bool _needsToBeCleared) { needsToBeCleared = _needsToBeCleared; };
    
    // GETTERS
    ofFbo*                      getFbo() { return &fbo; };
    PMRendererState             getState() { return state; };
    PMRendererType              getType() { return type; };
    bool                        getNeedsToBeCleared() { return needsToBeCleared; };
    ofColor                     getBackgroundColor();
    
    float getDeltaPitch()         { return pParams.deltaPitch; }
    float getDeltaEnergy()        { return eParams.deltaEnergy; }
    float getEnergyMin()          { return eParams.min; }
    float getEnergyMax()          { return eParams.max; }
    float getPitchMin()           { return pParams.min; }
    float getPitchMax()           { return pParams.max; }
    float getSmoothedPitch()      { return pParams.smoothedPitch; }
    float getSmoothedEnergy()     { return eParams.smoothedEnergy; }

    void showGUI(bool show);
    void clearFBOBackground(float r,float g,float b,float a);

protected:

    virtual void clear();

    PMRendererType          type;
    PMRendererState         state;

    ofFbo                   fbo;

    PMUICanvasBaseRenderer* gui;
    
    bool                    needsToBeCleared;
    
    bool                    isSilent;
    
    pitchParams             pParams;
    energyParams            eParams;
};


#endif //PMCONCERTPARAULES_PMBASERENDERER_H
