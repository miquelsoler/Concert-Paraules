//
// Created by Miquel Àngel Soler on 16/12/15.
//

#include "PMUICanvasRibbonRenderer.h"

PMUICanvasRibbonRenderer::PMUICanvasRibbonRenderer(PMUIRendererType type, string title, int headerFontSize) : PMUICanvasBaseRenderer(type, title, headerFontSize)
{

}

void PMUICanvasRibbonRenderer::init(int posX, int posY, bool autosize, int width, int height)
{
    PMUICanvasBaseRenderer::init(posX, posY, autosize, width, height);

    // Aquí va el codi específic
    addSpacer();
    addLabel("TEST");

    if (autosize) autoSizeToFitWidgets();

    loadPreset(0);
}

void PMUICanvasRibbonRenderer::clear()
{
    PMUICanvasBaseRenderer::clear();
    superInit("RIBBON_RENDERER", OFX_UI_FONT_MEDIUM);
}

void PMUICanvasRibbonRenderer::handleEvents(ofxUIEventArgs &e)
{
    PMUICanvasBaseRenderer::handleEvents(e);
    string name = e.getName();
}
