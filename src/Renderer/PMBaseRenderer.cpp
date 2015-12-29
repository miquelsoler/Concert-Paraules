//
// Created by Miquel Àngel Soler on 28/10/15.
//

#include "PMBaseRenderer.h"

PMBaseRenderer::PMBaseRenderer(PMRendererType _type)
{
    fbo.allocate(ofGetWidth(), ofGetHeight(), GL_RGBA32F_ARB, 4);

    type = _type;
    needsToBeCleared = false;
    isSilent = false;
}

void PMBaseRenderer::setup()
{
    fbo.begin();
    {
        // Often the FBO will contain artifacts from the memory that the graphics card has just allocated for it,
        // so it's good to clear it before starting to draw it
        ofClear(0, 0, 0, 0);
    }
    fbo.end();

    state = RENDERERSTATE_OFF;
}

void PMBaseRenderer::clearFBOBackground(float r,float g,float b,float a)
{
//    fbo.begin();
//    {

    if(a<1.0f)
    {
//        // background dimming
        ofFloatColor fc = ofFloatColor(r,g,b,a);
        ofSetColor(fc);
        //ofEnableBlendMode(OF_BLENDMODE_ALPHA);
        ofDrawRectangle(0, 0, fbo.getWidth(), fbo.getHeight());
    }
    else
    {
        ofClear(r,g,b);
    }
//    }
//    fbo.end();
}

void PMBaseRenderer::update()
{
    //drawIntoFBO();
}

void PMBaseRenderer::draw()
{
    drawIntoFBO();
    
    if (needsToBeCleared) {
        needsToBeCleared = false;
        clear();
    }

    // set background for base renderer
    ofColor c = ofColor(gui->getBackgroundColor().r, gui->getBackgroundColor().g, gui->getBackgroundColor().b, 255);
    ofClear(c);
    //ofBackground(gui->getBackgroundColor().r, gui->getBackgroundColor().g, gui->getBackgroundColor().b);

    // Skip FBO drawing if renderer is off
    if (state == RENDERERSTATE_OFF) return;

    // draw the fbo with contents to screen
    fbo.draw(0, 0);
}

void PMBaseRenderer::setState(PMRendererState newState)
{
    if (newState == state) return;

    switch(state) // Different behavior according to current state and new state
    {
        case RENDERERSTATE_ON: {
            if (newState == RENDERERSTATE_OFF) setNeedsToBeCleared(true);
            state = newState;
            break;
        }
//        case RENDERERSTATE_PAUSED: {
//            if (newState == RENDERERSTATE_OFF) setNeedsToBeCleared(true);
//            if (newState == RENDERERSTATE_ON) setNeedsToBeCleared(false);
//            state = newState;
//            break;
//        }
        case RENDERERSTATE_OFF: {
            if (newState == RENDERERSTATE_ON)
                state = newState;
            break;
        }
    }
}

void PMBaseRenderer::switchStateOnOff()
{
    switch(state)
    {
        case RENDERERSTATE_ON:
//        case RENDERERSTATE_PAUSED:
        setState(RENDERERSTATE_OFF);
            break;
        case RENDERERSTATE_OFF:
            setState(RENDERERSTATE_ON);
            break;
    }
}

void PMBaseRenderer::clear()
{
    fbo.begin();
        clearFBOBackground(float(gui->getBackgroundColor().r) / 255.0f,float(gui->getBackgroundColor().g) / 255.0f,float(gui->getBackgroundColor().b) / 255.0f,1.0f);
    fbo.end();
    
}

void PMBaseRenderer::showGUI(bool show)
{
    gui->setVisible(show);
}


void PMBaseRenderer::pitchChanged(pitchParams pitchParams)
{
    float deltaPitch = gui->getDeltaPitch();
    float currentPitch = pitchParams.midiNote;
    float smoothedPitch = (deltaPitch) * currentPitch + (1.0 - deltaPitch) * oldPitch;

    gui->setSmoothPitch(ofMap(smoothedPitch, gui->getPitchMin(), gui->getPitchMax(), 0.0, 1.0, true));

    oldPitch = smoothedPitch;
}

void PMBaseRenderer::energyChanged(energyParams energyParams)
{
    float deltaEnergy = gui->getDeltaEnergy();
    float currentEnergy = energyParams.energy;
    float smoothedEnergy = (deltaEnergy) * currentEnergy + (1.0 - deltaEnergy) * oldEnergy;

    gui->setSmoothEnergy(ofMap(smoothedEnergy, gui->getEnergyMin(), gui->getEnergyMax(), 0.0, 1.0, true));
    oldEnergy = smoothedEnergy;
}

void PMBaseRenderer::silenceStateChanged(silenceParams &silenceParams)
{
    isSilent = silenceParams.isSilent;
}

void PMBaseRenderer::pauseStateChanged(pauseParams &pauseParams)
{
//    if (pauseParams.isPaused)
//        setState(RENDERERSTATE_PAUSED);
//    else
//        setState(RENDERERSTATE_ON);
}

ofColor PMBaseRenderer::getBackgroundColor()
{
    return gui->getBackgroundColor();
}
