//
// Created by Miquel Àngel Soler on 16/12/15.
//

#include "PMRendererRibbon.h"

ofVec3f pathDirection,newPosition;

static const int POS_MARGIN = 1;
static const int NUM_GRADIENT_COLORS = 5;

typedef enum
{
    LEFT_RIGHT = 1,
    LEFT_RIGHT_NRG = 2,
    UP_DOWN = 3,
    UP_DOWN_NRG = 4,
    PITCH_RANDOM = 5,
    PITCH_DRIVE = 6,
    RM_7 = 7,
    RM_8 = 8,
    RM_9 = 9,
    RM_MOUSE = 10,
} RibbonMode;

PMRendererRibbon::PMRendererRibbon() : PMBaseRenderer(RENDERERTYPE_RIBBON)
{
    gui = new PMUICanvasRibbonRenderer(UI_RENDERERTYPE_TYPOGRAPHY, "RIBBON_RENDERER",OFX_UI_FONT_MEDIUM);
    gui->init(100, 500);
    myGUI = (PMUICanvasRibbonRenderer *)gui;

    xMin = POS_MARGIN;
    xMax = ofGetWidth() - POS_MARGIN - 1;
    yMin = POS_MARGIN;
    yMax = ofGetHeight() - POS_MARGIN - 1;
}

void PMRendererRibbon::setup()
{
    PMBaseRenderer::setup();

    numPainters = 1;// myGUI->getNumPainters();
    strokeWidth = myGUI->getStrokeWidth();
    ribbonColorR = (unsigned int)(myGUI->getRibbonColor().r);
    ribbonColorG = (unsigned int)(myGUI->getRibbonColor().g);
    ribbonColorB = (unsigned int)(myGUI->getRibbonColor().b);
    divisions = myGUI->getDivisions();

    rebuildPainters();
//    strokeStarted();

    isSilent = true;
    gradientPosition = 1 / (2 *float(NUM_GRADIENT_COLORS));
    gradientReverse = false;
    offsetSign = 1;
}

void PMRendererRibbon::update()
{
    if (state != RENDERERSTATE_ON) return;

    float ini = ofGetElapsedTimef();
    
    PMBaseRenderer::update(); 

    getGUIData();

    if (!isSilent)
    {
        switch(mode)
        {
            case LEFT_RIGHT: { // Left-right movement
                addOffsetToPosition(myGUI->getSpeed(), 0);
                break;
            }
            case LEFT_RIGHT_NRG: { // Left-right movement speeding via energy
                addOffsetToPosition(myGUI->getSpeed() * myGUI->getSmoothedEnergy(), 0);

            }
            case UP_DOWN: { // Up-down movement
                addOffsetToPosition(0, myGUI->getSpeed());
                break;
            }
            case UP_DOWN_NRG: { // Up-down movement speeding via energy
                addOffsetToPosition(0, myGUI->getSpeed() * myGUI->getSmoothedEnergy());
                break;
            }
            default: break;
        }
    }

//    if (!isInStroke) return;

    if (!isSilent || mode==RM_MOUSE)
    {
        for (int i=0; i<numPainters; ++i)
            painters[i].update();
    }
}

void PMRendererRibbon::drawIntoFBO()
{
    if ((state != RENDERERSTATE_ON) ) return;

    fbo.begin();
    {

        clearFBOBackground(float(gui->getBackgroundColor().r) / 255.0f,float(gui->getBackgroundColor().g) / 255.0f,float(gui->getBackgroundColor().b) / 255.0f,gui->getBackgroundFade());

        for (int i=0; i<numPainters; ++i)
            painters[i].draw();
    }
    fbo.end();
}

