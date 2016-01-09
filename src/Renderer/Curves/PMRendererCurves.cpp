//
// Created by Miquel Àngel Soler on 16/12/15.
//

#include "PMRendererCurves.h"

static const int NUM_GRADIENT_COLORS = 5;

typedef enum
{
    CURVES_DRIVE = 1,
    CURVES_X = 2,
    CURVES_Y = 3,
    CM_4 = 4,
    CM_5 = 5,
    CM_6 = 6,
    CM_7 = 7,
    CM_8 = 8,
    CM_9 = 9,
    CM_10 = 10,
} CurvesMode;

PMRendererCurves::PMRendererCurves() : PMBaseRenderer(RENDERERTYPE_CURVES)
{
    gui = new PMUICanvasCurvesRenderer(UI_RENDERERTYPE_TYPOGRAPHY, "CURVES_RENDERER",OFX_UI_FONT_MEDIUM);
    gui->init(100, 500);
    myGUI = (PMUICanvasCurvesRenderer *)gui;
}

void PMRendererCurves::setup()
{
    PMBaseRenderer::setup();
    isSilent = true;
    
    gradientPosition = 1 / (2 *float(NUM_GRADIENT_COLORS));
    gradientReverse = false;
    offsetSign = 1;
    
    rebuildPainters();
}

void PMRendererCurves::update()
{
    if (state != RENDERERSTATE_ON) return;
    
    PMBaseRenderer::update(); 

    for(int i=0;i<myGUI->getNumPainters();i++)
    {
        painters[i].update();
    }

//    if (!isSilent)
//    {
//        switch(mode)
//        {
//            case LEFT_RIGHT: { // Left-right movement
//                addOffsetToPosition(myGUI->getSpeed(), 0);
//                break;
//            }
//            case LEFT_RIGHT_NRG: { // Left-right movement speeding via energy
//                addOffsetToPosition(myGUI->getSpeed() * myGUI->getSmoothedEnergy(), 0);
//
//            }
//            case UP_DOWN: { // Up-down movement
//                addOffsetToPosition(0, myGUI->getSpeed());
//                break;
//            }
//            case UP_DOWN_NRG: { // Up-down movement speeding via energy
//                addOffsetToPosition(0, myGUI->getSpeed() * myGUI->getSmoothedEnergy());
//                break;
//            }
//            default: break;
//        }
//    }
//
//
//    if (!isSilent || mode==RM_MOUSE)
//    {
//        for (int i=0; i<numPainters; ++i)
//            painters[i].update();
//    }
}

void PMRendererCurves::drawIntoFBO()
{
    if ((state != RENDERERSTATE_ON) ) return;

    fbo.begin();
    {

        clearFBOBackground(float(gui->getBackgroundColor().r) / 255.0f,float(gui->getBackgroundColor().g) / 255.0f,float(gui->getBackgroundColor().b) / 255.0f,gui->getBackgroundFade());

        for (int i=0; i<myGUI->getNumPainters(); i++)
        {
            painters[i].draw();
        }
    }
    fbo.end();
}

