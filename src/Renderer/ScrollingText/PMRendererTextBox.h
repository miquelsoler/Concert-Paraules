//
// Created by Miquel Àngel Soler on 16/11/15.
//

#ifndef PMCONCERTPARAULES_PMRENDERERSCROLLINGTEXT_H
#define PMCONCERTPARAULES_PMRENDERERSCROLLINGTEXT_H


#define REF_X 95.047; // Observer= 2°, Illuminant= D65
#define REF_Y 100.000;
#define REF_Z 108.883;


#pragma once

#include "PMBaseRenderer.h"
#include "PMUICanvasTextBoxRenderer.h"
#include "PMSettingsManagerPoem.h"
//#include "ofxScrollingText.h"
//#include "ofxTextBox.h"
#include "ofxFontStash.h"


class PMRendererTextBox : public PMBaseRenderer
{
public:

    PMRendererTextBox();

    virtual void setup();
    virtual void update();
    virtual void drawIntoFBO();
    
    void keyPressed ( ofKeyEventArgs& eventArgs );
    void toggleGUIVisible();
    void getText();
    
private:
    
    PMUICanvasTextBoxRenderer       *myGUI;
    vector<string>                  textToWrite;
    string                          text;
    ofImage                         logoImage;

//    ofxScrollingText               *scrollText;
//    ofxTextBox                      textBox;
    ofVec2f                         boxMargins;
    
    ofxFontStash font;
    ofxFontStash unicodeFont;
    float fontSize;


};


#endif //PMCONCERTPARAULES_PMRENDERERSCROLLINGTEXT_H
