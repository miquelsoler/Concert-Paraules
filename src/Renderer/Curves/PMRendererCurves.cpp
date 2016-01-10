//
// Created by Miquel Àngel Soler on 16/12/15.
//

#include "PMRendererCurves.h"

static const int NUM_GRADIENT_COLORS = 5;

typedef enum
{
    CURVES_DRIVE = 1,
    CURVES_X = 2,
    CURVES_Y = 3,
    CM_4 = 4,
    CM_5 = 5,
    CM_6 = 6,
    CM_7 = 7,
    CM_8 = 8,
    CM_9 = 9,
    CM_10 = 10,
} CurvesMode;

PMRendererCurves::PMRendererCurves() : PMBaseRenderer(RENDERERTYPE_CURVES)
{
    gui = new PMUICanvasCurvesRenderer(UI_RENDERERTYPE_TYPOGRAPHY, "CURVES_RENDERER",OFX_UI_FONT_MEDIUM);
    gui->init(100, 500);
    myGUI = (PMUICanvasCurvesRenderer *)gui;
}

void PMRendererCurves::setup()
{
    PMBaseRenderer::setup();
    isSilent = true;
    
    gradientPosition = 1 / (2 *float(NUM_GRADIENT_COLORS));
    gradientReverse = false;
    offsetSign = 1;
    
    rebuildPainters();
    
    
}

void PMRendererCurves::update()
{

    if (state != RENDERERSTATE_ON) return;
    
    PMBaseRenderer::update(); 

    if(getSmoothedEnergy() >= myGUI->getUpdateThreshold())
    {
        for(int i=0;i<myGUI->getNumPainters();i++)
        {
            painters[i].update();
        }
    }
}

void PMRendererCurves::drawIntoFBO()
{
    if ((state != RENDERERSTATE_ON) ) return;

    fbo.begin();
    {

        clearFBOBackground(float(gui->getBackgroundColor().r) / 255.0f,float(gui->getBackgroundColor().g) / 255.0f,float(gui->getBackgroundColor().b) / 255.0f,gui->getBackgroundFade());

        for (int i=0; i<myGUI->getNumPainters(); i++)
        {
            painters[i].draw();
        }
    }
    fbo.end();
}

void PMRendererCurves::pitchChanged(pitchParams pitchParams)
{
    PMBaseRenderer::pitchChanged(pitchParams);
}

void PMRendererCurves::energyChanged(energyParams energyParams)
{
    PMBaseRenderer::energyChanged(energyParams);
}

void PMRendererCurves::silenceStateChanged(silenceParams &silenceParams)
{
    PMBaseRenderer::silenceStateChanged(silenceParams);
}

// TODO: Remove mouse events code once audio events are working

void PMRendererCurves::mouseDragged(int x, int y, int button)
{
}

void PMRendererCurves::mousePressed(int x, int y, int button)
{
}

void PMRendererCurves::mouseReleased(int x, int y, int button)
{
}

void PMRendererCurves::switchStateOnOff()
{
    PMBaseRenderer::switchStateOnOff();
    if (state == RENDERERSTATE_OFF)
    {
        
    }
}

void PMRendererCurves::rebuildPainters()
{
    painters.clear();
    
    for (int i=0; i<myGUI->getNumPainters(); ++i)
    {
        PMCurvesPainter painter = PMCurvesPainter(myGUI,this);
        painters.push_back(painter);
    }
    
    for (int i=0; i<myGUI->getNumPainters(); ++i)
    {
        painters[i].setup();
    }
}
