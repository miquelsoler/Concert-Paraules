//
// Created by Miquel Àngel Soler on 7/11/15.
//

#ifndef PMCONCERTPARAULES_PMUICANVASBRUSHRENDERER_H
#define PMCONCERTPARAULES_PMUICANVASBRUSHRENDERER_H

#include "PMBaseUICanvas.h"
#include "PMUICanvasBaseRenderer.h"

class PMUICanvasBrushRenderer : public PMUICanvasBaseRenderer
{
public:

    PMUICanvasBrushRenderer(string title, int headerFontSize);

    virtual void init(int posX, int posY, bool autosize = true, int width = 0, int height = 0);
    virtual void clear();

    virtual void handleEvents(ofxUIEventArgs &e);
    
    // GETTERS
    int         getMode();
    
private:

    int         guiMode;
};


#endif //PMCONCERTPARAULES_PMUICANVASBRUSHRENDERER_H




