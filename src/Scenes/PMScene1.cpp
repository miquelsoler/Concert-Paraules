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
    cout << "S1 setup" << endl;
}

void PMScene1::update()
{

}

void PMScene1::draw()
{
    PMBaseScene::draw();

#ifdef OF_DEBUG
    baseFont.drawString("SETTINGS", 15, 30);
#endif
}

void PMScene1::willExit()
{
}
