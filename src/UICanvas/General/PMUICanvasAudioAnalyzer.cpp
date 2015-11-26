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

    pitchMinMidiNote = settings->getMaxPitchMidiNote();
    pitchMaxMidiNote = settings->getMinPitchMidiNote();

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

            // Current freq value
            pitchSlider = addSlider("Midi note", settings->getMinPitchMidiNote(), settings->getMaxPitchMidiNote(), &pitchCurrentMidiNote, 300, 10);
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

        // Pause
        {
            addLabel("PAUSE");

            pauseToggle = addLabelToggle("PAUSE", &pauseOn);
            pauseToggle->setTriggerType(OFX_UI_TRIGGER_NONE);

            addSpacer();
            ofAddListener((*itAudioAnalyzer)->eventPauseStateChanged, this, &PMUICanvasAudioAnalyzer::pauseStateChanged);
        }

        // Onset
        {
            addLabel("ONSET");

            onsetToggle = addLabelToggle("ONSET", &onsetOn);
            onsetToggle->setTriggerType(OFX_UI_TRIGGER_NONE);

            addSpacer();
            ofAddListener((*itAudioAnalyzer)->eventOnsetStateChanged, this, &PMUICanvasAudioAnalyzer::onsetStateChanged);
        }
        // Onset
        {
            addLabel("SHT");
            
            shtToggle = addLabelToggle("SHT", &shtOn);
            shtToggle->setTriggerType(OFX_UI_TRIGGER_NONE);
            
            addSpacer();
            ofAddListener((*itAudioAnalyzer)->eventShtStateChanged, this, &PMUICanvasAudioAnalyzer::shtStateChanged);
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

    if ((pitchParams.midiNote > settings->getMinPitchMidiNote()) && (pitchParams.midiNote < pitchMinMidiNote)) {
        pitchMinMidiNote = pitchParams.midiNote;
    }

    if (pitchParams.midiNote > pitchMaxMidiNote) {
        pitchMaxMidiNote = pitchParams.midiNote;
    }

    pitchCurrentMidiNote = pitchParams.midiNote;
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

void PMUICanvasAudioAnalyzer::pauseStateChanged(pauseParams &pauseParams)
{
    if (pauseParams.audioInputIndex != audioInputIndex) return;
    pauseOn = pauseParams.isPaused;
}

void PMUICanvasAudioAnalyzer::onsetStateChanged(onsetParams &onsetParams)
{
    if (onsetParams.audioInputIndex != audioInputIndex) return;
    onsetOn = onsetParams.isOnset;
}


void PMUICanvasAudioAnalyzer::shtStateChanged(shtParams &_shtParams)
{
    if (_shtParams.audioInputIndex != audioInputIndex) return;
    shtOn = _shtParams.isSht;
}
