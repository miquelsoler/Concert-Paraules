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

    // GETTERS
    ofColor         getBackgroundColor()    { return ofColor(guiColorBgRed, guiColorBgGreen, guiColorBgBlue, 255); };
    float           getBackgroundFade()     { return guiFadeBackground; };
    float           getDeltaPitch()         { return guiDeltaPitch; };
    float           getDeltaEnergy()        { return guiDeltaEnergy; };
    float           getEnergyMin()          { return guiEnergyMin; };
    float           getEnergyMax()          { return guiEnergyMax; };
    float           getPitchMin()           { return guiPitchMin; };
    float           getPitchMax()           { return guiPitchMax; };
    float           getSmoothedPitch()      { return guiSmoothPitch; };
    float           getSmoothedEnergy()     { return guiSmoothEnergy; };
    int             getMode()               { return guiMode; };
    
    // SETTERS
    void            setSmoothPitch(float p)     { guiSmoothPitch = p; };
    void            setSmoothEnergy(float e)    { guiSmoothEnergy = e; };
    void            setPitchMin(float f)        { guiPitchMin = f; };
    void            setPitchMax(float f)        { guiPitchMax = f; };
    void            setEnergyMin(float f)       { guiEnergyMin = f; };
    void            setEnergyMax(float f)       { guiEnergyMax = f; };

    virtual void keyPressed ( ofKeyEventArgs& eventArgs );
    virtual void keyReleased ( ofKeyEventArgs& eventArgs );

    int             getActivePreset();

protected:

    void            loadPreset(int presetNumber = 0);
    void            savePreset(int presetNumber = 0);

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

    // --- 
    
};


#endif //PMCONCERTPARAULES_PMUICANVASBASERENDERER_H




