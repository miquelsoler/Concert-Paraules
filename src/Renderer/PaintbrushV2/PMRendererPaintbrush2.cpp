//
// Created by Miquel Àngel Soler on 3/12/15.
//

#include "PMRendererPaintbrush2.h"

#include "PMUICanvasBrushRenderer.h"

PMRendererPaintbrush2::PMRendererPaintbrush2() : PMBaseRenderer(RENDERERTYPE_PAINTBRUSH)
{
    gui = new PMUICanvasBrushRenderer(UI_RENDERERTYPE_PAINTBRUSH, "BRUSH_RENDERER",OFX_UI_FONT_MEDIUM);
    gui->init(100, 500, true);

    brush = new PMBrushContainer2();
}

void PMRendererPaintbrush2::setup()
{
    PMBaseRenderer::setup();
}

void PMRendererPaintbrush2::update()
{
    PMBaseRenderer::update();

    PMUICanvasBrushRenderer *myGUI = (PMUICanvasBrushRenderer *) gui;

    if (state == RENDERERSTATE_OFF)
        brush->setOrigin((PMBrushContainerOrigin)(myGUI->getBrushOrigin()));

    if ((state == RENDERERSTATE_PAUSED) || (state == RENDERERSTATE_OFF)) return;

    brush->setBounces(myGUI->getBouncyWalls());
    brush->setColor(myGUI->getBrushColor());
    brush->setMinSize(myGUI->getMinBrushSize());
    brush->setMaxSize(myGUI->getMaxBrushSize());
//    brush->update();
}

void PMRendererPaintbrush2::drawIntoFBO()
{
    if ((state != RENDERERSTATE_ON) && (state != RENDERERSTATE_PAUSED)) return;

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

    PMUICanvasBrushRenderer *myGUI = (PMUICanvasBrushRenderer *)gui;
    brush->setSize(myGUI->getSmoothedEnergy());
}
