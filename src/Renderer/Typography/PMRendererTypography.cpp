//
// Created by Miquel Àngel Soler on 16/11/15.
//

#include "PMRendererTypography.h"
#include "PMUICanvasTypoRenderer.h"
#include "PMSettingsManagerPoem.h"

//static const string DEFAULT_CHARSET = "?";
static const string DEFAULT_CHARSET = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
//static const string DEFAULT_CHARSET = "aeiouAEIOU";

static const float MILLISECONDS_NEXT_LETTER = 50;


PMRendererTypography::PMRendererTypography() : PMBaseRenderer(RENDERERTYPE_TYPOGRAPHY)
{
    buildCharsetFromPoem();

    // GUI
    {
        gui = new PMUICanvasTypoRenderer(UI_RENDERERTYPE_TYPOGRAPHY, "TYPO_RENDERER",OFX_UI_FONT_MEDIUM);
        gui->init(100, 500, 200, 300);
    }

    // Font preload
    {
        string fontName = "GaramondPremrPro.otf";
        string fontPath = "fonts/" + fontName;

        font = new ofTrueTypeFont();
        font->load(fontPath, 200,
                true, // antialiased
                true, // full character set
                true // make contours
        );
    }

    letterSize = 1.0;
    letterYVelocity = 1.0;

    // Box2D
    {
        PMUICanvasTypoRenderer *myGUI = (PMUICanvasTypoRenderer *)gui;

        box2d.init();
        box2d.enableEvents();
        box2d.setGravity(myGUI->getGravityX(), myGUI->getGravityY());
        box2d.createBounds();
        box2d.setFPS(60);

        // register the listener so that we get the events
        ofAddListener(box2d.contactStartEvents, this, &PMRendererTypography::contactStart);
        ofAddListener(box2d.contactEndEvents, this, &PMRendererTypography::contactEnd);
    }
    
    typoTimerEnabled = false;
    
    myGUI = (PMUICanvasTypoRenderer *)gui;
    addALetter = false;

}

void PMRendererTypography::setup()
{
    PMBaseRenderer::setup();

    if (!activeLetters.empty())
        activeLetters.clear();

    somethingInContact = false;
}

void PMRendererTypography::update()
{
    
    PMBaseRenderer::update();
    int _mode = myGUI->getMode();
    bool firstTimeInMode = false;
    
    if(oldMode != _mode)
    {
        firstTimeInMode = true;
        oldMode = _mode;
    }
    else firstTimeInMode = false;
    
    // IF ADDALETTER IS ENABLES IN ENERTGY CHANGED ...
    if(addALetter)
    {
        float minVelocity = 0.01;
        float maxVelocity = 1.0;
        float velocityY = ofMap(gui->getSmoothedPitch(), 0.0, 1.0, minVelocity, maxVelocity, true);
        setYVelocity(velocityY);
        addLetter();
        addALetter = false;
        
    }


//    if ((state != RENDERERSTATE_ON) && (state != RENDERERSTATE_PAUSED)) return;

    uint64_t maxAge = myGUI->getMaxAge() * uint64_t(1000);
    list<shared_ptr<PMLetterContainer>>::iterator letterIt;
    for (letterIt = activeLetters.begin(); letterIt != activeLetters.end(); ++letterIt)
    {
        if (((*letterIt)->getAge() >= maxAge) || ((*letterIt)->getNeedsToBeRemoved()))
        {
            (*letterIt).get()->destroy();
            activeLetters.erase(letterIt++);
        }
    }
    
    
    switch(_mode)
    {
        case 1 :
        {
            box2d.setGravity(myGUI->getGravityX(), myGUI->getGravityY());
            oldMode = 1;
            break;
        }
        case 2 :
        {
            float time = ofGetElapsedTimef();
            float gX = sin(time*myGUI->getSinusFreq()) * myGUI->getSinusAmplitude();
            float gY = cos(time*myGUI->getSinusFreq()) * myGUI->getSinusAmplitude();
            myGUI->setGravityX(gX);
            myGUI->setGravityY(gY);
            box2d.setGravity(gX, gY);
            
            
            break;
        }
        case 3 :
        {
            for (letterIt = activeLetters.begin(); letterIt != activeLetters.end(); ++letterIt)
            {
                ofVec2f mouse(ofGetMouseX(), ofGetMouseY());

                ofVec2f v = ofVec2f(ofGetMouseX(),ofGetMouseY());
                (*letterIt)->addAttractionPoint(mouse, 4.0);
            }
            
            if (firstTimeInMode)
            {
                box2d.getWorld()->ClearForces();
            }
            break;
        }
        default :
            break;
            
    }
    
    box2d.update();
    


}

void PMRendererTypography::drawIntoFBO()
{
    if ((state != RENDERERSTATE_ON) && (state != RENDERERSTATE_PAUSED)) return;

    fbo.begin();
    {
        //ofFloatColor fc = ofColor(gui->getBackgroundColor().r, gui->getBackgroundColor().g, gui->getBackgroundColor().b, 1);
        //ofClear(fc);

        list<shared_ptr<PMLetterContainer>>::iterator letterIt;
        mutexActiveLetters.lock();
        {
            for (letterIt = activeLetters.begin(); letterIt != activeLetters.end(); ++letterIt)
                (*letterIt).get()->draw();
        }
        mutexActiveLetters.unlock();
    }
    fbo.end();
}

