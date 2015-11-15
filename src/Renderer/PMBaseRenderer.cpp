//
// Created by Miquel Àngel Soler on 28/10/15.
//

#include "PMBaseRenderer.h"

PMBaseRenderer::PMBaseRenderer(unsigned int _numInputs)
{
    fbo.allocate(ofGetWidth(), ofGetHeight(), GL_RGBA32F_ARB);

    numInputs = _numInputs;
}

void PMBaseRenderer::setup()
{
    cout << "PMBaseRenderer::setup()" << endl;
    fbo.begin();
    {
        // Often the FBO will contain artifacts from the memory that the graphics card has just allocated for it,
        // so it's good to clear it before starting to draw it
        ofClear(255, 255, 255, 0);
    }
    fbo.end();

    shouldPaint = false;

//    ofSetBackgroundAuto(false);
}

void PMBaseRenderer::update()
{
}

void PMBaseRenderer::draw()
{
    ofClear(255, 255, 255, 255);
    drawIntoFBO();
}

void PMBaseRenderer::setShouldPaint(unsigned int inputIndex, bool _shouldPaint)
{
    shouldPaint = _shouldPaint;
}
