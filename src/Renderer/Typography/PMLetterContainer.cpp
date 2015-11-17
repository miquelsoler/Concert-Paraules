//
// Created by Miquel Àngel Soler on 16/11/15.
//

#include "PMLetterContainer.h"

PMLetterContainer::PMLetterContainer(string fontName)
{
//    verdana14.load("verdana.ttf", 14, true, true);
//    verdana14.setLineHeight(18.0f);
//    verdana14.setLetterSpacing(1.037);

    letterFont.load("fonts/" + fontName, 14, true, true);
    letterFont.setLineHeight(18.0f);
    letterFont.setLetterSpacing(1.037);
}

void PMLetterContainer::setPosition(float normalizedX, float normalizedY)
{

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

}
