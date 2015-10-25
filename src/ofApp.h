#pragma once

#include "ofMain.h"
#include "PMSceneManager.hpp"

class ofApp : public ofBaseApp
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

    PMSceneManager          *sceneManager;
    unsigned int            currentScene;

    int                     windowPosX, windowPosY;
};
