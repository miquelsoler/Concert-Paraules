//
// Created by Miquel Àngel Soler on 16/11/15.
//

#ifndef PMCONCERTPARAULES_PMRENDERERSTILLIMAGE_H
#define PMCONCERTPARAULES_PMRENDERERSTILLIMAGE_H


#define REF_X 95.047; // Observer= 2°, Illuminant= D65
#define REF_Y 100.000;
#define REF_Z 108.883;


#pragma once

#include "PMBaseRenderer.h"
#include "PMUICanvasTextBoxRenderer.h"
#include "PMSettingsManagerPoem.h"
//#include "ofxScrollingText.h"
//#include "ofxTextBox.h"
#include "ofxFontStash.h"


class PMRendererStillImage : public PMBaseRenderer
{
public:

    PMRendererStillImage();
    virtual void setup();
    virtual void update();
    virtual void drawIntoFBO();
    
private:
    
    ofImage                         stillImage;
};


#endif //PMCONCERTPARAULES_PMRENDERERSTILLIMAGE_H
