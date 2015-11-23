//
// Created by Miquel Àngel Soler on 28/10/15.
//

#include "PMRendererPaintbrush.h"

static ofColor tintColor = ofColor(200, 200, 0, 255);

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
    guiBaseRenderer = new PMUICanvasBrushRenderer("BRUSH_RENDERER",OFX_UI_FONT_MEDIUM);
    guiBaseRenderer->init(100, 500, 200, 300);

}

void PMRendererPaintbrush::setup()
{
    PMBaseRenderer::setup();
    
     canvasBrushRenderer = dynamic_cast<PMUICanvasBrushRenderer *> (guiBaseRenderer);
}

void PMRendererPaintbrush::update()
{
    for (int i=0; i<numInputs; ++i)
    {
        if (!isActive[i]) continue;

        brushes[i]->update();
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
    }
}

void PMRendererPaintbrush::drawIntoFBO()
{
    fbo.begin();
    {
//        switch (canvasBrushRenderer->getMode()){
//            case 1:
//                ofFloatColor fc = ofFloatColor(1.0,1.0,1.0,guiBaseRenderer->getFadeBackground());
//                //ofColor fc = ofColor(guiBaseRenderer->getColorBackground().r,guiBaseRenderer->getColorBackground().g,guiBaseRenderer->getColorBackground().b,255);
//                ofSetColor(fc);
//                
//                //        ofSetColor(255, 255, 255, 1);
//                ofDrawRectangle(0, 0, ofGetWidth(), ofGetHeight());
//                
//                
//                break;
//            case 2:
                ofFloatColor fc = ofFloatColor(1.0,1.0,1.0,guiBaseRenderer->getFadeBackground());
                //ofColor fc = ofColor(guiBaseRenderer->getColorBackground().r,guiBaseRenderer->getColorBackground().g,guiBaseRenderer->getColorBackground().b,255);
                ofSetColor(fc);
                
                //        ofSetColor(255, 255, 255, 1);
                ofDrawRectangle(0, 0, ofGetWidth(), ofGetHeight());
                
                ofEnableBlendMode(OF_BLENDMODE_ALPHA);
                
                for (int i=0; i<numInputs; ++i)
                {
                    if (!isActive[i]) continue;
                    
                    ofSetColor(tintColor);
                    brushes[i]->draw();
                }
        
                for (int i=0; i<particles.size(); i++){
                    particles[i].draw();
                }
            
                ofDisableBlendMode();
//                break;
//            default:
//                break;
//        }

    }
    fbo.end();

    ofSetColor(255, 255, 255, 255);
}

void PMRendererPaintbrush::changeBaseAngle(unsigned int inputIndex)
{
    brushes[inputIndex]->changeBaseAngle();
}

void PMRendererPaintbrush::setOffset(unsigned int inputIndex, float offset)
{
    brushes[inputIndex]->setOffset(offset);
}


void PMRendererPaintbrush::setPosition(unsigned int inputIndex, float normalizedX, float normalizedY)
{
    brushes[inputIndex]->setPosition(normalizedX, normalizedY);
}

void PMRendererPaintbrush::setPositionX(unsigned int inputIndex, float normalizedX)
{
    brushes[inputIndex]->setPositionX(normalizedX);
}

void PMRendererPaintbrush::setPositionY(unsigned int inputIndex, float normalizedY)
{
    brushes[inputIndex]->setPositionY(normalizedY);
}

void PMRendererPaintbrush::setSize(unsigned int inputIndex, float normalizedSize)
{
    brushes[inputIndex]->setSize(normalizedSize);
}

void PMRendererPaintbrush::changeDirection(unsigned int inputIndex, float direction)
{
    brushes[inputIndex]->changeDirection(direction);
}
