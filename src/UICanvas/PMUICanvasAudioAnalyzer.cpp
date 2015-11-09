//
// Created by Miquel Àngel Soler on 7/11/15.
//

#include "PMUICanvasAudioAnalyzer.h"
#include "PMAudioAnalyzerConstants.h"

void PMUICanvasAudioAnalyzer::init(int posX, int posY, bool autosize, int width, int height)
{
    PMBaseUICanvas::init(posX, posY, autosize, width, height);

    pitchMinFreq0 = pitchMinFreq1 = PITCH_MAXFREQ;
    pitchMaxFreq0 = pitchMaxFreq1 = PITCH_MINFREQ;

    audioAnalyzers = PMAudioAnalyzer::getInstance().getAudioAnalyzers();
    vector<PMDeviceAudioAnalyzer *>::iterator itAudioAnalyzer;
    int i=0;

    addSpacer();
    ofxUILabel *pitchLabel = addLabel("PITCH");
    pitchLabel->setColorFill(titleColor);
    for (itAudioAnalyzer = audioAnalyzers->begin(); itAudioAnalyzer != audioAnalyzers->end(); ++itAudioAnalyzer, ++i)
    {
        addSpacer();
        addLabel("Device: " + ofToString((*itAudioAnalyzer)->getDeviceID()) + " Channel: " + ofToString((*itAudioAnalyzer)->getChannelNumber()), OFX_UI_FONT_MEDIUM);

        if (i == 0) {
            pitchRangedSlider0 = addRangeSlider("Freq (min/max)", PITCH_MINFREQ, PITCH_MAXFREQ, pitchMinFreq0, pitchMaxFreq0, 300, 10);
            pitchRangedSlider0->setTriggerType(OFX_UI_TRIGGER_NONE);
            pitchSlider0 = addSlider("Freq (current)", PITCH_MINFREQ, PITCH_MAXFREQ, &currentPitchFreq0, 300, 10);
            pitchSlider0->setTriggerType(OFX_UI_TRIGGER_NONE);

            pitchSlider0->setTriggerType(OFX_UI_TRIGGER_NONE);
        } else {
            pitchRangedSlider1 = addRangeSlider("\"Freq (min/max)", PITCH_MINFREQ, PITCH_MAXFREQ, pitchMinFreq1, pitchMaxFreq1, 300, 10);
            pitchRangedSlider1->setTriggerType(OFX_UI_TRIGGER_NONE);
            pitchSlider1 = addSlider("Freq (current)", PITCH_MINFREQ, PITCH_MAXFREQ, &currentPitchFreq1, 300, 10);
            pitchSlider1->setTriggerType(OFX_UI_TRIGGER_NONE);
            pitchSlider1->setTriggerType(OFX_UI_TRIGGER_NONE);
        }

        ofAddListener((*itAudioAnalyzer)->eventPitchChanged, this, &PMUICanvasAudioAnalyzer::pitchChanged);
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
    bool found = false;
    int i=0, index = -1;

    vector<PMDeviceAudioAnalyzer *>::iterator itAudioAnalyzer;
    for (itAudioAnalyzer = audioAnalyzers->begin(); itAudioAnalyzer != audioAnalyzers->end() && !found; ++itAudioAnalyzer, ++i)
    {
        found = (pitchParams.deviceID == (*itAudioAnalyzer)->getDeviceID()) && (pitchParams.channel == (*itAudioAnalyzer)->getChannelNumber());
        if (found) index = i;
    }

    if (found)
    {
        if (index == 0)
        {
            // First of the two possible channels
            if ((pitchParams.freq > PITCH_MINFREQ) && (pitchParams.freq < pitchMinFreq0)) {
                pitchMinFreq0 = pitchParams.freq;
                pitchRangedSlider0->setValueLow(pitchMinFreq0);
            }
            if (pitchParams.freq > pitchMaxFreq0) {
                pitchMaxFreq0 = pitchParams.freq;
                pitchRangedSlider0->setValueHigh(pitchMaxFreq0);
            }

            currentPitchFreq0 = pitchParams.freq;
        }
        else if (index == 1)
        {
            // Seconds of the two possible channels
            if ((pitchParams.freq > PITCH_MINFREQ) && (pitchParams.freq < pitchMinFreq1)) {
                pitchMinFreq1 = pitchParams.freq;
                pitchRangedSlider1->setValueLow(pitchMinFreq1) ;
            }
            if (pitchParams.freq > pitchMaxFreq1) {
                pitchMaxFreq1 = pitchParams.freq;
                pitchRangedSlider1->setValueHigh(pitchMaxFreq1);
            }

            currentPitchFreq1 = pitchParams.freq;
        }
    }
}
