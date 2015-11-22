//
// Created by Miquel Àngel Soler on 16/11/15.
//

#include "PMRendererTypography.h"

static const unsigned int MAX_LETTERS = 10;

PMRendererTypography::PMRendererTypography(unsigned int numInputs) : PMBaseRenderer(RENDERERTYPE_TYPOGRAPHY, numInputs)
{
    availableLetters = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";

    ofAddListener(ofEvents().keyPressed, this, &PMRendererTypography::keyPressed);
}

void PMRendererTypography::setup()
{
    PMBaseRenderer::setup();

    if (!letters.empty())
        letters.clear();
}

void PMRendererTypography::update()
{
    PMBaseRenderer::update();
}

void PMRendererTypography::drawIntoFBO()
{
    fbo.begin();
    {
        ofSetColor(255, 255, 255, 1);
        ofDrawRectangle(0, 0, ofGetWidth(), ofGetHeight());

        ofEnableBlendMode(OF_BLENDMODE_ALPHA);

        list<PMLetterContainer *>::iterator letterIt;
        for (letterIt = letters.begin(); letterIt != letters.end(); ++letterIt)
            (*letterIt)->draw();

        ofDisableBlendMode();
    }
    fbo.end();

    ofSetColor(255, 255, 255, 255);

    fbo.draw(0, 0);
}

void PMRendererTypography::addLetter()
{
    int iLetter = int(ofRandom(availableLetters.size()));
    PMLetterContainer *letterContainer = new PMLetterContainer("5inq_-_Handserif.ttf", ofToString(availableLetters[iLetter]));
    letterContainer->setPosition(ofRandom(0,1), ofRandom(0.2,0.8));
    letterContainer->setSize(1.0);

    letters.push_back(letterContainer);

    if (letters.size() > MAX_LETTERS)
    {
        delete *(letters.begin());
        letters.pop_front();
    }
}

void PMRendererTypography::keyPressed ( ofKeyEventArgs& eventArgs )
{
    if (eventArgs.key == 'q')
        addLetter();
}
