//
// Created by Miquel Àngel Soler on 16/11/15.
//

#include "PMRendererTypography.h"

static const unsigned int MAX_LETTERS = 50;


PMRendererTypography::PMRendererTypography(unsigned int numInputs) : PMBaseRenderer(RENDERERTYPE_TYPOGRAPHY, numInputs)
{
}

void PMRendererTypography::setup()
{
//    PMBaseRenderer::setup();
//
//    if (!letters.empty())
//        letters.clear();
}

void PMRendererTypography::update()
{
    PMBaseRenderer::update();
}

void PMRendererTypography::drawIntoFBO()
{
    fbo.begin();
    {
//////        ofEnableBlendMode(OF_BLENDMODE_ALPHA);
//////        ofSetColor(255, 255, 255, 5);
//////        ofDrawRectangle(0, 0, ofGetWidth(), ofGetHeight());
//
//        ofSetColor(255, 255, 255, 1);
//        ofDrawRectangle(0, 0, ofGetWidth(), ofGetHeight());
//
//        ofEnableBlendMode(OF_BLENDMODE_ALPHA);
//
//        ofSetColor(0, 0, 0, 255);
//
//        list<PMLetterContainer>::iterator letterIt;
//        for (letterIt = letters.begin(); letterIt != letters.end(); ++letterIt)
//            (*letterIt).draw();
//
//        ofDisableBlendMode();
    }
    fbo.end();

    ofSetColor(255, 255, 255, 255);

    fbo.draw(0, 0);
}

void PMRendererTypography::addLetter()
{
//    PMLetterContainer letterContainer("verdana.ttf");
//    letterContainer.setPosition(0.5, 0.5);
//    letterContainer.setSize(1.0);
//
//    letters.push_back(letterContainer);
//
//    if (letters.size() > MAX_LETTERS)
//        letters.pop_front();
}
