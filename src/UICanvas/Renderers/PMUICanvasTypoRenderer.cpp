//
// Created by Miquel Àngel Soler on 7/11/15.
//

#include "PMUICanvasTypoRenderer.h"

PMUICanvasTypoRenderer::PMUICanvasTypoRenderer(PMUIRendererType type, string title, int headerFontSize) : PMUICanvasBaseRenderer(type, title, headerFontSize)
{
}

void PMUICanvasTypoRenderer::init(int posX, int posY, bool autosize, int width, int height)
{
    PMUICanvasBaseRenderer::init(posX, posY, autosize, width, height);
    
    addSpacer();
    addLabel("VELOCITY");
    addIntSlider("Min Velocity", 1, 10, &minVelocity);
    addIntSlider("Max Velocity", 10, 50, &maxVelocity);
    addSpacer();
    addLabel("SIZE");
    addSlider("Min Size", 0.1, 1.0, &minSize);
    addSlider("Max Size", 0.1, 1.0, &maxSize);
    addSpacer();
    addLabel("BOUNCE");
    addSlider("Bounce Factor", 0.1, 1.0, &bounceFactor);
    addSpacer();
    addLabel("LETTER MAX AGE");
    addIntSlider("Max Age (s)", 1, 300, &maxAge);
    addSpacer();
    addLabel("GRAVITY");
    addSlider("Gravity X", -50, 50, &gravityX);
    addSlider("Gravity Y", -50, 50, &gravityY);

    if (autosize) autoSizeToFitWidgets();

    loadPreset(0);
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
}
