//
//  PMScene1.cpp
//  PMConcertParaules
//
//  Created by Miquel Àngel Soler on 7/10/15.
//
//

#include "PMScene1.hpp"

void PMScene1::setup()
{
}

void PMScene1::update()
{

}

void PMScene1::draw()
{
    ofClear(ofColor::black);
    ofDrawBitmapString("SETTINGS SCENE", 15, 30);
}

void PMScene1::willExit()
{
    cout << "S1 will exit" << endl;
}
