//
//  PMSceneManager.hpp
//  PMConcertParaules
//
//  Created by Miquel Àngel Soler on 25/10/15.
//
//

#ifndef PMSceneManager_hpp
#define PMSceneManager_hpp

#include <stdio.h>
#include "ofxSceneManager.h"

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

private:

    ofxSceneManager         sceneManager;
};

#endif /* PMSceneManager_hpp */
