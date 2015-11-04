//
// Created by Miquel Àngel Soler on 28/10/15.
//

#include "PMBaseRenderer.h"

PMBaseRenderer::PMBaseRenderer()
{
    fbo.allocate(ofGetWidth(), ofGetHeight(), GL_RGBA32F);

    fbo.begin();
    {
        // Often the FBO will contain artifacts from the memory that the graphics card has just allocated for it,
        // so it's good to clear it before starting to draw it
        ofClear(255, 255, 255, 255);
    }
    fbo.end();
}

void PMBaseRenderer::setup()
{
    ofSetBackgroundAuto(false);
}

void PMBaseRenderer::update()
{
}

void PMBaseRenderer::draw()
{
    drawIntoFBO();
}
