#include "ofApp.h"
#include "PMSettingsManager.h"
#include "Defaults.h"
#include "PMSc1Settings.hpp"
#include "PMSc2Main.hpp"

///--------------------------------------------------------------
void ofApp::setup()
{
    ofSetFrameRate(60);
    ofSetVerticalSync(true);
    ofBackground(ofColor::black);

    isFullScreen = (DEFAULT_WINDOW_MODE == OF_FULLSCREEN);

    currentScene = 1;

    // Settings

#ifdef OF_DEBUG
    showFPS = PMSettingsManager::getInstance().debugShowFPS;
#else
    showFPS = PMSettingsManager::getInstance().releaseShowFPS;
#endif

    // Scenes

    sceneManager.addScene(ofPtr<ofxScene>(new PMSc1Settings));
    sceneManager.addScene(ofPtr<ofxScene>(new PMSc2Main));
    sceneManager.run();

    // For testing purposes

    audioAnalyzer = new PMDeviceAudioAnalyzer(this, 0, 2, 0, 44100, 512);
    audioAnalyzer->setup();
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
    if (showFPS)
    {
        ofSetColor(ofColor::white);
        ofDrawBitmapString(ofToString(ofGetFrameRate()) + "fps", 15, ofGetHeight() - 15);
    }

    sceneManager.draw();
}

///--------------------------------------------------------------
void ofApp::keyReleased(int key)
{
    switch(currentScene)
    {
        case 0:
        {
            sceneManager.changeScene();
            currentScene = 1;
            break;
        }
        case 1:
        {
            switch(key)
            {
                case 'f':
                case 'F':
                {
                    // Change window mode
                    isFullScreen = !isFullScreen;
                    ofSetFullscreen(isFullScreen);
                    break;
                }
                case 'p':
                case 'P':
                {
                    showFPS = !showFPS;
                    break;
                }
                case 'k':
                case 'K':
                {
                    audioAnalyzer->start();
                    break;
                }
                case 'l':
                case 'L':
                {
                    audioAnalyzer->stop();
                    break;
                }
                default:
                    break;
            }
        }
    }
}
