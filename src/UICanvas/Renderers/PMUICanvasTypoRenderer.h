//
// Created by Miquel Àngel Soler on 7/11/15.
//

#ifndef PMCONCERTPARAULES_PMUICANVASTYPORENDERER_H
#define PMCONCERTPARAULES_PMUICANVASTYPORENDERER_H

#include "PMBaseUICanvas.h"
#include "PMUICanvasBaseRenderer.h"

class PMUICanvasTypoRenderer : public PMUICanvasBaseRenderer
{
public:

    PMUICanvasTypoRenderer(PMUIRendererType type, string title, int headerFontSize);

    virtual void init(int posX, int posY, bool autosize = true, int width = 0, int height = 0);
    virtual void clear();

    virtual void handleEvents(ofxUIEventArgs &e);
    
    // GETTERS
    int getMode()           { return guiMode; };
    int getMinVelocity()    { return minVelocity; };
    int getMaxVelocity()    { return maxVelocity; };
    float getMinSize()      { return minSize; };
    float getMaxSize()      { return maxSize; };
    float getBounceFactor() { return bounceFactor; };
    int getMaxAge()         { return maxAge; };
    float getGravityX()     { return gravityX; };
    float getGravityY()     { return gravityY; };

private:

    int     guiMode;
    int     minVelocity;
    int     maxVelocity;
    float   minSize;
    float   maxSize;
    float   bounceFactor;
    int     maxAge;
    float   gravityX;
    float   gravityY;
    
};


#endif //PMCONCERTPARAULES_PMUICANVASTYPORENDERER_H




