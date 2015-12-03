//
// Created by Miquel Àngel Soler on 3/12/15.
//

#ifndef PMCONCERTPARAULES_PMRENDERERPAINTBRUSH2_H
#define PMCONCERTPARAULES_PMRENDERERPAINTBRUSH2_H

#include "PMBaseRenderer.h"
#include "PMBrushContainer2.h"

class PMRendererPaintbrush2 : public PMBaseRenderer
{
public:

    PMRendererPaintbrush2();

    virtual void setup();
    virtual void update();
    virtual void drawIntoFBO();

    virtual void pitchChanged(pitchParams pitchParams);
    virtual void energyChanged(energyParams energyParams);

private:

    PMBrushContainer2 *brush;
};


#endif //PMCONCERTPARAULES_PMRENDERERPAINTBRUSH2_H
