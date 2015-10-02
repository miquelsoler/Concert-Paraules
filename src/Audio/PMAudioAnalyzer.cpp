//
//  PMAudioAnalyzer.cpp
//  ConcertParaules
//
//  Created by Miquel Àngel Soler on 25/9/15.
//
//

#include "PMAudioAnalyzer.hpp"

///--------------------------------------------------------------
PMAudioAnalyzer::PMAudioAnalyzer(ofBaseApp *app, int _deviceID, int _inChannels, int _outChannels, int _sampleRate, int _bufferSize)
{
    deviceID = _deviceID;
    inChannels = _inChannels;
    outChannels = _outChannels;
    sampleRate = _sampleRate;
    bufferSize = _bufferSize;
//    numBuffers = _numBuffers;
    numBuffers = bufferSize/64;

    // Buffer matrix:
    // - Rows: channels
    // - Cols: channel buffer
    buffers = new float *[inChannels];
    for (int i=0; i<inChannels; i++)
    {
        buffers[i] = new float[bufferSize];
    }

    audioAnalyzer.setup(bufferSize, sampleRate);

    soundStream.printDeviceList();

    soundStream.setDeviceID(deviceID);
    cout << "Device Id: " << deviceID << endl;
    cout << "Setup: " << app << ", " << outChannels << ", " << inChannels << ", " << sampleRate << ", " << bufferSize << ", " << numBuffers << endl;
    soundStream.setup(outChannels, inChannels, sampleRate, bufferSize, numBuffers);
    soundStream.setInput(this);
}

PMAudioAnalyzer::~PMAudioAnalyzer()
{
}


///--------------------------------------------------------------
void PMAudioAnalyzer::audioIn(float *input, int bufferSize, int nChannels)
{
//    cout << "xxxSomeone called audioIn(" << input << ", " << bufferSize << ", " << nChannels << ")" << endl;

    for (int i=0; i<nChannels; ++i)
    {
        for (int j=0; j<bufferSize; j++)
        {
            buffers[i][j] = input[i + (nChannels * j)];
        }
    }

    // For testing purposes
    {
        audioAnalyzer.analyze(buffers[0], bufferSize);
        cout << "RMS: " << audioAnalyzer.getPitchFreq() << endl;
    }
}
