//
// Created by Miquel Àngel Soler on 16/11/15.
//

#include "PMRendererTypography.h"

PMRendererTypography::PMRendererTypography(unsigned int numInputs) : PMBaseRenderer(RENDERERTYPE_TYPOGRAPHY, numInputs)
{

}

void PMRendererTypography::setup()
{
    PMBaseRenderer::setup();
}

void PMRendererTypography::update()
{
    PMBaseRenderer::update();
}

void PMRendererTypography::drawIntoFBO()
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
