//
// Created by Miquel Àngel Soler on 16/12/15.
//

#ifndef PMCONCERTPARAULES_PMRENDERERRIBBON_H
#define PMCONCERTPARAULES_PMRENDERERRIBBON_H

#include "PMBaseRenderer.h"
#include "PMRibbonPainter.h"

class PMRendererRibbon : public PMBaseRenderer
{
public:

    PMRendererRibbon();

    virtual void setup();
    virtual void update();
    virtual void drawIntoFBO();

    void setPosition(int x, int y);
    void setColor(ofColor color);

    void strokeStarted();
    void strokeEnded();

// TODO: Remove mouse events code once audio events are working
    void mouseDragged(int x, int y, int button);
    void mousePressed(int x, int y, int button);
    void mouseReleased(int x, int y, int button);

private:

    vector<PMRibbonPainter> painters;

    ofPoint position;

    unsigned int numPainters;
    unsigned int size;

    bool isInStroke;

    void buildPainters();
};


#endif //PMCONCERTPARAULES_PMRENDERERRIBBON_H
