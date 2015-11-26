//
// Created by Miquel Àngel Soler on 7/11/15.
//

#include "PMUICanvasBrushRenderer.h"

PMUICanvasBrushRenderer::PMUICanvasBrushRenderer(PMUIRendererType type, string title, int headerFontSize) : PMUICanvasBaseRenderer(type, title, headerFontSize)
{
}

void PMUICanvasBrushRenderer::init(int posX, int posY, bool autosize, int width, int height)
{
    PMUICanvasBaseRenderer::init(posX, posY, autosize, width, height);
    
    addSpacer();
    addSpacer();
    addIntSlider("Mode",1,3,&guiMode);
    addSpacer();
    addIntSlider("Brush R",0,255,255);
    addIntSlider("Brush G",0,255,255);
    addIntSlider("Brush B",0,255,255);
    addSpacer();
    addSlider("Particle live", 0, 10, &particleLife);
    addSlider("Particle velocity", 0, 5, &particleVelocity);
    addToggle("Bouncy Walls", &bounceWalls);
    addSlider("Change Direction Curve", 0, 100, &directionFactor);
    if (autosize) autoSizeToFitWidgets();

    loadPreset(0);
}

void PMUICanvasBrushRenderer::clear()
{
    ofxUICanvas::clearWidgets();
    superInit("BRUSH_RENDERER", OFX_UI_FONT_MEDIUM);
}

void PMUICanvasBrushRenderer::handleEvents(ofxUIEventArgs &e)
{
    PMUICanvasBaseRenderer::handleEvents(e);
    
    string name = e.getName();

    if(name=="Brush R")
    {
        ofxUIIntSlider *s = (ofxUIIntSlider *) e.widget;
        paintColor.r = s->getValue();
    }
    else if(name=="Brush G")
    {
        ofxUIIntSlider *s = (ofxUIIntSlider *) e.widget;
        paintColor.g = s->getValue();
    }
    else if(name=="Brush B")
    {
        ofxUIIntSlider *s = (ofxUIIntSlider *) e.widget;
        paintColor.b = s->getValue();
    }
}


// GETTERS
int PMUICanvasBrushRenderer::getMode()
{
    return guiMode;
}
