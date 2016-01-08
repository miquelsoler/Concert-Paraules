//
// Created by Miquel Àngel Soler on 7/11/15.
//

#include "PMUICanvasTypoRenderer.h"

PMUICanvasTypoRenderer::PMUICanvasTypoRenderer(PMUIRendererType type, string title, int headerFontSize) : PMUICanvasBaseRenderer(type, title, headerFontSize)
{
}

void PMUICanvasTypoRenderer::init(int posX, int posY, bool autosize, int width, int height)
{
    PMUICanvasBaseRenderer::init(posX, posY, autosize, width, height);
    
    addSpacer();
    addSlider("Add Letter Sensitivity",0.0, 1.0, &guiAddLetterSensitivity);
    addSpacer();
    addLabel("VELOCITY");
    addIntSlider("Min Velocity", 1, 10, &minVelocity);
    addIntSlider("Max Velocity", 10, 150, &maxVelocity);
    addSpacer();
    addLabel("SIZE");
    addSlider("Min Size", 0.1, 1.0, &minSize);
    addSlider("Max Size", 0.1, 10.0, &maxSize);
    addSpacer();
    addLabel("BOUNCE");
    addSlider("Bounce Factor", 0.1, 1.0, &bounceFactor);
    addSpacer();
    addLabel("LETTER MAX AGE");
    addIntSlider("Max Age (s)", 1, 30, &maxAge);
    addSlider("Letter Speed Ms",10,500.0,&guiLetterSpeedMs);
    addSpacer();
    addLabel("GRAVITY");
    addSlider("Gravity X", -50, 50, &gravityX);
    addSlider("Gravity Y", -50, 50, &gravityY);
    addSlider("Gravity Sinus Freq",-8,8, &guiSinusFreq);
    addSlider("Gravity Sinus Amplitude",0, 250, &guiSinusAmplitude);
    addSpacer();
    addLabel("COLOR");
    addIntSlider("Red",    0, 255, &colorR);
    addIntSlider("Green",  0, 255, &colorG);
    addIntSlider("Blue",   0, 255, &colorB);
    
    if (autosize) autoSizeToFitWidgets();

    loadPreset(selectedPreset);
}

void PMUICanvasTypoRenderer::clear()
{
    ofxUICanvas::clearWidgets();
    superInit("TYPO_RENDERER", OFX_UI_FONT_MEDIUM);
}

void PMUICanvasTypoRenderer::handleEvents(ofxUIEventArgs &e)
{
    PMUICanvasBaseRenderer::handleEvents(e);
    
    string name = e.getName();
}
