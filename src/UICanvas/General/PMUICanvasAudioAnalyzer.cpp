//
// Created by Miquel Àngel Soler on 7/11/15.
//

static const unsigned int PRESETSMATRIX_NUMROWS = 1;
static const unsigned int PRESETSMATRIX_NUMCOLS = 6;
//static const string STR_CANVAS_BASEPATH = "presets/AUDIO_ANALYZER";


#include "PMUICanvasAudioAnalyzer.h"

//--------------------------------------------------------------------------------------------------
PMUICanvasAudioAnalyzer::PMUICanvasAudioAnalyzer(string title, int headerFontSize, unsigned int _audioInputIndex) : PMBaseUICanvas(title, headerFontSize)
{
    audioInputIndex = _audioInputIndex;
    savingPreset = false;
}

//--------------------------------------------------------------------------------------------------
void PMUICanvasAudioAnalyzer::init(int posX, int posY, bool autosize, int width, int height)
{
    PMBaseUICanvas::init(posX, posY, autosize, width, height);

//    settings = &PMSettingsManagerAudioAnalyzers::getInstance();
//
//    pitchMinMidiNote = settings->getMaxPitchMidiNote();
//    pitchMaxMidiNote = settings->getMinPitchMidiNote();

    silenceOn = false;

    audioAnalyzers = PMAudioAnalyzer::getInstance().getAudioAnalyzers();
    vector<PMDeviceAudioAnalyzer *>::iterator itAudioAnalyzer;

    for (itAudioAnalyzer = audioAnalyzers->begin(); itAudioAnalyzer != audioAnalyzers->end(); ++itAudioAnalyzer)
    {
        if ((*itAudioAnalyzer)->getInputIndex() != audioInputIndex) continue;

        string strChannelNumbers;
        vector<unsigned int> channelNumbers = (*itAudioAnalyzer)->getChannelNumbers();
        for (int i=0; i<channelNumbers.size(); ++i)
        {
            strChannelNumbers += ofToString(channelNumbers[i]);
            if (i < channelNumbers.size() - 1)
                strChannelNumbers += ",";
        }

        addLabel("Device: " + ofToString((*itAudioAnalyzer)->getDeviceID()) + " Channels: " + strChannelNumbers);
        addSpacer();

        // Presets
        addLabel("PRESETS");
        presetsMatrix = addToggleMatrix("PRESETS", PRESETSMATRIX_NUMROWS, PRESETSMATRIX_NUMCOLS,200/PRESETSMATRIX_NUMCOLS,20);
        presetsMatrix->setAllowMultiple(false);
        presetsMatrix->setTriggerType(OFX_UI_TRIGGER_NONE );
        
        ofAddListener(newGUIEvent, this, &PMUICanvasAudioAnalyzer::handleEvents);

        addSpacer();

        addLabel("PITCH");
        // Current freq value
//        pitchSlider = addSlider("Midi note", settings->getMinPitchMidiNote(), settings->getMaxPitchMidiNote(), &pitchCurrentMidiNote, 300, 10);
        pitchSlider = addSlider("Midi note", 0, 127, &pitchCurrentMidiNote);
        pitchSlider->setTriggerType(OFX_UI_TRIGGER_NONE);
        addSpacer();
        ofAddListener((*itAudioAnalyzer)->eventPitchChanged, this, &PMUICanvasAudioAnalyzer::pitchChanged);

        addLabel("ENERGY");
//        energySilder = addSlider("Energy", settings->getMinEnergy(), settings->getMaxEnergy(), &energyCurrent, 300, 10);
        
        energyGainSlider = addSlider("Gain",1.0,10.0,&energyGainCurrent);
        energySilder = addSlider("Energy", 0.0, 1.0, &energyCurrent);
        energySilder->setTriggerType(OFX_UI_TRIGGER_NONE);
        addSpacer();
        ofAddListener((*itAudioAnalyzer)->eventEnergyChanged, this, &PMUICanvasAudioAnalyzer::energyChanged);

        addLabel("SILENCE");
        addSlider("Silence Threshold",0.0,0.5,&silenceThreshold);
        addSlider("Silence Length (ms)",0.0,1000.0,&silenceQueueLength);
        silenceToggle = addLabelToggle("SILENCE", &silenceOn);
        silenceToggle->setTriggerType(OFX_UI_TRIGGER_NONE);
        addSpacer();
        ofAddListener((*itAudioAnalyzer)->eventSilenceStateChanged, this, &PMUICanvasAudioAnalyzer::silenceStateChanged);

        addLabel("PAUSE");
        addSlider("Pause Length (ms)",0.0,10000.0,&pauseQueueLength);
        pauseToggle = addLabelToggle("PAUSE", &pauseOn);
        pauseToggle->setTriggerType(OFX_UI_TRIGGER_NONE);
        addSpacer();
        ofAddListener((*itAudioAnalyzer)->eventPauseStateChanged, this, &PMUICanvasAudioAnalyzer::pauseStateChanged);

        addLabel("ONSET");
        addSlider("Onset Threshold",0.0,1.0,&silenceThreshold);
        onsetToggle = addLabelToggle("ONSET", &onsetOn);
        onsetToggle->setTriggerType(OFX_UI_TRIGGER_NONE);
        addSpacer();
        ofAddListener((*itAudioAnalyzer)->eventOnsetStateChanged, this, &PMUICanvasAudioAnalyzer::onsetStateChanged);

        addLabel("SHT");
        shtToggle = addLabelToggle("SHT", &shtOn);
        shtToggle->setTriggerType(OFX_UI_TRIGGER_NONE);
        addSpacer();
        ofAddListener((*itAudioAnalyzer)->eventShtStateChanged, this, &PMUICanvasAudioAnalyzer::shtStateChanged);
    }

    if (autosize) autoSizeToFitWidgets();
}

