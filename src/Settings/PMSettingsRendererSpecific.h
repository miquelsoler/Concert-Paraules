//
// Created by Miquel Àngel Soler on 29/10/15.
//

#pragma once

#ifndef PMCONCERTPARAULES_PMSETTINGSRENDERERSPECIFIC_H
#define PMCONCERTPARAULES_PMSETTINGSRENDERERSPECIFIC_H


class PMSettingsRendererSpecific
{
};

class PMSettingsRendererPaintbrush : public PMSettingsRendererSpecific
{
public:
    int size;
};

class PMSettingsRendererTypography : public PMSettingsRendererSpecific
{
public:
};

class PMSettingsRendererColors : public PMSettingsRendererSpecific
{
public:
};


#endif //PMCONCERTPARAULES_PMSETTINGSRENDERERSPECIFIC_H
