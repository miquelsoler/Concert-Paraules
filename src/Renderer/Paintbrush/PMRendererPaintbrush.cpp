//
// Created by Miquel Àngel Soler on 28/10/15.
//

#include "PMRendererPaintbrush.h"

//static ofColor tintColor = ofColor(200, 200, 0, 255);

//------------------------------------------------------------------------------------------
//PMRendererPaintbrush::PMRendererPaintbrush(unsigned int numInputs) : PMBaseRenderer(RENDERERTYPE_PAINTBRUSH, numInputs)
PMRendererPaintbrush::PMRendererPaintbrush() : PMBaseRenderer(RENDERERTYPE_PAINTBRUSH)
{
    brush = new PMBrushContainer("brushes/pinzell2.png");
    brush->setOrigin(PMBrushContainerOrigin(LEFT));
    brush->setSize(1);

    /// GUI
    gui = new PMUICanvasBrushRenderer(UI_RENDERERTYPE_PAINTBRUSH, "BRUSH_RENDERER",OFX_UI_FONT_MEDIUM);
    gui->init(100, 500, 200, 300);
}

//------------------------------------------------------------------------------------------
void PMRendererPaintbrush::setup()
{
    PMBaseRenderer::setup();
}

//------------------------------------------------------------------------------------------
void PMRendererPaintbrush::update()
{
    PMUICanvasBrushRenderer *myGUI = (PMUICanvasBrushRenderer *) gui;

//    if ((state == RENDERERSTATE_PAUSED) || (state == RENDERERSTATE_OFF)) return;
    if ( (state == RENDERERSTATE_OFF) ) return;

    brush->update();
    brush->setBounceWalls(myGUI->getBouncyWalls());
    brush->setColor(myGUI->getBrushColor());

    PMBaseRenderer::update();

    if (particles.size() == 0) {
        particles.push_back(PMParticle(brush->getPosition(), ofPoint(0, 0), brush->getImage()));
    } else {
        particles.push_back(PMParticle(brush->getPosition(), particles[particles.size() - 1].getPosition(), brush->getImage()));
    }

    if (particles.at(0).isDead()) {
        particles.pop_front();
    }

    for (int i = 0; i < particles.size(); i++) {
        particles[i].update();
        particles[i].setVelocity(myGUI->getParticleVelocity());
        particles[i].setLife(myGUI->getParticleLife());
        particles[i].setBounceWalls(myGUI->getBouncyWalls());
        particles[i].setColor(myGUI->getBrushColor());
    }
}

//------------------------------------------------------------------------------------------
void PMRendererPaintbrush::drawIntoFBO()
{
    fbo.begin();
    {
        ofFloatColor fc = ofFloatColor(1.0,1.0,1.0, gui->getBackgroundFade());
        ofSetColor(fc);

        ofDrawRectangle(0, 0, ofGetWidth(), ofGetHeight());

        ofEnableBlendMode(OF_BLENDMODE_ADD);

        if (state == RENDERERSTATE_ON) brush->draw();

        for (int i=0; i<particles.size(); i++){
            //particles[i].draw();
        }

        ofDisableBlendMode();
    }
    fbo.end();

    ofSetColor(255, 255, 255, 255);
}

//------------------------------------------------------------------------------------------
void PMRendererPaintbrush::changeBaseAngle()
{
    brush->changeBaseAngle();
}

//------------------------------------------------------------------------------------------
void PMRendererPaintbrush::setOffset(float offset)
{
    brush->setOffset(offset);
}


//------------------------------------------------------------------------------------------
void PMRendererPaintbrush::setPosition(float normalizedX, float normalizedY)
{
    brush->setPosition(normalizedX, normalizedY);
}

//------------------------------------------------------------------------------------------
void PMRendererPaintbrush::setPositionX(float normalizedX)
{
    brush->setPositionX(normalizedX);
}

//------------------------------------------------------------------------------------------
void PMRendererPaintbrush::setPositionY(float normalizedY)
{
    brush->setPositionY(normalizedY);
}

//------------------------------------------------------------------------------------------
void PMRendererPaintbrush::setSize(float normalizedSize)
{
    brush->setSize(normalizedSize);
}

//------------------------------------------------------------------------------------------
void PMRendererPaintbrush::changeDirection(float direction)
{
    brush->changeDirection(direction);
}

//------------------------------------------------------------------------------------------
void PMRendererPaintbrush::vibrate(float hasToVibrate)
{
    if(hasToVibrate){
        for (int i=0; i<particles.size(); i++){
            PMUICanvasBrushRenderer *myGUI = (PMUICanvasBrushRenderer *)gui;

            particles[i].setVelocity(ofRandom(myGUI->getParticleVelocity()-0.5f, myGUI->getParticleVelocity()));
        }
    }
}

//------------------------------------------------------------------------------------------
void PMRendererPaintbrush::pitchChanged(pitchParams pitchParams)
{
    PMBaseRenderer::pitchChanged(pitchParams);
    
    //            float pitch = ofMap(pitchParams.midiNote, audioAnalyzersSettings->getMinPitchMidiNote(), audioAnalyzersSettings->getMaxPitchMidiNote(), minOffset, maxOffset, true);
    //            paintbrushRenderer->changeDirection(pitchParams.audioInputIndex, pitchParams.midiPitchDivengence);
    setPositionY(gui->getSmoothedPitch());

}

//------------------------------------------------------------------------------------------
void PMRendererPaintbrush::energyChanged(energyParams energyParams)
{
    PMBaseRenderer::energyChanged(energyParams);
    
    PMRendererPaintbrush *paintbrushRenderer = (PMRendererPaintbrush *)gui;
    paintbrushRenderer->setSize(0.001);
}

