//
// Created by Miquel Àngel Soler on 28/10/15.
//

#include "PMRendererPaintbrush.h"

PMRendererPaintbrush::PMRendererPaintbrush(unsigned int _numInputs) : PMBaseRenderer(_numInputs)
{
    for (int i=0; i<numInputs; ++i)
    {
        PMBrushContainer *brush = new PMBrushContainer("brushes/pinzell.png");
        brush->setPosition(0.5, 0.5);
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
    PMBaseRenderer::update();
}

void PMRendererPaintbrush::drawIntoFBO()
{
    fbo.begin();
    {
//        ofEnableBlendMode(OF_BLENDMODE_ALPHA);
//        ofSetColor(255, 255, 255, 5);
//        ofDrawRectangle(0, 0, ofGetWidth(), ofGetHeight());

        ofSetColor(255, 255, 255, 1);
        ofDrawRectangle(0, 0, ofGetWidth(), ofGetHeight());

        ofEnableBlendMode(OF_BLENDMODE_ALPHA);

        for (int i=0; i<numInputs; ++i)
        {
            if (!shouldPaint[i]) continue;

            ofSetColor(255, 0, 0, 255);
            brushes[i]->draw();
        }

        ofDisableBlendMode();
    }
    fbo.end();

    ofSetColor(255, 255, 255, 255);

    fbo.draw(0, 0);
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
