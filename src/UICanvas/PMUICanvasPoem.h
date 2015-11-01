//
// Created by Miquel Àngel Soler on 30/10/15.
//

#ifndef PMCONCERTPARAULES_PMUICANVASPOEM_H
#define PMCONCERTPARAULES_PMUICANVASPOEM_H

#include "PMBaseUICanvas.h"

#include "PMSettingsManagerPoem.h"

class PMUICanvasPoem : public PMBaseUICanvas
{
public:

    PMUICanvasPoem(string title, int headerFontSize) : PMBaseUICanvas(title, headerFontSize) {}

    virtual void init(int posX, int posY);

    virtual void handleEvents(ofxUIEventArgs &e);

private:

    PMSettingsManagerPoem *settings;
};


#endif //PMCONCERTPARAULES_PMUICANVASPOEM_H