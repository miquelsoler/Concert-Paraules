//
// Created by Miquel Àngel Soler on 28/10/15.
//

#include "PMRendererPaintbrush.h"

void PMRendererPaintbrush::setup()
{
    PMBaseRenderer::setup();
    brush = ofImage("brushes/pinzell.png");
}

void PMRendererPaintbrush::update()
{
    PMBaseRenderer::update();
}

void PMRendererPaintbrush::drawIntoFBO()
{
    fbo.begin();
    {
//        if (paint)
//        {
            ofEnableBlendMode(OF_BLENDMODE_ALPHA);

//        ofFloatColor clearColor = ofFloatColor(1, 1, 1, 0.01);
//        ofSetColor(clearColor);
//        ofDrawRectangle(0, 0, ofGetWidth(), ofGetHeight());

        ofSetColor(255, 151, 88, 255);
        brush.draw(ofGetMouseX() - (brush.getWidth() / 2), ofGetMouseY() - (brush.getHeight() / 2));
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
