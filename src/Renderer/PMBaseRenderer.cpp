//
// Created by Miquel Àngel Soler on 28/10/15.
//

#include "PMBaseRenderer.h"

PMBaseRenderer::PMBaseRenderer(PMRendererType _type, unsigned int _numInputs)
{
    fbo.allocate(ofGetWidth(), ofGetHeight(), GL_RGBA32F_ARB);

    type = _type;
    numInputs = _numInputs;
    
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
    ofClear(0, 0, 0, 255);
    fbo.draw(0, 0);
}

void PMBaseRenderer::setShouldPaint(unsigned int inputIndex, bool _shouldPaint)
{
    isActive[inputIndex] = _shouldPaint;
}
