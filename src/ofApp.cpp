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
    audioAnalyzer = new PMAudioAnalyzer(this, 0, 2, 0, 44100, 512, 4);



//    int sampleRate = 44100;
//    int bufferSize = 512;
//    int outChannels = 0;
//    int inChannels = 2;
//    int ticksPerBuffer = bufferSize/64;
//
//    float *buffer_1 =  new float[bufferSize]; // potser per la definicio vector<vector<float>> enlloc del que s'espera???
//    float *buffer_2 =  new float[bufferSize];
//    for(int i = 0; i < bufferSize; i++) { buffer_1[i]=buffer_2[i]= 0;}
//    soundStream.printDeviceList();
//    soundStream.setDeviceID(0);
//    soundStream.setup(this, outChannels, inChannels, sampleRate, bufferSize, ticksPerBuffer);


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
        default:
            break;
    }
}
