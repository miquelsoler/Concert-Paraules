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

    addSpacer();
    addLabel("PAINTER");
    ofxUIIntSlider *numPaintersSlider = addIntSlider("Number of painters", 1, 100, &numPainters);
    numPaintersSlider->setTriggerType(OFX_UI_TRIGGER_END);
    ofxUIIntSlider *sizeSlider = addIntSlider("Stroke width", 1, 10, &strokeWidth);
    sizeSlider->setTriggerType(OFX_UI_TRIGGER_END);

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
