#include "PMRendererColor.h"


//******************************************************
ofVec3f rgb2xyz(int R, int G, int B)
{
    float r = R / 255.0;
    float g = G / 255.0;
    float b = B / 255.0;

    if (r > 0.04045) {r = pow((r + 0.055) / 1.055, 2.4);}
    else {r = r / 12.92;}
    if (g > 0.04045) {g = pow((g + 0.055) / 1.055, 2.4);}
    else {g = g / 12.92;}
    if (b > 0.04045) {b = pow((b + 0.055) / 1.055, 2.4);}
    else {b = b / 12.92;}

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

ofVec3f xyz2lab(float X, float Y, float Z)
{
    float x = X / REF_X;
    float y = Y / REF_X;
    float z = Z / REF_X;

    if (x > 0.008856) {x = pow(x, .3333333333f);}
    else {x = (7.787 * x) + (16 / 116.0);}
    if (y > 0.008856) {y = pow(y, .3333333333f);}
    else {y = (7.787 * y) + (16 / 116.0);}
    if (z > 0.008856) {z = pow(z, .3333333333f);}
    else {z = (7.787 * z) + (16 / 116.0);}

    ofVec3f lab;
    lab.x = (116 * y) - 16;
    lab.y = 500 * (x - y);
    lab.z = 200 * (y - z);
    return lab;
}

ofVec3f lab2xyz(float l, float a, float b)
{
    float y = (l + 16) / 116;
    float x = a / 500 + y;
    float z = y - b / 200;

    if (pow(y, 3) > 0.008856) {y = pow(y, 3);}
    else {y = (y - 16 / 116) / 7.787;}
    if (pow(x, 3) > 0.008856) {x = pow(x, 3);}
    else {x = (x - 16 / 116) / 7.787;}
    if (pow(z, 3) > 0.008856) {z = pow(z, 3);}
    else {z = (z - 16 / 116) / 7.787;}

    ofVec3f xyz;
    xyz.x = x * REF_X;
    xyz.y = y * REF_Y;
    xyz.z = z * REF_Z;
    return xyz;
}

ofVec3f xyz2rgb(float X, float Y, float Z)
{
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

    if (r > 0.0031308) {r = 1.055 * pow(r, (1 / 2.4f)) - 0.055;}
    else {r = 12.92 * r;}
    if (g > 0.0031308) {g = 1.055 * pow(g, (1 / 2.4f)) - 0.055;}
    else {g = 12.92 * g;}
    if (b > 0.0031308) {b = 1.055 * pow(b, (1 / 2.4f)) - 0.055;}
    else {b = 12.92 * b;}

    ofVec3f rgb;
    rgb.x = round(r * 255);
    rgb.y = round(g * 255);
    rgb.z = round(b * 255);
    return rgb;
}

ofVec3f rgb2lab(int R, int G, int B)
{
    ofVec3f xyz = rgb2xyz(R, G, B);
    return xyz2lab(xyz.x, xyz.y, xyz.z);
}

ofVec3f lab2rgb(int L, int a, int b)
{
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
        gui = new PMUICanvasColorRenderer(UI_RENDERERTYPE_TYPOGRAPHY, "COLOR_RENDERER", OFX_UI_FONT_MEDIUM);
        gui->init(100, 500, 200, 300);
    }

    myGUI = (PMUICanvasColorRenderer *) gui;

    // NEW STUFF
    drawingHeight = 50 + (ofRandomuf() * ofGetHeight() / 4);
    drawingPos = 0; //ofRandomuf()*ofGetHeight();
    whichSequentialBand = -1;

}

//--------------------------------------------------------------
void PMRendererColor::setup()
{
    PMBaseRenderer::setup();
    startNewBand();
}

