//
// Created by Miquel Àngel Soler on 16/12/15.
//

#ifndef PMCONCERTPARAULES_PMUICANVASRIBBONRENDERER_H
#define PMCONCERTPARAULES_PMUICANVASRIBBONRENDERER_H

#include "PMBaseUICanvas.h"
#include "PMUICanvasBaseRenderer.h"

class PMUICanvasRibbonRenderer : public PMUICanvasBaseRenderer
{
public:

    PMUICanvasRibbonRenderer(PMUIRendererType type, string title, int headerFontSize);

    virtual void init(int posX, int posY, bool autosize = true, int width = 0, int height = 0);
    virtual void clear();

    virtual void handleEvents(ofxUIEventArgs &e);

    unsigned int    getNumPainters()    { return (unsigned int)numPainters; };
    unsigned int    getStrokeWidth()    { return (unsigned int)strokeWidth; };
    ofColor         getRibbonColor()    { return ofColor(colorR, colorG, colorB, 255); };
    float           getDivisions()      { return divisions; };

private:

    int numPainters;
    int strokeWidth;
    int colorR, colorG, colorB;
    float divisions;
};


#endif //PMCONCERTPARAULES_PMUICANVASRIBBONRENDERER_H
