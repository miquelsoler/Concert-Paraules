//
// Created by Miquel Àngel Soler on 7/11/15.
//

#include "PMUICanvasAudioAnalyzer.h"

static const unsigned int PRESETSMATRIX_NUMROWS = 1;
static const unsigned int PRESETSMATRIX_NUMCOLS = 6;

static const string STR_PRESETS_BASEPATH = "presets/AUDIO_ANALYZER";

static const string STR_PRESETS         = "PRESETS";
static const string STR_PITCH           = "PITCH";
static const string STR_PITCH_MIDINOTE  = "Midi note";
static const string STR_ENERGY          = "ENERGY";
static const string STR_ENERGY_CURRENT  = "Energy";
static const string STR_ENERGY_GAIN     = "Gain";
static const string STR_SILENCE         = "SILENCE";
static const string STR_SILENCE_THRSHLD = "Silence Threshold";
static const string STR_SILENCE_LENGTH  = "Silence Length (ms)";
static const string STR_PAUSE           = "PAUSE";
static const string STR_PAUSE_LENGTH    = "Pause Length (ms)";
static const string STR_ONSET           = "ONSET";
static const string STR_ONSET_THRSHLD   = "Onset Threshold";
static const string STR_SHT             = "SHT";


PMUICanvasAudioAnalyzer::PMUICanvasAudioAnalyzer(string title, int headerFontSize, unsigned int _audioInputIndex) : PMBaseUICanvas(title, headerFontSize)
{
    audioInputIndex = _audioInputIndex;
    savingPreset = false;
}

void PMUICanvasAudioAnalyzer::init(int posX, int posY, bool autosize, int width, int height)
{
    PMBaseUICanvas::init(posX, posY, autosize, width, height);

    silenceOn = false;

    audioAnalyzers = PMAudioAnalyzer::getInstance().getAudioAnalyzers();
    vector<PMDeviceAudioAnalyzer *>::iterator itAudioAnalyzer;

    for (itAudioAnalyzer = audioAnalyzers->begin(); itAudioAnalyzer != audioAnalyzers->end(); ++itAudioAnalyzer)
    {
        if ((*itAudioAnalyzer)->getInputIndex() != audioInputIndex) continue;

        string strChannelNumbers;
        vector<unsigned int> channelNumbers = (*itAudioAnalyzer)->getChannelNumbers();
        for (int i = 0; i < channelNumbers.size(); ++i) {
            strChannelNumbers += ofToString(channelNumbers[i]);
            if (i < channelNumbers.size() - 1)
                strChannelNumbers += ",";
        }

        addLabel("Device: " + ofToString((*itAudioAnalyzer)->getDeviceID()) + " Channels: " + strChannelNumbers);
        addSpacer();

        // Presets
        addLabel(STR_PRESETS);
        presetsMatrix = addToggleMatrix(STR_PRESETS, PRESETSMATRIX_NUMROWS, PRESETSMATRIX_NUMCOLS, 200 / PRESETSMATRIX_NUMCOLS, 20);
        presetsMatrix->setAllowMultiple(false);

        addSpacer();

        addLabel(STR_PITCH);
        addSlider(STR_PITCH_MIDINOTE, 0, 127, &pitchCurrentMidiNote);
        addSpacer();
        ofAddListener((*itAudioAnalyzer)->eventPitchChanged, this, &PMUICanvasAudioAnalyzer::pitchChanged);

        addLabel(STR_ENERGY);
        addSlider(STR_ENERGY_GAIN, 1.0, 10.0, &energyGainCurrent);
        addSlider(STR_ENERGY_CURRENT, 0.0, 1.0, &energyCurrent);
        addSpacer();
        ofAddListener((*itAudioAnalyzer)->eventEnergyChanged, this, &PMUICanvasAudioAnalyzer::energyChanged);

        addLabel(STR_SILENCE);
        addSlider(STR_SILENCE_THRSHLD, 0.0, 0.5, &silenceThreshold);
        addSlider(STR_SILENCE_LENGTH, 0.0, 1000.0, &silenceQueueLength);
        addLabelToggle(STR_SILENCE, &silenceOn);
        addSpacer();
        ofAddListener((*itAudioAnalyzer)->eventSilenceStateChanged, this, &PMUICanvasAudioAnalyzer::silenceStateChanged);

        addLabel(STR_PAUSE);
        addSlider(STR_PAUSE_LENGTH, 0.0, 10000.0, &pauseQueueLength);
        addLabelToggle(STR_PAUSE, &pauseOn);
        addSpacer();
        ofAddListener((*itAudioAnalyzer)->eventPauseStateChanged, this, &PMUICanvasAudioAnalyzer::pauseStateChanged);

        addLabel(STR_ONSET);
        addSlider(STR_ONSET_THRSHLD, 0.0, 1.0, &onsetThreshold);
        addLabelToggle(STR_ONSET, &onsetOn);
        addSpacer();
        ofAddListener((*itAudioAnalyzer)->eventOnsetStateChanged, this, &PMUICanvasAudioAnalyzer::onsetStateChanged);

        addLabel(STR_SHT);
        addLabelToggle(STR_SHT, &shtOn);
        addSpacer();
        ofAddListener((*itAudioAnalyzer)->eventShtStateChanged, this, &PMUICanvasAudioAnalyzer::shtStateChanged);

        ofAddListener(newGUIEvent, this, &PMUICanvasAudioAnalyzer::handleEvents);
    }

    if (autosize) autoSizeToFitWidgets();

    loadPreset(0);
}

