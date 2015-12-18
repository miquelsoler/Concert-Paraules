//
// Created by Miquel Àngel Soler on 16/12/15.
//

#include "PMRendererRibbon.h"
#include "PMUICanvasRibbonRenderer.h"

const ofColor DEFAULT_RIBBON_COLOR = ofColor(1, 1, 1, 255);

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
    size = myGUI->getStrokeWidth();
    buildPainters();
}

void PMRendererRibbon::update()
{
    PMBaseRenderer::update();

    PMUICanvasRibbonRenderer *myGUI = dynamic_cast<PMUICanvasRibbonRenderer *>(gui);

    unsigned int guiSize = myGUI->getStrokeWidth();
    if (guiSize != size)
    {
        size = guiSize;
        for (int i=0; i<numPainters; ++i)
            painters[i].setSize(size);
    }

    unsigned int guiNumPainters = myGUI->getNumPainters();
    if (guiNumPainters != numPainters)
    {
        numPainters = guiNumPainters;
        buildPainters();
        return;
    }

    for (int i=0; i<numPainters; ++i)
        painters[i].update();
}

void PMRendererRibbon::drawIntoFBO()
{
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

void PMRendererRibbon::setColor(ofColor color)
{
    for (int i=0; i<numPainters; ++i)
        painters[i].setColor(color);
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

    for (int i=0; i<numPainters; ++i)
    {
        PMRibbonPainter painter = PMRibbonPainter(DEFAULT_RIBBON_COLOR, ofGetWidth()/2, ofGetHeight()/2, 0, 0, 0.1, ofRandom(0.0f, 1.0f) * 0.2f + 0.6f, size);
        painters.push_back(painter);
    }

    isInStroke = false;

    for (int i=0; i<numPainters; ++i)
        painters[i].setup();
}
