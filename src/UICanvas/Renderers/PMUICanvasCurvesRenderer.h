//
// Created by Miquel Àngel Soler on 16/12/15.
//

#ifndef PMCONCERTPARAULES_PMUICANVASCURVESRENDERER_H
#define PMCONCERTPARAULES_PMUICANVASCURVESRENDERER_H

#include "PMBaseUICanvas.h"
#include "PMUICanvasBaseRenderer.h"

typedef enum
{
    CCM_Fixed = 0,
    CCM_GradientSpeed = 1,
    CCM_GradientEdges = 2
} CurvesColorMode;

class PMUICanvasCurvesRenderer : public PMUICanvasBaseRenderer
{
public:

    PMUICanvasCurvesRenderer(PMUIRendererType type, string title, int headerFontSize);

    virtual void init(int posX, int posY, bool autosize = true, int width = 0, int height = 0);
    virtual void clear();
    virtual void loadPreset(int presetNumber = 0);
    virtual void handleEvents(ofxUIEventArgs &e);

    
    CurvesColorMode getColorMode()          { return colorMode; }
    ofColor         getGradientColor(int id, float xPos);
    int             getGradientId()         { return gradientId; }
    int             getGradientSpeed()      { return gradientSpeed; }

private:



    CurvesColorMode colorMode;
    ofImage     gradientImage;
    int         gradientId;
    int         gradientSpeed;
    int         numGradients;
    int         colorR, colorG, colorB;
    
};


#endif //PMCONCERTPARAULES_PMUICANVASCURVESRENDERER_H
