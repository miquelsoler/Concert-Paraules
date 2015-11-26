//
// Created by Miquel Àngel Soler on 30/10/15.
//

#ifndef PMCONCERTPARAULES_PMUICANVASPOEM_H
#define PMCONCERTPARAULES_PMUICANVASPOEM_H

#pragma once

#include "PMBaseUICanvas.h"

#include "PMSettingsManagerPoem.h"

class PMUICanvasPoem : public PMBaseUICanvas
{
public:

    PMUICanvasPoem(string title, int headerFontSize) : PMBaseUICanvas(title, headerFontSize) {}

    virtual void init(int posX, int posY, bool autosize = true, int width = 0, int height = 0);

    virtual void handleEvents(ofxUIEventArgs &e);

private:

    PMSettingsManagerPoem *settings;

    ofxUITextArea *poemTextArea;
};


#endif //PMCONCERTPARAULES_PMUICANVASPOEM_H
