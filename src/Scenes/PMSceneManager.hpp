//
//  PMSceneManager.hpp
//  PMConcertParaules
//
//  Created by Miquel Àngel Soler on 25/10/15.
//
//

#ifndef PMSceneManager_hpp
#define PMSceneManager_hpp

#pragma once

#include <stdio.h>
#include "ofxSceneManager.h"
#include "PMBaseScene.hpp"

typedef enum
{
    Scene1 = 0,
    Scene2 = 1
} PMSMSceneIndex;

class PMSceneManager
{
public:
    static PMSceneManager &getInstance()
    {
        static PMSceneManager instance;
        return instance;
    }

    void init();

    void update();
    void draw();

    void changeScene();
    void changeScene(PMSMSceneIndex sceneIndex);

    void willExit();

private:

    ofxSceneManager         sceneManager;
    vector<PMBaseScene *>   scenes;
};

#endif /* PMSceneManager_hpp */
