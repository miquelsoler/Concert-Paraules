//
// Created by Miquel Àngel Soler on 16/12/15.
//

#include "PMRendererRibbon.h"

static const int POS_MARGIN = 1;
static const int NUM_GRADIENT_COLORS = 5;

typedef enum
{
    RM_0 = 0,
    RM_1 = 1,
    RM_2 = 2,
    RM_3 = 3,
    RM_4 = 4,
    RM_5 = 5,
    RM_6 = 6,
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

//    float ini = ofGetElapsedTimef();
    
    PMBaseRenderer::update(); 

    getGUIData();

    if (!isSilent)
    {
        switch(mode)
        {
            case 1: updateMode1(); break;
            case 2: updateMode2(); break;
            case 3: updateMode3(); break;
            default: break;
        }
    }

//    if (!isInStroke) return;

    if (!isSilent || mode==RM_MOUSE)
    {
        for (int i=0; i<numPainters; ++i)
            painters[i].update();
    }

//    cout << "update duration = " << ofGetElapsedTimef() - ini << endl;
}

void PMRendererRibbon::updateMode1()
{
/*
    Moves right or left
    Color is chosen via GUI
*/
    bool didReachBorder;
    addOffsetToPosition(myGUI->getSpeed(), 0, &didReachBorder);
}

void PMRendererRibbon::updateMode2()
{
/*
    Moves right or left
    Color is changed automatically by using GUI gradient speed
*/

    float gradientSpeed = float(myGUI->getGradientSpeed()) / 10000.0f;
    float gradientSign = (gradientReverse ? -1 : 1);
    gradientPosition = gradientPosition + (gradientSign * gradientSpeed);

    if (gradientPosition > 1.0f)
    {
        gradientReverse = true;
        gradientPosition = 1.0f;
    }
    else if (gradientPosition < 0.0f)
    {
        gradientReverse = false;
        gradientPosition = 0.0f;
    }

    bool didReachBorder;
    for (int i = 0; i < numPainters; ++i) {
        addOffsetToPosition(myGUI->getSpeed(), 0, &didReachBorder);
        ofColor color = myGUI->getGradientColor(myGUI->getGradientId(), gradientPosition);
        painters[i].setColor(color);
    }
}

void PMRendererRibbon::updateMode3()
{
/*
    Moves right or left
    Color is changed automatically once the painter bounces
*/
    float gradientSign = (gradientReverse ? -1 : 1);

    for (int i = 0; i < numPainters; ++i)
    {
        bool didReachBorder;
        addOffsetToPosition(myGUI->getSpeed(), 0, &didReachBorder);
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

    for (int i=0; i<numPainters; ++i)
    {
        float ease = ofRandom(0.0f, 1.0f) * 0.2f + 0.6f;
        PMRibbonPainter painter = PMRibbonPainter(ribbonColor, dx, dy, divisions, ease, strokeWidth, myGUI);
        painters.push_back(painter);
    }

    isInStroke = false;

    for (int i=0; i<numPainters; ++i)
    {
        painters[i].setup();
        painters[i].setOrigin(PAINTER_LEFT);
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
        painters[i].setY(y);
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

    float y = ofMap(myGUI->getSmoothedPitch(), 0, 1, ofGetHeight()-1, 1, true);
    setY(int(y));
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
//        cout << "End stroke (state not ON)" << endl;
        strokeEnded();
        return;
    }

    if (!(silenceParams.isSilent))
    {
//        cout << "Start stroke (silence stopped)" << endl;
        strokeStarted();
    }
    else
    {
//        cout << "End stroke (new silence)" << endl;
        strokeEnded();
    }
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
        rebuildPainters();

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

    // Ribbon color changed
    {
        switch(mode)
        {
            case 1:
            case 10:
            {
                unsigned int guiRibbonColorR = myGUI->getRibbonColor().r;
                unsigned int guiRibbonColorG = myGUI->getRibbonColor().g;
                unsigned int guiRibbonColorB = myGUI->getRibbonColor().b;

                if ((guiRibbonColorR != ribbonColorR) || (guiRibbonColorG != ribbonColorG) || (guiRibbonColorB != ribbonColorB))
                {
                    for (int i=0; i<numPainters; ++i)
                        painters[i].setColor(ofColor(guiRibbonColorR, guiRibbonColorG, guiRibbonColorB, 255));
                }
                break;
            }
            case 2:
            {
                ofColor color = myGUI->getGradientColor(myGUI->getGradientId(), 0.1);
                for (int i=0; i<numPainters; ++i)
                    painters[i].setColor(color);
                break;
            }
            default: break;
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
}

void PMRendererRibbon::addOffsetToPosition(float xOffset, float yOffset, bool *didReachBorder)
{
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
                    painters[i].clear();
                    newX = xMin;
                } else {
                    offsetSign = -offsetSign;
                    newX = xMax;
                }
                *didReachBorder = true;
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
                *didReachBorder = true;
            }

            painters[i].setX(newX);
        }

        // Y offset
        {
            int newY = int(targetPos->y + (yOffset * offsetSign));
            if (newY > yMax)
            {
                if (!bounces) {
                    painters[i].clear();
                    newY = yMin;
                } else {
                    offsetSign = -1;
                    newY = yMax;
                }
                *didReachBorder = bounces;
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
                *didReachBorder = bounces;
            }

            painters[i].setY(newY);
        }
    }
}
