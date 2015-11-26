//
// Created by Miquel Àngel Soler on 7/11/15.
//

#include "PMUICanvasColorRenderer.h"

PMUICanvasColorRenderer::PMUICanvasColorRenderer(PMUIRendererType type, string title, int headerFontSize) : PMUICanvasBaseRenderer(type, title, headerFontSize)
{
}

void PMUICanvasColorRenderer::init(int posX, int posY, bool autosize, int width, int height)
{
    PMUICanvasBaseRenderer::init(posX, posY, autosize, width, height);

    gradientImage.load("./gradients/test4x_v1.png");
    
    addSpacer();
    addIntSlider("Mode",1,10,&guiMode);

    addSlider("Scan Speed X",0.0,5.0,&guiScanSpeedX);
    addSlider("Scan With",0.0,150.0,&guiScanWidth);

    addImageSampler("Gradient", &gradientImage);
    addIntSlider("Gradient Id",1,4,&gradientId);
    numGradients = 4;
    
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
//    int kind = e.getKind();

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

ofColor PMUICanvasColorRenderer::getGradientColor(int _id,float _p)
{
    ofxUIImageSampler* is = (ofxUIImageSampler*)getWidget("Gradient");
    ofPoint p = ofPoint( _p, ((_id)*((1.0/float(numGradients))) - ((1.0/float(numGradients))/2)));
    
    //cout << ofToString(((_id)*((1.0/float(numGradients))) - ((1.0/float(numGradients))/2))) << endl;
    is->setValue(p);
    return is->getColor();
}

int PMUICanvasColorRenderer::getGradientId()
{
    return gradientId;
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