void PMRendererRibbon::rebuildPainters()
{
    painters.clear();

    ofColor ribbonColor(ribbonColorR, ribbonColorG, ribbonColorB, 255);
    float dx = ofGetWidth() / 2;
    float dy = ofGetHeight() / 2;

    float ease = 0.6;
    for (int i=0; i<numPainters; ++i)
    {
        //float ease = myGUI->getEase();
        ease = ofRandom(0.0f, 1.0f) * 0.2f + 0.6f;

        PMRibbonPainter painter = PMRibbonPainter(ribbonColor, dx, dy, divisions, ease, strokeWidth, myGUI);
        painters.push_back(painter);
    }
//    lastEase = ease

    isInStroke = false;

    PMPainterOrigin origin;
    switch(mode)
    {
        case LEFT_RIGHT:
        case LEFT_RIGHT_NRG:
        {
            origin = PAINTER_LEFT;
            break;
        }
        case UP_DOWN:
        case UP_DOWN_NRG:
        {
            origin = PAINTER_UP;
            break;
        }
        case PITCH_RANDOM:  origin = PAINTER_CENTER; break;
            
        default:            origin = PAINTER_LEFT; break;
    }

    for (int i=0; i<numPainters; ++i)
    {
        painters[i].setup();
        painters[i].setOrigin(origin);
    }
}

void PMRendererRibbon::setPosition(int x, int y)
{
    for (int i=0; i<numPainters; ++i)
        painters[i].setPosition(x, y);
}

void PMRendererRibbon::setX(int x)
{
    for (int i=0; i<numPainters; ++i)
        painters[i].setX(x);
}

void PMRendererRibbon::setY(int y)
{
    for (int i=0; i<numPainters; ++i)
    {
        painters[i].setY(y);        
    }
}

void PMRendererRibbon::strokeStarted()
{
    isInStroke = true;
}

void PMRendererRibbon::strokeEnded()
{
    isInStroke = false;
    for (int i=0; i<numPainters; ++i)
        painters[i].clear();
}

void PMRendererRibbon::pitchChanged(pitchParams pitchParams)
{
    PMBaseRenderer::pitchChanged(pitchParams);

    if ((state != RENDERERSTATE_ON) ) return;
    if (mode == RM_MOUSE) return;

//    if(gui->getSmoothedEnergy()<0.15) return;

    switch(mode)
    {
        case LEFT_RIGHT:
        case LEFT_RIGHT_NRG:
        {
            float y = ofMap(myGUI->getSmoothedPitch(), 0, 1, ofGetHeight()-1, 1, true);
            setY(int(y));
            break;
        }
        case UP_DOWN:
        case UP_DOWN_NRG:
        {
            float x = ofMap(myGUI->getSmoothedPitch(), 0, 1, ofGetWidth()-1, 1, true);
            setX(int(x));
            break;
        }
        case PITCH_DRIVE:
        {
            pitchDrive  = myGUI->getSmoothedPitch()- 0.5f;
            int numVertices;
            
            for (int i=0; i<numPainters; ++i)
            {
                vector<ofPoint> points = painters[i].getPoints();
                int numOfPoints = points.size();
                ofPolyline p;
                
                if(numOfPoints>2)
                {
                    // we contrsutct a polyline to calculate it's tangent ...
                    for(int i=0;i<2;i++)
                    {
                        p.addVertex(points[numOfPoints-2+i]);
                    }

                    pathDirection = p.getTangentAtIndexInterpolated(numOfPoints-1);
                    
                    newPosition = pathDirection*30;
                    newPosition.rotate(12.5*pitchDrive, ofVec3f(0,0,1));
                    //newPosition = ofVec3f(points[numOfPoints-1] + ( pathDirection * 20 ) );
//                    newPosition.rotate(2.5*pitchDrive, ofVec3f(0,0,1));
                    newPosition = newPosition + points[numOfPoints-1] ;
                    painters[i].setPosition(newPosition.x,newPosition.y);
                }
            }
            break;
        }
            
        case PITCH_RANDOM: { // Random position every few pitch updates
//            float currentTime = ofGetElapsedTimef();
//            if (currentTime - pitchLastTime > 1)
//            {
            // OPCIO 1
//                pitchLastTime = currentTime;
//                float m3offsetX = ofMap(myGUI->getSmoothedPitch(), 0, 1, -15, 15);
//                float yOffset = ofMap(myGUI->getSmoothedPitch(), 0, 1, -15, 15);
//                cout << "Offset: " << m3offsetX << "-" << yOffset << endl;
//                addOffsetToPosition(m3offsetX, yOffset);

            // OPCIO 2
//                addOffsetToPosition(ofRandom(-15,15), ofRandom(-15,15));

            // OPCIO 3

            if (fabs(lastPitch - myGUI->getSmoothedPitch()) > 0.2)
            {
                float offset;
                float rndNumber2 = ofRandom(0, 1);
                if (rndNumber2 < 0.5)
                    offset = ofMap(myGUI->getSmoothedPitch(), 0, 1, 0, 15);
                else
                    offset = ofMap(myGUI->getSmoothedPitch(), 0, 1, -15, 0);

                float rndNumber1 = ofRandom(0, 1);
                if (rndNumber1 < 0.5)
                {
                    m3offsetX = offset;
                    m3offsetY = offset/10;
                }
                else
                {
                    m3offsetX = offset/10;
                    m3offsetY = offset;
                }

                addOffsetToPosition(m3offsetX, m3offsetY);
            }
            else
            {
                float increment = 0.2;
                if (fabs(m3offsetX) > fabs(m3offsetY))
                {
                    if (m3offsetX < 0)
                        m3offsetX += increment;
                    else
                        m3offsetX -= increment;
                }
                else
                {
                    if (m3offsetY < 0)
                        m3offsetY += increment;
                    else
                        m3offsetY -= increment;
                }
                cout << "(oX, oy) = ("<< m3offsetX << "; " << m3offsetY << ")" << endl;
                addOffsetToPosition(m3offsetX, m3offsetY);
            }


//            }
            break;
            
        }
    }

}

