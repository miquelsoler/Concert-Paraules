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

static const string STR_CANVAS_BASEPATH = "settings/gui/";

PMScene2::PMScene2() : PMBaseScene("Scene 2")
{
#ifdef OF_DEBUG
    showGUI= PMSettingsManagerGeneral::getInstance().getDebugShowGUIScene2();
#else
    showGUI = PMSettingsManagerGeneral::getInstance().getReleaseShowGUIScene2();
#endif

    audioAnalyzersSettings = &PMSettingsManagerAudioAnalyzers::getInstance();

    backgroundColor = ofColor::white;

    // GUI
    {
        canvasBgColor = ofColor(50, 50, 50, 200);

        guiRenderers = new PMUICanvasRenderers("RENDER MODE", OFX_UI_FONT_MEDIUM);
        guiRenderers->init(200, 200);
        guiRenderers->setBackgroundColor(canvasBgColor);
        guiRenderers->setVisible(false);

        guiAudioAnalyzerCreated = false;
    }

    // Renderer
    {
        renderer = new PMRendererPaintbrush((unsigned int)(PMSettingsManagerAudioDevices::getInstance().getEnabledAudioDevices()->size()));
    }
}

PMScene2::~PMScene2()
{
    delete guiRenderers;

    /**/
    for (int i=0; i<guiAudioAnalyzers.size(); ++i)
    {
        PMUICanvasAudioAnalyzer *gui = guiAudioAnalyzers[i];
        delete gui;
    }
    guiAudioAnalyzers.clear();
}

void PMScene2::setup()
{
    enabledAudioDevices = PMSettingsManagerAudioDevices::getInstance().getEnabledAudioDevices();

    vector<PMSettingsDevice>::iterator itDevice;

    for (itDevice = enabledAudioDevices->begin(); itDevice != enabledAudioDevices->end(); ++itDevice)
    {
        cout << "Device: " << (*itDevice).ID << "Channels: " << (*itDevice).channels.size() << endl;
    }

    unsigned int audioInputIndex = 0;

    for (itDevice = enabledAudioDevices->begin(); itDevice != enabledAudioDevices->end(); ++itDevice)
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
            unsigned int channelNumber = channel.ID;

            PMDeviceAudioAnalyzer *deviceAudioAnalyzer = PMAudioAnalyzer::getInstance().addDeviceAudioAnalyzer(audioInputIndex, deviceId,
                    inChannels, outChannels,
                    DEFAULT_SAMPLERATE, DEFAULT_BUFFERSIZE,
                    PMDAA_CHANNEL_MONO, channelNumber);

            ofAddListener(deviceAudioAnalyzer->eventPitchChanged, this, &PMScene2::pitchChanged);
            ofAddListener(deviceAudioAnalyzer->eventEnergyChanged, this, &PMScene2::energyChanged);
            ofAddListener(deviceAudioAnalyzer->eventSilenceStateChanged, this, &PMScene2::silenceStateChanged);

            audioInputIndex++;
        }
    }

    // GUI
    {
        if (!guiAudioAnalyzerCreated)
        {
            audioInputIndex = 0;
            for (itDevice = enabledAudioDevices->begin(); itDevice != enabledAudioDevices->end(); ++itDevice)
            {
                for (int i = 0; i < (*itDevice).channels.size(); ++i)
                {
                    string title = "AUDIO ANALYZER " + ofToString(audioInputIndex);
                    PMUICanvasAudioAnalyzer *guiAudioAnalyzer = new PMUICanvasAudioAnalyzer(title, OFX_UI_FONT_MEDIUM, audioInputIndex);
                    guiAudioAnalyzer->init(200, 400 + (audioInputIndex * 200));
                    guiAudioAnalyzer->setBackgroundColor(canvasBgColor);
                    guiAudioAnalyzer->setVisible(false);

                    guiAudioAnalyzers.push_back(guiAudioAnalyzer);

                    audioInputIndex++;
                }
            }
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

        int i;
        vector<PMUICanvasAudioAnalyzer *>::iterator it;
        for(i=0, it = guiAudioAnalyzers.begin(); it != guiAudioAnalyzers.end(); it++, i++)
        {
            string guiSettingsFilename = "audioAnalyzer2." + ofToString(i) + ".xml";
            (*it)->loadSettings(STR_CANVAS_BASEPATH + guiSettingsFilename);
            (*it)->setVisible(showGUI);
        }
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

    int i;
    vector<PMUICanvasAudioAnalyzer *>::iterator it;
    for(i=0, it = guiAudioAnalyzers.begin(); it != guiAudioAnalyzers.end(); it++, ++i)
    {
        string guiSettingsFilename = "audioAnalyzer2." + ofToString(i) + ".xml";
        (*it)->saveSettings(STR_CANVAS_BASEPATH + guiSettingsFilename);
        (*it)->setVisible(false);
    }
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

            vector<PMUICanvasAudioAnalyzer *>::iterator it;
            for(it = guiAudioAnalyzers.begin(); it != guiAudioAnalyzers.end(); it++)
                (*it)->setVisible(showGUI);

            ofClear(backgroundColor);

            break;
        }
        default: break;
    }
}

#pragma mark - Audio Events

void PMScene2::pitchChanged(pitchParams &pitchParams)
{
    float yMin = 1.0f;
    float yMax = 0.0f;

    float y = ofMap(pitchParams.freq, audioAnalyzersSettings->getMinPitchFreq(), audioAnalyzersSettings->getMaxPitchFreq(), yMin, yMax, true);
    renderer->setPositionY(pitchParams.audioInputIndex, y);
}

void PMScene2::energyChanged(energyParams &energyParams)
{
//    cout << "Energy from " << energyParams.audioInputIndex << ": " << energyParams.energy << endl;
    float normalizedSizeMin = 0.25f;
    float normalizedSizeMax = 1.0f;

    float size = ofMap(energyParams.energy,
            audioAnalyzersSettings->getMinEnergy(), audioAnalyzersSettings->getMaxEnergy(),
            normalizedSizeMin, normalizedSizeMax, true);

    renderer->setSize(energyParams.audioInputIndex, size);
}

void PMScene2::silenceStateChanged(silenceParams &silenceParams)
{
    renderer->setShouldPaint(silenceParams.audioInputIndex, !silenceParams.isSilent);
}
