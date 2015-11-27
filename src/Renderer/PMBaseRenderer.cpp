//
// Created by Miquel Àngel Soler on 28/10/15.
//

#include "PMBaseRenderer.h"

PMBaseRenderer::PMBaseRenderer(PMRendererType _type)
{
    fbo.allocate(ofGetWidth(), ofGetHeight(), GL_RGBA32F_ARB);

    type = _type;
//    numInputs = _numInputs;
    needsToBeCleared = false;
    isSilent = false;
    isPaused = false;

    /// GUI
//    gui = new PMUICanvasBaseRenderer("GUI BASE RENDERER",OFX_UI_FONT_MEDIUM);
//    gui->init(100, 500, 200, 300);
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

    enabled = false;
//    enabled.assign(numInputs, false); // Init all elements with false; FIXME: is it to false or true?
}

void PMBaseRenderer::update()
{
    fbo.begin();
    {
        // background dimming
        ofFloatColor fc = ofFloatColor(0.0, 0.0, 0.0, gui->getFadeBackground());
        //ofFloatColor fc = ofFloatColor(gui->getColorBackground().r,gui->getColorBackground().g,gui->getColorBackground().b,gui->getFadeBackground());
        ofSetColor(fc);

        ofEnableBlendMode(OF_BLENDMODE_ALPHA);
        ofDrawRectangle(0, 0, fbo.getWidth(), fbo.getHeight());
    }
    fbo.end();

    drawIntoFBO();
}

void PMBaseRenderer::draw()
{
    if (needsToBeCleared) {
        needsToBeCleared = false;
        clear();
    }

//    ofClear(255, 255, 255, 255);
//    fbo.draw(0, 0);

    // set background for base renderer
    ofColor c = ofColor(gui->getColorBackground().r, gui->getColorBackground().g, gui->getColorBackground().b, 255);
    ofClear(c);

    // draw the fbo with contents to screen
    fbo.draw(0, 0);

    // draw gui of base renderer
    //gui->draw();
}

bool PMBaseRenderer::getNeedsToBeCleared()
{
    return needsToBeCleared;
}

void PMBaseRenderer::setNeedsToBeCleared(bool _b)
{
    needsToBeCleared = _b;
}

void PMBaseRenderer::clear()
{
    ofClear(0, 0, 0, 0);

    fbo.begin();
    {
        // Often the FBO will contain artifacts from the memory that the graphics card has just allocated for it,
        // so it's good to clear it before starting to draw it
        ofClear(0, 0, 0, 0);
    }
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
    isPaused = pauseParams.isPaused;
}
