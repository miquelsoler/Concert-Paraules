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
    recorder = &PMRecorder::getInstance();

    backgroundColor = ofColor::white;

    // GUI
    {
        canvasBgColor = ofColor(50, 50, 50, 200);
        guiAudioAnalyzerCreated = false;
    }
}

PMScene2::~PMScene2()
{
    for (int i=0; i<guiAudioAnalyzers.size(); ++i)
    {
        PMUICanvasAudioAnalyzer *gui = guiAudioAnalyzers[i];
        delete gui;
    }
    guiAudioAnalyzers.clear();
}

void PMScene2::setup()
{
    // Create Renderer
    {
        unsigned int numAudioInputs = (unsigned int)(PMSettingsManagerAudioDevices::getInstance().getEnabledAudioDevices()->size());
        PMSettingsRenderer settingsRenderer = PMSettingsManagerRenderers::getInstance().getSelectedRenderer();
        switch(settingsRenderer.ID)
        {
            case RENDERERTYPE_PAINTBRUSH:   renderer = new PMRendererPaintbrush(numAudioInputs); break;
            case RENDERERTYPE_TYPOGRAPHY:   renderer = new PMRendererTypography(numAudioInputs); break;
            case RENDERERTYPE_COLOR:        renderer = new PMRendererColor(numAudioInputs); break;
            default:                        break;
        }
    }

    // Enabled audio devices
    {
        unsigned int audioInputIndex = 0;

        enabledAudioDevices = PMSettingsManagerAudioDevices::getInstance().getEnabledAudioDevices();

        vector<PMSettingsDevice>::iterator itDevice;

        // Creation of audio analyzers
        {
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
                    ofAddListener(deviceAudioAnalyzer->eventPauseStateChanged, this, &PMScene2::pauseStateChanged);
                    ofAddListener(deviceAudioAnalyzer->eventOnsetStateChanged, this, &PMScene2::onsetDetected);

                    audioInputIndex++;
                }
            }
        }

        // GUI
        {
            if (!guiAudioAnalyzerCreated)
            {
                int initialY = 5;
                int widthY = 300;
                audioInputIndex = 0;
                for (itDevice = enabledAudioDevices->begin(); itDevice != enabledAudioDevices->end(); ++itDevice)
                {
                    for (int i = 0; i < (*itDevice).channels.size(); ++i)
                    {
                        string title = "AUDIO ANALYZER " + ofToString(audioInputIndex + 1);
                        PMUICanvasAudioAnalyzer *guiAudioAnalyzer = new PMUICanvasAudioAnalyzer(title, OFX_UI_FONT_MEDIUM, audioInputIndex);
                        guiAudioAnalyzer->init(5, initialY + (audioInputIndex * widthY));
                        guiAudioAnalyzer->setBackgroundColor(canvasBgColor);
                        guiAudioAnalyzer->setVisible(false);

                        guiAudioAnalyzers.push_back(guiAudioAnalyzer);

                        audioInputIndex++;
                    }
                }
            }

            guiAudioAnalyzerCreated = true;
        }
    }

    renderer->setup();
    
    // Recorder setup

    vector<PMDeviceAudioAnalyzer* > aavec=*PMAudioAnalyzer::getInstance().getAudioAnalyzers();
    int sampleRate=aavec[0]->getSamplerate();
    int numChannels=aavec.at(0)->getNumChannels();
    recorder->init(renderer->getFbo(), sampleRate, numChannels, "testMovie", ofFilePath::getAbsolutePath("fonts/")+"../");
}

void PMScene2::update()
{
    renderer->update();
    
    // Record current frame
    if (recorder->isRecording()) {
        recorder->addVideoFrame();
    }
}

void PMScene2::updateEnter()
{
    if (isEnteringFirst())
    {
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
#ifdef OF_DEBUG
    ofSetColor(127);
    ofDrawBitmapString("Renderer type: " + ofToString(renderer->getType()), 15, ofGetHeight() - 40);
#endif
}

void PMScene2::saveSettings()
{
    PMAudioAnalyzer::getInstance().stop();
//    PMAudioAnalyzer::getInstance().clear();

    int i;
    vector<PMUICanvasAudioAnalyzer *>::iterator it;
    for(i=0, it = guiAudioAnalyzers.begin(); it != guiAudioAnalyzers.end(); it++, ++i)
    {
        string guiSettingsFilename = "audioAnalyzer2." + ofToString(i) + ".xml";
        (*it)->saveSettings(STR_CANVAS_BASEPATH + guiSettingsFilename);
        (*it)->setVisible(false);
    }
    
    //ens carreguem el fitxer audiodevices perque no dongui pel sac
    string cmd="rm " + ofFilePath::getAbsolutePath("settings/")+"/audioDevices.json";
    system(cmd.c_str());
    recorder->exit();
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

            vector<PMUICanvasAudioAnalyzer *>::iterator it;
            for(it = guiAudioAnalyzers.begin(); it != guiAudioAnalyzers.end(); it++)
                (*it)->setVisible(showGUI);

            ofClear(backgroundColor);

            break;
        }
        case 'r':
        case 'R':
        {
            if (!recorder->isRecording()) {
                // Start recording
                recorder->startRecording();
            } else {
                // Stop recording
                recorder->stopRecording();
            }
            break;
        }
        case 'c':
        case 'C':
        {
            // Discard recording
            recorder->discardRecording();
            break;
        }
        default: break;
    }
}

