//
// Created by Miquel Àngel Soler on 7/11/15.
//

#include "PMUICanvasBaseRenderer.h"

PMUICanvasBaseRenderer::PMUICanvasBaseRenderer(string title, int headerFontSize) : PMBaseUICanvas(title, headerFontSize)
{

}

void PMUICanvasBaseRenderer::init(int posX, int posY, bool autosize, int width, int height)
{
    PMBaseUICanvas::init(posX, posY, autosize, width, height);

    addLabelButton("Save to default",false);
    addNumberDialer("Fade Background", 0.0,1.0,&guiFadeBackground,4);
    addIntSlider("Background R",0,255,255);
    addIntSlider("Background G",0,255,255);
    addIntSlider("Background B",0,255,255);
    
    
    ofAddListener(newGUIEvent, this, &PMUICanvasBaseRenderer::handleEvents);
}

void PMUICanvasBaseRenderer::clear()
{
    ofxUICanvas::clearWidgets();
    superInit("BASE RENDERER", OFX_UI_FONT_MEDIUM);
}

void PMUICanvasBaseRenderer::handleEvents(ofxUIEventArgs &e)
{
    string name = e.getName();
    int kind = e.getKind();
    
    if(name=="Background R")
    {
        ofxUIIntSlider *s = (ofxUIIntSlider *) e.widget;
        guiColorBackground.r = s->getValue();
    }
    else if(name=="Background G")
    {
        ofxUIIntSlider *s = (ofxUIIntSlider *) e.widget;
        guiColorBackground.g = s->getValue();
    }
    else if(name=="Background B")
    {
        ofxUIIntSlider *s = (ofxUIIntSlider *) e.widget;
        guiColorBackground.b = s->getValue();
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

void PMUICanvasBaseRenderer::savePreset()
{
    saveSettings(ofFilePath::getAbsolutePath("presets")+"/" +title +"/default.xml");
    cout << "Saving Preset to : " << ofToString("presets")+"/" +title +"/default.xml)" << endl;
}
void PMUICanvasBaseRenderer::loadPreset()
{
    loadSettings(ofFilePath::getAbsolutePath("presets")+"/" +title +"/default.xml");
    cout << "Loading Preset from : " << ofToString("presets")+"/" +title +"/default.xml)" << endl;
}


