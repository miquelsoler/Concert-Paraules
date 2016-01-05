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

    
    CurvesColorMode getColorMode()          { return colorMode; };
    ofColor         getGradientColor(int id, float xPos);
    int             getGradientId()         { return gradientId; };
    int             getGradientSpeed()      { return gradientSpeed; };
    int             getNumPainters()        { return numPainters; };
    ofColor         getCurveColor()        { return ofColor(colorR, colorG, colorB, 255); }
    float           getSpeed()              { return speed; };
    float           getDelta()              { return delta; };
    float           getMaxRotation()        { return maxRotation; };
    float           getPowExponent()        { return powExponent; };
    float           getThickness()           { return thickness; };
    
private:

    int         numPainters;

    CurvesColorMode colorMode;
    ofImage     gradientImage;
    int         gradientId;
    int         gradientSpeed;
    int         numGradients;
    int         colorR, colorG, colorB;
    
    float       speed;
    float       delta;
    float       maxRotation;
    float       powExponent;
    float       thickness;
    
};


#endif //PMCONCERTPARAULES_PMUICANVASCURVESRENDERER_H
