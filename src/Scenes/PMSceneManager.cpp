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


void PMSceneManager::init()
{
    PMScene1 *scene1 = new PMScene1();
    scenes.push_back(scene1);
    sceneManager.addScene(ofPtr<ofxScene>(scene1));

    PMScene2 *scene2 = new PMScene2();
    scenes.push_back(scene2);
    sceneManager.addScene(ofPtr<ofxScene>(scene2));

    sceneManager.run();
}

void PMSceneManager::update()
{
    sceneManager.update();
}

void PMSceneManager::draw()
{
    sceneManager.draw();
}

void PMSceneManager::changeScene()
{
    sceneManager.changeScene();
}

void PMSceneManager::changeScene(PMSMSceneIndex sceneIndex)
{
    sceneManager.changeScene(sceneIndex);
}

void PMSceneManager::willExit()
{
    for (int i=0; i<scenes.size(); i++)
        scenes[i]->exit();
}
