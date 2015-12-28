//
// Created by Miquel Àngel Soler on 16/12/15.
//

#include "PMUICanvasRibbonRenderer.h"

PMUICanvasRibbonRenderer::PMUICanvasRibbonRenderer(PMUIRendererType type, string title, int headerFontSize) : PMUICanvasBaseRenderer(type, title, headerFontSize)
{

}

void PMUICanvasRibbonRenderer::init(int posX, int posY, bool autosize, int width, int height)
{
    PMUICanvasBaseRenderer::init(posX, posY, autosize, width, height);

    gradientImage.load("./gradients/gradient4x_512x160.png");
    numGradients = 4;

    setGlobalSliderHeight(10);
    setGlobalButtonDimension(14);

    addSpacer();
    addLabel("RIBBON BASIC");
    addIntSlider("Number of painters", 1, 100, &numPainters);
    addIntSlider("Stroke width", 1, 10, &strokeWidth);
    addSlider("Speed", 1.01f, 10, &speed);
    addToggle("Enable bounce", &enableBounce);
    addImageSampler("Gradient", &gradientImage);
    addIntSlider("Gradient Id", 1, 4, &gradientId);
    addIntSlider("Gradient Speed", 1, 500, &gradientSpeed);
    addIntSlider("Ribbon R", 0, 255, &colorR);
    addIntSlider("Ribbon G", 0, 255, &colorG);
    addIntSlider("Ribbon B", 0, 255, &colorB);

    addSpacer();
    addLabel("RIBBON ADVANCED");
    addSlider("Divisions", 0.01, 0.5, &divisions);
    addIntSlider("Path Max vertices", 50, 500, &pathMaxVertices);

    if (autosize) autoSizeToFitWidgets();

    loadPreset(0);
}

void PMUICanvasRibbonRenderer::clear()
{
    PMUICanvasBaseRenderer::clear();
    superInit("RIBBON_RENDERER", OFX_UI_FONT_MEDIUM);
}

void PMUICanvasRibbonRenderer::handleEvents(ofxUIEventArgs &e)
{
    PMUICanvasBaseRenderer::handleEvents(e);

    string name = e.getName();
}

ofColor PMUICanvasRibbonRenderer::getGradientColor(int id, float xPos)
{
    ofxUIImageSampler* is = (ofxUIImageSampler*)getWidget("Gradient");
    ofPoint p = ofPoint(xPos, ((id)*((1.0/float(numGradients))) - ((1.0/float(numGradients))/2)));

    //cout << ofToString(((_id)*((1.0/float(numGradients))) - ((1.0/float(numGradients))/2))) << endl;
    is->setValue(p);
    return is->getColor();
}
