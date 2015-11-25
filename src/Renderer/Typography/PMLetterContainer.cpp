//
// Created by Miquel Àngel Soler on 16/11/15.
//

#include "PMLetterContainer.h"

PMLetterContainer::PMLetterContainer(string _letter, ofTrueTypeFont *font, float _letterSize, float letterVelocity, ofxBox2d *_box2d)
{
    letterFont = font;
    letter = _letter;
    angle = ofRandom(-90, 90);

    box2d = _box2d;

    float posOffset = ofGetWidth() * 0.1;
    float posX = ofRandom(posOffset, ofGetWidth() - 2*posOffset);
    float posY = 1;

    float normalizedPosX = posX / ofGetWidth();
    float normalizedPosY = posY / ofGetHeight();

    letterSize = _letterSize;

    float width = letterFont->stringWidth(letter) * letterSize;
    float height = letterFont->stringHeight(letter) * letterSize;

    setPhysics(3.0, 0.53, 0.1);

    // Es queda en espera mentre no pot crear el nou objecte. (WTF?)
    while (box2d->getWorld()->IsLocked()) sleep(0.01);

    setup(box2d->getWorld(), posX, posY, width, height);
    float minYVelocity = 10.0;
    float maxYVelocity = 50.0;
    float velocity = ofMap(letterVelocity, 0.01, 1.0, minYVelocity, maxYVelocity, true);
    setVelocity(0, velocity);

    this->setPosition(normalizedPosX, normalizedPosY);

    timeCreated = ofGetElapsedTimeMillis();
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
    {
        ofTranslate(getPosition());
        ofRotateZ(getRotation());
        ofScale(letterSize, letterSize);
        ofSetColor(ofColor::black);
        letterFont->drawString(letter, -width/2, height/2);
    }
    ofPopMatrix();
}

uint64_t PMLetterContainer::getAge()
{
    return ofGetElapsedTimeMillis() - timeCreated;
}
