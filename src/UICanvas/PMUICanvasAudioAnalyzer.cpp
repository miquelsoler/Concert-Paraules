//
// Created by Miquel Àngel Soler on 7/11/15.
//

#include "PMUICanvasAudioAnalyzer.h"

void PMUICanvasAudioAnalyzer::init(int posX, int posY, bool autosize, int width, int height)
{
    PMBaseUICanvas::init(posX, posY, autosize, width, height);

    settings = &PMSettingsManagerAudioAnalyzers::getInstance();

    pitchMinFreq0 = pitchMinFreq1 = settings->getMaxPitchFreq();
    pitchMaxFreq0 = pitchMaxFreq1 = settings->getMinPitchFreq();

    silenceOn0 = false;
    silenceOn1 = false;

    audioAnalyzers = PMAudioAnalyzer::getInstance().getAudioAnalyzers();
    vector<PMDeviceAudioAnalyzer *>::iterator itAudioAnalyzer;
    int iDevice =0;

    for (itAudioAnalyzer = audioAnalyzers->begin(); itAudioAnalyzer != audioAnalyzers->end(); ++itAudioAnalyzer, ++iDevice)
    {
        ofxUILabel *deviceLabel = addLabel("Device: " + ofToString((*itAudioAnalyzer)->getDeviceID()) + " Channel: " + ofToString((*itAudioAnalyzer)->getChannelNumber()));
        deviceLabel->setColorFill(titleColor);

        addSpacer();

        // Pitch
        {
            addLabel("PITCH");
            if (iDevice == 0) {
                // Min/max pitch freqs
                pitchRangedSlider0 = addRangeSlider("Freq (min/max)", settings->getMinPitchFreq(), settings->getMaxPitchFreq(), &pitchMinFreq0, &pitchMaxFreq0, 300, 10);
                pitchRangedSlider0->setTriggerType(OFX_UI_TRIGGER_NONE);

                // Current freq value
                pitchSlider0 = addSlider("Freq (current)", settings->getMinPitchFreq(), settings->getMaxPitchFreq(), &currentPitchFreq0, 300, 10);
                pitchSlider0->setTriggerType(OFX_UI_TRIGGER_NONE);

            } else {
                // Min/max pitch freqs
                pitchRangedSlider1 = addRangeSlider("\"Freq (min/max)", settings->getMinPitchFreq(), settings->getMaxPitchFreq(), pitchMinFreq1, pitchMaxFreq1, 300, 10);
                pitchRangedSlider1->setTriggerType(OFX_UI_TRIGGER_NONE);

                // Current freq value
                pitchSlider1 = addSlider("Freq (current)", settings->getMinPitchFreq(), settings->getMaxPitchFreq(), &currentPitchFreq1, 300, 10);
                pitchSlider1->setTriggerType(OFX_UI_TRIGGER_NONE);
            }

            addSpacer();
            ofAddListener((*itAudioAnalyzer)->eventPitchChanged, this, &PMUICanvasAudioAnalyzer::pitchChanged);
        }

        // Silence
        {
            addLabel("SILENCE");
// ofxUILabelToggle* ofxUICanvas::addLabelToggle(string _name, bool *_value, float w, float h, float x, float y, bool _justifyLeft) {
// ofxUILabelToggle* ofxUICanvas::addLabelToggle(string _name, bool *_value, bool _justifyLeft) {

            if (iDevice == 0) {
                silenceToggle0 = addLabelToggle("SILENCE", &silenceOn0);
                silenceToggle0->setTriggerType(OFX_UI_TRIGGER_NONE);
            } else {
                silenceToggle1 = addLabelToggle("SILENCE", &silenceOn1);
                silenceToggle1->setTriggerType(OFX_UI_TRIGGER_NONE);
            }

            addSpacer();
            ofAddListener((*itAudioAnalyzer)->eventSilenceStateChanged, this, &PMUICanvasAudioAnalyzer::silenceStateChanged);
        }

//        addSpacer();
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
            if ((pitchParams.freq > settings->getMinPitchFreq()) && (pitchParams.freq < pitchMinFreq0)) {
                pitchMinFreq0 = pitchParams.freq;
//                pitchRangedSlider0->setValueLow(pitchMinFreq0);
            }
            if (pitchParams.freq > pitchMaxFreq0) {
                pitchMaxFreq0 = pitchParams.freq;
// TODO: Quan peta sembla que passa aquí:
//                pitchRangedSlider0->setValueHigh(pitchMaxFreq0);
            }

            currentPitchFreq0 = pitchParams.freq;
        }
        else if (index == 1)
        {
            // Seconds of the two possible channels
            if ((pitchParams.freq > settings->getMinPitchFreq()) && (pitchParams.freq < pitchMinFreq1)) {
                pitchMinFreq1 = pitchParams.freq;
//                pitchRangedSlider1->setValueLow(pitchMinFreq1);
            }
            if (pitchParams.freq > pitchMaxFreq1) {
                pitchMaxFreq1 = pitchParams.freq;
//                pitchRangedSlider1->setValueHigh(pitchMaxFreq1);
            }

            currentPitchFreq1 = pitchParams.freq;
        }
    }
}

void PMUICanvasAudioAnalyzer::silenceStateChanged(silenceParams &silenceParams)
{
    bool found = false;
    int i=0, index = -1;

    vector<PMDeviceAudioAnalyzer *>::iterator itAudioAnalyzer;
    for (itAudioAnalyzer = audioAnalyzers->begin(); itAudioAnalyzer != audioAnalyzers->end() && !found; ++itAudioAnalyzer, ++i)
    {
        found = (silenceParams.deviceID == (*itAudioAnalyzer)->getDeviceID()) && (silenceParams.channel == (*itAudioAnalyzer)->getChannelNumber());
        if (found) index = i;
    }

    if (found)
    {
        if (index == 0)
        {
            silenceOn0 = silenceParams.isSilent;
        } else if (index == 1) {
            silenceOn1 = silenceParams.isSilent;
        }
    }

}
