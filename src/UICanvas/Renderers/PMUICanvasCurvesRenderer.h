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
    virtual void update();
    virtual void clear();
    virtual void loadPreset(int presetNumber = 0);
    virtual void handleEvents(ofxUIEventArgs &e);

    
    CurvesColorMode getColorMode()          { return colorMode; };
    ofColor         getGradientColor(int id, float xPos);
    int             getGradientId()         { return gradientId; };
    float           getGradientSpeed()      { return gradientSpeed; };
    int             getNumPainters()        { return numPainters; };
    ofColor         getCurveColor();
    float           getSpeed()              { return speed; };
    float           getDelta()              { return delta; };
    float           getMaxRotation()        { return maxRotation; };
    float           getPowExponent()        { return powExponent; };
    float           getThickness()          { return thickness; };
    float           getBubbleness()         { return bubbleness;};
    float           getUpdateThreshold()    { return updateThreshold;};
private:

    int         numPainters;

    CurvesColorMode colorMode;
    ofImage     gradientImage;
    int         gradientId;
    float       gradientSpeed;
    int         numGradients;
    int         colorR, colorG, colorB;
    
    float       speed;
    float       delta;
    float       maxRotation;
    float       powExponent;
    float       thickness;
    
    float       gradientPos;
    
    float       bubbleness;
    
    float       updateThreshold;
    
};


#endif //PMCONCERTPARAULES_PMUICANVASCURVESRENDERER_H
