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
    addLabel("RIBBON BASIC");
    addIntSlider("Number of painters", 1, 100, &numPainters);
    addIntSlider("Stroke width", 1, 10, &strokeWidth);
    addIntSlider("Ribbon R", 0, 255, &colorR);
    addIntSlider("Ribbon G", 0, 255, &colorG);
    addIntSlider("Ribbon B", 0, 255, &colorB);

    addSpacer();
    addLabel("RIBBON ADVANCED");
    addSlider("Divisions", 0.01, 0.5, &divisions);

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
