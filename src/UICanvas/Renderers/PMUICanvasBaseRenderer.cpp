//
// Created by Miquel Àngel Soler on 7/11/15.
//

#include "PMUICanvasBaseRenderer.h"

static const unsigned int PRESETSMATRIX_NUMROWS = 1;
static const unsigned int PRESETSMATRIX_NUMCOLS = 10;

static const string STR_PRESETS = "PRESETS";
static const string STR_PRESETS_INFO = "Click to LOAD | Shift+Click to SAVE";

static const string STR_CANVAS_BASEPATH = "presets/";


PMUICanvasBaseRenderer::PMUICanvasBaseRenderer(PMUIRendererType _type, string title, int headerFontSize) : PMBaseUICanvas(title, headerFontSize)
{
    type = _type;
}

void PMUICanvasBaseRenderer::init(int posX, int posY, bool autosize, int width, int height)
{
    PMBaseUICanvas::init(posX, posY, autosize, width, height);

    setTriggerWidgetsUponLoad(false);

    setBackgroundColor(ofColor(0,20,40,128));

    guiFadeBackground = 0.01;
    guiPitchMin = 7;
    guiPitchMax = 96;
    guiEnergyMin = 0.1;
    guiEnergyMax = 0.9;
    guiSmoothEnergy = 0.5;
    guiSmoothPitch = 0.5;

    { // Presets
        addLabel(STR_PRESETS);
        addLabel(STR_PRESETS_INFO, OFX_UI_FONT_SMALL);
        setGlobalButtonDimension(32);
        presetsMatrix = addToggleMatrix(STR_PRESETS, PRESETSMATRIX_NUMROWS, PRESETSMATRIX_NUMCOLS);
        presetsMatrix->setAllowMultiple(false);
        presetsMatrix->setTriggerType(OFX_UI_TRIGGER_CHANGE);
    }

    { // Bg color
        addSpacer(); addSpacer();
        addLabel("BACKGROUND");
        addNumberDialer("Fade Background", 0.0,1.0,&guiFadeBackground,4);
        addIntSlider("Background R", 0, 255, &guiColorBgRed);
        addIntSlider("Background G", 0, 255, &guiColorBgGreen);
        addIntSlider("Background B", 0, 255, &guiColorBgBlue);
    }

    { // Audio
        addSpacer(); addSpacer();
        addLabel("AUDIO ENERGY");
        addRangeSlider("Energy Min-Max",0.0,1.0,&guiEnergyMin,&guiEnergyMax);
        addSlider("Smooth Energy",0.0,1.0,&guiSmoothEnergy);
        addSlider("Delta Energy",0.0,1.0,&guiDeltaEnergy);

        addSpacer();
        addLabel("AUDIO PITCH");
        addRangeSlider("Pitch Min-Max",0.0,127.0,&guiPitchMin,&guiPitchMax);
        addSlider("Smooth Pitch",0.0,1.0,&guiSmoothPitch);
        addSlider("Delta Pitch",0.0,1.0,&guiDeltaPitch);
    }

    { // Mode
        addSpacer(); addSpacer();
        addIntSlider("MODE",1,10,&guiMode);
    }

    addSpacer();

    ofAddListener(newGUIEvent, this, &PMUICanvasBaseRenderer::handleEvents);

    presetsMode = RENDERER_PRESET_LOAD;
}

void PMUICanvasBaseRenderer::clear()
{
    ofxUICanvas::clearWidgets();
    superInit("BASE RENDERER", OFX_UI_FONT_MEDIUM);
}

void PMUICanvasBaseRenderer::handleEvents(ofxUIEventArgs &e)
{
    string name = e.getName();

    if (ofIsStringInString(name, STR_PRESETS))
    {
        switch(presetsMode)
        {
            case RENDERER_PRESET_LOAD: loadPreset(getActivePreset()); break;
            case RENDERER_PRESET_SAVE: savePreset(getActivePreset()); break;
        }
    }
}

void PMUICanvasBaseRenderer::loadPreset(int presetNumber)
{
    string presetPath = STR_CANVAS_BASEPATH + title + "/" + ofToString(presetNumber) + ".xml";
    loadSettings(presetPath);

    // Force GUI position when loading
    setPosition(ofGetWidth() - 215, 5);
}

void PMUICanvasBaseRenderer::savePreset(int presetNumber)
{
    string presetPath = STR_CANVAS_BASEPATH + title + "/" + ofToString(presetNumber) + ".xml";
    saveSettings(presetPath);
}

int PMUICanvasBaseRenderer::getActivePreset()
{
    bool found = false;
    unsigned int col = 0, row = 0;
    for (unsigned int i=0; i<PRESETSMATRIX_NUMCOLS && !found; ++i) {
        col = i;
        for (unsigned int j=0; j<PRESETSMATRIX_NUMROWS && !found; ++j) {
            row = j;
            found = presetsMatrix->getState(j, i);
        }
    }

    if (!found) return -1;

    return (row * PRESETSMATRIX_NUMCOLS) + col;
}

void PMUICanvasBaseRenderer::keyPressed(int key)
{
    if (key != OF_KEY_SHIFT) return;
    presetsMode = RENDERER_PRESET_SAVE;
}

void PMUICanvasBaseRenderer::keyReleased(int key)
{
    if (key == OF_KEY_SHIFT)
    {
        presetsMode = RENDERER_PRESET_LOAD;
        return;
    }
    
    /// SHIT to avoid
    bool found = false;
    unsigned int col = 0, row = 0;
    for (unsigned int i=0; i<PRESETSMATRIX_NUMCOLS && !found; ++i) {
        col = i;
        for (unsigned int j=0; j<PRESETSMATRIX_NUMROWS && !found; ++j) {
            row = j;
            found = presetsMatrix->getState(j, i);
        }
    }
    int presetNumber = (row * PRESETSMATRIX_NUMCOLS) + col;
    
    switch(key)
    {
        case '1': presetNumber = 0; break;
        case '2': presetNumber = 1; break;
        case '3': presetNumber = 2; break;
        case '4': presetNumber = 3; break;
        case '5': presetNumber = 4; break;
        case '6': presetNumber = 5; break;
        case '7': presetNumber = 6; break;
        case '8': presetNumber = 7; break;
        case '9': presetNumber = 8; break;
        case '0': presetNumber = 9; break;
        default: break;
    }

    if (presetsMode == RENDERER_PRESET_LOAD)
    {
        row = presetNumber / PRESETSMATRIX_NUMCOLS;
        col = presetNumber % PRESETSMATRIX_NUMCOLS;
        for (unsigned int i=0; i<PRESETSMATRIX_NUMROWS; ++i) {
            for (unsigned int j=0; j<PRESETSMATRIX_NUMCOLS; ++j) {
                presetsMatrix->setToggle(i, j, (i==row) && (j==col), true);
            }
        }
    }

    loadPreset(presetNumber);
}
