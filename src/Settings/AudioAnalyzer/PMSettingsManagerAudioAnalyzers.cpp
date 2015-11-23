//
// Created by Miquel Àngel Soler on 13/11/15.
//

#include "PMSettingsManagerAudioAnalyzers.h"

static const string FILENAME = "settings/audioAnalyzer.json";

static const string STR_PITCH                   = "Pitch";
static const string STR_PITCH_MINMIDINOTE       = "Min MIDI Note";
static const string STR_PITCH_MAXMIDINOTE       = "Max MIDI Note";
static const string STR_ASCDESCSIZE             = "Ascending Descending Analysis Size";
static const string STR_ENERGY                  = "Energy";
static const string STR_ENERGY_MIN              = "Min Energy";
static const string STR_ENERGY_MAX              = "Max Energy";
static const string STR_SILENCE                 = "Silence";
static const string STR_SILENCE_ENABLE          = "Enabled";
static const string STR_SILENCE_THRESHOLD       = "Threshold (ms)";
static const string STR_SILENCE_QUEUELENGTH     = "Queue Length (ms)";
static const string STR_MELBANDS                = "Mel Bands";
static const string STR_MELBANDS_ENABLE         = "Enabled";
static const string STR_MELBANDS_NUMBANDS       = "Number of Bands";
static const string STR_ONSETS                  = "Onsets";
static const string STR_ONSETS_THRESHOLD        = "Silence Threshold";
static const string STR_ONSETS_ALPHA            = "Alpha";
static const string STR_SMOOTHING               = "Smoothing";
static const string STR_SMOOTHING_DELTA         = "Delta";

PMSettingsManagerAudioAnalyzers::PMSettingsManagerAudioAnalyzers() : PMSettingsManager()
{
    filename = FILENAME;

    bool parserResult = load(filename);
    if (!parserResult)
    {
        string msg = "BAD FORMAT IN " + FILENAME + ". Now quitting...";
        ofLog(OF_LOG_ERROR, msg);
        std::exit(EXIT_FAILURE);
    }
}

float PMSettingsManagerAudioAnalyzers::getMinPitchMidiNote() {
    return json[STR_PITCH][STR_PITCH_MINMIDINOTE].asFloat();
}

float PMSettingsManagerAudioAnalyzers::getMaxPitchMidiNote() {
    return json[STR_PITCH][STR_PITCH_MAXMIDINOTE].asFloat();
}

void PMSettingsManagerAudioAnalyzers::setMinPitchMidiNote(float midiNote) {
    json[STR_PITCH][STR_PITCH_MINMIDINOTE] = midiNote;
    json.save(FILENAME, true);
}

void PMSettingsManagerAudioAnalyzers::setMaxPitchMidiNote(float midiNote) {
    json[STR_PITCH][STR_PITCH_MAXMIDINOTE] = midiNote;
    json.save(FILENAME, true);
}

float PMSettingsManagerAudioAnalyzers::getMinEnergy() {
    return json[STR_ENERGY][STR_ENERGY_MIN].asFloat();
}

float PMSettingsManagerAudioAnalyzers::getMaxEnergy() {
    return json[STR_ENERGY][STR_ENERGY_MAX].asFloat();
}

void PMSettingsManagerAudioAnalyzers::setMinEnergy(float minEnergy) {
    json[STR_ENERGY][STR_ENERGY_MIN] = minEnergy;
    json.save(FILENAME, true);
}

void PMSettingsManagerAudioAnalyzers::setMaxEnergy(float maxEnergy) {
    json[STR_ENERGY][STR_ENERGY_MAX] = maxEnergy;
    json.save(FILENAME, true);
}

bool PMSettingsManagerAudioAnalyzers::getSilenceEnabled() {
    return json[STR_SILENCE][STR_SILENCE_ENABLE].asBool();
}

float PMSettingsManagerAudioAnalyzers::getSilenceThreshold() {
    return json[STR_SILENCE][STR_SILENCE_THRESHOLD].asFloat();
}

unsigned int PMSettingsManagerAudioAnalyzers::getSilenceQueueLength() {
    return json[STR_SILENCE][STR_SILENCE_QUEUELENGTH].asUInt();
}

void PMSettingsManagerAudioAnalyzers::setSilenceThreshold(float threshold) {
    json[STR_SILENCE][STR_SILENCE_THRESHOLD] = threshold;
    json.save(FILENAME, true);
}

void PMSettingsManagerAudioAnalyzers::setSilenceQueueLength(unsigned int length) {
    json[STR_SILENCE][STR_SILENCE_QUEUELENGTH] = length;
    json.save(FILENAME, true);
}

bool PMSettingsManagerAudioAnalyzers::getMelBandsEnabled() {
    return json[STR_MELBANDS][STR_MELBANDS_ENABLE].asBool();
}

unsigned int PMSettingsManagerAudioAnalyzers::getNumMelBands() {
    return json[STR_MELBANDS][STR_MELBANDS_NUMBANDS].asUInt();
}

void PMSettingsManagerAudioAnalyzers::setNumMelBands(unsigned int numBands) {
    json[STR_MELBANDS][STR_MELBANDS_NUMBANDS] = numBands;
    json.save(FILENAME, true);
}

float PMSettingsManagerAudioAnalyzers::getOnsetsThreshold() {
    return json[STR_ONSETS][STR_ONSETS_THRESHOLD].asFloat();
}

float PMSettingsManagerAudioAnalyzers::getOnsetsAlpha() {
    return json[STR_ONSETS][STR_ONSETS_ALPHA].asFloat();
}

void PMSettingsManagerAudioAnalyzers::setOnsetsThreshold(float threshold) {
    json[STR_ONSETS][STR_ONSETS_THRESHOLD] = threshold;
    json.save(FILENAME, true);
}

void PMSettingsManagerAudioAnalyzers::setOnsetsAlpha(float alpha) {
    json[STR_ONSETS][STR_ONSETS_ALPHA] = alpha;
    json.save(FILENAME, true);
}

float PMSettingsManagerAudioAnalyzers::getSmoothingDelta() {
    return json[STR_SMOOTHING][STR_SMOOTHING_DELTA].asFloat();
}

void PMSettingsManagerAudioAnalyzers::setSmoothingDelta(float delta) {
    json[STR_SMOOTHING][STR_SMOOTHING_DELTA] = delta;
    json.save(FILENAME, true);
}

int PMSettingsManagerAudioAnalyzers::getAscDescAnalysisSize() {
    return json[STR_PITCH][STR_ASCDESCSIZE].asInt();
}
