//
//  PMSceneManager.cpp
//  PMConcertParaules
//
//  Created by Miquel Àngel Soler on 25/10/15.
//
//

#include "PMSceneManager.hpp"
#include "PMScene1.hpp"
#include "PMScene2.hpp"

///--------------------------------------------------------------
void PMSceneManager::init()
{
    sceneManager.addScene(ofPtr<ofxScene>(new PMScene1()));
    sceneManager.addScene(ofPtr<ofxScene>(new PMScene2()));
    sceneManager.run();
}

///--------------------------------------------------------------
void PMSceneManager::update()
{
    sceneManager.update();
}

///--------------------------------------------------------------
void PMSceneManager::draw()
{
    sceneManager.draw();
}

///--------------------------------------------------------------
void PMSceneManager::changeScene()
{
    sceneManager.changeScene();
}
