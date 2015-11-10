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
    int deviceID;
    int channel;
};

struct pitchParams : public baseAudioInParams
{
    float freq;
    float confidence;
    float midiNote;
    float midiNoteNoOctave;
};

struct energyParams : public baseAudioInParams
{
    float energy;
};

struct silenceParams : public baseAudioInParams
{
};

struct freqBandsParams : public baseAudioInParams
{
    float *melBands;
    int numBands;
};

struct onsetParams : public baseAudioInParams
{
};


#endif /* PMAudioOutParams_h */
