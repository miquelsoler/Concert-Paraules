#include "ofApp.h"
#include "PMSettingsManager.h"
#include "Defaults.h"
#include "PMScene1.hpp"
#include "PMScene2.hpp"
#include "PMAudioAnalyzer.hpp"

///--------------------------------------------------------------
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
    currentScene = 0;

    // Settings

#ifdef OF_DEBUG
    showFPS = PMSettingsManager::getInstance().debugShowFPS;
#else
    showFPS = PMSettingsManager::getInstance().releaseShowFPS;
#endif

    // Scenes

    sceneManager.addScene(ofPtr<ofxScene>(new PMScene1));
    sceneManager.addScene(ofPtr<ofxScene>(new PMScene2));
    sceneManager.run();

    PMAudioAnalyzer::getInstance().init(true, 4);

    // For testing purposes

    int deviceId = 0;
    int inChannels = 2;
    int outChannels = 0;
    int sampleRate = 44100;
    int bufferSize = 512;
    int channelNumber = 0;

    PMAudioAnalyzer::getInstance().addDeviceAudioAnalyzer(deviceId, inChannels, outChannels, sampleRate, bufferSize, PMDAA_CHANNEL_MONO, channelNumber);
}

///--------------------------------------------------------------
void ofApp::update()
{
#ifdef OF_DEBUG
    ofShowCursor();
#endif

    sceneManager.update();
}

///--------------------------------------------------------------
void ofApp::draw()
{
    sceneManager.draw();

    if (showFPS)
    {
        ofSetColor(ofColor::white);
        ofDrawBitmapString(ofToString(int(roundf(ofGetFrameRate()))) + "fps", 15, ofGetHeight() - 15);
    }
}

///--------------------------------------------------------------
void ofApp::exit()
{
//    delete audioAnalyzer;
}

///--------------------------------------------------------------
void ofApp::keyReleased(int key)
{
    switch(key)
    {
        // Change scene
        case OF_KEY_LEFT:
        case OF_KEY_RIGHT:
        {
            sceneManager.changeScene();
            currentScene = (currentScene + 1) % 2;
            break;
        }
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

            cout << "Res: " << ofGetWidth() << "x" << ofGetHeight() << endl;
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
