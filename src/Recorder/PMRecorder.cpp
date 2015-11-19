//
//  PMRecorder.cpp
//  PMConcertParaules
//
//  Created by Eduard Frigola on 19/11/15.
//
//

#include "PMRecorder.hpp"

void PMRecorder::init(ofFbo *_fbo, int _samplerate, int _channels)
{
    fbo=_fbo;
    sampleRate=_samplerate;
    channels=_channels;
    pixelBufferBack.allocate(fbo->getWidth()*fbo->getHeight()*3,GL_DYNAMIC_READ);
    pixelBufferFront.allocate(fbo->getWidth()*fbo->getHeight()*3,GL_DYNAMIC_READ);
    //    vidRecorder.setFfmpegLocation(ofFilePath::getAbsolutePath("ffmpeg")); // use this is you have ffmpeg installed in your data folder
    
    fileName = "testMovie";
    fileExt = ".mov"; // ffmpeg uses the extension to determine the container type. run 'ffmpeg -formats' to see supported formats
    
    // override the default codecs if you like
    // run 'ffmpeg -codecs' to find out çwhat your implementation supports (or -formats on some older versions)
    vidRecorder.setVideoCodec("mpeg4");
    vidRecorder.setVideoBitrate("20000k");
    //    vidRecorder.setAudioCodec("mp3");
    //    vidRecorder.setAudioBitrate("256k");
    
    ofAddListener(vidRecorder.outputFileCompleteEvent, this, &PMRecorder::recordingComplete);
    
    //    soundStream.listDevices();
    //    soundStream.setDeviceID(11);
//    soundStream.setup(this, 0, channels, sampleRate, 256, 4);
    
//    ofSetWindowShape(ofGetWidth(), ofGetHeight());
    bRecording = false;
    ofEnableAlphaBlending();
}

void PMRecorder::addVideoFrame()
{
    if(bRecording){
        // copy the fbo texture to a buffer
        fbo->getTexture().copyTo(pixelBufferBack);
        
        // map the buffer so we can access it from the cpu
        // and wrap the memory in an ofPixels to save it
        // easily. Finally unmap it.
        pixelBufferFront.bind(GL_PIXEL_UNPACK_BUFFER);
        unsigned char * p = pixelBufferFront.map<unsigned char>(GL_READ_ONLY);
        pixels.setFromExternalPixels(p,fbo->getWidth(),fbo->getHeight(),OF_PIXELS_RGB);
        //        ofSaveImage(pixels,ofToString(ofGetFrameNum())+".jpg");
        pixelBufferFront.unmap();
        
        // swap the front and back buffer so we are always
        // copying the texture to one buffer and reading
        // back from another to avoid stalls
        swap(pixelBufferBack,pixelBufferFront);
        bool success = vidRecorder.addFrame(pixels);
        if (!success) {
            ofLogWarning("This frame was not added!");
        }
    }
    
    // Check if the video recorder encountered any error while writing video frame or audio smaples.
    if (vidRecorder.hasVideoError()) {
        ofLogWarning("The video recorder failed to write some frames!");
    }
    
    if (vidRecorder.hasAudioError()) {
        ofLogWarning("The video recorder failed to write some audio samples!");
    }
}

void PMRecorder::addAudioBuffer(float *input, int bufferSize, int nChannels)
{
    if(bRecording)
        vidRecorder.addAudioSamples(input, bufferSize, nChannels);
}

void PMRecorder::exit()
{
    
}

void PMRecorder::startRecording()
{
    bRecording = !bRecording;
    if(bRecording && !vidRecorder.isInitialized()) {
        vidRecorder.setup(fileName+ofGetTimestampString()+fileExt, ofGetWidth(), ofGetHeight(), 60, sampleRate, channels);
        //          vidRecorder.setup(fileName+ofGetTimestampString()+fileExt, vidGrabber.getWidth(), vidGrabber.getHeight(), 30); // no audio
        //            vidRecorder.setup(fileName+ofGetTimestampString()+fileExt, 0,0,0, sampleRate, channels); // no video
        //          vidRecorder.setupCustomOutput(vidGrabber.getWidth(), vidGrabber.getHeight(), 30, sampleRate, channels, "-vcodec mpeg4 -b 1600k -acodec mp2 -ab 128k -f mpegts udp://localhost:1234"); // for custom ffmpeg output string (streaming, etc)
        
        // Start recording
        vidRecorder.start();
    }
}

void PMRecorder::stopRecording()
{
    bRecording = false;
    vidRecorder.close();
}

void PMRecorder::discardRecording()
{
    bRecording = false;
    vidRecorder.close();
    //TODO erase last clip.
}

void PMRecorder::recordingComplete(ofxVideoRecorderOutputFileCompleteEventArgs& args){
    cout << "The recoded video file is now complete." << endl;
}