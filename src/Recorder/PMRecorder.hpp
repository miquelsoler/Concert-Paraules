//
//  PMRecorder.hpp
//  PMConcertParaules
//
//  Created by Eduard Frigola on 19/11/15.
//
//

#ifndef PMRecorder_hpp
#define PMRecorder_hpp

#include <stdio.h>
#include "ofxVideoRecorder.h"

#endif /* PMRecorder_hpp */


class PMRecorder
{
public:
    static PMRecorder &getInstance()
    {
        static PMRecorder instance;
        return instance;
    }

    void init(ofFbo *fbo, int _samplerate, int _channels, string fileName, string filePath);
    void addVideoFrame();
    void addAudioBuffer(float *input, int bufferSize, int nChannels);
    void exit();
    
    void startRecording();
    void stopRecording();
    void discardRecording();
    bool isRecording();
    
private:
    ofxVideoRecorder    vidRecorder;
    bool bRecording;
    string fileName;
    string fileExt;
    string filePath; //Where the file will be created
    string lastFileNameGenerated;
    
    void recordingComplete(ofxVideoRecorderOutputFileCompleteEventArgs& args);
    
    int sampleRate;
    int channels;
    ofFbo *fbo;
    ofFbo fboRecorderOut;
    ofPixels pixels;
    ofBoxPrimitive box;
    ofBufferObject pixelBufferBack, pixelBufferFront;
};