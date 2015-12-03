//
// Created by Miquel Àngel Soler on 7/11/15.
//


#include "PMUICanvasBrushRenderer.h"


static const string STR_BRUSH_COLOR         = "BRUSH COLOR";
static const string STR_BRUSH_ORIGIN        = "BRUSH ORIGIN";
static const string STR_BRUSH_ORIGIN_LEFT   = "Left";
static const string STR_BRUSH_ORIGIN_RIGHT  = "Right";
static const string STR_BRUSH_ORIGIN_UP     = "Up";
static const string STR_BRUSH_ORIGIN_DOWN   = "Down";
static const string STR_BRUSH_SIZE          = "BRUSH SIZE";


PMUICanvasBrushRenderer::PMUICanvasBrushRenderer(PMUIRendererType type, string title, int headerFontSize) : PMUICanvasBaseRenderer(type, title, headerFontSize)
{
}

void PMUICanvasBrushRenderer::init(int posX, int posY, bool autosize, int width, int height)
{
    PMUICanvasBaseRenderer::init(posX, posY, autosize, width, height);
    
    addSpacer();
    addSpacer();
    addIntSlider("Mode",1,3,&mode);
    addSpacer();

    addLabel(STR_BRUSH_COLOR);
    addIntSlider("Brush R", 0, 255, &brushR);
    addIntSlider("Brush G", 0, 255, &brushG);
    addIntSlider("Brush B", 0, 255, &brushB);
    addSpacer();

    addLabel(STR_BRUSH_ORIGIN);
    setGlobalButtonDimension(14);
    vector<string> originNames;
    originNames.push_back(STR_BRUSH_ORIGIN_LEFT);
    originNames.push_back(STR_BRUSH_ORIGIN_RIGHT);
    originNames.push_back(STR_BRUSH_ORIGIN_UP);
    originNames.push_back(STR_BRUSH_ORIGIN_DOWN);
    ofxUIRadio *radio = addRadio(STR_BRUSH_ORIGIN, originNames, OFX_UI_ORIENTATION_HORIZONTAL);
    radio->setTriggerType(OFX_UI_TRIGGER_CHANGE);
    radio->activateToggle(STR_BRUSH_ORIGIN_LEFT);
    addSpacer();

    addLabel(STR_BRUSH_SIZE);
    addRangeSlider("Size Min-Max", 1.0, 50.0, &minBrushSize, &maxBrushSize);
    addSpacer();

    addSlider("Particle live", 0, 10, &particleLife);
    addSlider("Particle velocity", 0, 5, &particleVelocity);
    addToggle("Bouncy Walls", &bounceWalls);
    addSlider("Change Direction Curve", 0, 100, &directionFactor);

    if (autosize) autoSizeToFitWidgets();

    loadPreset(0);
}

void PMUICanvasBrushRenderer::clear()
{
    ofxUICanvas::clearWidgets();
    superInit("BRUSH_RENDERER", OFX_UI_FONT_MEDIUM);
}

void PMUICanvasBrushRenderer::handleEvents(ofxUIEventArgs &e)
{
    PMUICanvasBaseRenderer::handleEvents(e);
    string name = e.getName();

    if (name == STR_BRUSH_ORIGIN) {
        ofxUIRadio *radio = (ofxUIRadio *)e.widget;
        brushOrigin = radio->getValue();
    }
}


// GETTERS

ofColor PMUICanvasBrushRenderer::getBrushColor()
{
    return ofColor(brushR, brushG, brushB);
}
