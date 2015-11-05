//
// Created by Miquel Àngel Soler on 4/11/15.
//

#include "PMUICanvasNavigation.h"


static const string STR_NAVIGATION_BUTTON_SAVE = "CONTINUE";


void PMUICanvasNavigation::init(int posX, int posY, bool autosize, int width, int height)
{
    PMBaseUICanvas::init(posX, posY, autosize, width, height);

    ofxUILabelButton *labelButton = addLabelButton(STR_NAVIGATION_BUTTON_SAVE, false);
    labelButton->setColorBack(ofColor::darkGray);

    autoSizeToFitWidgets();

    ofAddListener(newGUIEvent, this, &PMUICanvasNavigation::handleEvents);
}

void PMUICanvasNavigation::handleEvents(ofxUIEventArgs &e)
{
    if (e.getKind() != OFX_UI_WIDGET_LABELBUTTON) return;

    ofxUILabelButton *button = (ofxUILabelButton *)e.widget;
    if (!button->getValue()) return; // Ignore releases

    ofNotifyEvent(eventContinuePressed, this);
}
