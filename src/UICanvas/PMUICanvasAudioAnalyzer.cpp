//
// Created by Miquel Àngel Soler on 7/11/15.
//

#include "PMUICanvasAudioAnalyzer.h"

PMUICanvasAudioAnalyzer::PMUICanvasAudioAnalyzer(string title, int headerFontSize, unsigned int _audioInputIndex) : PMBaseUICanvas(title, headerFontSize)
{
    audioInputIndex = _audioInputIndex;
}

void PMUICanvasAudioAnalyzer::init(int posX, int posY, bool autosize, int width, int height)
{
    PMBaseUICanvas::init(posX, posY, autosize, width, height);

    settings = &PMSettingsManagerAudioAnalyzers::getInstance();

    pitchMinFreq = settings->getMaxPitchFreq();
    pitchMaxFreq = settings->getMinPitchFreq();

    silenceOn = false;

    audioAnalyzers = PMAudioAnalyzer::getInstance().getAudioAnalyzers();
    vector<PMDeviceAudioAnalyzer *>::iterator itAudioAnalyzer;

    for (itAudioAnalyzer = audioAnalyzers->begin(); itAudioAnalyzer != audioAnalyzers->end(); ++itAudioAnalyzer)
    {
        if ((*itAudioAnalyzer)->getInputIndex() != audioInputIndex) continue;

        ofxUILabel *deviceLabel = addLabel("Device: " + ofToString((*itAudioAnalyzer)->getDeviceID()) + " Channel: " + ofToString((*itAudioAnalyzer)->getChannelNumber()));
        deviceLabel->setColorFill(titleColor);

        // Pitch
        {
            addLabel("PITCH");

            // Min/max pitch freqs
            pitchRangedSlider = addRangeSlider("Freq (min/max)", settings->getMinPitchFreq(), settings->getMaxPitchFreq(), &pitchMinFreq, &pitchMaxFreq, 300, 10);
            pitchRangedSlider->setTriggerType(OFX_UI_TRIGGER_NONE);

            // Current freq value
            pitchSlider = addSlider("Freq (current)", settings->getMinPitchFreq(), settings->getMaxPitchFreq(), &pitchCurrentFreq, 300, 10);
            pitchSlider->setTriggerType(OFX_UI_TRIGGER_NONE);

            addSpacer();
            ofAddListener((*itAudioAnalyzer)->eventPitchChanged, this, &PMUICanvasAudioAnalyzer::pitchChanged);
        }

        // Energy
        {
            addLabel("ENERGY");

            energySilder = addSlider("Energy", settings->getMinEnergy(), settings->getMaxEnergy(), &energyCurrent, 300, 10);
            energySilder->setTriggerType(OFX_UI_TRIGGER_NONE);

            addSpacer();
            ofAddListener((*itAudioAnalyzer)->eventEnergyChanged, this, &PMUICanvasAudioAnalyzer::energyChanged);


        }

        // Silence
        {
            addLabel("SILENCE");

            silenceToggle = addLabelToggle("SILENCE", &silenceOn);
            silenceToggle->setTriggerType(OFX_UI_TRIGGER_NONE);

            addSpacer();
            ofAddListener((*itAudioAnalyzer)->eventSilenceStateChanged, this, &PMUICanvasAudioAnalyzer::silenceStateChanged);
        }
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
    if (pitchParams.audioInputIndex != audioInputIndex) return;

    if ((pitchParams.freq > settings->getMinPitchFreq()) && (pitchParams.freq < pitchMinFreq)) {
        pitchMinFreq = pitchParams.freq;
    }

    if (pitchParams.freq > pitchMaxFreq) {
        pitchMaxFreq = pitchParams.freq;
    }

    pitchCurrentFreq = pitchParams.freq;
}

void PMUICanvasAudioAnalyzer::energyChanged(energyParams &energyParams)
{
    if (energyParams.audioInputIndex != audioInputIndex) return;

    energyCurrent = energyParams.energy;
}


void PMUICanvasAudioAnalyzer::silenceStateChanged(silenceParams &silenceParams)
{
    if (silenceParams.audioInputIndex != audioInputIndex) return;

    silenceOn = silenceParams.isSilent;
}
