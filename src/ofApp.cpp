#include "ofApp.h"
#include "PMSettingsManager.h"
#include "Defaults.h"

///--------------------------------------------------------------
void ofApp::setup()
{
    ofSetFrameRate(60);
    ofSetVerticalSync(true);
    ofBackground(ofColor::black);

    isFullScreen = (DEFAULT_WINDOW_MODE == OF_FULLSCREEN);

    // For testing purposes
    audioAnalyzer = new PMAudioAnalyzer(this, 0, 2, 0, 44100, 512);
    audioAnalyzer->setup();


#ifdef OF_DEBUG
    showFPS = PMSettingsManager::getInstance().debugShowFPS;
#else
    showFPS = PMSettingsManager::getInstance().releaseShowFPS;
#endif
}

///--------------------------------------------------------------
void ofApp::update()
{
#ifdef OF_DEBUG
    ofShowCursor();
#endif
}

///--------------------------------------------------------------
void ofApp::draw()
{
    if (showFPS)
    {
        ofSetColor(ofColor::white);
        ofDrawBitmapString(ofToString(ofGetFrameRate()) + "fps", 15, ofGetHeight() - 15);
    }
}

///--------------------------------------------------------------
void ofApp::keyReleased(int key)
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
