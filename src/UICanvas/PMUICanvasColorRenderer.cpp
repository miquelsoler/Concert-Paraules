//
// Created by Miquel Àngel Soler on 7/11/15.
//

#include "PMUICanvasColorRenderer.h"

PMUICanvasColorRenderer::PMUICanvasColorRenderer(string title, int headerFontSize) : PMUICanvasBaseRenderer(title, headerFontSize)
{

}

void PMUICanvasColorRenderer::init(int posX, int posY, bool autosize, int width, int height)
{
    PMUICanvasBaseRenderer::init(posX, posY, autosize, width, height);

    gradientImage.load("./gradients/test4x_v1.png");
    
    addSpacer();
    addIntSlider("Mode",1,3,&guiMode);
    addSlider("Scan Speed X",0.0,5.0,&guiScanSpeedX);
    addSlider("Scan With",0.0,150.0,&guiScanWidth);
    addImageSampler("Gradient", &gradientImage);
    if (autosize) autoSizeToFitWidgets();

    loadPreset();

}

void PMUICanvasColorRenderer::clear()
{
    ofxUICanvas::clearWidgets();
    superInit("COLOR_RENDERER", OFX_UI_FONT_MEDIUM);
}

void PMUICanvasColorRenderer::handleEvents(ofxUIEventArgs &e)
{
    PMUICanvasBaseRenderer::handleEvents(e);
    
    string name = e.getName();
    int kind = e.getKind();
    
    if(name=="Save to default")
    {
        savePreset();
    }
}


// GETTERS
float PMUICanvasColorRenderer::getScanSpeedX()
{
    return guiScanSpeedX;
}
int PMUICanvasColorRenderer::getMode()
{
    return guiMode;
}
float PMUICanvasColorRenderer::getScanWidth()
{
    return guiScanWidth;
}



// SETTERS
void PMUICanvasColorRenderer::setScanSpeedX(float _s)
{
    guiScanSpeedX = _s;
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


