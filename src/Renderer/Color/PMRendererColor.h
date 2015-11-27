//
// Created by Miquel Àngel Soler on 16/11/15.
//

#ifndef PMCONCERTPARAULES_PMRENDERERCOLOR_H
#define PMCONCERTPARAULES_PMRENDERERCOLOR_H


#define REF_X 95.047; // Observer= 2°, Illuminant= D65
#define REF_Y 100.000;
#define REF_Z 108.883;


#pragma once

#include "PMBaseRenderer.h"
#include "PMSettingsManagerAudioAnalyzers.h"
#include "PMUICanvasColorRenderer.h"

class PMRendererColor : public PMBaseRenderer
{
public:

    PMRendererColor();

    virtual void setup();
    virtual void update();
    virtual void drawIntoFBO();
    
    void keyPressed ( ofKeyEventArgs& eventArgs );

private:
    
    
    int     scanWidth;
    
    PMSettingsManagerAudioAnalyzers     *audioAnalyzersSettings;

    /// mode 1
    ofVec3f LAB2RGB(float CIEL,float CIEa,float CIEb);

    /// mode 2
    float   scanX;
    
    /// NEW STUFF
    bool        drawingHorizontal;
    float       drawingHeight;
    float       drawingPos;
};


#endif //PMCONCERTPARAULES_PMRENDERERCOLOR_H
