//
// Created by Miquel Àngel Soler on 30/10/15.
//

#include "PMBaseUICanvas.h"

PMBaseUICanvas::PMBaseUICanvas(string _title, int headerFontSize) : ofxUIScrollableCanvas(_title)
{
    
}

void PMBaseUICanvas::init(int posX, int posY, bool _autosize, int width, int height)
{
    //setColorBack(bgColor);
    //getCanvasTitle()->setColorFill(titleColor);

    setTriggerWidgetsUponLoad(false);

    addSpacer();

    autosize = _autosize;

    setPosition(posX, posY);
    if (!autosize)
    {
        //setWidth(width);
        //setHeight(height);
    }
        
    ofAddListener(ofEvents().windowResized,this,&PMBaseUICanvas::windowResized);
    setTheme(OFX_UI_THEME_HACKER);
}

void PMBaseUICanvas::setBackgroundColor(ofColor backgroundColor)
{
    setColorBack(backgroundColor);
}


float PMBaseUICanvas::getWidth()
{
    return getRect()->getWidth();
}

float PMBaseUICanvas::getHeight()
{
    return getRect()->getHeight();
}


void PMBaseUICanvas::windowResized(ofResizeEventArgs& data)
{
}
