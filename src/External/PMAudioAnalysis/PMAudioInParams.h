//
//  PMAudioOutParams.h
//  PMConcertParaules
//
//  Created by Miquel Àngel Soler on 13/10/15.
//

#ifndef PMAudioOutParams_h
#define PMAudioOutParams_h

#pragma once

struct baseAudioInParams
{
    unsigned int audioInputIndex;
    int deviceID;
    int channel;
};

struct pitchParams : public baseAudioInParams
{
//    float freq;
    float confidence;
    float midiNote;
};

struct energyParams : public baseAudioInParams
{
    float energy;
};

struct silenceParams : public baseAudioInParams
{
    bool isSilent;
    float silenceTime;
};

struct freqBandsParams : public baseAudioInParams
{
    float *melBands;
    int numBands;
};

struct onsetParams : public baseAudioInParams
{
    bool isOnset;
};

struct shtParams : public baseAudioInParams
{
    float time;
};


#endif /* PMAudioOutParams_h */
