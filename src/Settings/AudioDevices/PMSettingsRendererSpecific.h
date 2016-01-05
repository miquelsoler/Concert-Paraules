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
};

class PMSettingsRendererColors : public PMSettingsRendererSpecific
{
};

class PMSettingsRendererRibbon : public PMSettingsRendererSpecific
{
};

class PMSettingsRendererCurves : public PMSettingsRendererSpecific
{
};

#endif //PMCONCERTPARAULES_PMSETTINGSRENDERERSPECIFIC_H
