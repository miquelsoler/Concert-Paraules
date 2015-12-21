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
PMRendererColor::PMRendererColor() : PMBaseRenderer(RENDERERTYPE_COLOR)
{
//    dimmBackground = 0.5;
    scanWidth = 3;

    // GUI
    {
        gui = new PMUICanvasColorRenderer(UI_RENDERERTYPE_TYPOGRAPHY, "COLOR_RENDERER",OFX_UI_FONT_MEDIUM);
        gui->init(100, 500, 200, 300);
        
    }
    
    // NEW STUFF
    drawingHorizontal = true;
    drawingHeight = 50 + (ofRandomuf()*ofGetHeight()/4);
    drawingPos = ofRandomuf()*ofGetHeight();

    myGUI = (PMUICanvasColorRenderer *)gui;
    ofAddListener(ofEvents().keyPressed, this, &PMRendererColor::keyPressed);
}

//--------------------------------------------------------------
void PMRendererColor::setup()
{
    PMBaseRenderer::setup();
    
    ofAddListener(ofEvents().keyPressed, this, &PMRendererColor::keyPressed);

    startNewBand();
}

//--------------------------------------------------------------
void PMRendererColor::startNewBand()
{
    scanX = 0;

    bool beRandom = myGUI->getIsRandom();
    
    if(beRandom)
    {
        // IS RANDOM = WE DRAW BASED ON PROBABILITYS
        float newProbabilityFull = ofRandomuf();
        float newProbabilityHalf = ofRandomuf();
        float newProbabilityHorizVert = ofRandomuf();
        
        bool newIsFull;
        bool newIsHalf;
        int whichFullBand;
        int resolution;
        
        // Horizontal / Vertical orientation
        if(newProbabilityHorizVert < myGUI->getHorizVertProbability())
        {
            drawingHorizontal = false;
        }
        else
        {
            drawingHorizontal = true;
        }
        
        
        // we a creating a full new band ... so height is maximum it can depending on resolution and orientation
        if(drawingHorizontal)
        {
            resolution = myGUI->getResolutionY();
            drawingHeight = int(fbo.getHeight()/resolution);
            //        cout << " NEW IS ----- HORIZONTAL !!" << endl;
        }
        else
        {
            resolution = myGUI->getResolutionX();
            drawingHeight = int(fbo.getWidth()/resolution);
            //        cout << " NEW IS ||||||| VERTICAL !! " << myGUI->getResolutionX() << endl;
        }
        
        // which full band position to draw next
        whichFullBand = int(ceil( ofRandom(0,resolution ) ) );
        
        // ARE WE IN A FULL BAND MODE ?
        if(newProbabilityFull>(1.0-myGUI->getFullProbability())) newIsFull=true;
        else newIsFull=false;
        
        drawingPos = (whichFullBand-1) * drawingHeight;
        
        if(newIsFull)
        {
            // do nothing
            //        cout << "New Prob. full : " << newProbabilityFull << " \\ GUI Full Prob. : " << myGUI->getFullProbability() << " Half :  " << myGUI->getHalfProbability() <<  endl;
            //        cout << "Band is Full : Resolution = " << resolution << " WhichFullBand : " << whichFullBand << " Height : " << drawingHeight << " Pos : " << drawingPos << endl;
        }
        else
        {
            //        cout << "New Prob. full : " << newProbabilityFull << " \\ GUI Full Prob. : " << myGUI->getFullProbability() << " Half : " << myGUI->getHalfProbability() << endl;
            //        cout << "Band is NOT FULL : Resolution = " << resolution << " WhichFullBand : " << whichFullBand << " Height : " << drawingHeight << " Pos : " << drawingPos << endl;
            // it's not a full band so we use half of it's width
            drawingHeight = drawingHeight/2;
            
            // ... so we want to know which half is it going (+/-)
            if(newProbabilityHalf>(1.0-myGUI->getHalfProbability())) newIsHalf=true;
            else newIsHalf=false;
            
            // FIRST OR SECOND BAND ?
            if(newIsHalf)
            {
                // do nothing
            }
            else
            {
                drawingPos = drawingPos + drawingHeight;
            }
        }
       
    }
    else
    {
        // NOT RANDOM ... SO SEQUENTIAL !!
        
        
    }
    
}