#pragma mark - Audio Events

void PMScene2::pitchChanged(pitchParams &pitchParams)
{
    
    switch(renderer->getType())
    {
        case RENDERERTYPE_PAINTBRUSH:
        {
            float minOffset = -1.0f;
            float maxOffset = 1.0f;
            float pitch = ofMap(pitchParams.midiNote, audioAnalyzersSettings->getMinPitchMidiNote(), audioAnalyzersSettings->getMaxPitchMidiNote(), minOffset, maxOffset, true);

            PMRendererPaintbrush *paintbrushRenderer = (PMRendererPaintbrush *)renderer;
            paintbrushRenderer->setOffset(pitchParams.audioInputIndex, pitch);
            break;
        }
        case RENDERERTYPE_COLOR:
        {
            float minOffset = 0.0f;
            float maxOffset = 1.0f;
            float pitch = ofMap(pitchParams.midiNote, audioAnalyzersSettings->getMinPitchMidiNote(), audioAnalyzersSettings->getMaxPitchMidiNote(), minOffset, maxOffset, true);

            PMRendererColor *colorRenderer = (PMRendererColor *)renderer;
            colorRenderer->setPitch(pitch);
            break;
            
        }
        default: break;
    }
}

void PMScene2::energyChanged(energyParams &energyParams)
{
    // calculate Energy
    /////////////////////
    float normalizedSizeMin = 0.0f;
    float normalizedSizeMax = 1.0f;
    
    // Non-linear ofMap, based on http://forum.openframeworks.cc/t/non-linear-ofmap/13508/2
    float linearSize = ofMap(energyParams.energy, audioAnalyzersSettings->getMinEnergy(), audioAnalyzersSettings->getMaxEnergy(), 0, 1, true);
    double eulerIdentity = M_E;
    // ? eloi : a mi em funciona millor en lineal // linearSize = powf(linearSize, float(1.0/eulerIdentity));
    
    float energy = ofMap(linearSize, 0, 1, normalizedSizeMin, normalizedSizeMax, true);
    
    // FIXME: In case size is NaN, set it to zero. PMDeviceAudioAnalyzer::getEnergy should never return NaN (because weightsum is 0).
    if (isnan(energy)) energy = 0;

    switch(renderer->getType())
    {
        case RENDERERTYPE_PAINTBRUSH:
        {
            PMRendererPaintbrush *paintbrushRenderer = (PMRendererPaintbrush *)renderer;
            paintbrushRenderer->setSize(energyParams.audioInputIndex, energy);
            break;
        }
        case RENDERERTYPE_COLOR:
        {
            PMRendererColor *colorRenderer = (PMRendererColor *)renderer;
            colorRenderer->setEnergy(energy);
        }
        default: break;
    }
}

void PMScene2::silenceStateChanged(silenceParams &silenceParams)
{
    switch (renderer->getType())
    {
        case RENDERERTYPE_PAINTBRUSH:
        {
            if (!silenceParams.isSilent)
            {
                PMRendererPaintbrush *paintbrushRenderer = (PMRendererPaintbrush *)renderer;
                paintbrushRenderer->changeBaseAngle(silenceParams.audioInputIndex);
            }
            break;
        }
        default: break;
    }
//    renderer->setShouldPaint(silenceParams.audioInputIndex, !silenceParams.isSilent);
}

void PMScene2::pauseStateChanged(pauseParams &pauseParams)
{
    switch (renderer->getType())
    {
        case RENDERERTYPE_TYPOGRAPHY:
        {
//            PMRendererTypography *typoRenderer = (PMRendererTypography *)renderer;
//            typoRenderer->addLetter();
            break;
        }
        default: break;
    }
    renderer->setShouldPaint(pauseParams.audioInputIndex, !pauseParams.isPaused);
}

void PMScene2::onsetDetected(onsetParams &onsetParams)
{
    switch(renderer->getType())
    {
        case RENDERERTYPE_PAINTBRUSH:
        {
//            PMRendererPaintbrush *paintbrushRenderer = (PMRendererPaintbrush *)renderer;
//            paintbrushRenderer->changeBaseAngle(onsetParams.audioInputIndex);
            break;
        }

        default: break;
    }
}
