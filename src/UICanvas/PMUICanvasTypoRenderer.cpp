//
// Created by Miquel Àngel Soler on 7/11/15.
//

#include "PMUICanvasTypoRenderer.h"

PMUICanvasTypoRenderer::PMUICanvasTypoRenderer(string title, int headerFontSize) : PMUICanvasBaseRenderer(title, headerFontSize)
{

}

void PMUICanvasTypoRenderer::init(int posX, int posY, bool autosize, int width, int height)
{
    PMUICanvasBaseRenderer::init(posX, posY, autosize, width, height);
    
    addSpacer();
    addIntSlider("Mode", 1, 3, &guiMode);
    addSpacer();
    addIntSlider("Max Font Size", 1, 200, &maxFontSize);
    addSpacer();
    addIntSlider("Min Velocity", 1, 10, &minVelocity);
    addIntSlider("Max Velocity", 10, 50, &maxVelocity);
    addSpacer();
    addSlider("Min Size", 0.1, 1.0, &minSize);
    addSlider("Max Size", 0.1, 1.0, &maxSize);
    addSpacer();
    addIntSlider("Max Age (s)", 1, 300, &maxAge);

    if (autosize) autoSizeToFitWidgets();

    loadPreset();
}

void PMUICanvasTypoRenderer::clear()
{
    ofxUICanvas::clearWidgets();
    superInit("TYPO_RENDERER", OFX_UI_FONT_MEDIUM);
}

void PMUICanvasTypoRenderer::handleEvents(ofxUIEventArgs &e)
{
    PMUICanvasBaseRenderer::handleEvents(e);
    
    string name = e.getName();
    int kind = e.getKind();
    
    if(name=="Save to default")
    {
        savePreset();
    }
}
