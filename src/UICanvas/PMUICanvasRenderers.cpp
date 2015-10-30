//
// Created by Miquel Àngel Soler on 30/10/15.
//

#include "PMUICanvasRenderers.h"

void PMUICanvasRenderers::init(int posX, int posY)
{
    PMBaseUICanvas::init(posX, posY);

    settings = &PMSettingsManagerRenderers::getInstance();

    vector<PMSettingsRenderer> *renderers = settings->getRenderers();

    ofxUIRadio *modeRadioButtons;

    // Add radio buttons for renderer modes
    {
        vector<string> modeNames;
        for (int iRenderer = 0; iRenderer < renderers->size(); ++iRenderer) {
            PMSettingsRenderer renderer = (*renderers)[iRenderer];
            modeNames.push_back(renderer.name);
        }
        modeRadioButtons = addRadio("Render Modes", modeNames);
    }

    // Set selected mode and ID according to settings file
    {
        vector<ofxUIToggle *> modeButtonsToggles = modeRadioButtons->getToggles();
        for (int i = 0; i < modeButtonsToggles.size(); ++i) {
            PMSettingsRenderer renderer = (*renderers)[i];
            modeButtonsToggles[i]->setID(renderer.ID);
            modeButtonsToggles[i]->setValue(renderer.enabled);
        }
    }

    autoSizeToFitWidgets();

    ofAddListener(newGUIEvent, this, &PMUICanvasRenderers::handleEvents);
}

void PMUICanvasRenderers::handleEvents(ofxUIEventArgs &e)
{
    if (e.getKind() != OFX_UI_WIDGET_TOGGLE) return;

    ofxUIToggle *toggle = (ofxUIToggle *)e.widget;
    if (!toggle->getValue()) return; // Ignore releases

    settings->enableRenderer((unsigned int)(toggle->getID()));
    settings->writeJSON();
}
