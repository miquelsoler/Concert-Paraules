//
// Created by Miquel Àngel Soler on 28/10/15.
//

#include "PMRendererPaintbrush.h"

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
    float alpha = ofMap(ofGetMouseX(), 0, ofGetWidth(), 0, 255);
//    fbo.begin();
    ofSetColor(255,255,255, alpha);
    ofDrawRectangle(0,0,400,400);

//    ofSetColor(ofColor::red);
//    ofDrawCircle(ofGetWidth()/2, ofGetHeight()/2, 200);
//
//    fbo.end();

//    fbo.begin();
//    {
//
//    }
//    fbo.end();
//    fbo.draw(400, 400);
}
