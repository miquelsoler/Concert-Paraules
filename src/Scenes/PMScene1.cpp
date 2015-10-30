//
//  PMScene1.cpp
//  PMConcertParaules
//
//  Created by Miquel Àngel Soler on 7/10/15.
//
//

#include "PMScene1.hpp"

static const string     STR_HEADER_MAINBUTTONS  = "GO TO MAIN SCENE";
static const string     STR_MAINBUTTONS_SAVE    = "SAVE & CONTINUE";


#pragma mark - UI building

///--------------------------------------------------------------
PMScene1::PMScene1()
{
    // Settings
    {
        backgroundColor = ofColor(64, 73, 47);

        canvasBgColor = ofColor(0, 0, 0, 50);
        canvasTitleColor = ofColor(252, 239, 157);
    }

    // GUI
    {
        guiX = 20;
        guiY = 20;

        int panelOriginX;
        int panelMarginX = 20;

        int lastWidth;

        // Poem selector
        panelOriginX = guiX;
        guiPoemSelector = new PMUICanvasPoem("POEM", OFX_UI_FONT_LARGE);
        guiPoemSelector->init(panelOriginX, guiY);
        lastWidth = int(guiPoemSelector->getWidth());

        // Audio settings
        panelOriginX += lastWidth + panelMarginX;
        guiAudioSettings = new PMUICanvasAudioDevices("INPUT DEVICES", OFX_UI_FONT_LARGE);
        guiAudioSettings->init(panelOriginX, guiY);
        lastWidth = int(guiAudioSettings->getWidth());

        // Renderer settings
        panelOriginX += lastWidth + panelMarginX;
        guiRendererSettings = new PMUICanvasRenderers("RENDER MODE", OFX_UI_FONT_LARGE);
        guiRendererSettings->init(panelOriginX, guiY);

        // Continue buttons
        this->setupGUIMainButtons();
    }
}

///--------------------------------------------------------------
PMScene1::~PMScene1()
{
    delete guiPoemSelector;
    delete guiAudioSettings;
    delete guiRendererSettings;
    delete guiMainButtons;
}

///--------------------------------------------------------------
void PMScene1::setup()
{
}

///--------------------------------------------------------------
void PMScene1::update()
{
}

///--------------------------------------------------------------
void PMScene1::draw()
{
    PMBaseScene::draw();
}

///--------------------------------------------------------------
void PMScene1::willDraw()
{
    guiPoemSelector->setVisible(true);
    guiAudioSettings->setVisible(true);
    guiRendererSettings->setVisible(true);
    guiMainButtons->setVisible(true);
}

///--------------------------------------------------------------
void PMScene1::willExit()
{
    guiPoemSelector->setVisible(false);
    guiAudioSettings->setVisible(false);
    guiRendererSettings->setVisible(false);
    guiMainButtons->setVisible(false);
}

#pragma mark - Panels

///--------------------------------------------------------------
void PMScene1::setupGUIMainButtons()
{
    guiMainButtons = new ofxUISuperCanvas(STR_HEADER_MAINBUTTONS);
    guiMainButtons->setColorBack(canvasBgColor);
    guiMainButtons->getCanvasTitle()->setColorFill(canvasTitleColor);

    guiMainButtons->addLabelButton(STR_MAINBUTTONS_SAVE, false);

    guiMainButtons->autoSizeToFitWidgets();

    ofxUIRectangle *widgetRect = guiMainButtons->getRect();

    float marginSize = 20;
    guiMainButtons->setPosition(int(ofGetWidth() - widgetRect->getWidth() - marginSize),
                                int(ofGetHeight() - widgetRect->getHeight() - marginSize));

    ofAddListener(guiMainButtons->newGUIEvent, this, &PMScene1::handleEventMainButtons);
}

#pragma mark - Event management

void PMScene1::handleEventMainButtons(ofxUIEventArgs &e)
{
    if (e.getKind() != OFX_UI_WIDGET_LABELBUTTON) return;

    ofxUILabelButton *button = (ofxUILabelButton *)e.widget;
    if (!button->getValue()) return; // Ignore releases

//    settingsAudioDevices->writeJSON();
    PMSceneManager::getInstance().changeScene();
}

#pragma mark - Convenience methods

void PMScene1::dragEvent(ofDragInfo dragInfo)
{
//    string filename = dragInfo.files[0];
//
//    settingsPoem->addPoem(filename);
//    settingsPoem->writeJSON();
//
//    vector <ofxUIWidget *> poemWidgets = guiPoemSelector->getWidgets();
//    ofxUILabel *fileLabel = NULL;
//    bool found = false;
//    for (int i=0; i<poemWidgets.size() && !found; i++)
//    {
//        found = (poemWidgets[i]->getKind() == OFX_UI_WIDGET_LABEL) && (poemWidgets[i]->getName() != STR_HEADER_POEM);
//        if (found)
//            fileLabel = (ofxUILabel *)(poemWidgets[i]);
//    }
//
//    if (found)
//        fileLabel->setLabel(filename);
//
//#ifdef OF_DEBUG
//    cout << "Dragged file \"" << dragInfo.files[0] << "\" into scene" << endl;
//#endif
}
