//
// Created by Miquel Àngel Soler on 16/11/15.
//

#include "PMRendererTypography.h"

static const unsigned int MAX_LETTERS = 10;

PMRendererTypography::PMRendererTypography(unsigned int numInputs) : PMBaseRenderer(RENDERERTYPE_TYPOGRAPHY, numInputs)
{
//    charset = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
    charset = "aeiou";

    string fontName = "5inq_-_Handserif.ttf";
    string fontPath = "fonts/" + fontName;

    for (int i=0; i<charset.size(); ++i)
    {
        ofTrueTypeFont *letterFont = new ofTrueTypeFont();
        letterFont->load(fontPath, 80,
                true, // antialiased
                true, // full character set
                true // make contours
        );

////    letterFont->setLineHeight(18.0f);
////    letterFont->setLetterSpacing(1.037);

        fontCharset.push_back(letterFont);
    }

    ofAddListener(ofEvents().keyPressed, this, &PMRendererTypography::keyPressed);
}

void PMRendererTypography::setup()
{
    PMBaseRenderer::setup();

    if (!activeLetters.empty())
        activeLetters.clear();
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
        for (letterIt = activeLetters.begin(); letterIt != activeLetters.end(); ++letterIt)
            (*letterIt)->draw();

        ofDisableBlendMode();
    }
    fbo.end();

    ofSetColor(255, 255, 255, 255);

    fbo.draw(0, 0);
}

void PMRendererTypography::addLetter()
{
    int iLetter = int(ofRandom(charset.size()));

//    PMLetterContainer *letterContainer = new PMLetterContainer("5inq_-_Handserif.ttf", ofToString(charset[iLetter]));
    PMLetterContainer *letterContainer = new PMLetterContainer(ofToString(charset[iLetter]), fontCharset[iLetter]);
    letterContainer->setPosition(ofRandom(0.2, 0.8), ofRandom(0.2, 0.8));
    letterContainer->setSize(1.0);

    activeLetters.push_back(letterContainer);

    if (activeLetters.size() > MAX_LETTERS)
    {
        delete *(activeLetters.begin());
        activeLetters.pop_front();
    }
}

void PMRendererTypography::keyPressed ( ofKeyEventArgs& eventArgs )
{
    if (eventArgs.key == 'q')
        addLetter();
}
