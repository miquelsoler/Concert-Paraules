#include "PMRendererStillImage.h"
#include "PMSettingsManagerPoem.h"


// TODO : finish to get Text from poems ... something does'nt work with getText() !!?!!


//--------------------------------------------------------------
PMRendererStillImage::PMRendererStillImage() : PMBaseRenderer(RENDERERTYPE_TEXTBOX)
{
}

//--------------------------------------------------------------
void PMRendererStillImage::setup()
{
    PMBaseRenderer::setup();
    
    stillImage.load("./images/plantillaText.jpg");

    //----------------------------
    setState(RENDERERSTATE_ON);

}


//--------------------------------------------------------------
void PMRendererStillImage::update()
{
    PMBaseRenderer::update();

    if (state != RENDERERSTATE_ON) return;
    
    

}

//--------------------------------------------------------------
void PMRendererStillImage::drawIntoFBO()
{
    
    if (state != RENDERERSTATE_ON) return;

    fbo.begin();
    {
        ofSetColor(255);
        ofEnableAlphaBlending();
        stillImage.draw(0,0,ofGetWidth(),ofGetHeight());
        ofDisableAlphaBlending();
    }
    fbo.end();

}

