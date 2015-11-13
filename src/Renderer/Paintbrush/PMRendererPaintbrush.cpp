//
// Created by Miquel Àngel Soler on 28/10/15.
//

#include "PMRendererPaintbrush.h"

PMRendererPaintbrush::PMRendererPaintbrush(unsigned int numInputs) : PMBaseRenderer(numInputs)
{

}

void PMRendererPaintbrush::setup()
{
    PMBaseRenderer::setup();

    brush = new PMBrushContainer("brushes/splat8 copy.png");
    brush->setPosition(0.5, 0.5);
    brush->setSize(1);
}

void PMRendererPaintbrush::update()
{
    PMBaseRenderer::update();

//    brush->setPosition(float(ofGetMouseX())/float(ofGetWidth()), float(ofGetMouseY())/float(ofGetHeight()));
}

void PMRendererPaintbrush::drawIntoFBO()
{
    fbo.begin();
    {
        ofEnableBlendMode(OF_BLENDMODE_ALPHA);

//        ofFloatColor clearColor = ofFloatColor(1.0f, 1.0f, 1.0f, 0.01f);
//        ofSetColor(clearColor);

        ofSetColor(255, 255, 255, 5);
        ofDrawRectangle(0, 0, ofGetWidth(), ofGetHeight());

        if (shouldPaint)
        {
            ofSetColor(255, 0, 0, 127);
            brush->draw();
        }
        ofDisableBlendMode();
    }
    fbo.end();
    fbo.draw(0, 0);
}

void PMRendererPaintbrush::setPosition(unsigned int inputId, float normalizedX, float normalizedY)
{
    brush->setPosition(normalizedX, normalizedY);
}

void PMRendererPaintbrush::setPositionX(unsigned int inputId, float normalizedX)
{
    brush->setPositionX(normalizedX);
}

void PMRendererPaintbrush::setPositionY(unsigned int inputId, float normalizedY)
{
    brush->setPositionY(normalizedY);
}

void PMRendererPaintbrush::setSize(unsigned int inputId, float normalizedSize)
{
    brush->setSize(normalizedSize);
}
