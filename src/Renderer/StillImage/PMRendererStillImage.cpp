#include "PMRendererStillImage.h"

PMRendererStillImage::PMRendererStillImage() : PMBaseRenderer(RENDERERTYPE_STILLIMAGE)
{
}

void PMRendererStillImage::setup(string s)
{
    PMBaseRenderer::setup();

    filename = s;
    stillImage.load(filename);

    setState(RENDERERSTATE_ON);
}

void PMRendererStillImage::update()
{
    PMBaseRenderer::update();
    if (state != RENDERERSTATE_ON) return;
}

void PMRendererStillImage::drawIntoFBO()
{
    if (state != RENDERERSTATE_ON) return;

    fbo.begin();
    {
        ofSetColor(255);
        ofEnableAlphaBlending();

        ofSetRectMode(OF_RECTMODE_CENTER);
        stillImage.draw(ofGetWidth()/2,ofGetHeight()/2,ofGetHeight()*1.33333,ofGetHeight());
        ofSetRectMode(OF_RECTMODE_CORNER);

        ofDisableAlphaBlending();
    }
    fbo.end();
}
