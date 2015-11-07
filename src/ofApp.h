#pragma once

#include "ofMain.h"
#include "ofxAppUtils.h"

class ofApp : public ofxApp
{
public:

    void setup();
    void update();
    void draw();
    void exit();

    void keyReleased(int key);

private:

    bool                    showFPS;
    bool                    isFullScreen;

    ofxSceneManager         sceneManager;

    int                     windowPosX, windowPosY;
};
