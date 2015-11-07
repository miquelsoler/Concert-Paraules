#include "ofApp.h"

#include "Defaults.h"
#include "PMSettingsManagerGeneral.h"
#include "PMAudioAnalyzer.hpp"

#include "PMScene1.hpp"
#include "PMScene2.hpp"

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

    PMScene1 *scene1 = new PMScene1();
    sceneManager.add(scene1);

    PMScene2 *scene2 = new PMScene2();
    sceneManager.add(scene2);

    sceneManager.setup(true);

    sceneManager.setOverlap(true);
    ofSetLogLevel("ofxSceneManager", OF_LOG_VERBOSE); // lets see whats going on inside

    setSceneManager(&sceneManager);

    // For testing purposes

    int deviceId = 0;
    int inChannels = 2;
    int outChannels = 0;
    int sampleRate = 44100;
    int bufferSize = 512;
    int channelNumber = 0;

    PMAudioAnalyzer::getInstance().addDeviceAudioAnalyzer(deviceId, inChannels, outChannels, sampleRate, bufferSize, PMDAA_CHANNEL_MONO, channelNumber);

    sceneManager.gotoScene("Scene 1", false);
}

void ofApp::update()
{
#ifdef OF_DEBUG
    ofShowCursor();
#endif
}

void ofApp::draw()
{
    ofColor debugMessagesColor = ofColor(127);

    if (showFPS && sceneManager.getCurrentSceneIndex() != -1)
    {
        ofSetColor(debugMessagesColor);
        ofxBitmapString(15, ofGetHeight() - 15) << roundf(ofGetFrameRate()) << "fps" << endl;
    }

#if OF_DEBUG
    ofSetColor(debugMessagesColor);
    ofxBitmapString(15, ofGetHeight()-28)
            << "[Current Scene] ID: " << sceneManager.getCurrentSceneIndex()
            << " Name: " << sceneManager.getCurrentSceneName() << endl;
#endif
}

void ofApp::exit()
{
//    delete audioAnalyzer;
}

void ofApp::keyReleased(int key)
{
    switch(key)
    {
        // Scene change
        case OF_KEY_RIGHT:  sceneManager.nextScene(); break;
        case OF_KEY_LEFT:   sceneManager.prevScene(); break;

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
