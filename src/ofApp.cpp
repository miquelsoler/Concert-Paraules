#include "ofApp.h"

#include "Defaults.h"
#include "PMSettingsManagerGeneral.h"
#include "PMSettingsManagerAudioAnalyzers.h"
#include "PMAudioAnalyzer.hpp"

#include "PMScene1.hpp"
#include "PMScene2.hpp"

void ofApp::setup()
{
    
#ifdef OF_DEBUG
    ofSetVerticalSync(false);
    limitFrameRate = false;
#else
    ofSetFrameRate(60);
    ofSetVerticalSync(true);
#endif

    ofBackground(ofColor::black);

    isFullScreen = (DEFAULT_WINDOW_MODE == OF_FULLSCREEN);
    if (!isFullScreen)
    {
        windowPosX = ofGetWindowPositionX();
        windowPosY = ofGetWindowPositionY();
    }

    // Initialize audio analyzer
    {
        PMSettingsManagerAudioAnalyzers settingsAA = PMSettingsManagerAudioAnalyzers::getInstance();

        PMAudioAnalyzer::getInstance().init(
                settingsAA.getSilenceThreshold(), settingsAA.getSilenceQueueLength(),
                settingsAA.getOnsetsThreshold(),
                settingsAA.getAscDescAnalysisSize());
    }

    // General Settings
    {
#ifdef OF_DEBUG
        showFPS = PMSettingsManagerGeneral::getInstance().getDebugShowFPS();
#else
        showFPS = PMSettingsManagerGeneral::getInstance().getReleaseShowFPS();
#endif
    }

    // Scenes

    PMScene1 *scene1 = new PMScene1();
    sceneManager.add(scene1);

    PMScene2 *scene2 = new PMScene2();
    sceneManager.add(scene2);

    sceneManager.setup(false);
    sceneManager.setOverlap(true);

    ofSetLogLevel("ofxSceneManager", OF_LOG_VERBOSE); // lets see whats going on inside

    setSceneManager(&sceneManager);

    //sceneManager.gotoScene("Scene 1", false);
    
    initImage.load("./images/pantallaInicial.jpg");
}

void ofApp::update()
{
#ifdef OF_DEBUG
//    ofShowCursor();
#endif
}

void ofApp::draw()
{
    ofColor debugMessagesColor = ofColor(127);

    if (showFPS && sceneManager.getCurrentSceneIndex() != -1)
    {
        ofSetColor(ofColor(0,255,0));
        ofxBitmapString(15, ofGetHeight() - 15) << roundf(ofGetFrameRate()) << "fps" << endl;
    }

    if(sceneManager.getCurrentSceneIndex() == -1)
    {
        initImage.draw(0,0,ofGetWidth(),ofGetHeight());
    }

    

#if OF_DEBUG
    ofSetColor(debugMessagesColor);
    ofxBitmapString(15, ofGetHeight()-28)
            << "[Current Scene] ID: " << sceneManager.getCurrentSceneIndex()
            << " Name: " << sceneManager.getCurrentSceneName() << endl;
#endif


    ofSetColor(ofColor::white);
}

void ofApp::exit()
{
    PMScene1 * scene1 = (PMScene1 *)(sceneManager.getScene("Scene 1"));
    scene1->saveSettings();
    PMScene2 * scene2 = (PMScene2 *)(sceneManager.getScene("Scene 2"));
    scene2->saveSettings();
}

void ofApp::keyReleased(int key)
{
    switch(key)
    {
        // Scene change
        case OF_KEY_RIGHT:  sceneManager.nextScene(); break;
        case OF_KEY_LEFT:   sceneManager.prevScene(); break;

        // Change window mode
        case 'w':
        case 'W':
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
        case 'f':
        case 'F':
        {
            showFPS = !showFPS;
            break;
        }
#ifdef OF_DEBUG
        case '.':
        {
            limitFrameRate = !limitFrameRate;
            ofSetFrameRate(limitFrameRate ? 60 : 0);
            break;
        }
#endif
        default:
            break;
    }
}
