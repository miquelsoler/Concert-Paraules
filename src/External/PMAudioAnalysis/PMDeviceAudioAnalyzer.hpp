//
//  PMAudioAnalyzer.hpp
//  ConcertParaules
//
//  Created by Miquel Àngel Soler on 25/9/15.
//
//

#pragma once

#ifndef PMDeviceAudioAnalyzer_hpp
#define PMDeviceAudioAnalyzer_hpp

#include <stdio.h>
#include "ofMain.h"
#include "ofxAubio.h"
#include "PMAudioInParams.h"

typedef enum {
    PMDAA_CHANNEL_MULTI = 0,
    PMDAA_CHANNEL_MONO = 1
} PMDAA_ChannelMode;


class PMDeviceAudioAnalyzer : public ofBaseSoundInput {
public:

    PMDeviceAudioAnalyzer(int deviceID, int inChannels, int outChannels, int sampleRate, int bufferSize);
    PMDeviceAudioAnalyzer() {};
    ~PMDeviceAudioAnalyzer();

    void setup(unsigned int audioInputIndex, PMDAA_ChannelMode channelMode, vector<unsigned int> channelNumbers,
            float silenceThreshold, unsigned int silenceQueueLength,
            float onsetsThreshold,
            float smoothingDelta,
            int ascDescAnalysisSize);

    void start();
    void stop();
    void clear();
    void audioIn(float *input, int bufferSize, int nChannels);

    unsigned int getInputIndex() { return audioInputIndex; };

    int getDeviceID() { return deviceID; };
    int getChannelNumber() { return channelNumber; };
    int getSamplerate();
    int getNumChannels();

    // Events for listeners
    ofEvent<pitchParams> eventPitchChanged;
    ofEvent<silenceParams> eventSilenceStateChanged;
    ofEvent<energyParams> eventEnergyChanged;
    ofEvent<onsetParams> eventOnsetStateChanged;
    ofEvent<freqBandsParams> eventFreqBandsParams;
    ofEvent<shtParams> eventShtStateChanged;
    ofEvent<pauseParams> eventPauseStateChanged;
    ofEvent<melodyDirectionParams> eventMelodyDirection;

    // Setters
    void setSilenceThreshold(float _f) {silenceThreshold=_f;};
    void setSilenceQueueLength(float _f) {silenceTimeTreshold=_f;};
    void setPauseTimeTreshold(float _f) {pauseTimeTreshold=_f;};
    void setOnsetsThreshold(float _f);

private:

    // Setup
    unsigned int audioInputIndex;
    int deviceID;
    int inChannels;
    int outChannels;
    int sampleRate;
    int bufferSize;
    int numBuffers;

    // Channel mode
    PMDAA_ChannelMode channelMode;
    vector<unsigned int> channelNumbers;
    int channelNumber;

    // Pitch
    float minPitchMidiNote;
    float maxPitchMidiNote;

    // Silence
    bool wasSilent;
    float silenceThreshold;

    // Onsets
    float onsetsThreshold;
    vector<bool> oldOnsetState;

    // Smoothing
    float smoothingDelta;
    vector<float> oldMidiNotesValues;
    vector<deque<float> > midiNoteHistory;

    // Sound analysis

    ofSoundStream soundStream;

    vector<ofxAubioPitch *> vAubioPitches;
    vector<ofxAubioOnset *> vAubioOnsets;
    vector<ofxAubioMelBands *> vAubioMelBands;

    bool isSetup;

    vector<bool> isInSilence;
    vector<bool> isInPause;
    vector<float> silenceBeginTime;
    float silenceTimeTreshold;
    float pauseTimeTreshold;

    float getEnergy(unsigned int channel);
    float getRms(float *input, int bufferSize, int channel);
    float getAbsMean(float *input, int bufferSize, int channel);
    void detectedSilence(int channel);
    void updateSilenceTime(int channel);
    void detectedEndSilence(int channel);
    void checkMelodyDirection(int channel);

    int ascDescAnalysisSize;

    // sshht
    vector<bool> isShtSounding;
    vector<float> shtBeginTime;
    float shtTimeTreshold;
    vector<bool> isShtTrueSent;
    vector<bool> isShtFalseSent;

    void checkShtSound(int channel);
};

#endif /* PMDeviceAudioAnalyzer_h */
