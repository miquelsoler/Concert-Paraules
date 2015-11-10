//
//  PMScene2.cpp
//  PMConcertParaules
//
//  Created by Miquel Àngel Soler on 7/10/15.
//
//

#include "PMScene2.hpp"
#include "Defaults.h"
#include "PMSettingsManagerGeneral.h"
#include "PMSettingsManagerAudioDevices.h"
#include "PMAudioAnalyzerConstants.h"

static const string STR_CANVAS_BASEPATH = "settings/gui/";

PMScene2::PMScene2() : PMBaseScene("Scene 2")
{
#ifdef OF_DEBUG
    showGUI= PMSettingsManagerGeneral::getInstance().getDebugShowGUIScene2();
#else
    showGUI = PMSettingsManagerGeneral::getInstance().getReleaseShowGUIScene2();
#endif

    backgroundColor = ofColor::white;

    // GUI
    {
        canvasBgColor = ofColor(50, 50, 50, 200);

        guiRenderers = new PMUICanvasRenderers("RENDER MODE", OFX_UI_FONT_MEDIUM);
        guiRenderers->init(200, 200);
        guiRenderers->setBackgroundColor(canvasBgColor);
        guiRenderers->setVisible(false);

        guiAudioAnalyzerCreated = false;

//        guiAudioAnalyzer = new PMUICanvasAudioAnalyzer("AUDIO ANALYZER", OFX_UI_FONT_MEDIUM);
//        guiAudioAnalyzer->init(200, 400);
//        guiAudioAnalyzer->setBackgroundColor(canvasBgColor);
//        guiAudioAnalyzer->setVisible(false);
    }

    // Renderer
    {
        renderer = new PMRendererPaintbrush();
    }
}

PMScene2::~PMScene2()
{
    delete guiRenderers;
    delete guiAudioAnalyzer;
}

void PMScene2::setup()
{
#if OF_DEBUG
    cout << "S2 SETUP" << endl;
#endif
    vector<PMSettingsDevice> *audioDevices = PMSettingsManagerAudioDevices::getInstance().getAudioDevices();
    vector<PMSettingsDevice>::iterator itDevice;

    for (itDevice = audioDevices->begin(); itDevice != audioDevices->end(); ++itDevice)
    {
        if (!(*itDevice).enabled) continue;
        unsigned int numChannels = (unsigned int)((*itDevice).channels.size());

        for (unsigned int i=0; i<numChannels; i++)
        {
            PMSettingsDeviceChannel channel = (*itDevice).channels[i];

            if (!channel.enabled) continue;

            int deviceId = (*itDevice).ID;
            int inChannels = (*itDevice).inChannels;
            int outChannels = (*itDevice).outChannels;
            int channelNumber = channel.ID;

            PMDeviceAudioAnalyzer *deviceAudioAnalyzer = PMAudioAnalyzer::getInstance().addDeviceAudioAnalyzer(deviceId,
                    inChannels, outChannels,
                    DEFAULT_SAMPLERATE, DEFAULT_BUFFERSIZE,
                    PMDAA_CHANNEL_MONO, channelNumber);

            ofAddListener(deviceAudioAnalyzer->eventPitchChanged, this, &PMScene2::pitchChanged);
            ofAddListener(deviceAudioAnalyzer->eventEnergyChanged, this, &PMScene2::energyChanged);
            ofAddListener(deviceAudioAnalyzer->eventSilenceStateChanged, this, &PMScene2::silenceStateChanged);
        }
    }

    // GUI
    {
        if (!guiAudioAnalyzerCreated) {
            guiAudioAnalyzer = new PMUICanvasAudioAnalyzer("AUDIO ANALYZER", OFX_UI_FONT_MEDIUM);
            guiAudioAnalyzer->init(200, 400);
            guiAudioAnalyzer->setBackgroundColor(canvasBgColor);
            guiAudioAnalyzer->setVisible(false);
        }

        guiAudioAnalyzerCreated = true;
    }

    renderer->setup();
}

void PMScene2::update()
{
    renderer->update();
}

void PMScene2::updateEnter()
{
//    cout << "PMScene2::updateEnter()" << endl;
    if (isEnteringFirst())
    {
        guiRenderers->loadSettings(STR_CANVAS_BASEPATH + "renderers2.xml");
        guiRenderers->setVisible(showGUI);

        guiAudioAnalyzer->loadSettings(STR_CANVAS_BASEPATH + "audioAnalyzer2.xml");
        guiAudioAnalyzer->setVisible(showGUI);
    }

    PMAudioAnalyzer::getInstance().start();

    PMBaseScene::updateEnter();
}

void PMScene2::updateExit()
{
    saveSettings();
    PMBaseScene::updateExit();
}

void PMScene2::draw()
{
    renderer->draw();
}

void PMScene2::saveSettings()
{
    PMAudioAnalyzer::getInstance().stop();
    PMAudioAnalyzer::getInstance().clear();

    guiRenderers->saveSettings(STR_CANVAS_BASEPATH + "renderers2.xml");
    guiRenderers->setVisible(false);

    guiAudioAnalyzer->saveSettings(STR_CANVAS_BASEPATH + "audioAnalyzer2.xml");
    guiAudioAnalyzer->setVisible(false);
}

#pragma mark - Keyboard events

void PMScene2::keyReleased(int key)
{
    PMBaseScene::keyReleased(key);

    switch(key)
    {
        case 'g':
        case 'G':
        {
            showGUI = !showGUI;
            guiRenderers->setVisible(showGUI);
            guiAudioAnalyzer->setVisible(showGUI);
            ofClear(backgroundColor);
            break;
        }
        default: break;
    }
}

#pragma mark - Audio Events

void PMScene2::pitchChanged(pitchParams &pitchParams)
{
    float pitchFreqMin = AUDIOANALYZER_PITCH_MINFREQ;
    float pitchFreqMax = AUDIOANALYZER_PITCH_MAXFREQ;
    float yMin = 1.0f;
    float yMax = 0.0f;

    float y = ofMap(pitchParams.freq, pitchFreqMin, pitchFreqMax, yMin, yMax, true);
    renderer->setPositionY(y);
}

void PMScene2::energyChanged(energyParams &energyParams)
{
    float energyMin = AUDIOANALYZER_ENERGY_MIN;
    float energyMax = AUDIOANALYZER_ENERGY_MAX;
    float normalizedSizeMin = 0.25f;
    float normalizedSizeMax = 1.0f;

    float size = ofMap(energyParams.energy, energyMin, energyMax, normalizedSizeMin, normalizedSizeMax, true);

    renderer->setSize(size);
}

void PMScene2::silenceStateChanged(silenceParams &silenceParams)
{
    renderer->setShouldPaint(!silenceParams.isSilent);
}
