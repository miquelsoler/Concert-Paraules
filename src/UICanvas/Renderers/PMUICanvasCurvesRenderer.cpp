//
// Created by Miquel Àngel Soler on 16/12/15.
//

#include "PMUICanvasCurvesRenderer.h"

static const string STR_BRUSH_COLORMODE             = "BRUSH COLOR MODE";
static const string STR_BRUSH_COLORMODE_RADIO       = "RADIO BRUSH COLOR MODE";
static const string STR_BRUSH_COLORMODE_MFIXEDCOLOR = "Fixed Color";
static const string STR_BRUSH_COLORMODE_MGRSPEED    = "Gradient (with Speed)";
static const string STR_BRUSH_COLORMODE_MGREDGES    = "Gradient (edges)";
static const string STR_BRUSH_COLORMODE_GRIMAGE     = "Gradient";
static const string STR_BRUSH_COLORMODE_GRID        = "Gradient ID";
static const string STR_BRUSH_COLORMODE_GRSPEED     = "Gradient Speed";
static const string STR_BRUSH_COLORMODE_R           = "Fixed Red";
static const string STR_BRUSH_COLORMODE_G           = "Fixed Green";
static const string STR_BRUSH_COLORMODE_B           = "Fixed Blue";
static const string STR_NUM_PAINTERS                = "Num. Painters";
static const string STR_SPEED                       = "Speed";
static const string STR_DELTA                       = "Delta";
static const string STR_POW                         = "Pow Exponent";
static const string STR_MAX_ROTATION                = "Max Rotation";
static const string STR_THICKNESS                   = "Thickness";
static const string STR_BUBBLENESS                  = "Bubbleness";

PMUICanvasCurvesRenderer::PMUICanvasCurvesRenderer(PMUIRendererType type, string title, int headerFontSize)
        : PMUICanvasBaseRenderer(type, title, headerFontSize)
{
}

void PMUICanvasCurvesRenderer::init(int posX, int posY, bool autosize, int width, int height)
{
    PMUICanvasBaseRenderer::init(posX, posY, autosize, width, height);

    gradientImage.load("./gradients/gradient4x_512x160_CURVES.png");
    numGradients = 4;

    setGlobalSliderHeight(10);
    setGlobalButtonDimension(14);

    { // Color mode
        addSpacer();

        addIntSlider(STR_NUM_PAINTERS, 1, 100, &numPainters);
        addSlider(STR_SPEED, 0.0, 200.0, &speed);
        addSlider(STR_DELTA, 0.0, 1.0, &delta);
        addSlider(STR_POW, 0.0, 5.0, &powExponent);
        addSlider(STR_MAX_ROTATION, 0.0, 180.0, &maxRotation);
        addSlider(STR_THICKNESS, 0.0, 90.0, &thickness);
        addSlider(STR_BUBBLENESS, 0.0,1.0, &bubbleness);
//        addSlider("Energy Threshold for Update",0.0,0.25,&updateThreshold);
        addSpacer();
        addLabel(STR_BRUSH_COLORMODE);

        vector<string> colorModesNames;
        colorModesNames.push_back(STR_BRUSH_COLORMODE_MFIXEDCOLOR);
        colorModesNames.push_back(STR_BRUSH_COLORMODE_MGRSPEED);
        colorModesNames.push_back(STR_BRUSH_COLORMODE_MGREDGES);
        addRadio(STR_BRUSH_COLORMODE_RADIO, colorModesNames, OFX_UI_ORIENTATION_VERTICAL);

        addImageSampler(STR_BRUSH_COLORMODE_GRIMAGE, &gradientImage);
        addIntSlider(STR_BRUSH_COLORMODE_GRID, 1, 4, &gradientId);
        addSlider(STR_BRUSH_COLORMODE_GRSPEED, 0.0, 0.10, &gradientSpeed);
        addIntSlider(STR_BRUSH_COLORMODE_R, 0, 255, &colorR);
        addIntSlider(STR_BRUSH_COLORMODE_G, 0, 255, &colorG);
        addIntSlider(STR_BRUSH_COLORMODE_B, 0, 255, &colorB);
    }

    if (autosize) autoSizeToFitWidgets();

    gradientPos = 0.0f;
//    updateThreshold = 0.0f;
    
    loadPreset(selectedPreset);
}

