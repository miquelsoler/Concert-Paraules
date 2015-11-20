//
// Created by Miquel Àngel Soler on 16/11/15.
//

#include "PMRendererColor.h"

PMRendererColor::PMRendererColor(unsigned int numInputs) : PMBaseRenderer(RENDERERTYPE_COLOR, numInputs)
{

}

void PMRendererColor::setup()
{
    PMBaseRenderer::setup();
}

void PMRendererColor::update()
{
    PMBaseRenderer::update();
}

void PMRendererColor::drawIntoFBO()
{
    fbo.begin();
    {
//        ofEnableBlendMode(OF_BLENDMODE_ALPHA);
//        ofSetColor(255, 255, 255, 5);
//        ofDrawRectangle(0, 0, ofGetWidth(), ofGetHeight());

        ofSetColor(255, 255, 255, 5);
        ofDrawRectangle(0, 0, ofGetWidth(), ofGetHeight());

        ofEnableBlendMode(OF_BLENDMODE_ALPHA);

        
        //ofDrawCircle(ofRandom(ofGetWidth()),ofRandom(ofGetHeight()),100*pitch);
        ofColor c = ofColor::fromHsb(ofMap(abs(pitch),0,1.0,0,1.0)*255, 255, 255);
        //cout << ofMap(pitch,0.0,1.0,0,1.0) << endl;
        //ofColor c = ofColor::fromHsb(128, 255, 255);
        ofSetColor(c);
        ofSetCircleResolution(128);
        ofDrawCircle(ofGetWidth()/2,ofGetHeight()/2,(ofGetHeight()/2)*energy);

        cout << "Color Pitch" <<  pitch << " Energy : " << energy << endl;

        ofDisableBlendMode();
    }
    fbo.end();

    ofSetColor(255, 255, 255, 255);

    fbo.draw(0, 0);
}

void PMRendererColor::setPitch(float p)
{
    pitch = p;
}
void PMRendererColor::setEnergy(float e)
{
    energy = e;
}
