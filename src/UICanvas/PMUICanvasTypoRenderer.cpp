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
    addIntSlider("Mode",1,3,&guiMode);
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


// GETTERS
int PMUICanvasTypoRenderer::getMode()
{
    return guiMode;
}