//--------------------------------------------------------------
void PMRendererColor::update()
{
    if (state != RENDERERSTATE_ON) return;
    
    PMBaseRenderer::update();

    
    
    //ofxUIToggleMatrix *toggleMatrix = dynamic_cast<ofxUIToggleMatrix *>(channelToggles);
    if((!myGUI->getStopOnSilence()))
    {
        // STOP ON SILENCE = FALSE
        scanX = scanX + int(myGUI->getScanSpeedX()) + int(myGUI->getScanWidth()) -1 ;
    }
    else
    {
        // STOP ON SILENCE = TRUE
        if( !isSilent )
        {
            scanX = scanX + int(myGUI->getScanSpeedX()) + int(myGUI->getScanWidth()) -1 ;
        }
        else
        {
            
        }
    }
    if(drawingHorizontal)
    {        
        if(scanX > ofGetWidth())
        {
            startNewBand();
//cout << "scanX : " << scanX << " // pos " << drawingPos << " // Height " << drawingHeight << endl;
            // we're at the end of the screen ! go back !!
//            scanX = 0;
//            float luck = ofRandomf();
//            bool doTurn;
//            if(luck>=0.0) doTurn = true;
//            else doTurn = false;
//            bool doTurn=true;
//            
//            
//            if (doTurn)
//            {
//                drawingHorizontal=false;
//                // change direction
//                //drawingHeight = 50 + (ofRandomuf()*ofGetWidth()/4);
//                drawingPos = ofRandomuf()*ofGetWidth();
//                
//                startNewBand();
//            }
//            else
//            {
//                // change direction
//                drawingHeight = 50 + (ofRandomuf()*ofGetHeight()/4);
//                drawingPos = ofRandomuf()*ofGetHeight();
//            }
        }
    }
    else
    {
        // we're drawing vertical
        if(scanX > ofGetHeight())
        {
            startNewBand();
//            cout << "scanX : " << scanX << " // pos " << drawingPos << " // Height " << drawingHeight << endl;
//
//            scanX = 0;
//            
//            bool doTurn;
//            if(ofRandomf()>=0.0) doTurn = true;
//            else doTurn = false;
//            
//            if (doTurn)
//            {
//                // change direction
//                drawingHorizontal = true;
//                drawingHeight = 50 + (ofRandomuf()*ofGetHeight()/4);
//                drawingPos = ofRandomuf()*ofGetHeight();
//            }
//            else
//            {
//                // change direction
//                drawingHeight = 50 + (ofRandomuf()*ofGetWidth()/4);
//                drawingPos = ofRandomuf()*ofGetWidth();
//            }
        }
    }
}

//--------------------------------------------------------------
void PMRendererColor::drawIntoFBO()
{
    if (state != RENDERERSTATE_ON) return;

    PMUICanvasColorRenderer *myGUI = (PMUICanvasColorRenderer *)gui;

    fbo.begin();
    {
        float pitchSmooth = gui->getSmoothedPitch();
        float energySmooth = gui->getSmoothedEnergy();
        
        switch (myGUI->getMode())
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
                
                ofColor c = myGUI->getGradientColor(myGUI->getGradientId(),pitchSmooth);
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
                ofColor c = myGUI->getGradientColor(myGUI->getGradientId(),pitchSmooth);
                ofSetColor(c);

                ofDrawRectangle(scanX,fbo.getHeight()/2.0,myGUI->getScanWidth(),(energySmooth) * ofGetHeight());
                
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
                ofColor c = myGUI->getGradientColor(myGUI->getGradientId(),pitchSmooth);
                ofSetColor(c);

                ofDrawRectangle(scanX,fbo.getHeight()/2.0,myGUI->getScanWidth(), ofGetHeight());
                
                ofSetRectMode(OF_RECTMODE_CORNER);
                
                break;
            }
            case 4 :
            {
                ofSetRectMode(OF_RECTMODE_CENTER);
                ofColor c = myGUI->getGradientColor(myGUI->getGradientId(),pitchSmooth);
                c.a = 255.0 * energySmooth;
                ofSetColor(c);
                ofDrawRectangle(scanX,fbo.getHeight()/2.0,myGUI->getScanWidth(), ofGetHeight());
                
                ofSetRectMode(OF_RECTMODE_CORNER);
                
                break;
            }
            case 5 :
            {
                // color
                ofColor c = myGUI->getGradientColor(myGUI->getGradientId(),pitchSmooth);
                ofSetColor(c);
                
                // shape
                if((!isSilent))
                {
                    ofSetRectMode(OF_RECTMODE_CORNER);
                    if(drawingHorizontal)
                    {
                        ofDrawRectangle(scanX,drawingPos,myGUI->getScanWidth(), drawingHeight);
//                        cout << "Drawing Horizontal!!";
                    }
                    else
                    {
                        ofDrawRectangle(drawingPos,scanX,drawingHeight,myGUI->getScanWidth());
//                        cout << "Drawing Vertical!!";
                    }
                    ofSetRectMode(OF_RECTMODE_CORNER);
                }
                
//                cout << "scanX : " << scanX << " // pos " << drawingPos << " // Height " << drawingHeight << endl;
                
                break;
            }
            default:
                break;
        }

        ofDisableBlendMode();
        
        //update old values
        
        //oldPitch = pitchSmooth;
        //oldEnergy = energySmooth;
    }
    fbo.end();

    ofSetColor(255, 255, 255, 255);
    
    ofScale(0.75,0.75,0.75);
// Miquel: commented because it's already done in PMBaseRenderer::draw()
//    fbo.draw(0, 0);
}
//--------------------------------------------------------------------------------
void PMRendererColor::keyPressed ( ofKeyEventArgs& eventArgs )
{
    if (eventArgs.key == 'q')
    {
    }
}
