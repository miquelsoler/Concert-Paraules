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
    fbo.begin();
    {
        int size = 100;
        ofSetColor(ofColor::red);
        ofDrawCircle(ofGetWidth()/2, ofGetHeight()/2, size);
        ofSetColor(ofColor::white);

        ofSetColor(255, 255, 255, int(alpha));
        ofDrawRectangle(0, 0, ofGetWidth(), ofGetHeight());
    }
    fbo.end();

    fbo.draw(0, 0);
}