//--------------------------------------------------------------------------------------------------
void PMUICanvasAudioAnalyzer::clear()
{
    ofxUICanvas::clearWidgets();
    superInit("AUDIO ANALYZER", OFX_UI_FONT_MEDIUM);
}

//--------------------------------------------------------------------------------------------------
void PMUICanvasAudioAnalyzer::handleEvents(ofxUIEventArgs &e)
{
    string name = e.getName();

    if (name.find("PRESETS")!=-1)
    {
        int activePreset = getActivePreset();

        if (savingPreset) {
            savePreset(activePreset);
        } else {
            loadPreset(activePreset);
        }
    }
    else if(name=="Silence Threshold")
    {
        vector<PMDeviceAudioAnalyzer *>::iterator itAudioAnalyzer;
        for (itAudioAnalyzer = audioAnalyzers->begin(); itAudioAnalyzer != audioAnalyzers->end(); ++itAudioAnalyzer)
        {
            if ((*itAudioAnalyzer)->getInputIndex() != audioInputIndex) continue;
            (*itAudioAnalyzer)->setSilenceThreshold(e.getFloat());
        }
    }
    else if(name == "Silence Length (ms)")
    {
        vector<PMDeviceAudioAnalyzer *>::iterator itAudioAnalyzer;
        for (itAudioAnalyzer = audioAnalyzers->begin(); itAudioAnalyzer != audioAnalyzers->end(); ++itAudioAnalyzer)
        {
            if ((*itAudioAnalyzer)->getInputIndex() != audioInputIndex) continue;
            (*itAudioAnalyzer)->setSilenceQueueLength(e.getFloat());
        }
    }
    else if(name == "Pause Length (ms)")
    {
        vector<PMDeviceAudioAnalyzer *>::iterator itAudioAnalyzer;
        for (itAudioAnalyzer = audioAnalyzers->begin(); itAudioAnalyzer != audioAnalyzers->end(); ++itAudioAnalyzer)
        {
            if ((*itAudioAnalyzer)->getInputIndex() != audioInputIndex) continue;
            (*itAudioAnalyzer)->setPauseTimeTreshold(e.getFloat());
        }
    }
    else if(name == "Onset Threshold")
    {
        vector<PMDeviceAudioAnalyzer *>::iterator itAudioAnalyzer;
        for (itAudioAnalyzer = audioAnalyzers->begin(); itAudioAnalyzer != audioAnalyzers->end(); ++itAudioAnalyzer)
        {
            if ((*itAudioAnalyzer)->getInputIndex() != audioInputIndex) continue;
            (*itAudioAnalyzer)->setOnsetsThreshold(e.getFloat());
        }
    }
    
}

