//
// Created by Miquel Àngel Soler on 28/10/15.
//

#include "PMRendererPaintbrush.h"

//static ofColor tintColor = ofColor(200, 200, 0, 255);

//------------------------------------------------------------------------------------------
PMRendererPaintbrush::PMRendererPaintbrush(unsigned int numInputs) : PMBaseRenderer(RENDERERTYPE_PAINTBRUSH, numInputs)
{
    for (int i=0; i<numInputs; ++i)
    {
        PMBrushContainer *brush = new PMBrushContainer("brushes/pinzell2.png");
        brush->setOrigin(PMBrushContainerOrigin(i % NUM_ORIGINS));
        brush->setSize(1);
        brushes.push_back(brush);
    }
    
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
    PMUICanvasBrushRenderer *myGUI = (PMUICanvasBrushRenderer *)gui;

    for (int i=0; i<numInputs; ++i)
    {
        if (!isActive[i]) continue;

        brushes[i]->update();
        brushes[i]->setBounceWalls(myGUI->getBouncyWalls());
        brushes[i]->setColor(myGUI->getBrushColor());
    }
    PMBaseRenderer::update();
    
    if(particles.size()==0){
        particles.push_back(PMParticle(brushes[0]->getPosition(), ofPoint(0,0), brushes[0]->getImage()));
    }else{
        particles.push_back(PMParticle(brushes[0]->getPosition(), particles[particles.size()-1].getPosition(), brushes[0]->getImage()));
    }
    
    if(particles.at(0).isDead()){
        particles.pop_front();
    }
    
    for (int i=0; i<particles.size(); i++){
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
        ofFloatColor fc = ofFloatColor(1.0,1.0,1.0, gui->getFadeBackground());
        ofSetColor(fc);

        ofDrawRectangle(0, 0, ofGetWidth(), ofGetHeight());

        ofEnableBlendMode(OF_BLENDMODE_ADD);

        for (int i=0; i<numInputs; ++i)
        {
            if (!isActive[i]) continue;

//                    ofSetColor(tintColor);
            brushes[i]->draw();
        }

        for (int i=0; i<particles.size(); i++){
            particles[i].draw();
        }

        ofDisableBlendMode();
    }
    fbo.end();

    ofSetColor(255, 255, 255, 255);
}

//------------------------------------------------------------------------------------------
void PMRendererPaintbrush::changeBaseAngle(unsigned int inputIndex)
{
    brushes[inputIndex]->changeBaseAngle();
}

//------------------------------------------------------------------------------------------
void PMRendererPaintbrush::setOffset(unsigned int inputIndex, float offset)
{
    brushes[inputIndex]->setOffset(offset);
}


//------------------------------------------------------------------------------------------
void PMRendererPaintbrush::setPosition(unsigned int inputIndex, float normalizedX, float normalizedY)
{
    brushes[inputIndex]->setPosition(normalizedX, normalizedY);
}

//------------------------------------------------------------------------------------------
void PMRendererPaintbrush::setPositionX(unsigned int inputIndex, float normalizedX)
{
    brushes[inputIndex]->setPositionX(normalizedX);
}

//------------------------------------------------------------------------------------------
void PMRendererPaintbrush::setPositionY(unsigned int inputIndex, float normalizedY)
{
    brushes[inputIndex]->setPositionY(normalizedY);
}

//------------------------------------------------------------------------------------------
void PMRendererPaintbrush::setSize(unsigned int inputIndex, float normalizedSize)
{
    //brushes[inputIndex]->setSize(normalizedSize);
}

//------------------------------------------------------------------------------------------
void PMRendererPaintbrush::changeDirection(unsigned int inputIndex, float direction)
{
    brushes[inputIndex]->changeDirection(direction);
}

//------------------------------------------------------------------------------------------
void PMRendererPaintbrush::vibrate(unsigned int inputIndex, float hasToVibrate)
{
    if(hasToVibrate){
        for (int i=0; i<particles.size(); i++){
            PMUICanvasBrushRenderer *myGUI = (PMUICanvasBrushRenderer *)gui;

            particles[i].setVelocity(ofRandom(myGUI->getParticleVelocity()-0.5, myGUI->getParticleVelocity()));
        }
    }
}

//------------------------------------------------------------------------------------------
void PMRendererPaintbrush::pitchChanged(pitchParams pitchParams)
{
    PMBaseRenderer::pitchChanged(pitchParams);
    
    //            float pitch = ofMap(pitchParams.midiNote, audioAnalyzersSettings->getMinPitchMidiNote(), audioAnalyzersSettings->getMaxPitchMidiNote(), minOffset, maxOffset, true);
    //            paintbrushRenderer->changeDirection(pitchParams.audioInputIndex, pitchParams.midiPitchDivengence);
    setPositionY(pitchParams.audioInputIndex,gui->getSmoothedPitch());

}

//------------------------------------------------------------------------------------------
void PMRendererPaintbrush::energyChanged(energyParams energyParams)
{
    PMBaseRenderer::energyChanged(energyParams);
    
    PMRendererPaintbrush *paintbrushRenderer = (PMRendererPaintbrush *)gui;
    paintbrushRenderer->setSize(energyParams.audioInputIndex,gui->getSmoothedEnergy());
}

