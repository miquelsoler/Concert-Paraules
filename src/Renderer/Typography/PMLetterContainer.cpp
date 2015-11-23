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

//    float posX = ofGetWidth() / 2;
    float posX = ofRandomWidth();
    float posY = 1;

    float normalizedPosX = posX / ofGetWidth();
    float normalizedPosY = posY / ofGetHeight();

    float width = letterFont->stringWidth(letter);
    float height = letterFont->stringHeight(letter);

    setPhysics(3.0, 0.53, 0.1);
    setup(box2d->getWorld(), posX, posY, width, height);
    setVelocity(ofRandom(-10, 10), ofRandom(0, 30));

    this->setPosition(normalizedPosX, normalizedPosY);
    //    p.get()->setupTheCustomData();
#endif
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
#ifdef WITH_BOX2D
        ofTranslate(getPosition());
        ofRotateZ(getRotation());
#else
        ofTranslate(x, y);
        ofRotate(angle);
#endif
        ofSetColor(ofColor::black);
        letterFont->drawString(letter, -width/2, height/2);
    ofPopMatrix();
}
