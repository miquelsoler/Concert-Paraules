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

    recorder = &PMRecorder::getInstance();

    backgroundColor = ofColor::white;

    // GUI
    {
        canvasBgColor = ofColor(50, 50, 50, 200);
        guiAudioAnalyzerCreated = false;
    }
    
    recState = 0;
    durationRecordingText = 4000;
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
        PMSettingsRenderer settingsRenderer = PMSettingsManagerRenderers::getInstance().getSelectedRenderer();
        switch(settingsRenderer.ID)
        {
            case RENDERERTYPE_PAINTBRUSH:
                renderer = new PMRendererPaintbrush2();
                break;
            case RENDERERTYPE_TYPOGRAPHY:
                renderer = new PMRendererTypography();
                break;
            case RENDERERTYPE_COLOR:
                renderer = new PMRendererColor();
                break;
            case RENDERERTYPE_RIBBON:
                renderer = new PMRendererRibbon();
                break;
            default:
                break;
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

                vector<unsigned int> enabledChannelNumbers;

                for (unsigned int i=0; i<numChannels; i++)
                {
                    PMSettingsDeviceChannel channel = (*itDevice).channels[i];
                    if (!channel.enabled) continue;

                    enabledChannelNumbers.push_back(channel.ID);
                }

                int deviceId = (*itDevice).ID;
                int inChannels = (*itDevice).inChannels;
                int outChannels = (*itDevice).outChannels;

                PMDeviceAudioAnalyzer *deviceAudioAnalyzer = PMAudioAnalyzer::getInstance().addDeviceAnalyzer(audioInputIndex, deviceId,
                    inChannels, outChannels, DEFAULT_SAMPLERATE, DEFAULT_BUFFERSIZE, enabledChannelNumbers);

                ofAddListener(deviceAudioAnalyzer->eventPitchChanged, this, &PMScene2::pitchChanged);
                ofAddListener(deviceAudioAnalyzer->eventEnergyChanged, this, &PMScene2::energyChanged);

                ofAddListener(deviceAudioAnalyzer->eventSilenceStateChanged, this, &PMScene2::silenceStateChanged);
                ofAddListener(deviceAudioAnalyzer->eventPauseStateChanged, this, &PMScene2::pauseStateChanged);
                ofAddListener(deviceAudioAnalyzer->eventOnsetStateChanged, this, &PMScene2::onsetDetected);
                ofAddListener(deviceAudioAnalyzer->eventShtStateChanged, this, &PMScene2::shtDetected);
                ofAddListener(deviceAudioAnalyzer->eventMelodyDirection, this, &PMScene2::melodyDirection);

                audioInputIndex++;
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
//                    for (int i = 0; i < (*itDevice).channels.size(); ++i)
//                    {
                        string title = "AUDIO ANALYZER " + ofToString(audioInputIndex + 1);
                        PMUICanvasAudioAnalyzer *guiAudioAnalyzer = new PMUICanvasAudioAnalyzer(title, OFX_UI_FONT_MEDIUM, audioInputIndex);
                        guiAudioAnalyzer->init(5, initialY + (audioInputIndex * widthY));
                        guiAudioAnalyzer->setBackgroundColor(canvasBgColor);
                        guiAudioAnalyzer->setVisible(false);

                        guiAudioAnalyzers.push_back(guiAudioAnalyzer);

                        audioInputIndex++;
//                    }
                }
            }

            guiAudioAnalyzerCreated = true;
        }
    }

    renderer->setup();
    
    // Recorder setup

    vector<PMDeviceAudioAnalyzer* > aavec=*PMAudioAnalyzer::getInstance().getAudioAnalyzers();
    int sampleRate=aavec[0]->getSampleRate();
    int numChannels=aavec.at(0)->getNumChannels();
    recorder->init(renderer->getFbo(), sampleRate, numChannels, "testMovie", ofFilePath::getAbsolutePath("fonts")+"/../");
    
    // Still Image Setup
    stillImage.setup();
}