void PMRendererRibbon::energyChanged(energyParams energyParams)
{
    PMBaseRenderer::energyChanged(energyParams);

    if ((state != RENDERERSTATE_ON) ) return;

    if (mode == RM_MOUSE) return;

    float size = ofMap(myGUI->getSmoothedEnergy(), 0, 1, 1, myGUI->getStrokeWidth());
    for (int i=0; i<numPainters; ++i)
        painters[i].setSize((unsigned int)size);
}

void PMRendererRibbon::silenceStateChanged(silenceParams &silenceParams)
{
    PMBaseRenderer::silenceStateChanged(silenceParams);

    if (mode == RM_MOUSE) return;

    isSilent = silenceParams.isSilent;

    if (state != RENDERERSTATE_ON)
    {
//        strokeEnded();
        return;
    }

/*
    if (!(silenceParams.isSilent))
        strokeStarted();
    else
        strokeEnded();
*/
}

// TODO: Remove mouse events code once audio events are working

void PMRendererRibbon::mouseDragged(int x, int y, int button)
{
    if (mode != RM_MOUSE) return;

    if (button == OF_MOUSE_BUTTON_1)
        setPosition(x, y);
}

void PMRendererRibbon::mousePressed(int x, int y, int button)
{
    if (mode != RM_MOUSE) return;

    if (button == OF_MOUSE_BUTTON_1)
    {
        setPosition(x, y);
        strokeStarted();
    }
}

void PMRendererRibbon::mouseReleased(int x, int y, int button)
{
    if (mode != RM_MOUSE) return;

    strokeEnded();
}

void PMRendererRibbon::switchStateOnOff()
{
    PMBaseRenderer::switchStateOnOff();
    if (state == RENDERERSTATE_OFF)
    {
        rebuildPainters();
    }
}

