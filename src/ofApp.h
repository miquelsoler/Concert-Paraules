#pragma once

#include "ofMain.h"
#include "PMDeviceAudioAnalyzer.hpp"
#include "ofxSceneManager.h"

class ofApp : public ofBaseApp
{
public:

    void setup();
    void update();
    void draw();
    void exit();

    void keyReleased(int key);

private:

    PMDeviceAudioAnalyzer   *audioAnalyzer;

    bool                    showFPS;
    bool                    isFullScreen;

    ofxSceneManager         sceneManager;
    unsigned int            currentScene;

    int                     windowPosX, windowPosY;
};
