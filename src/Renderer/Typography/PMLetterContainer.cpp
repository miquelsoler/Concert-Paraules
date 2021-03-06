//
// Created by Miquel Àngel Soler on 16/11/15.
//

#include "PMLetterContainer.h"

PMLetterContainer::PMLetterContainer(string _letter, ofTrueTypeFont *font, ofPoint pos, float _letterSize, float letterVelocity, ofxBox2d *_box2d, PMUICanvasTypoRenderer* _gui)
{
    letterFont = font;
    letter = _letter;
    angle = ofRandom(-90, 90);

    box2d = _box2d;

//    float posOffset = ofGetWidth() * 0.1f;
//    float posX = ofRandom(posOffset, ofGetWidth() - 2*posOffset);
//    float posY = 1;
//
    float posX = pos.x;
    float posY = pos.y;

    
//    float normalizedPosX = posX / ofGetWidth();
//    float normalizedPosY = posY / ofGetHeight();

    gui = _gui;
    
    letterSize = ofMap(_letterSize, 0.1, 1.0, gui->getMinSize(), gui->getMaxSize(), true);

    float width = letterFont->stringWidth(letter) * letterSize;
    float height = letterFont->stringHeight(letter) * letterSize;

    setPhysics(3.0, gui->getBounceFactor(), 0.1);

    // Es queda en espera mentre no pot crear el nou objecte. (WTF?)
    while (box2d->getWorld()->IsLocked()) sleep(0.01);

    setup(box2d->getWorld(), posX, posY, width, height);
    
    float yVelocity = ofMap(letterVelocity, 0.01, 1.0, gui->getMinVelocity(), gui->getMaxVelocity(), true);
    setVelocity(0, yVelocity);

    timeCreated = ofGetElapsedTimeMillis();

    needsToBeRemoved = false;
}

PMLetterContainer::~PMLetterContainer()
{
}

void PMLetterContainer::draw()
{
    float width = letterFont->stringWidth(letter);
    float height = letterFont->stringHeight(letter);

    ofSetColor(gui->getLetterColor());
    ofFill();
    ofPushMatrix();
    {
        ofTranslate(getPosition());
        ofRotateZ(getRotation());
        ofScale(letterSize, letterSize);
        letterFont->drawStringAsShapes(letter, -width/2, height/2);
    }
    ofPopMatrix();
}

uint64_t PMLetterContainer::getAge()
{
    return ofGetElapsedTimeMillis() - timeCreated;
}
