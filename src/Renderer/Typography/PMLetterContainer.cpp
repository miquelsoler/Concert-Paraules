//
// Created by Miquel Àngel Soler on 16/11/15.
//

#include "PMLetterContainer.h"

#ifdef WITH_BOX2D
PMLetterContainer::PMLetterContainer(string _letter, ofTrueTypeFont *font, ofxBox2d *_box2d) : ofxBox2dRect()
#else
PMLetterContainer::PMLetterContainer(string _letter, ofTrueTypeFont *font)
#endif
{
    letterFont = font;
    letter = _letter;
    angle = ofRandom(-90, 90);

#ifdef WITH_BOX2D
    box2d = _box2d;
#endif
}

PMLetterContainer::~PMLetterContainer()
{
}

void PMLetterContainer::setPosition(float normalizedX, float normalizedY)
{
    x = ofGetWidth() * normalizedX;
    y = ofGetHeight() * normalizedY;

#ifdef WITH_BOX2D
//    float width = letterFont->stringWidth(letter);
//    float height = letterFont->stringHeight(letter);
//    setup(box2d->getWorld(), x, y, 100, 100);
//    setPhysics(1.0, 0.5, 0.3);
//    setVelocity(ofRandom(-30, 30), ofRandom(-30, 30));
//    p.get()->setupTheCustomData();
#endif
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
