//
// Created by Miquel Àngel Soler on 7/11/15.
//

#include "PMUICanvasBaseRenderer.h"

static const unsigned int PRESETSMATRIX_NUMROWS = 1;
static const unsigned int PRESETSMATRIX_NUMCOLS = 6;

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

    addLabel(STR_PRESETS);
    addLabel(STR_PRESETS_INFO, OFX_UI_FONT_SMALL);
    setGlobalButtonDimension(32);
    presetsMatrix = addToggleMatrix(STR_PRESETS, PRESETSMATRIX_NUMROWS, PRESETSMATRIX_NUMCOLS);
    presetsMatrix->setAllowMultiple(false);
    presetsMatrix->setTriggerType(OFX_UI_TRIGGER_END);
    addSpacer();
    addLabel("BACKGROUND");
    addNumberDialer("Fade Background", 0.0,1.0,&guiFadeBackground,4);
    addIntSlider("Background R",0,255,255);
    addIntSlider("Background G",0,255,255);
    addIntSlider("Background B",0,255,255);
    addSpacer();
    addLabel("ENERGY");
    addSlider("Delta Energy",0.0,1.0,&guiDeltaEnergy);
    addSlider("Smooth Energy",0.0,1.0,&guiSmoothEnergy);
    addSpacer();
    addLabel("PITCH");
    addSlider("Delta Pitch",0.0,1.0,&guiDeltaPitch);
    addSlider("Smooth Pitch",0.0,1.0,&guiSmoothPitch);

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
    else
    {
        if(name == "Background R")
        {
            ofxUIIntSlider *s = (ofxUIIntSlider *) e.widget;
            guiColorBackground.r = s->getValue();
        }
        else if(name == "Background G")
        {
            ofxUIIntSlider *s = (ofxUIIntSlider *) e.widget;
            guiColorBackground.g = s->getValue();
        }
        else if(name == "Background B")
        {
            ofxUIIntSlider *s = (ofxUIIntSlider *) e.widget;
            guiColorBackground.b = s->getValue();
        }
    }
}

//void PMUICanvasBaseRenderer::pitchChanged(pitchParams &pitchParams)
//{
//    if (pitchParams.audioInputIndex != audioInputIndex) return;
//
//    if ((pitchParams.midiNote > settings->getMinPitchMidiNote()) && (pitchParams.midiNote < pitchMinMidiNote)) {
//        pitchMinMidiNote = pitchParams.midiNote;
//    }
//
//    if (pitchParams.midiNote > pitchMaxMidiNote) {
//        pitchMaxMidiNote = pitchParams.midiNote;
//    }
//
//    pitchCurrentMidiNote = pitchParams.midiNote;
//}
//
//void PMUICanvasAudioAnalyzer::energyChanged(energyParams &energyParams)
//{
//    if (energyParams.audioInputIndex != audioInputIndex) return;
//    energyCurrent = energyParams.energy;
//}
//
//
//void PMUICanvasAudioAnalyzer::silenceStateChanged(silenceParams &silenceParams)
//{
//    if (silenceParams.audioInputIndex != audioInputIndex) return;
//    silenceOn = silenceParams.isSilent;
//}
//
//void PMUICanvasAudioAnalyzer::pauseStateChanged(pauseParams &pauseParams)
//{
//    if (pauseParams.audioInputIndex != audioInputIndex) return;
//    pauseOn = pauseParams.isPaused;
//}
//
//void PMUICanvasAudioAnalyzer::onsetStateChanged(onsetParams &onsetParams)
//{
//    if (onsetParams.audioInputIndex != audioInputIndex) return;
//    onsetOn = onsetParams.isOnset;
//}

float PMUICanvasBaseRenderer::getFadeBackground()
{
    return guiFadeBackground;
}

ofColor PMUICanvasBaseRenderer::getColorBackground()
{
    return guiColorBackground;
}

float PMUICanvasBaseRenderer::getDeltaPitch()
{
    return guiDeltaPitch;
}

float PMUICanvasBaseRenderer::getDeltaEnergy()
{
    return guiDeltaEnergy;
}

void PMUICanvasBaseRenderer::setSmoothPitch(float _p)
{
    guiSmoothPitch = _p;
}
void PMUICanvasBaseRenderer::setSmoothEnergy(float _e)
{
    guiSmoothEnergy = _e;
}

void PMUICanvasBaseRenderer::loadPreset(int presetNumber)
{
    string presetPath = STR_CANVAS_BASEPATH + title + "/" + ofToString(presetNumber) + ".xml";
    loadSettings(presetPath);
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
    if (key != OF_KEY_SHIFT) return;
    presetsMode = RENDERER_PRESET_LOAD;
}
