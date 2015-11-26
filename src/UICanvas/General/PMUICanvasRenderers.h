//
// Created by Miquel Àngel Soler on 30/10/15.
//

#ifndef PMCONCERTPARAULES_PMUICANVASRENDERERS_H
#define PMCONCERTPARAULES_PMUICANVASRENDERERS_H

#pragma once

#include "PMBaseUICanvas.h"

#include "PMSettingsManagerRenderers.h"

class PMUICanvasRenderers : public PMBaseUICanvas
{
public:

    PMUICanvasRenderers(string title, int headerFontSize) : PMBaseUICanvas(title, headerFontSize) {}

    virtual void init(int posX, int posY, bool autosize = true, int width = 0, int height = 0);

    virtual void handleEvents(ofxUIEventArgs &e);

private:

    PMSettingsManagerRenderers *settings;
};


#endif //PMCONCERTPARAULES_PMUICANVASRENDERERS_H
