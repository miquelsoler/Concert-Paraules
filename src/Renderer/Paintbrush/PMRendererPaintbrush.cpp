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

    brush = new PMBrushContainer("brushes/pinzell.png");
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
//        ofEnableBlendMode(OF_BLENDMODE_ALPHA);
//        ofSetColor(255, 255, 255, 5);
//        ofDrawRectangle(0, 0, ofGetWidth(), ofGetHeight());

        ofSetColor(255, 255, 255, 1);
        ofDrawRectangle(0, 0, ofGetWidth(), ofGetHeight());

        ofEnableBlendMode(OF_BLENDMODE_ALPHA);

        if (shouldPaint)
        {
            ofSetColor(255, 0, 0, 255);
            brush->draw();
        }
        ofDisableBlendMode();
    }
    fbo.end();

    ofSetColor(255, 255, 255, 255);

    fbo.draw(0, 0);
}

void PMRendererPaintbrush::setPosition(unsigned int inputIndex, float normalizedX, float normalizedY)
{
    cout << "Input index: " << inputIndex << endl;
    brush->setPosition(normalizedX, normalizedY);
}

void PMRendererPaintbrush::setPositionX(unsigned int inputIndex, float normalizedX)
{
    brush->setPositionX(normalizedX);
}

void PMRendererPaintbrush::setPositionY(unsigned int inputIndex, float normalizedY)
{
    brush->setPositionY(normalizedY);
}

void PMRendererPaintbrush::setSize(unsigned int inputIndex, float normalizedSize)
{
    brush->setSize(normalizedSize);
}
