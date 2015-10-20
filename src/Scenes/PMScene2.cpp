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
    cout << "S2 setup" << endl;
}

void PMScene2::update()
{

}

void PMScene2::draw()
{
    PMBaseScene::draw();

#ifdef OF_DEBUG
    baseFont.drawString("MAIN", 15, 30);
#endif
}

void PMScene2::willExit()
{
}
