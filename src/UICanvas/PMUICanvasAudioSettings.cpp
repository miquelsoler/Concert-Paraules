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
static const string STR_SILENCE_THRESHOLD = "Threshold (dB)";
static const string STR_SILENCE_QUEUE_LENGTH = "Queue Length";

static const string STR_ONSETS = "ONSETS";
static const string STR_ONSETS_THRESHOLD = "Silence Threshold";
static const string STR_ONSETS_ALPHA = "Alpha";

static const string STR_SMOOTHING = "SMOOTHING";
static const string STR_SMOOTHING_DELTA = "Delta";

static const string STR_MELBANDS = "MEL BANDS";
static const string STR_MELBANDS_NUMBANDS = "Num Bands";

PMUICanvasAudioSettings::PMUICanvasAudioSettings(string title, int headerFontSize) : PMBaseUICanvas(title, headerFontSize)
{
}

void PMUICanvasAudioSettings::init(int posX, int posY, bool autosize, int width, int height)
{
    PMBaseUICanvas::init(posX, posY, autosize, width, height);

    settings = &PMSettingsManagerAudioAnalyzers::getInstance();

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
    maxMidiSlider = addSlider(STR_PITCH_MAX_MIDI_NOTE, 0, 100, &maxMidiValue);
    addSpacer();

    addLabel(STR_ENERGY);
    minEnergyValue = settings->getMinEnergy();
    maxEnergyValue = settings->getMaxEnergy();
    minEnergySlider = addSlider(STR_ENERGY_MIN, 0, 10, &minEnergyValue);
    maxEnergySlider = addSlider(STR_ENERGY_MAX, 0, 10, &maxEnergyValue);
    addSpacer();

    addLabel(STR_SILENCE);
    silenceThresholdValue = settings->getSilenceThreshold();
    silenceQueueValue = settings->getSilenceQueueLength();
    silenceThresholdSlider = addIntSlider(STR_SILENCE_THRESHOLD, -60, -1, &silenceThresholdValue);
    silenceQueueSlider = addIntSlider(STR_SILENCE_QUEUE_LENGTH, 0, 200, &silenceQueueValue);
    addSpacer();

    addLabel(STR_ONSETS);
    onsetThresholdValue = settings->getOnsetsThreshold();
    onsetAlphaValue = settings->getOnsetsAlpha();
    onsetThresholdSlider = addSlider(STR_ONSETS_THRESHOLD, 0, 10, &onsetThresholdValue);
    onsetAlphaSlider = addSlider(STR_ONSETS_ALPHA, 0, 1, &onsetAlphaValue);
    addSpacer();

    addLabel(STR_SMOOTHING);
    smoothingDeltaValue = settings->getSmoothingDelta();
    smoothingDeltaSlider = addSlider(STR_SMOOTHING_DELTA, 0, 1, &smoothingDeltaValue);
    smoothingDeltaSlider->setLabelPrecision(10);
    addSpacer();

    addLabel(STR_MELBANDS);
    numMelBandsValue = settings->getNumMelBands();
    numMelBandsSlider = addIntSlider(STR_MELBANDS_NUMBANDS, 1, 32, &numMelBandsValue);

    ofAddListener(newGUIEvent, this, &PMUICanvasAudioSettings::handleEvents);

    if (autosize) autoSizeToFitWidgets();
}

void PMUICanvasAudioSettings::clear()
{
    ofxUICanvas::clearWidgets();
    superInit("AUDIO SETTINGS", OFX_UI_FONT_MEDIUM);
}

void PMUICanvasAudioSettings::handleEvents(ofxUIEventArgs &e)
{
    string name = e.getName();
    int kind = e.getKind();

    if (ofIsStringInString(name, STR_PRESETS))
        cout << "Got event from: " << name << endl;
}