//--------------------------------------------------------------
void PMRendererColor::startNewBand()
{

    bool beRandom = myGUI->getIsRandom();
    bool upToDown = myGUI->getUpToDown();
    bool leftToRight = myGUI->getLeftToRight();

    int resolution;


    if (beRandom) {
        // IS RANDOM = WE DRAW BASED ON PROBABILITYS
        float newProbabilityFull = ofRandomuf();
        float newProbabilityHalf = ofRandomuf();
        float newProbabilityHorizVert = ofRandomuf();

        bool newIsFull;
        bool newIsHalf;
        int whichFullBand;

        // Horizontal / Vertical orientation
        if (newProbabilityHorizVert < myGUI->getHorizVertProbability()) {
            // NEXT BAND DRAWING VERTICAL
            myGUI->setDrawHorizontal(false);
            resolution = myGUI->getResolutionX();
            drawingHeight = int(fbo.getWidth() / resolution);
            if (upToDown) scanX = 0;
            else scanX = ofGetHeight();
            cout << "NEW IS VERTICAL ||||||||||||| " << endl;
        }
        else {
            // NEXT BAND DRAWING HORIZONTAL
            myGUI->setDrawHorizontal(true);
            resolution = myGUI->getResolutionY();
            drawingHeight = int(fbo.getHeight() / resolution);
            if (leftToRight) scanX = 0;
            else scanX = ofGetWidth();
            cout << "NEW IS HORIZONTAL ---------------" << endl;
        }



        // which full band position to draw next
        whichFullBand = int(ceil(ofRandom(0, resolution)));

        // ARE WE IN A FULL BAND MODE ?
        if (newProbabilityFull > (1.0 - myGUI->getFullProbability())) newIsFull = true;
        else newIsFull = false;

        drawingPos = (whichFullBand - 1) * drawingHeight;

        if (newIsFull) {
            // do nothing
            //        cout << "New Prob. full : " << newProbabilityFull << " \\ GUI Full Prob. : " << myGUI->getFullProbability() << " Half :  " << myGUI->getHalfProbability() <<  endl;
            //        cout << "Band is Full : Resolution = " << resolution << " WhichFullBand : " << whichFullBand << " Height : " << drawingHeight << " Pos : " << drawingPos << endl;
        }
        else {
            //        cout << "New Prob. full : " << newProbabilityFull << " \\ GUI Full Prob. : " << myGUI->getFullProbability() << " Half : " << myGUI->getHalfProbability() << endl;
            //        cout << "Band is NOT FULL : Resolution = " << resolution << " WhichFullBand : " << whichFullBand << " Height : " << drawingHeight << " Pos : " << drawingPos << endl;
            // it's not a full band so we use half of it's width
            drawingHeight = drawingHeight / 2;

            // ... so we want to know which half is it going (+/-)
            if (newProbabilityHalf > (1.0 - myGUI->getHalfProbability())) newIsHalf = true;
            else newIsHalf = false;

            // FIRST OR SECOND BAND ?
            if (newIsHalf) {
                // do nothing
            }
            else {
                drawingPos = drawingPos + drawingHeight;
            }
        }

    }
    else {
        bool isDrawHorizontal = myGUI->getDrawHorizontal();

        if (isDrawHorizontal) {
            resolution = myGUI->getResolutionY();
            drawingHeight = int(fbo.getHeight() / resolution);

            if (upToDown) {
                whichSequentialBand = whichSequentialBand + 1;
                if (whichSequentialBand > (resolution - 1)) whichSequentialBand = 0;
                drawingPos = (whichSequentialBand) * drawingHeight;
            }
            else {
                whichSequentialBand = whichSequentialBand - 1;
                if (whichSequentialBand < 0) whichSequentialBand = resolution - 1;
                drawingPos = (whichSequentialBand) * drawingHeight;
            }
        }
        else {
            // NEW VERTICAL BAND

            resolution = myGUI->getResolutionX();
            drawingHeight = int(fbo.getWidth() / resolution);

            if (leftToRight) {
                whichSequentialBand = whichSequentialBand + 1;
                if (whichSequentialBand > (resolution - 1)) whichSequentialBand = 0;
                drawingPos = (whichSequentialBand) * drawingHeight;
            }
            else {
                whichSequentialBand = whichSequentialBand - 1;
                if (whichSequentialBand < 0) whichSequentialBand = resolution - 1;
                drawingPos = (whichSequentialBand) * drawingHeight;
            }

        }



//        cout << "SEQ NEW BAND : Height : " << drawingHeight << " __ Resolution : " << resolution << "__ WhichSeqBand : " << whichSequentialBand << " __ ScanX = " << scanX << " __ drawPos = " << drawingPos  << endl;
    }

}

