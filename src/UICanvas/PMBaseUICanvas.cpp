//
// Created by Miquel Àngel Soler on 30/10/15.
//

#include "PMBaseUICanvas.h"

void PMBaseUICanvas::init(int posX, int posY)
{
    setColorBack(bgColor);
    getCanvasTitle()->setColorFill(titleColor);

    addSpacer();

    setPosition(posX, posY);
}

float PMBaseUICanvas::getWidth()
{
    return getRect()->getWidth();
}

float PMBaseUICanvas::getHeight()
{
    return getRect()->getHeight();
}
