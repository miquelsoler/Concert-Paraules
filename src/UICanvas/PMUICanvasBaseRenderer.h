//
// Created by Miquel Àngel Soler on 7/11/15.
//

#ifndef PMCONCERTPARAULES_PMUICANVASBASERENDERER_H
#define PMCONCERTPARAULES_PMUICANVASBASERENDERER_H

#include "PMBaseUICanvas.h"


class PMUICanvasBaseRenderer : public PMBaseUICanvas
{
public:

    PMUICanvasBaseRenderer(string title, int headerFontSize);

    virtual void init(int posX, int posY, bool autosize = true, int width = 0, int height = 0);
    virtual void clear();

    virtual void handleEvents(ofxUIEventArgs &e);
    virtual void savePreset();
    virtual void loadPreset();

    // GETTERS
    float           getFadeBackground();
    ofColor         getColorBackground();
    float           getDeltaPitch();
    float           getDeltaEnergy();
    
    // SETTERS
    void            setSmoothPitch(float _p);
    void            setSmoothEnergy(float _e);
    
private:

    string          rendererName;
    
    float           guiFadeBackground;
    ofColor         guiColorBackground;

    // Pitch & Energy
    float           guiSmoothPitch;
    float           guiSmoothEnergy;
    
    float           guiDeltaPitch;
    float           guiDeltaEnergy;


    
};


#endif //PMCONCERTPARAULES_PMUICANVASBASERENDERER_H




