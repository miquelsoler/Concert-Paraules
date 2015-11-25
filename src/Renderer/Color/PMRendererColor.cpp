#include "PMRendererColor.h"


//******************************************************
ofVec3f rgb2xyz(int R,int G,int B)
{
    float r = R / 255.0;
    float g = G / 255.0;
    float b = B / 255.0;
    
    if (r > 0.04045){ r = pow((r + 0.055) / 1.055, 2.4); }
    else { r = r / 12.92; }
    if ( g > 0.04045){ g = pow((g + 0.055) / 1.055, 2.4); }
    else { g = g / 12.92; }
    if (b > 0.04045){ b = pow((b + 0.055) / 1.055, 2.4); }
    else {  b = b / 12.92; }
    
    r = r * 100;
    g = g * 100;
    b = b * 100;
    //Observer. = 2°, Illuminant = D65
    ofVec3f xyz;
    xyz.x = r * 0.4124 + g * 0.3576 + b * 0.1805;
    xyz.y = r * 0.2126 + g * 0.7152 + b * 0.0722;
    xyz.z = r * 0.0193 + g * 0.1192 + b * 0.9505;
    return xyz;
}

ofVec3f xyz2lab(float X,float Y, float Z){
    float x = X / REF_X;
    float y = Y / REF_X;
    float z = Z / REF_X;
    
    if ( x > 0.008856 ) { x = pow( x , .3333333333f ); }
    else { x = ( 7.787 * x ) + ( 16/116.0 ); }
    if ( y > 0.008856 ) { y = pow( y , .3333333333f ); }
    else { y = ( 7.787 * y ) + ( 16/116.0 ); }
    if ( z > 0.008856 ) { z = pow( z , .3333333333f ); }
    else { z = ( 7.787 * z ) + ( 16/116.0 ); }
    
    ofVec3f lab;
    lab.x = ( 116 * y ) - 16;
    lab.y = 500 * ( x - y );
    lab.z = 200 * ( y - z );
    return lab;
}
ofVec3f lab2xyz(float l, float a, float b){
    float y = (l + 16) / 116;
    float x = a / 500 + y;
    float z = y - b / 200;
    
    if ( pow( y , 3 ) > 0.008856 ) { y = pow( y , 3 ); }
    else { y = ( y - 16 / 116 ) / 7.787; }
    if ( pow( x , 3 ) > 0.008856 ) { x = pow( x , 3 ); }
    else { x = ( x - 16 / 116 ) / 7.787; }
    if ( pow( z , 3 ) > 0.008856 ) { z = pow( z , 3 ); }
    else { z = ( z - 16 / 116 ) / 7.787; }
    
    ofVec3f xyz;
    xyz.x = x * REF_X;
    xyz.y = y * REF_Y;
    xyz.z = z * REF_Z;
    return xyz;
}
ofVec3f xyz2rgb(float X,float Y,float Z){
    //X from 0 to  95.047      (Observer = 2°, Illuminant = D65)
    //Y from 0 to 100.000
    //Z from 0 to 108.883
    X = ofClamp(X, 0, 95.047);
    
    float x = X * .01;
    float y = Y * .01;
    float z = Z * .01;
    
    float r = x * 3.2406 + y * -1.5372 + z * -0.4986;
    float g = x * -0.9689 + y * 1.8758 + z * 0.0415;
    float b = x * 0.0557 + y * -0.2040 + z * 1.0570;
    
    if ( r > 0.0031308 ) { r = 1.055 * pow( r , ( 1 / 2.4f ) ) - 0.055; }
    else { r = 12.92 * r; }
    if ( g > 0.0031308 ) { g = 1.055 * pow( g , ( 1 / 2.4f ) ) - 0.055; }
    else { g = 12.92 * g; }
    if ( b > 0.0031308 ) { b = 1.055 * pow( b , ( 1 / 2.4f ) ) - 0.055; }
    else { b = 12.92 * b; }
    
    ofVec3f rgb;
    rgb.x = round( r * 255 );
    rgb.y = round( g * 255 );
    rgb.z = round( b * 255 );
    return rgb;
}
ofVec3f rgb2lab(int R,int G,int B){
    ofVec3f xyz = rgb2xyz(R, G, B);
    return xyz2lab(xyz.x, xyz.y, xyz.z);
}
ofVec3f lab2rgb(int L,int a,int b){
    ofVec3f xyz = lab2xyz(L, a, b);
    return xyz2rgb(xyz.x, xyz.y, xyz.z);
}
//******************************************************


//--------------------------------------------------------------
PMRendererColor::PMRendererColor(unsigned int numInputs) : PMBaseRenderer(RENDERERTYPE_COLOR, numInputs)
{
    audioAnalyzersSettings = &PMSettingsManagerAudioAnalyzers::getInstance();
    dimmBackground = 0.5;
    scanWidth = 3;

    /// GUI
    guiBaseRenderer = new PMUICanvasColorRenderer("COLOR_RENDERER",OFX_UI_FONT_MEDIUM);
    guiBaseRenderer->init(100, 500, 200, 300);
}

