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
private:
    static PMRecorder &getInstance()
    {
        static PMRecorder instance;
        return instance;
    }
    
    void init(){};
    
    
    ofxVideoRecorder    vidRecorder;
    bool bRecording;
    string fileName;
    string fileExt;
    
    void recordingComplete(ofxVideoRecorderOutputFileCompleteEventArgs& args);
    
    ofPixels pixels;
    ofBoxPrimitive box;
    ofBufferObject pixelBufferBack, pixelBufferFront;
};