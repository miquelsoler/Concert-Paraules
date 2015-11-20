//
// Created by Miquel Àngel Soler on 20/11/15.
//

#include "PMUICanvasAudioSettings.h"

PMUICanvasAudioSettings::PMUICanvasAudioSettings(string title, int headerFontSize) : PMBaseUICanvas(title, headerFontSize)
{
}

void PMUICanvasAudioSettings::init(int posX, int posY, bool autosize, int width, int height)
{
    PMBaseUICanvas::init(posX, posY, autosize, width, height);

    settings = &PMSettingsManagerAudioAnalyzers::getInstance();

    addLabel("PITCH");
    minMidiValue = settings->getMinPitchMidiNote();
    maxMidiValue = settings->getMaxPitchMidiNote();
    minMidiSlider = addSlider("Min MIDI Note", 0, 100, &minMidiValue);
    maxMidiSlider = addSlider("Max MIDI Note", 0, 100, &maxMidiValue);
    addSpacer();

    addLabel("ENERGY");
    minEnergyValue = settings->getMinEnergy();
    maxEnergyValue = settings->getMaxEnergy();
    minEnergySlider = addSlider("Min", 0, 10, &minEnergyValue);
    maxEnergySlider = addSlider("Max", 0, 10, &maxEnergyValue);
    addSpacer();

    addLabel("SILENCE");
    silenceThresholdValue = settings->getSilenceThreshold();
    silenceQueueValue = settings->getSilenceQueueLength();
    silenceThresholdSlider = addIntSlider("Threshold (dB)", -60, -1, &silenceThresholdValue);
    silenceQueueSlider = addIntSlider("Threshold (dB)", -60, -1, &silenceQueueValue);
    addSpacer();

    addLabel("ONSETS");
    onsetThresholdValue = settings->getOnsetsThreshold();
    onsetAlphaValue = settings->getOnsetsAlpha();
    onsetThresholdSlider = addSlider("Silence Threshold", 0, 10, &onsetThresholdValue);
    onsetAlphaSlider = addSlider("Alpha", 0, 1, &onsetAlphaValue);
    addSpacer();

    addLabel("SMOOTHING");
    smoothingDeltaValue = settings->getSmoothingDelta();
    smoothingDeltaSlider = addSlider("Delta", 0, 1, &smoothingDeltaValue);
    addSpacer();

    addLabel("MEL BANDS");
    numMelBandsValue = settings->getNumMelBands();
    numMelBandsSlider = addIntSlider("Num Bands", 1, 32, &numMelBandsValue);


    if (autosize) autoSizeToFitWidgets();
}

void PMUICanvasAudioSettings::clear()
{
    ofxUICanvas::clearWidgets();
    superInit("AUDIO SETTINGS", OFX_UI_FONT_MEDIUM);
}

void PMUICanvasAudioSettings::handleEvents(ofxUIEventArgs &e)
{
}
