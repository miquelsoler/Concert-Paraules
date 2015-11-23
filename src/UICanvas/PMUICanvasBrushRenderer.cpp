//
// Created by Miquel Àngel Soler on 7/11/15.
//

#include "PMUICanvasBrushRenderer.h"

PMUICanvasBrushRenderer::PMUICanvasBrushRenderer(string title, int headerFontSize) : PMUICanvasBaseRenderer(title, headerFontSize)
{

}

void PMUICanvasBrushRenderer::init(int posX, int posY, bool autosize, int width, int height)
{
    PMUICanvasBaseRenderer::init(posX, posY, autosize, width, height);
    
    addSpacer();
    addIntSlider("Mode",1,3,&guiMode);
    if (autosize) autoSizeToFitWidgets();
    loadPreset();

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
    int kind = e.getKind();
    
    if(name=="Save to default")
    {
        savePreset();
    }
}


// GETTERS
int PMUICanvasBrushRenderer::getMode()
{
    return guiMode;
}