//--------------------------------------------------------------
void PMRendererColor::update()
{

    if (state != RENDERERSTATE_ON) return;

//    float ini = ofGetElapsedTimef();

    //PMBaseRenderer::update();



    // STOP ON SILENCE ?
    bool updateScan = false;

    if ((!myGUI->getStopOnSilence())) {
        // STOP ON SILENCE = FALSE
        updateScan = true;
    }
    else {
        // STOP ON SILENCE = TRUE
        if (!isSilent) {
            updateScan = true;
        }
    }

    // DETERMINE WHEN TO GENERATE A NEW BAND ...
    bool upToDown = myGUI->getUpToDown();
    bool leftToRight = myGUI->getLeftToRight();
    bool isDrawHorizontal = myGUI->getDrawHorizontal();
    int limit;

    // DETERMINE THE LIMIT VALUE DEPENDING ON H or V
    if (isDrawHorizontal) {
        // Draw HORIZONTAL
        limit = ofGetWidth();

        if (leftToRight) {
            if (updateScan) {
                scanX = scanX + int(myGUI->getScanWidth()); //+ int(myGUI->getScanWidth()) -1 ;
            }

            if (scanX > (limit + int(myGUI->getScanWidth()))) {
                scanX = 0;
                startNewBand();
            }
        }
        else {
            if (updateScan) {
                scanX = scanX - int(myGUI->getScanWidth());//- int(myGUI->getScanWidth()) -1 ;
            }

            if (scanX < -int(myGUI->getScanWidth())) {
                scanX = ofGetWidth();
                startNewBand();
            }

        }
    }
    else {
        // Draw VERTICAL
        limit = ofGetHeight();

        if (upToDown) {
            // VERTICAL Up -> Down
            if (updateScan) {
                scanX = scanX + int(myGUI->getScanWidth()); // + int(myGUI->getScanWidth()) -1 ;
            }

            if (scanX > (limit + int(myGUI->getScanWidth()))) {
                scanX = 0;
                startNewBand();

            }
        }
        else {
            // VERTICAL Down -> Up
            if (updateScan) {
                scanX = scanX - int(myGUI->getScanWidth()); // - int(myGUI->getScanWidth()) -1 ;
            }

            if (scanX < -int(myGUI->getScanWidth())) {
                scanX = ofGetHeight();
                startNewBand();
                //cout << "SEQ NEW BAND : Height : " << drawingHeight  << " __ ScanX = " << scanX << " __ drawPos = " << drawingPos  << endl;

            }


        }


    }

//    cout << "update duration = " << ofGetElapsedTimef() - ini << endl;

}

