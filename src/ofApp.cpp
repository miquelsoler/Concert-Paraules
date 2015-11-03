#include "ofApp.h"
#include "PMSettingsManagerGeneral.h"
#include "Defaults.h"
#include "PMAudioAnalyzer.hpp"

void ofApp::setup()
{
    ofSetFrameRate(60);
    ofSetVerticalSync(true);
    ofBackground(ofColor::black);

    isFullScreen = (DEFAULT_WINDOW_MODE == OF_FULLSCREEN);
    if (!isFullScreen)
    {
        windowPosX = ofGetWindowPositionX();
        windowPosY = ofGetWindowPositionY();
    }

    PMAudioAnalyzer::getInstance().init(true, 4);

    // Settings

#ifdef OF_DEBUG
    showFPS = PMSettingsManagerGeneral::getInstance().getDebugShowFPS();
#else
    showFPS = PMSettingsManagerGeneral::getInstance().getReleaseShowFPS();
#endif

    // Scenes

    sceneManager = &(PMSceneManager::getInstance());
    sceneManager->init();

    // For testing purposes

    int deviceId = 0;
    int inChannels = 2;
    int outChannels = 0;
    int sampleRate = 44100;
    int bufferSize = 512;
    int channelNumber = 0;

    PMAudioAnalyzer::getInstance().addDeviceAudioAnalyzer(deviceId, inChannels, outChannels, sampleRate, bufferSize, PMDAA_CHANNEL_MONO, channelNumber);
}

void ofApp::update()
{
#ifdef OF_DEBUG
    ofShowCursor();
#endif

    sceneManager->update();
}

void ofApp::draw()
{
    sceneManager->draw();

    if (showFPS)
    {
        ofSetColor(ofColor::black);
        ofDrawBitmapString(ofToString(int(roundf(ofGetFrameRate()))) + "fps", 15, ofGetHeight() - 15);
    }
}

void ofApp::exit()
{
    sceneManager->willExit();
//    delete audioAnalyzer;
}

void ofApp::keyReleased(int key)
{
    switch(key)
    {
        // Change window mode
        case 'f':
        case 'F':
        {
            isFullScreen = !isFullScreen;
            if (!isFullScreen)
            {
                ofSetWindowShape(DEFAULT_WINDOW_WIDTH, DEFAULT_WINDOW_HEIGHT);
                ofSetWindowPosition(windowPosX, windowPosY);
            }
            else
            {
                windowPosX = ofGetWindowPositionX();
                windowPosY = ofGetWindowPositionY();
            }
            ofSetFullscreen(isFullScreen);
            break;
        }
        // Show/hide FPS
        case 'p':
        case 'P':
        {
            showFPS = !showFPS;
            break;
        }
        // Start/stop audio analysis
        case 'k':
        case 'K':
        {
            PMAudioAnalyzer::getInstance().start();
            break;
        }
        case 'l':
        case 'L':
        {
            PMAudioAnalyzer::getInstance().stop();
            break;
        }
        default:
            break;
    }
}
