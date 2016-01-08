//
// Created by Miquel Àngel Soler on 3/12/15.
//

#include "PMRendererPaintbrush2.h"

PMRendererPaintbrush2::PMRendererPaintbrush2() : PMBaseRenderer(RENDERERTYPE_UNDEFINED)
{
    gui = new PMUICanvasBrushRenderer(UI_RENDERERTYPE_PAINTBRUSH, "BRUSH_RENDERER",OFX_UI_FONT_MEDIUM);
    gui->init(100, 500, true);

    brush = new PMBrushContainer2();
    PMUICanvasBrushRenderer *myGUI = (PMUICanvasBrushRenderer *) gui;
    brush->setBounces(myGUI->getBouncyWalls());
    brush->setColor(myGUI->getBrushColor());
    brush->setMinSize(myGUI->getMinBrushSize());
    brush->setMaxSize(myGUI->getMaxBrushSize());
    brush->setSpeed(myGUI->getBrushSpeed());
//    brush->setOrigin((PMBrushContainerOrigin)(myGUI->getBrushOrigin()));
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

//    if ((state == RENDERERSTATE_PAUSED) || (state == RENDERERSTATE_OFF)) return;
    if ((state == RENDERERSTATE_OFF)) return;

    brush->setBounces(myGUI->getBouncyWalls());
    brush->setColor(myGUI->getBrushColor());
    brush->setMinSize(myGUI->getMinBrushSize());
    brush->setMaxSize(myGUI->getMaxBrushSize());
    brush->setSpeed(myGUI->getBrushSpeed());
//    brush->update();
}

void PMRendererPaintbrush2::drawIntoFBO()
{
//    if ((state != RENDERERSTATE_ON) && (state != RENDERERSTATE_PAUSED)) return;
    if ((state != RENDERERSTATE_ON) ) return;

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

//    if ((state != RENDERERSTATE_ON) && (state != RENDERERSTATE_PAUSED)) return;
    if ((state != RENDERERSTATE_ON) ) return;

    // Update brush offset
    PMUICanvasBrushRenderer *myGUI = (PMUICanvasBrushRenderer *)gui;
    float normalizedOffset = ofMap(myGUI->getSmoothedPitch(), 0, 1, 1.0f, -1.0f, true);
    brush->setOffset(normalizedOffset);

    brush->update();
}

void PMRendererPaintbrush2::energyChanged(energyParams energyParams)
{
    PMBaseRenderer::energyChanged(energyParams);

    PMUICanvasBrushRenderer *myGUI = (PMUICanvasBrushRenderer *)gui;
    brush->setSize(myGUI->getSmoothedEnergy());
}