void PMScene2::update()
{
    if(recState==0)
    {
        renderer->update();
        
        // Record current frame
        if (recorder->isRecording()) {
            recorder->addVideoFrame(renderer->getBackgroundColor());
        }
    }
    else if(recState ==1)
    {
        recorder->addVideoFrame(ofColor(0));

        if(ofGetElapsedTimeMillis()-startTimeRecordingText>durationRecordingText)
        {
            cout << "SCENE 2 :: STOPPING RECORDING !! " << endl;
            recorder->stopRecording();
            recState = 0;
        }
        stillImage.update();
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

    renderer->showGUI(showGUI);

    PMBaseScene::updateEnter();
}

void PMScene2::updateExit()
{
    renderer->showGUI(false);

    saveSettings();
    PMBaseScene::updateExit();
}

void PMScene2::draw()
{
    if(recState==0) renderer->draw();
    else stillImage.draw();
    
#ifdef OF_DEBUG
    ofSetColor(127);
    ofDrawBitmapString("Renderer type: " + ofToString(renderer->getType()), 15, ofGetHeight() - 40);
    string stat = "";
    switch(renderer->getState())
    {
        case 0 :
            stat = " OFF !! ";
            break;
            
        case 1 :
            stat = " ON ...";
            break;
    }
    ofDrawBitmapString("Renderer state: " + stat, 15, ofGetHeight() - 60);
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

            renderer->showGUI(showGUI);

            ofClear(backgroundColor);

            break;
        }
        case ' ':
        {
            renderer->switchStateOnOff();
            break;
        }
        case 'r':
        case 'R':
        {
            if (!recorder->isRecording()) {
                // Start recording
                recorder->startRecording();
            } else {
                
                // Start StillImage Recording
                recState = 1;
                recorder->changeFbo(stillImage.getFbo());
                startTimeRecordingText = ofGetElapsedTimeMillis();
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
        case 'x' :
            renderer->setNeedsToBeCleared(true);
            break;
        default: break;
        
        
    }
}


#pragma mark - Audio Events

void PMScene2::pitchChanged(pitchParams &pitchParams)
{
    renderer->pitchChanged(pitchParams);
    
    switch(renderer->getType())
    {
        case RENDERERTYPE_PAINTBRUSH:
        {
            PMRendererPaintbrush2* p = (PMRendererPaintbrush2*)renderer;
            p->pitchChanged(pitchParams);
            break;
        }
        default: break;
    }
 
}

void PMScene2::energyChanged(energyParams &energyParams)
{
    renderer->energyChanged(energyParams);

    switch(renderer->getType())
    {
        default: break;
    }
}

//--------------------------------------------------------------------------------------------------
void PMScene2::silenceStateChanged(silenceParams &silenceParams)
{
    renderer->silenceStateChanged(silenceParams);
    
    switch (renderer->getType())
    {
        case RENDERERTYPE_PAINTBRUSH:
        {
            if (!silenceParams.isSilent)
            {
//                PMRendererPaintbrush *paintbrushRenderer = (PMRendererPaintbrush2 *)renderer;
//                paintbrushRenderer->changeBaseAngle();
            }
            break;
        }
        default: break;
    }
}

void PMScene2::pauseStateChanged(pauseParams &pauseParams)
{
    if (pauseParams.isPaused)
    {
//        renderer->setState(RENDERERSTATE_PAUSED);
        renderer->pauseStateChanged(pauseParams);
    }
    else
    {
//        if (renderer->getState() == RENDERERSTATE_PAUSED)
//        {
//            renderer->setState(RENDERERSTATE_ON);
//            renderer->pauseStateChanged(pauseParams);
//        }
    }
}

void PMScene2::onsetDetected(onsetParams &onsetParams)
{
}

void PMScene2::shtDetected(shtParams &shtParams)
{
    switch(renderer->getType())
    {
        case RENDERERTYPE_PAINTBRUSH:
        {
//            PMRendererPaintbrush *paintbrushRenderer = (PMRendererPaintbrush *)renderer;
//            paintbrushRenderer->vibrate(shtParams.isSht);
            break;
        }
        case RENDERERTYPE_COLOR:
        {
            PMRendererColor *colorRenderer = (PMRendererColor*)renderer;
            colorRenderer->setNeedsToBeCleared(shtParams.isSht);
            break;
        }
        default:
            break;
    }
}

void PMScene2::melodyDirection(melodyDirectionParams &melodyDirectionParams)
{
    switch (renderer->getType())
    {
        case RENDERERTYPE_PAINTBRUSH:
        {
//            PMRendererPaintbrush *paintbrushRenderer = (PMRendererPaintbrush *)renderer;
//            paintbrushRenderer->changeDirection(melodyDirectionParams.direction);
            break;
        }
        default:
            break;
    }
}

void PMScene2::mouseDragged(int x, int y, int button)
{
    renderer->mouseDragged(x, y, button);
}

void PMScene2::mousePressed(int x, int y, int button)
{
    renderer->mousePressed(x, y, button);
}

void PMScene2::mouseReleased(int x, int y, int button)
{
    renderer->mouseReleased(x, y, button);
}