//--------------------------------------------------------------
void PMRendererColor::setup()
{
    PMBaseRenderer::setup();
    
    canvasColorRenderer = dynamic_cast<PMUICanvasColorRenderer *> (guiBaseRenderer);
    
    scanX = 0.0;

}

//--------------------------------------------------------------
void PMRendererColor::update()
{
    PMBaseRenderer::update();
    
    //    ofxUIToggleMatrix *toggleMatrix = dynamic_cast<ofxUIToggleMatrix *>(channelToggles);
    scanX = scanX + canvasColorRenderer->getScanSpeedX();

    if(scanX > ofGetWidth())
    {
        scanX = ofGetWidth() - scanX;
    }
}

//--------------------------------------------------------------
void PMRendererColor::drawIntoFBO()
{
    fbo.begin();
    {
        // SMOOTHING AUDIO SHIT
        float deltaPitch = canvasColorRenderer->getDeltaPitch();
        float deltaEnergy = canvasColorRenderer->getDeltaEnergy();

        float pitchSmooth = (deltaPitch)*pitch + (1.0-deltaPitch)*oldPitch;
        float energySmooth = (deltaEnergy)*energy + (1.0-deltaEnergy)*oldEnergy;

        canvasColorRenderer->setSmoothEnergy(energySmooth);
        canvasColorRenderer->setSmoothPitch(pitchSmooth);
        
        switch (canvasColorRenderer->getMode())
        {
            case 1 :
            {
                float pitchL,pitchA,pitchB;
                
                pitchL = ofMap(pitchSmooth,0.0,1.0,0.0   ,100.0,true);
                pitchA = ofMap(pitchSmooth,0.0,0.5,-128.0,128.0,true);
                pitchB = ofMap(pitchSmooth,0.0,0.5,-128.0,128.0,true);

                //pitchB = pow(pitchB,10);
                // convert from lab to rgb
                ofVec3f vcol = lab2rgb(pitchL,pitchA,pitchB);
                ofSetColor(vcol.x , vcol.y , vcol.z ,255);
                
                ofColor c = canvasColorRenderer->getGradientColor(canvasColorRenderer->getGradientId(),pitchSmooth);
                c.a = 255.0 * energySmooth;
                ofSetColor(c);
                
                ofSetCircleResolution(256);
                ofDrawCircle(ofGetWidth()/2,ofGetHeight()/2,(ofGetHeight()/2)*energySmooth);
                
                break;
            }
            case 2 :
            {
                ofSetRectMode(OF_RECTMODE_CENTER);

                float pitchL,pitchA,pitchB;
                
                pitchL = ofMap(pitchSmooth,0.0,1.0,0.0   ,100.0,true);
                pitchA = ofMap(pitchSmooth,0.0,0.5,-128.0,128.0,true);
                pitchB = ofMap(pitchSmooth,0.0,0.5,-128.0,128.0,true);
                
                // convert from lab to rgb
                ofColor c = canvasColorRenderer->getGradientColor(canvasColorRenderer->getGradientId(),pitchSmooth);
                ofSetColor(c);

                ofDrawRectangle(scanX,fbo.getHeight()/2.0,canvasColorRenderer->getScanWidth(),(energySmooth) * ofGetHeight());
                
                ofSetRectMode(OF_RECTMODE_CORNER);
                
                break;
            }
            case 3 :
            {
                ofSetRectMode(OF_RECTMODE_CENTER);
                
                float pitchL,pitchA,pitchB;
                
                pitchL = ofMap(pitchSmooth,0.0,1.0,0.0   ,100.0,true);
                pitchA = ofMap(pitchSmooth,0.0,0.5,-128.0,128.0,true);
                pitchB = ofMap(pitchSmooth,0.0,0.5,-128.0,128.0,true);
                
                // convert from lab to rgb
                ofColor c = canvasColorRenderer->getGradientColor(canvasColorRenderer->getGradientId(),pitchSmooth);
                ofSetColor(c);

                ofDrawRectangle(scanX,fbo.getHeight()/2.0,canvasColorRenderer->getScanWidth(), ofGetHeight());
                
                ofSetRectMode(OF_RECTMODE_CORNER);
                
                break;
            }
            case 4 :
            {
                ofSetRectMode(OF_RECTMODE_CENTER);
                ofColor c = canvasColorRenderer->getGradientColor(canvasColorRenderer->getGradientId(),pitchSmooth);
                c.a = 255.0 * energySmooth;
                ofSetColor(c);
                ofDrawRectangle(scanX,fbo.getHeight()/2.0,canvasColorRenderer->getScanWidth(), ofGetHeight());
                
                ofSetRectMode(OF_RECTMODE_CORNER);
                
                break;
            }
                
                
            default:
                break;
        }

        ofDisableBlendMode();
        
        //update old values
        
        oldPitch = pitchSmooth;
        oldEnergy = energySmooth;

    }
    fbo.end();

    ofSetColor(255, 255, 255, 255);
    
    ofScale(0.75,0.75,0.75);
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