void PMRendererRibbon::getGUIData()
{
    int oldMode = mode;
    if (myGUI->getMode() != oldMode)
    {
        rebuildPainters();
        if (myGUI->getMode() == PITCH_RANDOM)
            pitchLastTime = ofGetElapsedTimef();
            lastPitch = 0;
    }

    mode = myGUI->getMode();

    // Stroke width changed
    {
        unsigned int guiStrokeWidth = myGUI->getStrokeWidth();
        if (guiStrokeWidth != strokeWidth) {
            strokeWidth = guiStrokeWidth;
            for (int i = 0; i < numPainters; ++i)
                painters[i].setSize(strokeWidth);
        }
    }

    // Ribbon color
    {
        switch(myGUI->getColorMode())
        {
            case RCM_Fixed:
            {
                ribbonColorR = myGUI->getRibbonColor().r;
                ribbonColorG = myGUI->getRibbonColor().g;
                ribbonColorB = myGUI->getRibbonColor().b;
                for (int i=0; i<numPainters; ++i)
                    painters[i].setColor(ofColor(ribbonColorR, ribbonColorG, ribbonColorB, 255));
                break;
            }
            case RCM_GradientSpeed:
            {
                float gradientSpeed = float(myGUI->getGradientSpeed()) / 10000.0f;
                float gradientSign = (gradientReverse ? -1 : 1);
                gradientPosition = gradientPosition + (gradientSign * gradientSpeed);

                if (gradientPosition > 1.0f) {
                    gradientReverse = true;
                    gradientPosition = 1.0f;
                } else if (gradientPosition < 0.0f) {
                    gradientReverse = false;
                    gradientPosition = 0.0f;
                }
                ofColor color = myGUI->getGradientColor(myGUI->getGradientId(), gradientPosition);
                for (int i = 0; i < numPainters; ++i) {
                    painters[i].setColor(color);
                }
                break;
            }
            case RCM_GradientEdges:
            {
                float gradientSign = (gradientReverse ? -1 : 1);

                for (int i = 0; i < numPainters; ++i)
                {
                    if (didReachBorder && i==0)
                    {
                        float increment = (1 / float(NUM_GRADIENT_COLORS)) * gradientSign;
                        gradientPosition += increment;
                        if (gradientPosition >= 1.0f)
                        {
                            gradientReverse = true;
                            gradientPosition -= increment * 2.0f;
                        }
                        else if (gradientPosition <= 0.0f)
                        {
                            gradientReverse = false;
                            gradientPosition -= increment * 2.0f;
                        }
                    }
                    ofColor color = myGUI->getGradientColor(myGUI->getGradientId(), gradientPosition);
                    painters[i].setColor(color);
                }
                break;
            }
        }
    }

    // Number of divisions changed
    {
        float guiDivisions = myGUI->getDivisions();
        if (guiDivisions != divisions)
        {
            divisions = guiDivisions;
            rebuildPainters();
            return;
        }
    }

    // Number of painters changed
    {
        unsigned int guiNumPainters = myGUI->getNumPainters();
        if (guiNumPainters != numPainters)
        {
            numPainters = guiNumPainters;
            rebuildPainters();
            return;
        }
    }

    // Ease
    {
//        if (myGUI->getEase() != lastEase)
//        {
//            for (int i=0; i<numPainters; ++i)
//            {
//                painters[i].setEase(myGUI->getEase());
//            }
//            lastEase = myGUI->getEase();
//        }
//        
//        for (int i=0; i<numPainters; ++i)
//        {
//            painters[i].setEaseRandomness(myGUI->getEaseRandomness());
//        }
        
    }
    
    
}

void PMRendererRibbon::addOffsetToPosition(float xOffset, float yOffset)
{
    didReachBorder = false;

    bool bounces = myGUI->getBounceEnabled();
    for (int i=0; i<numPainters; ++i)
    {
        ofPoint *targetPos = painters[i].getTargetPos();

        // X offset
        {
            int newX = int(targetPos->x + (xOffset * offsetSign));
            if (newX > xMax)
            {
                if (!bounces) {
                    //painters[i].clear();
                    newX = xMin;
                } else {
                    offsetSign = -offsetSign;
                    newX = xMax;
                }
                didReachBorder = true;
            }
            else if (newX < xMin)
            {
                if (!bounces) {
                    painters[i].clear();
                    newX = xMax;
                } else {
                    offsetSign = -offsetSign;
                    newX = xMin;
                }
                didReachBorder = true;
            }

            painters[i].setX(newX);
        }

        // Y offset
        {
            int newY = int(targetPos->y + (yOffset * offsetSign));
            if (newY > yMax)
            {
                if (!bounces) {
                    //painters[i].clear();
                    newY = yMin;
                } else {
                    offsetSign = -1;
                    newY = yMax;
                }
                didReachBorder = bounces;
            }
            else if (newY < 1)
            {
                if (!bounces) {
                    painters[i].clear();
                    newY = yMax;
                } else {
                    offsetSign = 1;
                    newY = yMin;
                }
                didReachBorder = bounces;
            }

            painters[i].setY(newY);
        }
    }
}