void PMRendererCurves::pitchChanged(pitchParams pitchParams)
{
    PMBaseRenderer::pitchChanged(pitchParams);

    if ((state != RENDERERSTATE_ON) ) return;
//    if (mode == RM_MOUSE) return;

//    if(gui->getSmoothedEnergy()<0.15) return;

//    switch(mode)
//    {
//        case LEFT_RIGHT:
//        case LEFT_RIGHT_NRG:
//        {
//            float y = ofMap(myGUI->getSmoothedPitch(), 0, 1, ofGetHeight()-1, 1, true);
//            setY(int(y));
//            //cout << "-> settingY  = " << y << " __ smooth.pitch = " << myGUI->getSmoothedPitch() << endl;
//             break;
//        }
//        case UP_DOWN:
//        case UP_DOWN_NRG:
//        {
//            float x = ofMap(myGUI->getSmoothedPitch(), 0, 1, ofGetWidth()-1, 1, true);
//            setX(int(x));
//            break;
//        }
//        case PITCH_DRIVE:
//        {
//            int numVertices;
//            bool positive;
//            
//            pitchDrive  = myGUI->getSmoothedPitch()- 0.5f;
//            
//            if(pitchDrive > 0.0) positive = true;
//            else positive = false;
//            
//            pitchDrive = pow(pitchDrive,1/2);
//            
//            if(positive) pitchDrive = pitchDrive;
//            else pitchDrive = - pitchDrive;
//        
//            
//            
//            for (int i=0; i<numPainters; ++i)
//            {
//                vector<ofPoint> points = painters[i].getPoints();
//                int numOfPoints = points.size();
//                ofPolyline p;
//                
//                if(numOfPoints>2)
//                {
//                    // we contrsutct a polyline to calculate it's tangent ...
//                    for(int i=0;i<2;i++)
//                    {
//                        p.addVertex(points[numOfPoints-2+i]);
//                    }
//
//                    pathDirection = p.getTangentAtIndexInterpolated(numOfPoints-1).normalize();
//                    
//                    newPosition = pathDirection * 10.0 ;
//                    newPosition.rotate(2.5*pitchDrive, ofVec3f(0,0,1));
//                    newPosition = (myGUI->getSmoothedEnergy()*newPosition) + points[numOfPoints-1] ;
//                    
//                    // Y
//                    /////
//                    if(newPosition.y < 0)
//                    {
//                        newPosition.y = newPosition.y * -1;
//                        cout << "y<0" << endl;
//                    }
//                    else if(newPosition.y > ofGetHeight())
//                    {
//                        float dif = newPosition.y - ofGetHeight();
//                        newPosition.y = ofGetHeight() - dif;
//                        cout << "y>h" << endl;
//                    }
//
//                    // X
//                    /////
//                    if(newPosition.x < 0)
//                    {
//                        newPosition.x = newPosition.x * -1;
//                        cout << "x<0" << endl;
//                    }
//                    else if(newPosition.x > ofGetWidth())
//                    {
//                        float dif = newPosition.x - ofGetWidth();
//                        newPosition.x = ofGetWidth() - dif;
//                        cout << "x>w" << endl;
//                    }
//
//                    //newPosition = ofVec3f(points[numOfPoints-1] + ( pathDirection * 20 ) );
////                    newPosition.rotate(2.5*pitchDrive, ofVec3f(0,0,1));
//                    
//                    painters[i].setPosition(newPosition.x,newPosition.y);
//                }
//            }
//            break;
//        }
//            
//        case PITCH_RANDOM: { // Random position every few pitch updates
////            float currentTime = ofGetElapsedTimef();
////            if (currentTime - pitchLastTime > 1)
////            {
//            // OPCIO 1
////                pitchLastTime = currentTime;
////                float m3offsetX = ofMap(myGUI->getSmoothedPitch(), 0, 1, -15, 15);
////                float yOffset = ofMap(myGUI->getSmoothedPitch(), 0, 1, -15, 15);
////                cout << "Offset: " << m3offsetX << "-" << yOffset << endl;
////                addOffsetToPosition(m3offsetX, yOffset);
//
//            // OPCIO 2
////                addOffsetToPosition(ofRandom(-15,15), ofRandom(-15,15));
//
//            // OPCIO 3
//
//            if (fabs(lastPitch - myGUI->getSmoothedPitch()) > 0.2)
//            {
//                float offset;
//                float rndNumber2 = ofRandom(0, 1);
//                if (rndNumber2 < 0.5)
//                    offset = ofMap(myGUI->getSmoothedPitch(), 0, 1, 0, 15);
//                else
//                    offset = ofMap(myGUI->getSmoothedPitch(), 0, 1, -15, 0);
//
//                float rndNumber1 = ofRandom(0, 1);
//                if (rndNumber1 < 0.5)
//                {
//                    m3offsetX = offset;
//                    m3offsetY = offset/10;
//                }
//                else
//                {
//                    m3offsetX = offset/10;
//                    m3offsetY = offset;
//                }
//
//                addOffsetToPosition(m3offsetX, m3offsetY);
//            }
//            else
//            {
//                float increment = 0.2;
//                if (fabs(m3offsetX) > fabs(m3offsetY))
//                {
//                    if (m3offsetX < 0)
//                        m3offsetX += increment;
//                    else
//                        m3offsetX -= increment;
//                }
//                else
//                {
//                    if (m3offsetY < 0)
//                        m3offsetY += increment;
//                    else
//                        m3offsetY -= increment;
//                }
//                cout << "(oX, oy) = ("<< m3offsetX << "; " << m3offsetY << ")" << endl;
//                addOffsetToPosition(m3offsetX, m3offsetY);
//            }
//
//
////            }
//            break;
//            
//        }
//    }

}

void PMRendererCurves::energyChanged(energyParams energyParams)
{
    PMBaseRenderer::energyChanged(energyParams);

    if ((state != RENDERERSTATE_ON) ) return;

//    if (mode == RM_MOUSE) return;
//
//    float size = ofMap(myGUI->getSmoothedEnergy(), 0, 1, 1, myGUI->getStrokeWidth());
//    for (int i=0; i<numPainters; ++i)
//        painters[i].setSize((unsigned int)size);
}

void PMRendererCurves::silenceStateChanged(silenceParams &silenceParams)
{
    PMBaseRenderer::silenceStateChanged(silenceParams);

//    if (myGUI->getMode() == RM_MOUSE) return;
//
//    isSilent = silenceParams.isSilent;
//
//    if (state != RENDERERSTATE_ON)
//    {
////        strokeEnded();
//        return;
//    }

/*
    if (!(silenceParams.isSilent))
        strokeStarted();
    else
        strokeEnded();
*/
}

// TODO: Remove mouse events code once audio events are working

void PMRendererCurves::mouseDragged(int x, int y, int button)
{
//    if (mode != RM_MOUSE) return;
//
//    if (button == OF_MOUSE_BUTTON_1)
//        setPosition(x, y);
}

void PMRendererCurves::mousePressed(int x, int y, int button)
{
//    if (mode != RM_MOUSE) return;
//
//    if (button == OF_MOUSE_BUTTON_1)
//    {
//        setPosition(x, y);
//    }
}

void PMRendererCurves::mouseReleased(int x, int y, int button)
{
//    if (mode != RM_MOUSE) return;
}

void PMRendererCurves::switchStateOnOff()
{
    PMBaseRenderer::switchStateOnOff();
    if (state == RENDERERSTATE_OFF)
    {
//        rebuildPainters();
    }
}

void PMRendererCurves::rebuildPainters()
{
    painters.clear();
    
    for (int i=0; i<myGUI->getNumPainters(); ++i)
    {
        PMCurvesPainter painter = PMCurvesPainter(this);
        painters.push_back(painter);
    }
    
    for (int i=0; i<myGUI->getNumPainters(); ++i)
    {
        painters[i].setup();
    }
}