void PMUICanvasCurvesRenderer::clear()
{
    PMUICanvasBaseRenderer::clear();
    //superInit("CURVES_RENDERER", OFX_UI_FONT_MEDIUM);
}

void PMUICanvasCurvesRenderer::loadPreset(int presetNumber)
{
    PMUICanvasBaseRenderer::loadPreset(presetNumber);

    ofxUIRadio *colorModeRadio = (ofxUIRadio *) getWidget(STR_BRUSH_COLORMODE_RADIO);

    ofxUIIntSlider *slColorR = (ofxUIIntSlider *) getWidget(STR_BRUSH_COLORMODE_R);
    colorR = slColorR->getValue();
    ofxUIIntSlider *slColorG = (ofxUIIntSlider *) getWidget(STR_BRUSH_COLORMODE_G);
    colorG = slColorG->getValue();
    ofxUIIntSlider *slColorB = (ofxUIIntSlider *) getWidget(STR_BRUSH_COLORMODE_B);
    colorB = slColorB->getValue();

    vector<ofxUIToggle *> toggles = colorModeRadio->getToggles();
    bool found = false;
    for (int i = 0; i < toggles.size() && !found; ++i) {
        found = toggles[i]->getValue();
        if (found) colorMode = (CurvesColorMode) i;
    }

    if (!found) colorMode = CCM_Fixed;
}

void PMUICanvasCurvesRenderer::handleEvents(ofxUIEventArgs &e)
{
    PMUICanvasBaseRenderer::handleEvents(e);

    string name = e.getName();

    if (name == STR_BRUSH_COLORMODE_RADIO) {
        ofxUIRadio *colorModeRadio = (ofxUIRadio *) (e.widget);
        colorMode = (CurvesColorMode) (colorModeRadio->getValue());

        ofxUIIntSlider *slColorR = (ofxUIIntSlider *) getWidget(STR_BRUSH_COLORMODE_R);
        colorR = slColorR->getValue();
        ofxUIIntSlider *slColorG = (ofxUIIntSlider *) getWidget(STR_BRUSH_COLORMODE_G);
        colorG = slColorG->getValue();
        ofxUIIntSlider *slColorB = (ofxUIIntSlider *) getWidget(STR_BRUSH_COLORMODE_B);
        colorB = slColorB->getValue();
    }
}

ofColor PMUICanvasCurvesRenderer::getGradientColor(int id, float xPos)
{
    ofxUIImageSampler *is = (ofxUIImageSampler *) getWidget("Gradient");
    ofPoint p = ofPoint(xPos, ((id) * ((1.0f / float(numGradients))) - ((1.0f / float(numGradients)) / 2)));

    is->setValue(p);
    return is->getColor();
}

void PMUICanvasCurvesRenderer::update()
{
    ofxUICanvas::update();
    
    gradientPos = fmod(gradientPos + getGradientSpeed(),1.0);
}

ofColor PMUICanvasCurvesRenderer::getCurveColor()
{
    if(getColorMode()==CCM_Fixed)
    {
        return ofColor(colorR, colorG, colorB, 255);
    }
    else if(getColorMode()==CCM_GradientSpeed)
    {
        ofxUIImageSampler *is = (ofxUIImageSampler *) getWidget("Gradient");
        int id = int(getGradientId());
        ofPoint p = ofPoint(gradientPos, ((id) * ((1.0f / float(numGradients))) - ((1.0f / float(numGradients)) / 2)));
        is->setValue(p);
        return is->getColor();
        
        
    }
    
}
