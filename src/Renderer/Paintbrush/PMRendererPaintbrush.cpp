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
}

void PMRendererPaintbrush::setup()
{
    PMBaseRenderer::setup();
}

void PMRendererPaintbrush::update()
{
    

    for (int i=0; i<numInputs; ++i)
    {
        if (!isActive[i]) continue;

        brushes[i]->update();
    }
    PMBaseRenderer::update();
}

void PMRendererPaintbrush::drawIntoFBO()
{
    fbo.begin();
    {
        ofSetColor(255, 255, 255, 1);
        ofDrawRectangle(0, 0, ofGetWidth(), ofGetHeight());

        ofEnableBlendMode(OF_BLENDMODE_ALPHA);

        for (int i=0; i<numInputs; ++i)
        {
            if (!isActive[i]) continue;

            ofSetColor(tintColor);
            brushes[i]->draw();
        }

        ofDisableBlendMode();
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
