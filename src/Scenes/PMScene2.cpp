//
//  PMScene2.cpp
//  PMConcertParaules
//
//  Created by Miquel Àngel Soler on 7/10/15.
//
//

#include "PMScene2.hpp"

#include "PMSettingsManagerGeneral.h"

PMScene2::PMScene2() : PMBaseScene("Scene 2")
{
#ifdef OF_DEBUG
    showGUI = PMSettingsManagerGeneral::getInstance().getDebugShowGUIScene2();
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

    recState = RECORDING_NORMAL;
    durationRecordingText = 4000;

    rendererAlreadyCreated = false;
}

PMScene2::~PMScene2()
{
    for (int i = 0; i < guiAudioAnalyzers.size(); ++i) {
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
        goToRenderer(settingsRenderer.ID);
        rendererAlreadyCreated = true;
    }

    // Enabled audio devices
    {
        unsigned int audioInputIndex = 0;

        enabledAudioDevices = PMSettingsManagerAudioDevices::getInstance().getEnabledAudioDevices();

        vector<PMSettingsDevice>::iterator itDevice;

        // Creation of audio analyzers
        {
            for (itDevice = enabledAudioDevices->begin(); itDevice != enabledAudioDevices->end(); ++itDevice) {
                if (!(*itDevice).enabled) continue;
                unsigned int numChannels = (unsigned int) ((*itDevice).channels.size());

                vector<unsigned int> enabledChannelNumbers;

                for (unsigned int i = 0; i < numChannels; i++) {
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
            if (!guiAudioAnalyzerCreated) {
                int initialY = 5;
                int widthY = 300;
                audioInputIndex = 0;
                for (itDevice = enabledAudioDevices->begin(); itDevice != enabledAudioDevices->end(); ++itDevice) {
//                    for (int i = 0; i < (*itDevice).channels.size(); ++i)
//                    {
                    string title = "AUDIO ANALYZER " + ofToString(audioInputIndex + 1);
                    PMUICanvasAudioAnalyzer *guiAudioAnalyzer = new PMUICanvasAudioAnalyzer(title, OFX_UI_FONT_MEDIUM, audioInputIndex);
                    guiAudioAnalyzer->init(5, initialY + (audioInputIndex * widthY));
//                    guiAudioAnalyzer->setBackgroundColor(canvasBgColor);
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

    recorderSetup();
    
    // Still Image Setup
    stillImagePoem.setup(PMSettingsManagerPoem::getInstance().getFolderPath() + "/" + PMSettingsManagerPoem::getInstance().getPoemFilename());
    stillImageTitle.setup("./images/titol.jpg");
    
}

void PMScene2::goToRenderer(int rendererID)
{
    if (rendererAlreadyCreated)
    {
        // TODO: Aquí s'hauria de fer un ofRemoveListener de tots els events d'audio que reb el renderer abans d'esborrar-lo.
        delete renderer;
    }

    currentRenderer = rendererID;

    switch (currentRenderer)
    {
        case RENDERERTYPE_TYPOGRAPHY:   renderer = new PMRendererTypography(); break;
        case RENDERERTYPE_COLOR:        renderer = new PMRendererColor(); break;
        case RENDERERTYPE_CURVES:       renderer = new PMRendererCurves(); break;
        default: break;
    }
}

void PMScene2::recorderSetup()
{
    // Recorder setup
    
    vector<PMDeviceAudioAnalyzer *> aavec = *PMAudioAnalyzer::getInstance().getAudioAnalyzers();
    int sampleRate = aavec[0]->getSampleRate();
    int numChannels = aavec.at(0)->getNumChannels();
    // FIXME : FORCED 2 CHANNELS OF AUDIO !!
    
    string filename = PMSettingsManagerPoem::getInstance().getPoemFilename();
    ofStringReplace(filename, " ", "_");
    ofStringReplace(filename, ".jpg", "");
    recorder->init(renderer->getFbo(), sampleRate, 2, filename, ofFilePath::getAbsolutePath("", true));
    
}

void PMScene2::update()
{
    switch (recState)
    {
        case RECORDING_NORMAL: {
            // normal state ... if recording record !!
            renderer->update();

            // Record current frame
            if (recorder->isRecording()) {
                recorder->addVideoFrame(renderer->getBackgroundColor());
            }
            break;
        }
        case RECORDING_ADDPOEM:
        {
            stillImagePoem.update();

            // recording text image ... (we've changed the fbo in keyPress)
            if (recorder->isRecording()) {
                recorder->addVideoFrame(ofColor(0));
            }

            if (ofGetElapsedTimeMillis() - startTimeRecordingText > durationRecordingText) {
                cout << "SCENE 2 :: Timer for POEM Image ended !! STOPPING RECORDING !! " << endl;
                recorder->stopRecording();
                recState = RECORDING_NORMAL;
            }
            break;
        }
        case RECORDING_ADDTITLE:
        {
            stillImageTitle.update();
            
            // recording text image ... (we've changed the fbo in keyPress)
            if (recorder->isRecording()) {
                recorder->addVideoFrame(ofColor(0));
            }
            
            if (ofGetElapsedTimeMillis() - startTimeRecordingText > durationRecordingText) {
                cout << "SCENE 2 :: Timer for TITLE Image ended !! STOPPING RECORDING !! " << endl;
                recState = RECORDING_NORMAL;
                recorder->changeFbo(renderer->getFbo());

                
            }
            break;
        }
    }
    

}

void PMScene2::updateEnter()
{
    if (isEnteringFirst()) {
        int i;
        vector<PMUICanvasAudioAnalyzer *>::iterator it;
        for (i = 0, it = guiAudioAnalyzers.begin(); it != guiAudioAnalyzers.end(); it++, i++)
        {
            (*it)->setVisible(showGUI);
            (*it)->enableKeyEventCallbacks();
            (*it)->enableAppUpdateCallback();
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
    // if we're in recState 0 (normal) ... draw the renderer.
    // else if we're in recState 1 (rendering text jpg) ... draw the still image
    switch(recState) {
        case RECORDING_ADDTITLE: stillImageTitle.draw(); break;
        case RECORDING_NORMAL: renderer->draw(); break;
        case RECORDING_ADDPOEM: stillImagePoem.draw(); break;
    }

#ifdef OF_DEBUG
    ofSetColor(127);
    ofDrawBitmapString("Renderer type: " + ofToString(renderer->getType()), 15, ofGetHeight() - 40);
    string stat;
    switch (renderer->getState()) {
        case RENDERERSTATE_OFF: stat = " OFF !! "; break;
        case RENDERERSTATE_ON: stat = " ON ..."; break;
    }
    ofDrawBitmapString("Renderer state: " + stat, 15, ofGetHeight() - 60);
#endif

    
    if(recorder->isRecording())
    {
        ofSetColor(255*sin(ofGetElapsedTimef()*10),0,0);
        ofDrawCircle(ofGetWidth()-50,50,15);
    }
}

void PMScene2::saveSettings()
{
    PMAudioAnalyzer::getInstance().stop();
//    PMAudioAnalyzer::getInstance().clear();

    int i;
    vector<PMUICanvasAudioAnalyzer *>::iterator it;
    for (i = 0, it = guiAudioAnalyzers.begin(); it != guiAudioAnalyzers.end(); it++, ++i)
        (*it)->setVisible(false);

    recorder->exit();
}

#pragma mark - Keyboard events

void PMScene2::keyReleased(int key)
{
    PMBaseScene::keyReleased(key);

    switch (key)
    {
        case 'g':
        case 'G':
        {
            if(!showGUI) ofShowCursor();
            else ofHideCursor();

            showGUI = !showGUI;
            
            vector<PMUICanvasAudioAnalyzer *>::iterator it;
            for (it = guiAudioAnalyzers.begin(); it != guiAudioAnalyzers.end(); it++)
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
        case 'n':
        case 'N':
        {
            currentRenderer = (currentRenderer + 1) % RENDERERTYPE_NUMRENDERERS;
            cout << "Current renderer: " << currentRenderer << endl;
            goToRenderer(currentRenderer);
            break;
        }
        case 'r':
        case 'R':
        {
            if (!recorder->isRecording()) {
                // if not reocording -> Start recording
                recorder->changeFbo(stillImageTitle.getFbo());
                recorder->startRecording();
                startTimeRecordingText = ofGetElapsedTimeMillis();
                recState = RECORDING_ADDTITLE;
                
            } else {
                // if we're already recording
                // Start StillImage Recording
                cout << "Scene 2 :: changing FBO to record still image..." << endl;
                recState = RECORDING_ADDPOEM;
                recorder->changeFbo(stillImagePoem.getFbo());
                cout << "Scene 2 :: changed FBO to still iamge one !! " << endl;
                startTimeRecordingText = ofGetElapsedTimeMillis();
                cout << "Scene 2 :: started timer for still image render..." << endl;
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
        case 'x':
        {
            renderer->setNeedsToBeCleared(true);
            break;
        }
        case 'p': takeSnapshot(); break;
        default: break;
    }
}


#pragma mark - Audio Events

void PMScene2::pitchChanged(pitchParams &pitchParams)
{
    renderer->pitchChanged(pitchParams);
    
    // update LOW confidence on pitch
    int i;
    vector<PMUICanvasAudioAnalyzer *>::iterator it;
    for (i = 0, it = guiAudioAnalyzers.begin(); it != guiAudioAnalyzers.end(); it++, ++i)
    {
        if(pitchParams.confidence < pitchParams.minConfidence)
        {
            (*it)->setLowConfidence(true);
        }
        else
        {
            (*it)->setLowConfidence(false);
        }
    }

    
}

void PMScene2::energyChanged(energyParams &energyParams)
{
    renderer->energyChanged(energyParams);
}

//--------------------------------------------------------------------------------------------------
void PMScene2::silenceStateChanged(silenceParams &silenceParams)
{
    renderer->silenceStateChanged(silenceParams);
}

void PMScene2::pauseStateChanged(pauseParams &pauseParams)
{
    if (pauseParams.isPaused) {
        renderer->pauseStateChanged(pauseParams);
    }
}

void PMScene2::onsetDetected(onsetParams &onsetParams)
{
}

void PMScene2::shtDetected(shtParams &shtParams)
{
    switch (renderer->getType())
    {
        case RENDERERTYPE_COLOR: {
            PMRendererColor *colorRenderer = (PMRendererColor *) renderer;
            colorRenderer->setNeedsToBeCleared(shtParams.isSht);
            break;
        }
        default:
            break;
    }
}

void PMScene2::melodyDirection(melodyDirectionParams &melodyDirectionParams)
{
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

void PMScene2::takeSnapshot()
{
    string fileExt = ".png";
    string filename =  "./snapshots/" + ofGetTimestampString("%Y.%m.%d") + "-" + ofGetTimestampString("%H.%M.%S") + fileExt;
    
    ofImage i;
    i.grabScreen(0,0, ofGetWidth(), ofGetHeight());
    i.save(filename);

    cout << "Taking Snapshot : filename : " << filename << endl;

}

void PMScene2::windowResized(int x, int y)
{
    recorderSetup();
    cout << "PMScene2 :: Window has been resized to : " << x << " , " << y << " . So Recorder setup again ..." <<endl;
}
