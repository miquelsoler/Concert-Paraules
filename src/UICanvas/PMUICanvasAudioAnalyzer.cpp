//
// Created by Miquel Àngel Soler on 7/11/15.
//

#include "PMUICanvasAudioAnalyzer.h"
#include "PMAudioAnalyzer.hpp"

void PMUICanvasAudioAnalyzer::init(int posX, int posY, bool autosize, int width, int height)
{
    PMBaseUICanvas::init(posX, posY, autosize, width, height);

    vector<PMDeviceAudioAnalyzer *> *audioAnalyzers = PMAudioAnalyzer::getInstance().getAudioAnalyzers();
    vector<PMDeviceAudioAnalyzer *>::iterator itAudioAnalyzer;
    int i=0;
    for (itAudioAnalyzer = audioAnalyzers->begin(); itAudioAnalyzer != audioAnalyzers->end(); ++itAudioAnalyzer, ++i)
    {
        addLabel("Device: " + ofToString((*itAudioAnalyzer)->getDeviceID()));
        addSpacer();

        ofAddListener((*itAudioAnalyzer)->eventPitchChanged, this, &PMUICanvasAudioAnalyzer::pitchChanged);

        cout << "Audio analyzer " << i << endl;
    }

    if (autosize) autoSizeToFitWidgets();
}

void PMUICanvasAudioAnalyzer::clear()
{
    ofxUICanvas::clearWidgets();
    superInit("AUDIO ANALYZER", OFX_UI_FONT_MEDIUM);
}

void PMUICanvasAudioAnalyzer::handleEvents(ofxUIEventArgs &e)
{
}

void PMUICanvasAudioAnalyzer::pitchChanged(pitchParams &pitchParams)
{
    cout << "CANVAS pitch changed" << endl;
}
