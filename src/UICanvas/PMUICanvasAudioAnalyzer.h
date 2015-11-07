//
// Created by Miquel Àngel Soler on 7/11/15.
//

#ifndef PMCONCERTPARAULES_PMUICANVASAUDIOANALYZER_H
#define PMCONCERTPARAULES_PMUICANVASAUDIOANALYZER_H

#include "PMBaseUICanvas.h"

#include "PMAudioOutParams.h"

class PMUICanvasAudioAnalyzer : public PMBaseUICanvas
{
public:

    PMUICanvasAudioAnalyzer(string title, int headerFontSize) : PMBaseUICanvas(title, headerFontSize) {}

    virtual void init(int posX, int posY, bool autosize = true, int width = 0, int height = 0);
    virtual void clear();

    virtual void handleEvents(ofxUIEventArgs &e);

    void pitchChanged(pitchParams &pitchParams);
};


#endif //PMCONCERTPARAULES_PMUICANVASAUDIOANALYZER_H
