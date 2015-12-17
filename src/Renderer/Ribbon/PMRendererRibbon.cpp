//
// Created by Miquel Àngel Soler on 16/12/15.
//

#include "PMRendererRibbon.h"
#include "PMUICanvasRibbonRenderer.h"

const unsigned int DEFAULT_NUM_PAINTERS = 50;
const unsigned int DEFAULT_SIZE = 1;
const ofColor DEFAULT_RIBBON_COLOR = ofColor(1, 1, 1, 255);

PMRendererRibbon::PMRendererRibbon() : PMBaseRenderer(RENDERERTYPE_RIBBON)
{
    // GUI
    {
        gui = new PMUICanvasRibbonRenderer(UI_RENDERERTYPE_TYPOGRAPHY, "RIBBON_RENDERER",OFX_UI_FONT_MEDIUM);
        gui->init(100, 500);
    }

    // Ribbon
    {
        for (int i=0; i<DEFAULT_NUM_PAINTERS; ++i)
        {
            PMRibbonPainter painter = PMRibbonPainter(DEFAULT_RIBBON_COLOR, ofGetWidth()/2, ofGetHeight()/2, 0, 0, 0.1, ofRandom(0.0f, 1.0f) * 0.2f + 0.6f);
            painters.push_back(painter);
        }

        size = DEFAULT_SIZE;
        isInStroke = false;
    }
}

void PMRendererRibbon::setup()
{
    PMBaseRenderer::setup();

    for (int i=0; i<DEFAULT_NUM_PAINTERS; ++i)
        painters[i].setup();
}

void PMRendererRibbon::update()
{
    PMBaseRenderer::update();

    for (int i=0; i<DEFAULT_NUM_PAINTERS; ++i)
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

        for (int i=0; i<DEFAULT_NUM_PAINTERS; ++i)
            painters[i].draw();
    }
    fbo.end();

}

void PMRendererRibbon::setPosition(int x, int y)
{
    for (int i=0; i<DEFAULT_NUM_PAINTERS; ++i)
        painters[i].setPosition(x, y);
}

void PMRendererRibbon::setColor(ofColor color)
{
    for (int i=0; i<DEFAULT_NUM_PAINTERS; ++i)
        painters[i].setColor(color);
}

void PMRendererRibbon::setSize(unsigned int _size)
{
    if (_size > 0) size = _size;
}

void PMRendererRibbon::strokeStarted()
{
    isInStroke = true;
}

void PMRendererRibbon::strokeEnded()
{
    isInStroke = false;
    for (int i=0; i<DEFAULT_NUM_PAINTERS; ++i)
        painters[i].clear();
}

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
