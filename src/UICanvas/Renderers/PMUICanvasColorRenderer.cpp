//
// Created by Miquel Àngel Soler on 7/11/15.
//

#include "PMUICanvasColorRenderer.h"

PMUICanvasColorRenderer::PMUICanvasColorRenderer(PMUIRendererType type, string title, int headerFontSize)
        : PMUICanvasBaseRenderer(type, title, headerFontSize)
{
}

void PMUICanvasColorRenderer::init(int posX, int posY, bool autosize, int width, int height)
{
    PMUICanvasBaseRenderer::init(posX, posY, autosize, width, height);

    gradientImage.load("./gradients/gradient4x_512x160.png");

    guiHorizontalVerticalProbability = 0.5;
    guiRandomOrSequential = false;
    guiDrawHorizontal = true;

    guiLeftToRight = true;
    guiUpToDown = true;
//    addSpacer();
//    addIntSlider("Mode",1,10,&guiMode);
    addSpacer();
    addLabel("COLOR");
    addImageSampler("Gradient", &gradientImage);
    addIntSlider("Gradient Id", 1, 4, &gradientId);
    numGradients = 4;

    addSpacer();
    addLabel("GRID");
    addIntSlider("Resolution X", 1, 64, &guiResolutionX);
    addIntSlider("Resolution Y", 1, 64, &guiResolutionY);
    addToggle("Drawing Horizontal?", &guiDrawHorizontal);
    addToggle("Up To Down ?", &guiUpToDown);
    addToggle("Left To Right ?", &guiLeftToRight);
    addToggle("Random ?", &guiRandomOrSequential);
    addSlider("Full Probability", 0.0, 1.0, &guiFullProbability);
    addSlider("Half Probability -/+(", 0.0, 1.0, &guiHalfProbability);
    addSlider("Horiz./Vertical Probability", 0.0, 1.0, &guiHorizontalVerticalProbability);
    addSpacer();
    addToggle("Stop on Silence?", &guiStopOnSilence);
    //addSlider("Scan Speed X",0.0,500.0,&guiScanSpeedX);
    addSlider("Scan With", 1.0, 300.0, &guiScanWidth);


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

float PMUICanvasColorRenderer::getScanWidth()
{
    return guiScanWidth;
}

ofColor PMUICanvasColorRenderer::getGradientColor(int _id, float _p)
{
    ofxUIImageSampler *is = (ofxUIImageSampler *) getWidget("Gradient");
    ofPoint p = ofPoint(_p, ((_id) * ((1.0f / float(numGradients))) - ((1.0f / float(numGradients)) / 2)));

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