//--------------------------------------------------------------------------------------------------
void PMUICanvasAudioAnalyzer::pitchChanged(pitchParams &pitchParams)
{
    if (pitchParams.audioInputIndex != audioInputIndex) return;

    pitchCurrentMidiNote = pitchParams.midiNote;

//    pitchMinMidiNote = pitchParams.midiNote;
//    if ((pitchParams.midiNote > settings->getMinPitchMidiNote()) && (pitchParams.midiNote < pitchMinMidiNote)) {
//        
//    }

//    if (pitchParams.midiNote > pitchMaxMidiNote) {
//        pitchMaxMidiNote = pitchParams.midiNote;
//    }

}

//--------------------------------------------------------------------------------------------------
void PMUICanvasAudioAnalyzer::energyChanged(energyParams &energyParams)
{
    if (energyParams.audioInputIndex != audioInputIndex) return;
    energyCurrent = energyGainCurrent * energyParams.energy;
}


//--------------------------------------------------------------------------------------------------
void PMUICanvasAudioAnalyzer::silenceStateChanged(silenceParams &silenceParams)
{
    if (silenceParams.audioInputIndex != audioInputIndex) return;
    silenceOn = silenceParams.isSilent;
//    cout << "Silent is " << silenceOn << "En.Curr : " << energyCurrent << "Silence Thr , Length  :  " << silenceThreshold << " , " << silenceQueueLength << endl;
}

//--------------------------------------------------------------------------------------------------
void PMUICanvasAudioAnalyzer::pauseStateChanged(pauseParams &pauseParams)
{
    if (pauseParams.audioInputIndex != audioInputIndex) return;
    pauseOn = pauseParams.isPaused;
}

//--------------------------------------------------------------------------------------------------
void PMUICanvasAudioAnalyzer::onsetStateChanged(onsetParams &onsetParams)
{
    if (onsetParams.audioInputIndex != audioInputIndex) return;
    onsetOn = onsetParams.isOnset;
}


//--------------------------------------------------------------------------------------------------
void PMUICanvasAudioAnalyzer::shtStateChanged(shtParams &_shtParams)
{
    if (_shtParams.audioInputIndex != audioInputIndex) return;
    shtOn = _shtParams.isSht;
}

//--------------------------------------------------------------------------------------------------
void PMUICanvasAudioAnalyzer::loadPreset(int presetNumber)
{
    string presetPath = "presets/AUDIO_ANALYZER/" + ofToString(presetNumber) + ".xml";
    loadSettings(presetPath);
    cout << "AudioAnalyzer :: loading preset : " << presetNumber << " to " << presetPath << endl;
}

//--------------------------------------------------------------------------------------------------
void PMUICanvasAudioAnalyzer::savePreset(int presetNumber)
{
    string presetPath = "presets/AUDIO_ANALYZER/" + ofToString(presetNumber) + ".xml";
    saveSettings(presetPath);
    cout << "AudioAnalyzer :: saving preset : " << presetNumber << " to " << presetPath << endl;
}

//--------------------------------------------------------------------------------------------------
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

//--------------------------------------------------------------------------------------------------
void PMUICanvasAudioAnalyzer::keyPressed(int key)
{
    if (key != OF_KEY_SHIFT) return;
    savingPreset = true;
}

//--------------------------------------------------------------------------------------------------
void PMUICanvasAudioAnalyzer::keyReleased(int key)
{
    if (key != OF_KEY_SHIFT) return;
    savingPreset = false;
}
