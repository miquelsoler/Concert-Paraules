//
// Created by Miquel Àngel Soler on 7/11/15.
//

#ifndef PMCONCERTPARAULES_PMUICANVASBASERENDERER_H
#define PMCONCERTPARAULES_PMUICANVASBASERENDERER_H

#include "PMBaseUICanvas.h"

typedef enum
{
    RENDERER_PRESET_LOAD = 0,
    RENDERER_PRESET_SAVE = 1
} RENDERER_PRESET_MODE;

typedef enum
{
    UI_RENDERERTYPE_PAINTBRUSH = 0,
    UI_RENDERERTYPE_TYPOGRAPHY = 1,
    UI_RENDERERTYPE_COLOR = 2
} PMUIRendererType;

class PMUICanvasBaseRenderer : public PMBaseUICanvas
{
public:

    PMUICanvasBaseRenderer(PMUIRendererType type, string title, int headerFontSize);

    virtual void init(int posX, int posY, bool autosize = true, int width = 0, int height = 0);
    virtual void clear();

    virtual void handleEvents(ofxUIEventArgs &e);
    virtual void windowResized(ofResizeEventArgs& data);


    // GETTERS
    ofColor         getBackgroundColor()    { return ofColor(guiColorBgRed, guiColorBgGreen, guiColorBgBlue, 255); }
    float           getBackgroundFade()     { return guiFadeBackground; }
    virtual int     getMode()               { return guiMode; }
    
    // SETTERS

    void            keyPressed(int key);
    void            keyReleased(int key);

    int             getActivePreset();
    
protected:

    virtual void    loadPreset(int presetNumber = 0);
    void            savePreset(int presetNumber = 0);

    int            selectedPreset;

private:

    PMUIRendererType        type;
    string                  rendererName;

    ofxUIToggleMatrix       *presetsMatrix;
    RENDERER_PRESET_MODE    presetsMode;

    // GUI VARS
    //----------------
    int             guiMode;
    float           guiFadeBackground;
    int             guiColorBgRed;
    int             guiColorBgGreen;
    int             guiColorBgBlue;
//    ofColor         guiColorBackground;

    // Pitch
    float           guiSmoothPitch;
    float           guiDeltaPitch;
    float           guiPitchMin;
    float           guiPitchMax;
    
    // Energy
    float           guiDeltaEnergy;
    float           guiSmoothEnergy;
    float           guiEnergyMin;
    float           guiEnergyMax;

    void resetGUIPosition();
};


#endif //PMCONCERTPARAULES_PMUICANVASBASERENDERER_H




