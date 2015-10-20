//
//  PMScene2.cpp
//  PMConcertParaules
//
//  Created by Miquel Àngel Soler on 7/10/15.
//
//

#include "PMScene2.hpp"

///--------------------------------------------------------------
PMScene2::~PMScene2()
{
//    cout << "Called delete PMScene2";
}

///--------------------------------------------------------------
void PMScene2::setup()
{
    cout << "S2 setup" << endl;
}

///--------------------------------------------------------------
void PMScene2::update()
{

}

///--------------------------------------------------------------
void PMScene2::draw()
{
//    cout << "SC2 draw" << endl;

    PMBaseScene::draw();

#ifdef OF_DEBUG
    baseFont.drawString("MAIN", 15, 30);
#endif
}

///--------------------------------------------------------------
void PMScene2::willExit()
{
}
