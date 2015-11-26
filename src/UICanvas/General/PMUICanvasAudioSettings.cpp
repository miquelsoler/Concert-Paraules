//
// Created by Miquel Àngel Soler on 20/11/15.
//

#include "PMUICanvasAudioSettings.h"

static const unsigned int PRESETSMATRIX_NUMROWS = 2;
static const unsigned int PRESETSMATRIX_NUMCOLS = 5;

static const string STR_PRESETS = "PRESETS";
static const string STR_PRESETS_INFO = "Click to LOAD | Shift+Click to SAVE";

static const string STR_PITCH = "PITCH";
static const string STR_PITCH_MIN_MIDI_NOTE = "Min MIDI Note";
static const string STR_PITCH_MAX_MIDI_NOTE = "Max MIDI Note";

static const string STR_ENERGY = "ENERGY";
static const string STR_ENERGY_MIN = "Min";
static const string STR_ENERGY_MAX = "Max";

static const string STR_SILENCE = "SILENCE";
static const string STR_SILENCE_THRESHOLD = "Threshold (ms)";
static const string STR_SILENCE_QUEUE_LENGTH = "Queue Length";

static const string STR_ONSETS = "ONSETS";
static const string STR_ONSETS_THRESHOLD = "Silence Threshold";
static const string STR_ONSETS_ALPHA = "Alpha";

static const string STR_SMOOTHING = "SMOOTHING";
static const string STR_SMOOTHING_DELTA = "Delta";

static const string STR_MELBANDS = "MEL BANDS";
static const string STR_MELBANDS_NUMBANDS = "Num Bands";

static const string STR_CANVAS_BASEPATH = "settings/gui/";

PMUICanvasAudioSettings::PMUICanvasAudioSettings(string title, int headerFontSize) : PMBaseUICanvas(title, headerFontSize)
{
}

void PMUICanvasAudioSettings::init(int posX, int posY, bool autosize, int width, int height)
{
    PMBaseUICanvas::init(posX, posY, autosize, width, height);

    settings = &PMSettingsManagerAudioAnalyzers::getInstance();

    setTriggerWidgetsUponLoad(false);

    addLabel(STR_PRESETS);
    addLabel(STR_PRESETS_INFO, OFX_UI_FONT_SMALL);
    setGlobalButtonDimension(32);
    presetsMatrix = addToggleMatrix(STR_PRESETS, PRESETSMATRIX_NUMROWS, PRESETSMATRIX_NUMCOLS);
    presetsMatrix->setAllowMultiple(false);
    addSpacer();

    addLabel(STR_PITCH);
    minMidiValue = settings->getMinPitchMidiNote();
    maxMidiValue = settings->getMaxPitchMidiNote();
    minMidiSlider = addSlider(STR_PITCH_MIN_MIDI_NOTE, 0, 100, &minMidiValue);
    minMidiSlider->setLabelPrecision(2);
    minMidiSlider->setTriggerType(OFX_UI_TRIGGER_END);
    maxMidiSlider = addSlider(STR_PITCH_MAX_MIDI_NOTE, 0, 100, &maxMidiValue);
    maxMidiSlider->setTriggerType(OFX_UI_TRIGGER_END);
    addSpacer();

    addLabel(STR_ENERGY);
    minEnergyValue = settings->getMinEnergy();
    maxEnergyValue = settings->getMaxEnergy();
    minEnergySlider = addSlider(STR_ENERGY_MIN, 0, 10, &minEnergyValue);
    minEnergySlider->setTriggerType(OFX_UI_TRIGGER_END);
    maxEnergySlider = addSlider(STR_ENERGY_MAX, 0, 10, &maxEnergyValue);
    maxEnergySlider->setTriggerType(OFX_UI_TRIGGER_END);
    addSpacer();

    addLabel(STR_SILENCE);
    silenceThresholdValue = settings->getSilenceThreshold();
    silenceQueueValue = settings->getSilenceQueueLength();
    silenceThresholdSlider = addSlider(STR_SILENCE_THRESHOLD, 0, 10, &silenceThresholdValue);
    silenceThresholdSlider->setLabelPrecision(2);
    silenceThresholdSlider->setTriggerType(OFX_UI_TRIGGER_END);
    silenceQueueSlider = addIntSlider(STR_SILENCE_QUEUE_LENGTH, 0, 200, &silenceQueueValue);
    silenceQueueSlider->setTriggerType(OFX_UI_TRIGGER_END);
    addSpacer();

    addLabel(STR_ONSETS);
    onsetThresholdValue = settings->getOnsetsThreshold();
    onsetAlphaValue = settings->getOnsetsAlpha();
    onsetThresholdSlider = addSlider(STR_ONSETS_THRESHOLD, 0, 10, &onsetThresholdValue);
    onsetThresholdSlider->setTriggerType(OFX_UI_TRIGGER_END);
    onsetAlphaSlider = addSlider(STR_ONSETS_ALPHA, 0, 1, &onsetAlphaValue);
    onsetAlphaSlider->setTriggerType(OFX_UI_TRIGGER_END);
    addSpacer();

    addLabel(STR_SMOOTHING);
    smoothingDeltaValue = settings->getSmoothingDelta();
    smoothingDeltaSlider = addSlider(STR_SMOOTHING_DELTA, 0, 1, &smoothingDeltaValue);
    smoothingDeltaSlider->setLabelPrecision(5);
    smoothingDeltaSlider->setTriggerType(OFX_UI_TRIGGER_END);
    addSpacer();

    addLabel(STR_MELBANDS);
    numMelBandsValue = settings->getNumMelBands();
    numMelBandsSlider = addIntSlider(STR_MELBANDS_NUMBANDS, 1, 32, &numMelBandsValue);
    numMelBandsSlider->setTriggerType(OFX_UI_TRIGGER_END);

    ofAddListener(newGUIEvent, this, &PMUICanvasAudioSettings::handleEvents);

    if (autosize) autoSizeToFitWidgets();

    presetsMode = PRESET_LOAD;

    int presetNumber = getActivePreset();
    if (presetNumber == -1) return;

    string presetFilename = "audioSettings" + ofToString(presetNumber) + ".xml";
    loadSettings(STR_CANVAS_BASEPATH + presetFilename);
}

