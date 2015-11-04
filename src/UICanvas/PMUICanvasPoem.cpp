//
// Created by Miquel Àngel Soler on 30/10/15.
//

#include "PMUICanvasPoem.h"


void PMUICanvasPoem::init(int posX, int posY, bool autosize, int width, int height)
{
    PMBaseUICanvas::init(posX, posY, autosize, width, height);

    settings = &PMSettingsManagerPoem::getInstance();

    poemTextArea= addTextArea("Poem name", settings->getPoemFilename(), OFX_UI_FONT_SMALL);

    string buttonLabel = settings->getPoemValidity() ? "CHANGE" : "SELECT";
    addLabelButton(buttonLabel, false);

    if (autosize) autoSizeToFitWidgets();

    ofAddListener(newGUIEvent, this, &PMUICanvasPoem::handleEvents);
}

void PMUICanvasPoem::handleEvents(ofxUIEventArgs &e)
{
    if (e.getKind() != OFX_UI_WIDGET_LABELBUTTON) return;

    ofxUILabelButton *button = (ofxUILabelButton *)e.widget;
    if (!button->getValue()) return; // Ignore releases

    string path = ofFilePath::getAbsolutePath("",true);
    path += "/" + settings->getFolderPath();

    ofFileDialogResult poemSelectDialog = ofSystemLoadDialog("Select Poem", false, path);
    if (!poemSelectDialog.bSuccess) return;

    settings->setPoem(poemSelectDialog.getName());
    settings->write();

    poemTextArea->setTextString(settings->getPoemFilename());
}
