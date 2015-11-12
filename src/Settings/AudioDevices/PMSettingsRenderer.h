//
// Created by Miquel Àngel Soler on 29/10/15.
//

#pragma once

#ifndef PMCONCERTPARAULES_PMSETTINGSRENDERER_H
#define PMCONCERTPARAULES_PMSETTINGSRENDERER_H

#include "PMSettingsRendererSpecific.h"


class PMSettingsRenderer
{
public:
    int                         ID;
    string                      name;
    bool                        enabled;
    PMSettingsRendererSpecific  specificSettings;
};

#endif //PMCONCERTPARAULES_PMSETTINGSRENDERER_H
