//
// Created by Miquel Àngel Soler on 7/11/15.
//

#include "PMUICanvasTextBoxRenderer.h"

PMUICanvasTextBoxRenderer::PMUICanvasTextBoxRenderer(PMUIRendererType type, string title, int headerFontSize) : PMUICanvasBaseRenderer(type, title, headerFontSize)
{
}

void PMUICanvasTextBoxRenderer::init(int posX, int posY, bool autosize, int width, int height)
{
    PMUICanvasBaseRenderer::init(posX, posY, autosize, width, height);
    
    addSpacer();
    addIntSlider("Mode",1,10,&guiMode);
    addSpacer();

    
    if (autosize) autoSizeToFitWidgets();

    loadPreset(0);
}

void PMUICanvasTextBoxRenderer::clear()
{
    ofxUICanvas::clearWidgets();
    //superInit("COLOR_RENDERER", OFX_UI_FONT_MEDIUM);
}

void PMUICanvasTextBoxRenderer::handleEvents(ofxUIEventArgs &e)
{
    PMUICanvasBaseRenderer::handleEvents(e);
    
    string name = e.getName();
}


