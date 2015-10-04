//
//  PMAudioAnalyzer.hpp
//  ConcertParaules
//
//  Created by Miquel Àngel Soler on 25/9/15.
//
//

#ifndef PMSoundAnalyzer_hpp
#define PMSoundAnalyzer_hpp

#include <stdio.h>
#include "ofMain.h"
#include "ofxAudioAnalyzer.h"

typedef enum
{
    PMAA_CHANNEL_MULTI = 0,
    PMAA_CHANNEL_MONO = 1
} PMAA_ChannelMode;


class PMAudioAnalyzer : public ofBaseSoundInput
{
public:

    // Constructor just sets attributes. Calling it doesn't start the sound stream analysis.
    PMAudioAnalyzer(ofBaseApp *app, int deviceID, int inChannels, int outChannels, int sampleRate, int bufferSize);
    ~PMAudioAnalyzer();

    void setup(PMAA_ChannelMode channelMode = PMAA_CHANNEL_MULTI, int channelNumber = -1);

    void start();
    void stop();

    void audioIn(float *input, int bufferSize, int nChannels);

private:

    int                         deviceID;
    int                         inChannels;
    int                         outChannels;
    int                         sampleRate;
    int                         bufferSize;
    int                         numBuffers;

    PMAA_ChannelMode            channelMode;
    int                         channelNumber;

    ofSoundStream               soundStream;
    vector<ofxAudioAnalyzer *>  audioAnalyzers;

    float                   **buffers; // buffers[ CHANNEL ][ CHANNEL BUFFER ]

    bool                    isSetup;
};

#endif /* PMSoundAnalyzer_h */
