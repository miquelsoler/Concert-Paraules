//
// Created by Miquel Àngel Soler on 4/11/15.
//

#ifndef PMCONCERTPARAULES_PMUICANVASNAVIGATION_H
#define PMCONCERTPARAULES_PMUICANVASNAVIGATION_H

#pragma once

#include "PMBaseUICanvas.h"


class PMUICanvasNavigation : public PMBaseUICanvas
{
public:

    PMUICanvasNavigation(string title, int headerFontSize) : PMBaseUICanvas(title, headerFontSize) {}
    virtual void init(int posX, int posY, bool autosize = true, int width = 0, int height = 0);
    
    virtual void handleEvents(ofxUIEventArgs &e);

    ofEvent<void> eventContinuePressed;
};


#endif //PMCONCERTPARAULES_PMUICANVASNAVIGATION_H
