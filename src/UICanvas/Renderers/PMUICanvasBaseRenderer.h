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
    float           getFadeBackground();
    ofColor         getColorBackground();
    float           getDeltaPitch();
    float           getDeltaEnergy();
    
    // SETTERS
    void            setSmoothPitch(float _p);
    void            setSmoothEnergy(float _e);

protected:

    void            loadPreset(int presetNumber = 0);

private:

    PMUIRendererType        type;
    string                  rendererName;

    ofxUIToggleMatrix       *presetsMatrix;
    RENDERER_PRESET_MODE    presetsMode;

    float                   guiFadeBackground;
    ofColor                 guiColorBackground;

    // Pitch & Energy
    float                   guiSmoothPitch;
    float                   guiSmoothEnergy;
    
    float                   guiDeltaPitch;
    float                   guiDeltaEnergy;

    void            keyPressed(int key);
    void            keyReleased(int key);

    int             getActivePreset();
};


#endif //PMCONCERTPARAULES_PMUICANVASBASERENDERER_H




