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

class PMAudioAnalyzer : public ofBaseSoundInput
{
public:

    PMAudioAnalyzer(ofBaseApp *app, int deviceID, int inChannels, int outChannels, int sampleRate, int bufferSize);
    ~PMAudioAnalyzer();

    void audioIn(float *input, int bufferSize, int nChannels);

private:

    int deviceID;
    int inChannels;
    int outChannels;
    int sampleRate;
    int bufferSize;
    int numBuffers;

    ofSoundStream soundStream;
    ofxAudioAnalyzer audioAnalyzer;

    float **buffers;
};

#endif /* PMSoundAnalyzer_h */
