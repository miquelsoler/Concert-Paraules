//
// Created by Miquel Àngel Soler on 30/10/15.
//

#ifndef PMCONCERTPARAULES_PMBASEUICANVAS_H
#define PMCONCERTPARAULES_PMBASEUICANVAS_H

#include "ofxUI.h"


class PMBaseUICanvas : public ofxUISuperCanvas
{
public:

    PMBaseUICanvas(string title, int headerFontSize) : ofxUISuperCanvas(title, headerFontSize) {}

    virtual void init(int posX, int posY, bool autosize = true, int width = 0, int height = 0);

    virtual void handleEvents(ofxUIEventArgs &e) = 0;

    float getWidth();
    float getHeight();

protected:

    ofColor bgColor = ofColor(0, 0, 0, 50);
    ofColor titleColor = ofColor(252, 239, 157);

    bool autosize;
};


#endif //PMCONCERTPARAULES_PMBASEUICANVAS_H
