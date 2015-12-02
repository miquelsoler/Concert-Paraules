//
// Created by Miquel Àngel Soler on 7/11/15.
//

#ifndef PMCONCERTPARAULES_PMUICANVASCOLORRENDERER_H
#define PMCONCERTPARAULES_PMUICANVASCOLORRENDERER_H

#include "PMBaseUICanvas.h"
#include "PMUICanvasBaseRenderer.h"

class PMUICanvasColorRenderer : public PMUICanvasBaseRenderer
{
public:

    PMUICanvasColorRenderer(PMUIRendererType type, string title, int headerFontSize);

    virtual void init(int posX, int posY, bool autosize = true, int width = 0, int height = 0);
    virtual void clear();

    virtual void handleEvents(ofxUIEventArgs &e);
//    virtual void saveGui();
    
    // GETTERS
    float       getScanSpeedX();
    int         getMode();
    float       getScanWidth();
    ofColor     getGradientColor(int _row,float _p);
    int         getGradientId();
    
    int         getResolutionX(){return guiResolutionX;};
    int         getResolutionY(){return guiResolutionY;};
    float       getFullProbability(){return guiFullProbability;};
    float       getHalfProbability(){return guiHalfProbability;};
    float       getHorizVertProbability(){return guiHorizontalVerticalProbability;};
    float       getStopOnSilence(){return guiStopOnSilence;};
    
    // SETTERS
    void        setScanSpeedX(float _s);
    
private:

    int         guiMode;

    float       guiScanWidth;
    float       guiScanSpeedX;
    bool        guiStopOnSilence;
    
    /// GUI COLOR
    ofImage     gradientImage;
    int         gradientId;
    int         numGradients;
    
    /// GUI GRID
    int         guiResolutionX;
    int         guiResolutionY;
    float       guiFullProbability;
    float       guiHalfProbability;
    float       guiHorizontalVerticalProbability;
    
    
    
};


#endif //PMCONCERTPARAULES_PMUICANVASCOLORRENDERER_H




