//
// Created by Miquel Àngel Soler on 16/12/15.
//

#include "PMRendererRibbon.h"
#include "PMUICanvasRibbonRenderer.h"

typedef enum
{
    RM_0 = 0,
    RM_1 = 1,
    RM_2 = 2,
    RM_3 = 3,
    RM_4 = 4,
    RM_5 = 5,
    RM_6 = 6,
    RM_7 = 7,
    RM_8 = 8,
    RM_9 = 9,
    RM_MOUSE = 10,
} RibbonMode;

PMRendererRibbon::PMRendererRibbon() : PMBaseRenderer(RENDERERTYPE_RIBBON)
{
    // GUI
    {
        gui = new PMUICanvasRibbonRenderer(UI_RENDERERTYPE_TYPOGRAPHY, "RIBBON_RENDERER",OFX_UI_FONT_MEDIUM);
        gui->init(100, 500);
    }

    myGUI = (PMUICanvasRibbonRenderer *)gui;
}

void PMRendererRibbon::setup()
{
    PMBaseRenderer::setup();

    numPainters = myGUI->getNumPainters();
    strokeWidth = myGUI->getStrokeWidth();
    ribbonColorR = (unsigned int)(myGUI->getRibbonColor().r);
    ribbonColorG = (unsigned int)(myGUI->getRibbonColor().g);
    ribbonColorB = (unsigned int)(myGUI->getRibbonColor().b);
    divisions = myGUI->getDivisions();

    buildPainters();
    setPosition(ofGetWidth()/2, ofGetHeight()/2);
//    strokeStarted();
}

void PMRendererRibbon::update()
{
    PMBaseRenderer::update();

    if ((state != RENDERERSTATE_ON) && (state != RENDERERSTATE_PAUSED)) return;

    int mode = myGUI->getMode();

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

    switch(mode)
    {
        case 1:
        {
            break;
        }
    }

    if (!isInStroke) return;

    for (int i=0; i<numPainters; ++i)
        painters[i].update();
}

void PMRendererRibbon::drawIntoFBO()
{
    ofEnableSmoothing();

    if ((state != RENDERERSTATE_ON) && (state != RENDERERSTATE_PAUSED)) return;

    fbo.begin();
    {
//        ofFloatColor fc = ofColor(gui->getBackgroundColor().r, gui->getBackgroundColor().g, gui->getBackgroundColor().b, 1);
//        ofClear(fc);
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

void PMRendererRibbon::setX(int x)
{
    for (int i=0; i<numPainters; ++i)
        painters[i].setX(x);
}

void PMRendererRibbon::setY(int y)
{
    for (int i=0; i<numPainters; ++i)
        painters[i].setY(y);
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

    int mode = myGUI->getMode();
    if (mode == RM_MOUSE) return;

    float x = ofMap(myGUI->getSmoothedPitch(), 0, 1, 0, ofGetWidth());
    setX(int(x));
}

void PMRendererRibbon::energyChanged(energyParams energyParams)
{
    PMBaseRenderer::energyChanged(energyParams);

    if ((state != RENDERERSTATE_ON) && (state != RENDERERSTATE_PAUSED)) return;

    int mode = myGUI->getMode();
    if (mode == RM_MOUSE) return;

    float y = ofMap(myGUI->getSmoothedEnergy(), 0, 1, 0, ofGetHeight());
    setY(int(y));
}

void PMRendererRibbon::silenceStateChanged(silenceParams &silenceParams)
{
    PMBaseRenderer::silenceStateChanged(silenceParams);

    int mode = myGUI->getMode();
    if (mode == RM_MOUSE) return;

    if (state != RENDERERSTATE_ON)
    {
        cout << "End stroke (state not ON)" << endl;
        strokeEnded();
        return;
    }

    if (!(silenceParams.isSilent))
    {
        cout << "Start stroke (silence stopped)" << endl;
        strokeStarted();
    }
    else
    {
        cout << "End stroke (new silence)" << endl;
        strokeEnded();
    }
}

// TODO: Remove mouse events code once audio events are working

void PMRendererRibbon::mouseDragged(int x, int y, int button)
{
    int mode = myGUI->getMode();
    if (mode != RM_MOUSE) return;

    if (button == OF_MOUSE_BUTTON_1)
        setPosition(x, y);
}

void PMRendererRibbon::mousePressed(int x, int y, int button)
{
    int mode = myGUI->getMode();
    if (mode != RM_MOUSE) return;

    if (button == OF_MOUSE_BUTTON_1)
    {
        setPosition(x, y);
        strokeStarted();
    }
}

void PMRendererRibbon::mouseReleased(int x, int y, int button)
{
    int mode = myGUI->getMode();
    if (mode != RM_MOUSE) return;

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
