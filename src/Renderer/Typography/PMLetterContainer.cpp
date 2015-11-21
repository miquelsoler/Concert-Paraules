//
// Created by Miquel Àngel Soler on 16/11/15.
//

#include "PMLetterContainer.h"

PMLetterContainer::PMLetterContainer(string fontName, string _letter)
{
//    verdana14.load("verdana.ttf", 14, true, true);
//    verdana14.setLineHeight(18.0f);
//    verdana14.setLetterSpacing(1.037);


//    bool ofTrueTypeFont::load(const std::string& _filename, int _fontSize, bool _bAntiAliased, bool _bFullCharacterSet, bool _makeContours, float _simplifyAmt, int _dpi) {

    letterFont.load("fonts/" + fontName, 80, true, true, true);
//    letterFont.setLineHeight(18.0f);
//    letterFont.setLetterSpacing(1.037);

    letter = _letter;

    angle = ofRandom(360);
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
    float width = letterFont.stringWidth(letter);
    float height = letterFont.stringHeight(letter);

    ofPushMatrix();
        ofTranslate(x, y);
        ofRotate(angle);
        ofSetColor(ofColor::black);
        letterFont.drawStringAsShapes(letter, -width/2, height/2);
    ofPopMatrix();
}
