#include "PMRendererStillImage.h"
#include "PMSettingsManagerPoem.h"

PMRendererStillImage::PMRendererStillImage() : PMBaseRenderer(RENDERERTYPE_STILLIMAGE)
{
}

void PMRendererStillImage::setup()
{
    PMBaseRenderer::setup();

    string poemPath = PMSettingsManagerPoem::getInstance().getFolderPath() + "/" + PMSettingsManagerPoem::getInstance().getPoemFilename();
    stillImage.load(poemPath);

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
        stillImage.draw(0, 0, ofGetWidth(), ofGetHeight());
        ofDisableAlphaBlending();
    }
    fbo.end();
}
