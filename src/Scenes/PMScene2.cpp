//
//  PMScene2.cpp
//  PMConcertParaules
//
//  Created by Miquel Àngel Soler on 7/10/15.
//
//

#include "PMScene2.hpp"
#include "Defaults.h"
#include "PMAudioAnalyzer.hpp"
#include "PMSettingsManagerGeneral.h"
#include "PMSettingsManagerAudioDevices.h"


PMScene2::PMScene2() : PMBaseScene("Scene 2")
{
#ifdef OF_DEBUG
    showGUI= PMSettingsManagerGeneral::getInstance().getDebugShowGUIScene2();
#else
    showGUI = PMSettingsManagerGeneral::getInstance().getReleaseShowGUIScene2();
#endif

    backgroundColor = ofColor::white;

    // GUI
    {
        canvasBgColor = ofColor(50, 50, 50, 200);

        guiRenderers = new PMUICanvasRenderers("RENDER MODE", OFX_UI_FONT_LARGE);
        guiRenderers->init(200, 200);
        guiRenderers->setBackgroundColor(canvasBgColor);
        guiRenderers->setVisible(false);
    }

    // Renderer
    {
        renderer = new PMRendererPaintbrush();
    }
}

PMScene2::~PMScene2()
{
    delete guiRenderers;
}

void PMScene2::setup()
{
    vector<PMSettingsDevice> *audioDevices = PMSettingsManagerAudioDevices::getInstance().getAudioDevices();
    vector<PMSettingsDevice>::iterator itDevice;

    for (itDevice = audioDevices->begin(); itDevice != audioDevices->end(); ++itDevice)
    {
        if (!(*itDevice).enabled) continue;
        unsigned int numChannels = (unsigned int)((*itDevice).channels.size());

        for (unsigned int i=0; i<numChannels; i++)
        {
            PMSettingsDeviceChannel channel = (*itDevice).channels[i];

            if (!channel.enabled) continue;

            int deviceId = (*itDevice).ID;
            int inChannels = (*itDevice).inChannels;
            int outChannels = (*itDevice).outChannels;
            int channelNumber = channel.ID;

            PMAudioAnalyzer::getInstance().addDeviceAudioAnalyzer(deviceId, inChannels, outChannels, DEFAULT_SAMPLERATE, DEFAULT_BUFFERSIZE, PMDAA_CHANNEL_MONO, channelNumber);
        }
    }

    renderer->setup();
}

void PMScene2::update()
{
    renderer->update();
}

void PMScene2::updateEnter()
{
//    cout << "PMScene2::updateEnter()" << endl;
    if (isEnteringFirst())
    {
        guiRenderers->loadSettings("settings/gui/renderers2.xml");
        guiRenderers->setVisible(showGUI);
    }

    PMBaseScene::updateEnter();
}

void PMScene2::updateExit()
{
    saveSettings();
    PMBaseScene::updateExit();
}

void PMScene2::draw()
{
    renderer->draw();
}

void PMScene2::saveSettings()
{
    guiRenderers->saveSettings("settings/gui/renderers2.xml");
    guiRenderers->setVisible(false);
}

void PMScene2::keyReleased(int key)
{
    PMBaseScene::keyReleased(key);

    switch(key)
    {
        case 'g':
        case 'G':
        {
            showGUI = !showGUI;
            guiRenderers->setVisible(showGUI);
            ofClear(backgroundColor);
            break;
        }
        default: break;
    }
}
