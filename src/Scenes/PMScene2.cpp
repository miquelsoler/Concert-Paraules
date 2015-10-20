//
//  PMScene2.cpp
//  PMConcertParaules
//
//  Created by Miquel Àngel Soler on 7/10/15.
//
//

#include "PMScene2.hpp"

void PMScene2::setup()
{
}

void PMScene2::update()
{

}

void PMScene2::draw()
{
    ofClear(ofColor::black);
    ofDrawBitmapString("MAIN SCENE", 15, 30);
}

void PMScene2::willExit()
{
    cout << "S2 will exit" << endl;
}
