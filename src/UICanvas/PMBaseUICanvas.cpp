//
// Created by Miquel Àngel Soler on 30/10/15.
//

#include "PMBaseUICanvas.h"

void PMBaseUICanvas::init(int posX, int posY, bool _autosize, int width, int height)
{
    setColorBack(bgColor);
    getCanvasTitle()->setColorFill(titleColor);

    addSpacer();

    autosize = _autosize;

    setPosition(posX, posY);
    if (!autosize)
    {
        setWidth(width);
        setHeight(height);
    }
}

float PMBaseUICanvas::getWidth()
{
    return getRect()->getWidth();
}

float PMBaseUICanvas::getHeight()
{
    return getRect()->getHeight();
}
