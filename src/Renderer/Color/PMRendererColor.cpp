//
// Created by Miquel Àngel Soler on 16/11/15.
//

#include "PMRendererColor.h"

PMRendererColor::PMRendererColor(unsigned int numInputs) : PMBaseRenderer(RENDERERTYPE_COLOR, numInputs)
{

}

void PMRendererColor::setup()
{
    PMBaseRenderer::setup();
}

void PMRendererColor::update()
{
    PMBaseRenderer::update();
}

void PMRendererColor::drawIntoFBO()
{
    fbo.begin();
    {
////        ofEnableBlendMode(OF_BLENDMODE_ALPHA);
////        ofSetColor(255, 255, 255, 5);
////        ofDrawRectangle(0, 0, ofGetWidth(), ofGetHeight());
//
//        ofSetColor(255, 255, 255, 1);
//        ofDrawRectangle(0, 0, ofGetWidth(), ofGetHeight());
//
//        ofEnableBlendMode(OF_BLENDMODE_ALPHA);
//
//        for (int i=0; i<numInputs; ++i)
//        {
//            if (!shouldPaint[i]) continue;
//
//            ofSetColor(255, 0, 0, 255);
//            brushes[i]->draw();
//        }
//
//        ofDisableBlendMode();
    }
    fbo.end();

    ofSetColor(255, 255, 255, 255);

    fbo.draw(0, 0);
}
