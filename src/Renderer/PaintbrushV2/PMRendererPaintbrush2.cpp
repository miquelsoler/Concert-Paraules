//
// Created by Miquel Àngel Soler on 3/12/15.
//

#include "PMRendererPaintbrush2.h"

#include "PMUICanvasBrushRenderer.h"

PMRendererPaintbrush2::PMRendererPaintbrush2() : PMBaseRenderer(RENDERERTYPE_PAINTBRUSH)
{
    brush = new PMBrushContainer2();

    gui = new PMUICanvasBrushRenderer(UI_RENDERERTYPE_PAINTBRUSH, "BRUSH_RENDERER",OFX_UI_FONT_MEDIUM);
    gui->init(100, 500, 200, 300);
}

void PMRendererPaintbrush2::setup()
{
    PMBaseRenderer::setup();
}

void PMRendererPaintbrush2::update()
{
    PMBaseRenderer::update();

    if ((state == RENDERERSTATE_PAUSED) || (state == RENDERERSTATE_OFF)) return;

    PMUICanvasBrushRenderer *myGUI = (PMUICanvasBrushRenderer *) gui;

    brush->setBounces(myGUI->getBouncyWalls());
    brush->setColor(myGUI->getBrushColor());
//    brush->update();

    cout << "PMRendererPaintbrush2::update()" << endl;
}

void PMRendererPaintbrush2::drawIntoFBO()
{
    if ((state != RENDERERSTATE_ON) && (state != RENDERERSTATE_PAUSED)) return;

    PMUICanvasBrushRenderer *myGUI = (PMUICanvasBrushRenderer *)gui;

    fbo.begin();
    {
        if (state == RENDERERSTATE_ON) brush->draw();
    }
    fbo.end();

    ofSetColor(255, 255, 255, 255);
}

void PMRendererPaintbrush2::pitchChanged(pitchParams pitchParams)
{
    PMBaseRenderer::pitchChanged(pitchParams);

    if ((state != RENDERERSTATE_ON) && (state != RENDERERSTATE_PAUSED)) return;

    brush->update();
}

void PMRendererPaintbrush2::energyChanged(energyParams energyParams)
{
    PMBaseRenderer::energyChanged(energyParams);
}