void PMUICanvasAudioSettings::clear()
{
    ofxUICanvas::clearWidgets();
    superInit("AUDIO SETTINGS", OFX_UI_FONT_MEDIUM);
}

void PMUICanvasAudioSettings::handleEvents(ofxUIEventArgs &e)
{
    string name = e.getName();

    if (ofIsStringInString(name, STR_PRESETS))
    {
        // Preset load/save

        int presetNumber = getActivePreset();
        if (presetNumber == -1) return;

        string presetFilename = "audioSettings" + ofToString(presetNumber) + ".xml";

        switch(presetsMode)
        {
            case PRESET_LOAD:
                loadSettings(STR_CANVAS_BASEPATH + presetFilename);
                updateExternalSettings();
                break;
            case PRESET_SAVE:
                saveSettings(STR_CANVAS_BASEPATH + presetFilename);
                break;
        }
    }
    else
    {
        // Sliders

        if (e.widget->getTriggerType() != OFX_UI_TRIGGER_END) return;

        if (name == STR_PITCH_MIN_MIDI_NOTE) settings->setMinPitchMidiNote(minMidiValue);
        if (name == STR_PITCH_MAX_MIDI_NOTE) settings->setMaxPitchMidiNote(maxMidiValue);
        if (name == STR_ENERGY_MIN) settings->setMinEnergy(minEnergyValue);
        if (name == STR_ENERGY_MAX) settings->setMaxEnergy(maxEnergyValue);
        if (name == STR_SILENCE_THRESHOLD) settings->setSilenceThreshold(silenceThresholdValue);
        if (name == STR_SILENCE_QUEUE_LENGTH) settings->setSilenceQueueLength((unsigned int)silenceQueueValue);
        if (name == STR_ONSETS_THRESHOLD) settings->setOnsetsThreshold(onsetThresholdValue);
        if (name == STR_ONSETS_ALPHA) settings->setOnsetsAlpha(onsetAlphaValue);
        if (name == STR_SMOOTHING_DELTA) settings->setSmoothingDelta(smoothingDeltaValue);
        if (name == STR_MELBANDS_NUMBANDS) settings->setNumMelBands((unsigned int)numMelBandsValue);
    }
}

void PMUICanvasAudioSettings::keyPressed(int key)
{
    if (key != OF_KEY_SHIFT) return;
    presetsMode = PRESET_SAVE;
}

void PMUICanvasAudioSettings::keyReleased(int key)
{
    if (key != OF_KEY_SHIFT) return;
    presetsMode = PRESET_LOAD;
}

void PMUICanvasAudioSettings::updateExternalSettings()
{
    settings->setMinPitchMidiNote(minMidiValue);
    settings->setMaxPitchMidiNote(maxMidiValue);
    settings->setMinEnergy(minEnergyValue);
    settings->setMaxEnergy(maxEnergyValue);
    settings->setSilenceThreshold(silenceThresholdValue);
    settings->setSilenceQueueLength((unsigned int)silenceQueueValue);
    settings->setOnsetsThreshold(onsetThresholdValue);
    settings->setOnsetsAlpha(onsetAlphaValue);
    settings->setSmoothingDelta(smoothingDeltaValue);
    settings->setNumMelBands((unsigned int)numMelBandsValue);
}

int PMUICanvasAudioSettings::getActivePreset()
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
