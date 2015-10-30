//
// Created by Miquel Àngel Soler on 30/10/15.
//

#include "PMUICanvasPoem.h"

void PMUICanvasPoem::init(int posX, int posY)
{
    PMBaseUICanvas::init(posX, posY);

    settings = &PMSettingsManagerPoem::getInstance();

    addLabel(settings->getPoemFilename(), OFX_UI_FONT_MEDIUM);

    autoSizeToFitWidgets();
}

void PMUICanvasPoem::handleEvents(ofxUIEventArgs &e)
{
}