void PMUICanvasAudioAnalyzer::clear()
{
    ofxUICanvas::clearWidgets();
    superInit("AUDIO ANALYZER", OFX_UI_FONT_MEDIUM);
}

void PMUICanvasAudioAnalyzer::handleEvents(ofxUIEventArgs &e)
{
    string name = e.getName();

    if (name.find(STR_PRESETS)!=-1)
    {
        int activePreset = getActivePreset();

        if (savingPreset) {
            savePreset(activePreset);
        } else {
            loadPreset(activePreset);
        }
    }
    else
    {
        vector<PMDeviceAudioAnalyzer *>::iterator itAudioAnalyzer;
        if (name == STR_SILENCE_THRSHLD)
        {
            for (itAudioAnalyzer = audioAnalyzers->begin(); itAudioAnalyzer != audioAnalyzers->end(); ++itAudioAnalyzer) {
                if ((*itAudioAnalyzer)->getInputIndex() != audioInputIndex) continue;
                (*itAudioAnalyzer)->setSilenceThreshold(e.getFloat());
            }
        }
        else if (name == STR_SILENCE_LENGTH)
        {
            for (itAudioAnalyzer = audioAnalyzers->begin(); itAudioAnalyzer != audioAnalyzers->end(); ++itAudioAnalyzer) {
                if ((*itAudioAnalyzer)->getInputIndex() != audioInputIndex) continue;
                (*itAudioAnalyzer)->setSilenceQueueLength(e.getFloat());
            }
        }
        else if (name == STR_PAUSE_LENGTH)
        {
            for (itAudioAnalyzer = audioAnalyzers->begin(); itAudioAnalyzer != audioAnalyzers->end(); ++itAudioAnalyzer) {
                if ((*itAudioAnalyzer)->getInputIndex() != audioInputIndex) continue;
                (*itAudioAnalyzer)->setPauseTimeTreshold(e.getFloat());
            }
        }
        else if (name == STR_ONSET_THRSHLD)
        {
            for (itAudioAnalyzer = audioAnalyzers->begin(); itAudioAnalyzer != audioAnalyzers->end(); ++itAudioAnalyzer) {
                if ((*itAudioAnalyzer)->getInputIndex() != audioInputIndex) continue;
                (*itAudioAnalyzer)->setOnsetsThreshold(onsetThreshold);
            }
        }
        else if (name == STR_ENERGY_GAIN)
        {
            for (itAudioAnalyzer = audioAnalyzers->begin(); itAudioAnalyzer != audioAnalyzers->end(); ++itAudioAnalyzer) {
                if ((*itAudioAnalyzer)->getInputIndex() != audioInputIndex) continue;
                (*itAudioAnalyzer)->setDigitalGain(energyGainCurrent);
            }
        }
    }
}

void PMUICanvasAudioAnalyzer::pitchChanged(pitchParams &pitchParams)
{
    if (pitchParams.audioInputIndex != audioInputIndex) return;
    pitchCurrentMidiNote = pitchParams.midiNote;
}

void PMUICanvasAudioAnalyzer::energyChanged(energyParams &energyParams)
{
    if (energyParams.audioInputIndex != audioInputIndex) return;
    energyCurrent = energyGainCurrent * energyParams.energy;
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

void PMUICanvasAudioAnalyzer::loadPreset(int presetNumber)
{
    string presetPath = STR_PRESETS_BASEPATH + "/" + ofToString(presetNumber) + ".xml";
    loadSettings(presetPath);

    vector<PMDeviceAudioAnalyzer *>::iterator itAudioAnalyzer;
    for (itAudioAnalyzer = audioAnalyzers->begin(); itAudioAnalyzer != audioAnalyzers->end(); ++itAudioAnalyzer)
    {
        if ((*itAudioAnalyzer)->getInputIndex() != audioInputIndex) continue;

        // Update analyzer settings according to preset
        (*itAudioAnalyzer)->setDigitalGain(energyGainCurrent);
        (*itAudioAnalyzer)->setSilenceThreshold(silenceThreshold);
        (*itAudioAnalyzer)->setSilenceQueueLength(silenceQueueLength);
        (*itAudioAnalyzer)->setPauseTimeTreshold(pauseQueueLength);
        (*itAudioAnalyzer)->setOnsetsThreshold(onsetThreshold);
    }

    // Force GUI position when loading
    setPosition(5, 5);
}

void PMUICanvasAudioAnalyzer::savePreset(int presetNumber)
{
    string presetPath = STR_PRESETS_BASEPATH + "/" + ofToString(presetNumber) + ".xml";
    saveSettings(presetPath);
}

int PMUICanvasAudioAnalyzer::getActivePreset()
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

void PMUICanvasAudioAnalyzer::keyPressed(int key)
{
    if (key != OF_KEY_SHIFT) return;
    savingPreset = true;
}

void PMUICanvasAudioAnalyzer::keyReleased(int key)
{
    if (key != OF_KEY_SHIFT) return;
    savingPreset = false;
}
