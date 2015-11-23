//
// Created by Miquel Àngel Soler on 16/11/15.
//

#include "PMLetterContainer.h"

PMLetterContainer::PMLetterContainer(string _letter, ofTrueTypeFont *font)
{
    letterFont = font;
    letter = _letter;
    angle = ofRandom(-90, 90);
}

PMLetterContainer::~PMLetterContainer()
{
}

void PMLetterContainer::setPosition(float normalizedX, float normalizedY)
{
    x = ofGetWidth() * normalizedX;
    y = ofGetHeight() * normalizedY;
}

void PMLetterContainer::setPositionX(float normalizedX)
{
}

void PMLetterContainer::setPositionY(float normalizedY)
{
}

void PMLetterContainer::setSize(float normalizedSize) {

}

void PMLetterContainer::draw()
{
    float width = letterFont->stringWidth(letter);
    float height = letterFont->stringHeight(letter);

    ofSetColor(ofColor::black);
    ofPushMatrix();
        ofTranslate(x, y);
        ofRotate(angle);
        ofSetColor(ofColor::black);
        letterFont->drawString(letter, -width/2, height/2);
    ofPopMatrix();
}
