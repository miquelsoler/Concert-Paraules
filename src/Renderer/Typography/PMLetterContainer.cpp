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

//PMLetterContainer::PMLetterContainer(string fontName, string _letter)
//{
////    bool ofTrueTypeFont::load(const std::string& _filename, int _fontSize, bool _bAntiAliased, bool _bFullCharacterSet, bool _makeContours, float _simplifyAmt, int _dpi) {
//
//    letterFont = new ofTrueTypeFont();
//    letterFont->load("fonts/" + fontName, 80,
//            true, // antialiased
//            true, // full character set
//            true // make contours
//    );
////    letterFont->setLineHeight(18.0f);
////    letterFont->setLetterSpacing(1.037);
//
//    letter = _letter;
//
//    angle = ofRandom(-90, 90);
//}

PMLetterContainer::~PMLetterContainer()
{
//    delete letterFont;
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
