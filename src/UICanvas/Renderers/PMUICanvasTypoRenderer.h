//
// Created by Miquel Àngel Soler on 7/11/15.
//

#ifndef PMCONCERTPARAULES_PMUICANVASTYPORENDERER_H
#define PMCONCERTPARAULES_PMUICANVASTYPORENDERER_H

#include "PMBaseUICanvas.h"
#include "PMUICanvasBaseRenderer.h"

class PMUICanvasTypoRenderer : public PMUICanvasBaseRenderer
{
public:

    PMUICanvasTypoRenderer(PMUIRendererType type, string title, int headerFontSize);

    virtual void init(int posX, int posY, bool autosize = true, int width = 0, int height = 0);
    virtual void clear();

    virtual void handleEvents(ofxUIEventArgs &e);
    
    // GETTERS
    int getMinVelocity()    { return minVelocity; };
    int getMaxVelocity()    { return maxVelocity; };
    float getMinSize()      { return minSize; };
    float getMaxSize()      { return maxSize; };
    float getBounceFactor() { return bounceFactor; };
    int getMaxAge()         { return maxAge; };
    float getGravityX()     { return gravityX; };
    float getGravityY()     { return gravityY; };
    float getSinusFreq()    { return guiSinusFreq; };
    float getLetterSpeedMs() {return guiLetterSpeedMs; };
    // SETTERS
    void setGravityX(float f)      { gravityX = f;};
    void setGravityY(float f)      { gravityY = f;};

    // ELOI
    float getSinusAmplitude()       { return guiSinusAmplitude; };
    float getAddLetterSensitivity() { return guiAddLetterSensitivity; };
    ofColor getLetterColor()        { return ofColor(colorR,colorG,colorB);};
    
private:

    int     minVelocity;
    int     maxVelocity;
    float   minSize;
    float   maxSize;
    float   bounceFactor;
    int     maxAge;
    float   gravityX;
    float   gravityY;
    
    // ELOI
    float   guiSinusFreq;
    float   guiSinusAmplitude;
    float   guiAddLetterSensitivity;
    float   guiLetterSpeedMs;
    int     colorR;
    int     colorG;
    int     colorB;
};


#endif //PMCONCERTPARAULES_PMUICANVASTYPORENDERER_H




