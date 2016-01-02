//
// Created by Miquel Àngel Soler on 16/12/15.
//

#ifndef PMCONCERTPARAULES_PMUICANVASRIBBONRENDERER_H
#define PMCONCERTPARAULES_PMUICANVASRIBBONRENDERER_H

#include "PMBaseUICanvas.h"
#include "PMUICanvasBaseRenderer.h"

typedef enum
{
    RCM_Fixed = 0,
    RCM_GradientSpeed = 1,
    RCM_GradientEdges = 2
} RibbonColorMode;

class PMUICanvasRibbonRenderer : public PMUICanvasBaseRenderer
{
public:

    PMUICanvasRibbonRenderer(PMUIRendererType type, string title, int headerFontSize);

    virtual void init(int posX, int posY, bool autosize = true, int width = 0, int height = 0);
    virtual void clear();

    virtual void loadPreset(int presetNumber = 0);

    virtual void handleEvents(ofxUIEventArgs &e);

    unsigned int    getNumPainters()        { return (unsigned int)numPainters; }
    unsigned int    getStrokeWidth()        { return (unsigned int)strokeWidth; }
    float           getSpeed()              { return speed; }
    bool            getBounceEnabled()      { return enableBounce; }

    float           getDivisions()          { return divisions; }
    float           getEase()               { return ease; }
    float           getEaseRandomness()     { return easeRandomness; };
    int             getPathNumVertices()    { return pathMaxVertices; }

    RibbonColorMode getColorMode()          { return colorMode; }
    ofColor         getGradientColor(int id, float xPos);
    int             getGradientId()         { return gradientId; }
    int             getGradientSpeed()      { return gradientSpeed; }
    ofColor         getRibbonColor()        { return ofColor(colorR, colorG, colorB, 255); }
    float           getNextPositionDelta()  { return nextPositionDelta; };

private:

    int     numPainters;
    int     strokeWidth;
    float   speed;
    bool    enableBounce;

    float   divisions;
    float   ease;
    float   easeRandomness;
    int     pathMaxVertices;

    RibbonColorMode colorMode;
    ofImage     gradientImage;
    int         gradientId;
    int         gradientSpeed;
    int         numGradients;
    int         colorR, colorG, colorB;
    
    float       nextPositionDelta;
};


#endif //PMCONCERTPARAULES_PMUICANVASRIBBONRENDERER_H
