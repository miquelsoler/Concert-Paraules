//
// Created by Miquel Àngel Soler on 7/11/15.
//

#include "PMUICanvasColorRenderer.h"

PMUICanvasColorRenderer::PMUICanvasColorRenderer(PMUIRendererType type, string title, int headerFontSize) : PMUICanvasBaseRenderer(type, title, headerFontSize)
{
}

void PMUICanvasColorRenderer::init(int posX, int posY, bool autosize, int width, int height)
{
    PMUICanvasBaseRenderer::init(posX, posY, autosize, width, height);

    gradientImage.load("./gradients/test4x_v1.png");
    
    guiHorizontalVerticalProbability = 0.5;
    
    addSpacer();
    addIntSlider("Mode",1,10,&guiMode);
    addSpacer();
    addLabel("COLOR");
    addImageSampler("Gradient", &gradientImage);
    addIntSlider("Gradient Id",1,4,&gradientId);
    numGradients = 4;

    addSpacer();
    addLabel("GRID");
    addIntSlider("Resolution X",1,64,&guiResolutionX);
    addIntSlider("Resolution Y",1,64,&guiResolutionY);
    addSlider("Full Probability",0.0,1.0,&guiFullProbability);
    addSlider("Half Probability -/+(",0.0,1.0,&guiHalfProbability);
    addSlider("Horiz./Vertical Probability",0.0,1.0,&guiHorizontalVerticalProbability);
    addSpacer();
    addToggle("Stop on Silence?",&guiStopOnSilence);
    addSlider("Scan Speed X",0.0,5.0,&guiScanSpeedX);
    addSlider("Scan With",0.0,150.0,&guiScanWidth);

    
    if (autosize) autoSizeToFitWidgets();

    loadPreset(0);
}

void PMUICanvasColorRenderer::clear()
{
    ofxUICanvas::clearWidgets();
    superInit("COLOR_RENDERER", OFX_UI_FONT_MEDIUM);
}

void PMUICanvasColorRenderer::handleEvents(ofxUIEventArgs &e)
{
    PMUICanvasBaseRenderer::handleEvents(e);
    
    string name = e.getName();
}


// GETTERS
float PMUICanvasColorRenderer::getScanSpeedX()
{
    return guiScanSpeedX;
}
int PMUICanvasColorRenderer::getMode()
{
    return guiMode;
}
float PMUICanvasColorRenderer::getScanWidth()
{
    return guiScanWidth;
}

ofColor PMUICanvasColorRenderer::getGradientColor(int _id,float _p)
{
    ofxUIImageSampler* is = (ofxUIImageSampler*)getWidget("Gradient");
    ofPoint p = ofPoint( _p, ((_id)*((1.0/float(numGradients))) - ((1.0/float(numGradients))/2)));
    
    //cout << ofToString(((_id)*((1.0/float(numGradients))) - ((1.0/float(numGradients))/2))) << endl;
    is->setValue(p);
    return is->getColor();
}

int PMUICanvasColorRenderer::getGradientId()
{
    return gradientId;
}


// SETTERS
void PMUICanvasColorRenderer::setScanSpeedX(float _s)
{
    guiScanSpeedX = _s;
}