//--------------------------------------------------------------
void PMRendererColor::drawIntoFBO()
{
    if (state != RENDERERSTATE_ON) return;


    fbo.begin();
    {
        clearFBOBackground(float(gui->getBackgroundColor().r) / 255.0f, float(gui->getBackgroundColor().g) / 255.0f, float(gui->getBackgroundColor().b) / 255.0f, gui->getBackgroundFade());

        float pitchSmooth = gui->getSmoothedPitch();
        float energySmooth = gui->getSmoothedEnergy();

        switch (myGUI->getMode()) {
            case 1 : {
                float pitchL, pitchA, pitchB;

                pitchL = ofMap(pitchSmooth, 0.0, 1.0, 0.0, 100.0, true);
                pitchA = ofMap(pitchSmooth, 0.0, 0.5, -128.0f, 128.0, true);
                pitchB = ofMap(pitchSmooth, 0.0, 0.5, -128.0f, 128.0, true);

                //pitchB = pow(pitchB,10);
                // convert from lab to rgb
                ofVec3f vcol = lab2rgb(pitchL, pitchA, pitchB);
                ofSetColor(vcol.x, vcol.y, vcol.z, 255);

                ofColor c = myGUI->getGradientColor(myGUI->getGradientId(), pitchSmooth);
                c.a = 255.0 * energySmooth;
                ofSetColor(c);

                ofSetCircleResolution(256);
                ofDrawCircle(ofGetWidth() / 2, ofGetHeight() / 2, (ofGetHeight() / 2) * energySmooth);

                break;
            }
            case 2 : {
                ofSetRectMode(OF_RECTMODE_CENTER);

                float pitchL, pitchA, pitchB;

                pitchL = ofMap(pitchSmooth, 0.0, 1.0, 0.0, 100.0, true);
                pitchA = ofMap(pitchSmooth, 0.0, 0.5, -128.0f, 128.0, true);
                pitchB = ofMap(pitchSmooth, 0.0, 0.5, -128.0f, 128.0, true);

                // convert from lab to rgb
                ofColor c = myGUI->getGradientColor(myGUI->getGradientId(), pitchSmooth);
                ofSetColor(c);

                ofDrawRectangle(scanX, fbo.getHeight() / 2.0f, myGUI->getScanWidth(), (energySmooth) * ofGetHeight());

                ofSetRectMode(OF_RECTMODE_CORNER);

                break;
            }
            case 3 : {
                ofSetRectMode(OF_RECTMODE_CENTER);

                float pitchL, pitchA, pitchB;

                pitchL = ofMap(pitchSmooth, 0.0, 1.0, 0.0, 100.0, true);
                pitchA = ofMap(pitchSmooth, 0.0, 0.5, -128.0f, 128.0, true);
                pitchB = ofMap(pitchSmooth, 0.0, 0.5, -128.0f, 128.0, true);

                // convert from lab to rgb
                ofColor c = myGUI->getGradientColor(myGUI->getGradientId(), pitchSmooth);
                ofSetColor(c);

                ofDrawRectangle(scanX, fbo.getHeight() / 2.0, myGUI->getScanWidth(), ofGetHeight());

                ofSetRectMode(OF_RECTMODE_CORNER);

                break;
            }
            case 4 : {
                ofSetRectMode(OF_RECTMODE_CENTER);
                ofColor c = myGUI->getGradientColor(myGUI->getGradientId(), pitchSmooth);
                c.a = 255.0 * energySmooth;
                ofSetColor(c);
                ofDrawRectangle(scanX, fbo.getHeight() / 2.0, myGUI->getScanWidth(), ofGetHeight());

                ofSetRectMode(OF_RECTMODE_CORNER);

                break;
            }
            case 5 : {
                // color
                ofColor c = myGUI->getGradientColor(myGUI->getGradientId(), pitchSmooth);
                ofSetColor(c);
                bool isDrawHorizontal = myGUI->getDrawHorizontal();

                // shape
                if ((!isSilent)) {
                    ofSetRectMode(OF_RECTMODE_CORNER);
                    if (isDrawHorizontal) {
                        ofDrawRectangle(scanX, drawingPos, myGUI->getScanWidth(), drawingHeight);
//                        cout << "Drawing Horizontal!!";
                    }
                    else {
                        ofDrawRectangle(drawingPos, scanX, drawingHeight, myGUI->getScanWidth());
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

    //cout << "Drawing...  Pos = " << drawingPos << " :::: whichSeqBand ? = " << whichSequentialBand << endl;

// Miquel: commented because it's already done in PMBaseRenderer::draw()
//    fbo.draw(0, 0);
}

//--------------------------------------------------------------------------------
void PMRendererColor::keyPressed(ofKeyEventArgs &eventArgs)
{
    if (state == RENDERERSTATE_ON) {
    }

}

//--------------------------------------------------------------------------------
void PMRendererColor::keyReleased(ofKeyEventArgs &eventArgs)
{
    if (state == RENDERERSTATE_ON) {
        int key = eventArgs.key;

        int firstAsciiCode = (int) '1';
        int lastAsciiCode = (int) '9';

        if ((key > firstAsciiCode) || (key < lastAsciiCode)) {
            clear();
            return;
        }
    }
}


//--------------------------------------------------------------------------------
void PMRendererColor::clear()
{
    PMBaseRenderer::clear();

    startNewBand();

    if (!(myGUI->getDrawHorizontal()) && !(myGUI->getLeftToRight())) {
        drawingPos = ofGetWidth();
        whichSequentialBand = myGUI->getResolutionX() - 1;
        cout << "A :: " << endl;
    }
    else if (myGUI->getDrawHorizontal() && (myGUI->getLeftToRight())) {
        drawingPos = 0;
        whichSequentialBand = 0;
        cout << "B :: " << endl;
    }
    scanX = 0;

    cout << "ScanX = " << scanX << " ___ D Pos = " << drawingPos << endl;

}
