//
// Created by Miquel Àngel Soler on 16/12/15.
//

#include "PMRendererRibbon.h"
#include "PMUICanvasRibbonRenderer.h"

PMRendererRibbon::PMRendererRibbon() : PMBaseRenderer(RENDERERTYPE_RIBBON)
{
    // GUI
    {
        gui = new PMUICanvasRibbonRenderer(UI_RENDERERTYPE_TYPOGRAPHY, "RIBBON_RENDERER",OFX_UI_FONT_MEDIUM);
        gui->init(100, 500);
    }
}

void PMRendererRibbon::setup()
{
    PMBaseRenderer::setup();
    PMUICanvasRibbonRenderer *myGUI = dynamic_cast<PMUICanvasRibbonRenderer *>(gui);

    numPainters = myGUI->getNumPainters();
    strokeWidth = myGUI->getStrokeWidth();
    ribbonColorR = (unsigned int)(myGUI->getRibbonColor().r);
    ribbonColorG = (unsigned int)(myGUI->getRibbonColor().g);
    ribbonColorB = (unsigned int)(myGUI->getRibbonColor().b);
    divisions = myGUI->getDivisions();

    buildPainters();
}

void PMRendererRibbon::update()
{
    PMBaseRenderer::update();

    PMUICanvasRibbonRenderer *myGUI = dynamic_cast<PMUICanvasRibbonRenderer *>(gui);

    // Stroke width changed
    {
        unsigned int guiStrokeWidth = myGUI->getStrokeWidth();
        if (guiStrokeWidth != strokeWidth) {
            strokeWidth = guiStrokeWidth;
            for (int i = 0; i < numPainters; ++i)
                painters[i].setSize(strokeWidth);
        }
    }

    // Ribbon color changed
    {
        unsigned int guiRibbonColorR = myGUI->getRibbonColor().r;
        unsigned int guiRibbonColorG = myGUI->getRibbonColor().g;
        unsigned int guiRibbonColorB = myGUI->getRibbonColor().b;

        if ((guiRibbonColorR != ribbonColorR) || (guiRibbonColorG != ribbonColorG) || (guiRibbonColorB != ribbonColorB))
        {
            for (int i=0; i<numPainters; ++i)
                painters[i].setColor(ofColor(guiRibbonColorR, guiRibbonColorG, guiRibbonColorB, 255));
        }
    }

    // Number of divisions changed
    {
        float guiDivisions = myGUI->getDivisions();
        if (guiDivisions != divisions)
        {
            divisions = guiDivisions;
            buildPainters();
            return;
        }
    }

    // Number of painters changed
    {
        unsigned int guiNumPainters = myGUI->getNumPainters();
        if (guiNumPainters != numPainters)
        {
            numPainters = guiNumPainters;
            buildPainters();
            return;
        }
    }

    for (int i=0; i<numPainters; ++i)
        painters[i].update();
}

void PMRendererRibbon::drawIntoFBO()
{
    ofEnableSmoothing();

    if ((state != RENDERERSTATE_ON) && (state != RENDERERSTATE_PAUSED)) return;

    fbo.begin();
    {
//        ofFloatColor fc = ofColor(gui->getColorBackground().r, gui->getColorBackground().g, gui->getColorBackground().b, 1);
//        ofClear(fc);

//        cout << "Ribbon draw: " << int(gui->getColorBack().r) << ", " << int(gui->getColorBackground().g) << ", " << int (gui->getColorBack().b) << endl;

        for (int i=0; i<numPainters; ++i)
            painters[i].draw();
    }
    fbo.end();

}

void PMRendererRibbon::setPosition(int x, int y)
{
    for (int i=0; i<numPainters; ++i)
        painters[i].setPosition(x, y);
}

void PMRendererRibbon::strokeStarted()
{
    isInStroke = true;
}

void PMRendererRibbon::strokeEnded()
{
    isInStroke = false;
    for (int i=0; i<numPainters; ++i)
        painters[i].clear();
}

void PMRendererRibbon::pitchChanged(pitchParams pitchParams)
{
    PMBaseRenderer::pitchChanged(pitchParams);

    if ((state != RENDERERSTATE_ON) && (state != RENDERERSTATE_PAUSED)) return;

    // Update brush offset
    PMUICanvasRibbonRenderer *myGUI = (PMUICanvasRibbonRenderer *)gui;


//    PMUICanvasBrushRenderer *myGUI = (PMUICanvasBrushRenderer *)gui;
//    float normalizedOffset = ofMap(myGUI->getSmoothedPitch(), 0, 1, 1.0f, -1.0f, true);
//    brush->setOffset(normalizedOffset);
//
//    brush->update();
//
//    cout << "Pitch changed: " << pitchParams.midiNote << endl;
}

void PMRendererRibbon::pauseStateChanged(pauseParams &pauseParams)
{
    cout << "Pause state changed" << endl;
    PMBaseRenderer::pauseStateChanged(pauseParams);

    if (state != RENDERERSTATE_ON) return;

    if (pauseParams.isPaused)
    {
        cout << "End stroke" << endl;
        strokeEnded();
    }
    else
    {
        cout << "Start stroke" << endl;
        strokeStarted();
    }
}

void PMRendererRibbon::energyChanged(energyParams energyParams)
{
    PMBaseRenderer::energyChanged(energyParams);
}

// TODO: Remove mouse events code once audio events are working

void PMRendererRibbon::mouseDragged(int x, int y, int button)
{
    if (button == OF_MOUSE_BUTTON_1)
        setPosition(x, y);
}

void PMRendererRibbon::mousePressed(int x, int y, int button)
{
    if (button == OF_MOUSE_BUTTON_1)
    {
        setPosition(x, y);
        strokeStarted();
    }
}

void PMRendererRibbon::mouseReleased(int x, int y, int button)
{
    strokeEnded();
}

void PMRendererRibbon::buildPainters()
{
    painters.clear();

    ofColor ribbonColor(ribbonColorR, ribbonColorG, ribbonColorB, 255);
    float dx = ofGetWidth() / 2;
    float dy = ofGetHeight() / 2;

    for (int i=0; i<numPainters; ++i)
    {
        float ease = ofRandom(0.0f, 1.0f) * 0.2f + 0.6f;
        PMRibbonPainter painter = PMRibbonPainter(ribbonColor, dx, dy, divisions, ease, strokeWidth);
        painters.push_back(painter);
    }

    isInStroke = false;

    for (int i=0; i<numPainters; ++i)
        painters[i].setup();
}