void PMRendererTypography::addLetter()
{
    if (somethingInContact) return;

    mutexAddLetter.lock();
    {
        int iLetter = int(ofRandom(charset.size()));

        mutexActiveLetters.lock();
        {
            shared_ptr<PMLetterContainer> letterContainer =
                    shared_ptr<PMLetterContainer>(new PMLetterContainer(ofToString(charset[iLetter]), font, letterSize, letterYVelocity, &box2d, myGUI));

            activeLetters.push_back(letterContainer);
        }
        mutexActiveLetters.unlock();
    }
    mutexAddLetter.unlock();
    

}

void PMRendererTypography::setLetterSize(float normalizedSize)
{
    letterSize = normalizedSize;

    if (letterSize <= 0.0f) letterSize = 0.01;
    if (letterSize > 1.0f) letterSize = 1.0;
}

void PMRendererTypography::setYVelocity(float normalizedVelocity)
{
    letterYVelocity = normalizedVelocity;
    if (letterYVelocity < 0) letterYVelocity = 0.0;
    if (letterYVelocity > 1) letterYVelocity = 1.0;
}

void PMRendererTypography::buildCharsetFromPoem()
{
    PMSettingsManagerPoem *poemSettings = &PMSettingsManagerPoem::getInstance();

    string strPoemFolder = poemSettings->getFolderPath();
    string strPoemFilename = poemSettings->getPoemFilename();

    ofBuffer buffer = ofBufferFromFile(strPoemFolder + "/" + strPoemFilename);
    if (buffer.size() == 0) {
        charset = DEFAULT_CHARSET;
        return;
    }

    charset = "";

    ofBuffer::Lines lines = buffer.getLines();
    ofBuffer::Line iter = lines.begin();

    while (iter != lines.end())
    {
        if (!(*iter).empty())
        {
            string line = (*iter);
            ofStringReplace(line, ",", " "); ofStringReplace(line, ";", " ");
            ofStringReplace(line, ":", " "); ofStringReplace(line, ".", " ");
            ofStringReplace(line, "-", " "); ofStringReplace(line, "!", " ");
            ofStringReplace(line, "?", " "); ofStringReplace(line, "'", " ");
            vector<string> words = ofSplitString(line, " ", true, true);
            for (int i = 0; i < words.size(); ++i) {
                string word = words[i];
                string::iterator it;
                for (it = word.begin(); it != word.end(); ++it) {
                    bool found = ofIsStringInString(charset, ofToString(*it));
                    if (!found)
                        charset += ofToString(*it);
                }
            }
        }
        ++iter;
    }

    // FIXME: Charset still includes characters like �.
    charset = DEFAULT_CHARSET;
}

void PMRendererTypography::pitchChanged(pitchParams pitchParams)
{
    PMBaseRenderer::pitchChanged(pitchParams);

    if (state != RENDERERSTATE_ON) return;

    if (typoTimerEnabled)
    {
        float diffTimeMs = ofGetElapsedTimeMillis() - typoTimer;
        if (diffTimeMs > MILLISECONDS_NEXT_LETTER)
        {
            typoTimer = ofGetElapsedTimeMillis();

            float minVelocity = 0.01;
            float maxVelocity = 1.0;
            float velocityY = ofMap(gui->getSmoothedPitch(), 0.0, 1.0, minVelocity, maxVelocity, true);
            setYVelocity(velocityY);
            //addLetter();
        }
    }
}

void PMRendererTypography::energyChanged(energyParams energyParams)
{
    PMBaseRenderer::energyChanged(energyParams);
    setLetterSize(gui->getSmoothedEnergy());
    
    if(gui->getSmoothedEnergy()>0.1)
    {
        addALetter = true;
    }
}

void PMRendererTypography::silenceStateChanged(silenceParams &silenceParams)
{
    PMBaseRenderer::silenceStateChanged(silenceParams);
    
    typoTimerEnabled = !silenceParams.isSilent;
    if (typoTimerEnabled)
        typoTimer = ofGetElapsedTimeMillis();
}

void PMRendererTypography::contactStart(ofxBox2dContactArgs &e)
{
    somethingInContact = true;
}

void PMRendererTypography::contactEnd(ofxBox2dContactArgs &e)
{
    somethingInContact = false;
}

void PMRendererTypography::clear()
{
    PMBaseRenderer::clear();

    list<shared_ptr<PMLetterContainer>>::iterator letterIt;
    for (letterIt = activeLetters.begin(); letterIt != activeLetters.end(); ++letterIt) {
        (*letterIt).get()->setNeedsToBeRemoved();
    }
}

void PMRendererTypography::keyPressed ( ofKeyEventArgs& eventArgs )
{
    if(state == RENDERERSTATE_ON)
    {
        if (eventArgs.key == 'q')
            addLetter();
        
        cout << " KEY TYPORenderer" << endl;
    }
    
}