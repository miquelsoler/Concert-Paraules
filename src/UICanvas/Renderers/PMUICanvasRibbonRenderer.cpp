//
// Created by Miquel Àngel Soler on 16/12/15.
//

#include "PMUICanvasRibbonRenderer.h"

static const string STR_BRUSH_BASIC                 = "BRUSH (BASIC)";
static const string STR_BRUSH_BASIC_NUMPAINTERS     = "Number of Painters";
static const string STR_BRUSH_BASIC_WIDTH           = "Stroke Width";
static const string STR_BRUSH_BASIC_SPEED           = "Stroke Speed";
static const string STR_BRUSH_BASIC_ENABLEBOUNCE    = "Enable Bounce";
static const string STR_BRUSH_ADVANCED              = "BRUSH (ADVANCED)";
static const string STR_BRUSH_ADVANCED_DIVISIONS    = "Number of Divisions";
static const string STR_BRUSH_ADVANCED_EASE         = "Ease";
static const string STR_BRUSH_ADVANCED_MAXVERT      = "Path Max Vertices";
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

    { // Brush (basic)
        addSpacer();
        addLabel(STR_BRUSH_BASIC);
        addIntSlider(STR_BRUSH_BASIC_NUMPAINTERS, 1, 100, &numPainters);
        addIntSlider(STR_BRUSH_BASIC_WIDTH, 1, 10, &strokeWidth);
        addSlider(STR_BRUSH_BASIC_SPEED, 1.01f, 100, &speed);
        addToggle(STR_BRUSH_BASIC_ENABLEBOUNCE, &enableBounce);
    }

    { // Brush (advanced)
        addSpacer();
        addLabel(STR_BRUSH_ADVANCED);
        addSlider(STR_BRUSH_ADVANCED_DIVISIONS, 0.001, 4.5, &divisions);
//        addSlider(STR_BRUSH_ADVANCED_EASE, -1.0, 10.0, &ease);
//        addSlider("Ease Randomness",0.0,1.0,&easeRandomness);
//        addIntSlider(STR_BRUSH_ADVANCED_MAXVERT,3, 4000, &pathMaxVertices);
        addSlider("Next Position Delta",0.0,1.0,&nextPositionDelta);
    }

    { // Color mode
        addSpacer();
        addLabel(STR_BRUSH_COLORMODE);

        vector<string> colorModesNames;
        colorModesNames.push_back(STR_BRUSH_COLORMODE_MFIXEDCOLOR);
        colorModesNames.push_back(STR_BRUSH_COLORMODE_MGRSPEED);
        colorModesNames.push_back(STR_BRUSH_COLORMODE_MGREDGES);
        addRadio(STR_BRUSH_COLORMODE_RADIO, colorModesNames, OFX_UI_ORIENTATION_VERTICAL);

        addImageSampler(STR_BRUSH_COLORMODE_GRIMAGE, &gradientImage);
        addIntSlider(STR_BRUSH_COLORMODE_GRID, 1, 4, &gradientId);
        addIntSlider(STR_BRUSH_COLORMODE_GRSPEED, 1, 500, &gradientSpeed);
        addIntSlider(STR_BRUSH_COLORMODE_R, 0, 255, &colorR);
        addIntSlider(STR_BRUSH_COLORMODE_G, 0, 255, &colorG);
        addIntSlider(STR_BRUSH_COLORMODE_B, 0, 255, &colorB);
    }

    if (autosize) autoSizeToFitWidgets();

    loadPreset(0);
}

void PMUICanvasRibbonRenderer::clear()
{
    PMUICanvasBaseRenderer::clear();
    superInit("RIBBON_RENDERER", OFX_UI_FONT_MEDIUM);
}

void PMUICanvasRibbonRenderer::loadPreset(int presetNumber)
{
    PMUICanvasBaseRenderer::loadPreset(presetNumber);

    ofxUIRadio *colorModeRadio = (ofxUIRadio *)getWidget(STR_BRUSH_COLORMODE_RADIO);

    ofxUIIntSlider *slColorR = (ofxUIIntSlider *)getWidget(STR_BRUSH_COLORMODE_R);
    colorR = slColorR->getValue();
    ofxUIIntSlider *slColorG = (ofxUIIntSlider *)getWidget(STR_BRUSH_COLORMODE_G);
    colorG = slColorG->getValue();
    ofxUIIntSlider *slColorB = (ofxUIIntSlider *)getWidget(STR_BRUSH_COLORMODE_B);
    colorB = slColorB->getValue();

    vector<ofxUIToggle *> toggles = colorModeRadio->getToggles();
    bool found = false;
    for (int i=0; i<toggles.size() && !found; ++i) {
        found = toggles[i]->getValue();
        if (found) colorMode = (RibbonColorMode)i;
    }

    if (!found) colorMode = RCM_Fixed;
}

void PMUICanvasRibbonRenderer::handleEvents(ofxUIEventArgs &e)
{
    PMUICanvasBaseRenderer::handleEvents(e);

    string name = e.getName();

    if (name == STR_BRUSH_COLORMODE_RADIO)
    {
        ofxUIRadio *colorModeRadio = (ofxUIRadio *)(e.widget);
        colorMode = (RibbonColorMode)(colorModeRadio->getValue());

        ofxUIIntSlider *slColorR = (ofxUIIntSlider *)getWidget(STR_BRUSH_COLORMODE_R);
        colorR = slColorR->getValue();
        ofxUIIntSlider *slColorG = (ofxUIIntSlider *)getWidget(STR_BRUSH_COLORMODE_G);
        colorG = slColorG->getValue();
        ofxUIIntSlider *slColorB = (ofxUIIntSlider *)getWidget(STR_BRUSH_COLORMODE_B);
        colorB = slColorB->getValue();
    }
}

ofColor PMUICanvasRibbonRenderer::getGradientColor(int id, float xPos)
{
    ofxUIImageSampler* is = (ofxUIImageSampler*)getWidget("Gradient");
    ofPoint p = ofPoint(xPos, ((id)*((1.0/float(numGradients))) - ((1.0/float(numGradients))/2)));

    //cout << ofToString(((_id)*((1.0/float(numGradients))) - ((1.0/float(numGradients))/2))) << endl;
    is->setValue(p);
    return is->getColor();
}
