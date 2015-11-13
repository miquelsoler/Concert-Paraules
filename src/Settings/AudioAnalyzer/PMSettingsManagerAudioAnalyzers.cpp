//
// Created by Miquel Àngel Soler on 13/11/15.
//

#include "PMSettingsManagerAudioAnalyzers.h"

static const string FILENAME = "settings/audioAnalyzer.json";

static const string STR_PITCH                   = "Pitch";
static const string STR_PITCH_MINFREQ           = "Min Frequency";
static const string STR_PITCH_MAXFREQ           = "Max Frequency";
static const string STR_ENERGY                  = "Energy";
static const string STR_ENERGY_MIN              = "Min Energy";
static const string STR_ENERGY_MAX              = "Max Energy";
static const string STR_SILENCE                 = "Silence";
static const string STR_SILENCE_ENABLE          = "Enabled";
static const string STR_SILENCE_THRESHOLD       = "Threshold (dB)";
static const string STR_SILENCE_QUEUELENGTH     = "Queue Length";
static const string STR_MELBANDS                = "Mel Bands";
static const string STR_MELBANDS_ENABLE         = "Enabled";
static const string STR_MELBANDS_NUMBANDS       = "Number of Bands";
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

float PMSettingsManagerAudioAnalyzers::getMinPitchFreq()
{
    return json[STR_PITCH][STR_PITCH_MINFREQ].asFloat();
}

float PMSettingsManagerAudioAnalyzers::getMaxPitchFreq()
{
    return json[STR_PITCH][STR_PITCH_MAXFREQ].asFloat();
}

float PMSettingsManagerAudioAnalyzers::getMinEnergy()
{
    return json[STR_ENERGY][STR_ENERGY_MIN].asFloat();
}

float PMSettingsManagerAudioAnalyzers::getMaxEnergy()
{
    return json[STR_ENERGY][STR_ENERGY_MAX].asFloat();
}

bool PMSettingsManagerAudioAnalyzers::getSilenceEnabled()
{
    return json[STR_SILENCE][STR_SILENCE_ENABLE].asBool();
}

int PMSettingsManagerAudioAnalyzers::getSilenceThreshold()
{
    return json[STR_SILENCE][STR_SILENCE_THRESHOLD].asInt();
}

unsigned int PMSettingsManagerAudioAnalyzers::getSilenceQueueLength()
{
    return json[STR_SILENCE][STR_SILENCE_QUEUELENGTH].asUInt();
}

bool PMSettingsManagerAudioAnalyzers::getMelBandsEnabled()
{
    return json[STR_MELBANDS][STR_MELBANDS_ENABLE].asBool();
}

unsigned int PMSettingsManagerAudioAnalyzers::getNumMelBands()
{
    return json[STR_MELBANDS][STR_MELBANDS_NUMBANDS].asUInt();
}

float PMSettingsManagerAudioAnalyzers::getSmoothingDelta()
{
    return json[STR_SMOOTHING][STR_SMOOTHING_DELTA].asFloat();
}

