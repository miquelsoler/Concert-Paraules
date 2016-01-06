//
// Created by Miquel Àngel Soler on 7/11/15.
//

#ifndef PMCONCERTPARAULES_PMUICANVASSCROLLINGTEXTRENDERER_H
#define PMCONCERTPARAULES_PMUICANVASSCROLLINGTEXTRENDERER_H

#include "PMBaseUICanvas.h"
#include "PMUICanvasBaseRenderer.h"

class PMUICanvasTextBoxRenderer : public PMUICanvasBaseRenderer
{
public:

    PMUICanvasTextBoxRenderer(PMUIRendererType type, string title, int headerFontSize);

    virtual void init(int posX, int posY, bool autosize = true, int width = 0, int height = 0);
    virtual void clear();

    virtual void handleEvents(ofxUIEventArgs &e);

private:

    int         guiMode;
};


#endif //PMCONCERTPARAULES_PMUICANVASSCROLLINGTEXTRENDERER_H




