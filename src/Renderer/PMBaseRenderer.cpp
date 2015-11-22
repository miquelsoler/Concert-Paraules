//
// Created by Miquel Àngel Soler on 28/10/15.
//

#include "PMBaseRenderer.h"

PMBaseRenderer::PMBaseRenderer(PMRendererType _type, unsigned int _numInputs)
{
    fbo.allocate(ofGetWidth(), ofGetHeight(), GL_RGBA32F_ARB);

    type = _type;
    numInputs = _numInputs;
    
    
    /// GUI
    //guiBaseRenderer = PMUICanvasBaseRenderer::guiBaseRenderer();
    guiBaseRenderer = new PMUICanvasBaseRenderer("GUI BASE RENDERER",OFX_UI_FONT_MEDIUM);
    guiBaseRenderer->init(100, 500, 200, 300);
    
}

void PMBaseRenderer::setup()
{
    fbo.begin();
    {
        // Often the FBO will contain artifacts from the memory that the graphics card has just allocated for it,
        // so it's good to clear it before starting to draw it
        ofClear(0, 0, 0, 0);
    }
    fbo.end();

    isActive.assign(numInputs, true); // Init all elements with false;

//    ofSetBackgroundAuto(false);
}

void PMBaseRenderer::update()
{
    drawIntoFBO();
}

void PMBaseRenderer::draw()
{
    ofClear(255, 255, 255, 255);
    fbo.draw(0, 0);

//    // set background for base renderer
//    ofColor c = ofColor(guiBaseRenderer->getColorBackground().r,guiBaseRenderer->getColorBackground().g,guiBaseRenderer->getColorBackground().b,255);
//    ofClear(c);
    
    // draw the fbo with contents to screen
    fbo.draw(0, 0);
    
    // draw gui of base renderer
    guiBaseRenderer->draw();
}

void PMBaseRenderer::setShouldPaint(unsigned int inputIndex, bool _shouldPaint)
{
    isActive[inputIndex] = _shouldPaint;
}
