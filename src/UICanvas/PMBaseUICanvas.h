//
// Created by Miquel Àngel Soler on 30/10/15.
//

#ifndef PMCONCERTPARAULES_PMBASEUICANVAS_H
#define PMCONCERTPARAULES_PMBASEUICANVAS_H

#pragma once

#include "ofxUI.h"


class PMBaseUICanvas : public ofxUISuperCanvas
{
public:

    PMBaseUICanvas(string title, int headerFontSize);

    virtual void init(int posX, int posY, bool autosize = true, int width = 0, int height = 0);
    virtual void clear() {};

    void setBackgroundColor(ofColor backgroundColor);

    float getWidth();
    float getHeight();

    virtual void handleEvents(ofxUIEventArgs &e) = 0;

protected:

    ofColor bgColor = ofColor(0, 0, 0, 50);
    ofColor titleColor = ofColor(252, 239, 157);

    bool autosize;
};


#endif //PMCONCERTPARAULES_PMBASEUICANVAS_H
