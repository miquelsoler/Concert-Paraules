//
// Created by Miquel Àngel Soler on 28/10/15.
//

#include "PMRendererPaintbrush.h"

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

    brush->setPosition(float(ofGetMouseX())/float(ofGetWidth()), float(ofGetMouseY())/float(ofGetHeight()));
}

void PMRendererPaintbrush::drawIntoFBO()
{
    fbo.begin();
    {
//        if (paint)
//        {
        ofEnableBlendMode(OF_BLENDMODE_ALPHA);

//        ofFloatColor clearColor = ofFloatColor(1.0f, 1.0f, 1.0f, 0.01f);
//        ofSetColor(clearColor);


        ofSetColor(255, 255, 255, 5);
        ofDrawRectangle(0, 0, ofGetWidth(), ofGetHeight());

        ofSetColor(255, 255, 255, 255);
        brush->draw();
//        brush.draw(ofGetMouseX() - (brush.getWidth() / 2), ofGetMouseY() - (brush.getHeight() / 2));
        ofDisableBlendMode();
//        }
    }
    fbo.end();
    fbo.draw(0, 0);

//    float alpha = ofMap(ofGetMouseX(), 0, ofGetWidth(), 0, 255);
//    fbo.begin();
//    {
//        int size = 100;
//        ofSetColor(ofColor::red);
//        ofDrawCircle(ofGetWidth()/2, ofGetHeight()/2, size);
//        ofSetColor(ofColor::white);
//
//        ofSetColor(255, 255, 255, int(alpha));
//        ofDrawRectangle(0, 0, ofGetWidth(), ofGetHeight());
//    }
//    fbo.end();
//
//    fbo.draw(0, 0);
}

void PMRendererPaintbrush::setPosition(float normalizedX, float normalizedY)
{
    brush->setPosition(normalizedX, normalizedY);
}

void PMRendererPaintbrush::setSize(float normalizedSize)
{
    brush->setSize(normalizedSize);
}
