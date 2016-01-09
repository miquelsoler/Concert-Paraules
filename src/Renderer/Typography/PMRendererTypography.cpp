//
// Created by Miquel Àngel Soler on 16/11/15.
//

#include "PMRendererTypography.h"
#include "PMUICanvasTypoRenderer.h"
#include "PMSettingsManagerPoem.h"

static const string DEFAULT_CHARSET = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";

static const float MILLISECONDS_NEXT_LETTER = 50;


PMRendererTypography::PMRendererTypography() : PMBaseRenderer(RENDERERTYPE_TYPOGRAPHY)
{
    buildCharsetFromPoem();

    // GUI
    {
        gui = new PMUICanvasTypoRenderer(UI_RENDERERTYPE_TYPOGRAPHY, "TYPO_RENDERER", OFX_UI_FONT_MEDIUM);
        gui->init(100, 500, 200, 300);
    }

    // Font preload
    {
        string fontName = "GaramondPremrPro.otf";
        string fontPath = "fonts/" + fontName;

        font = new ofTrueTypeFont();
        font->load(fontPath, 100,
                true, // antialiased
                true, // full character set
                true // make contours
        );


    }

    letterSize = 1.0;
    letterYVelocity = 1.0;

    // Box2D
    {
        PMUICanvasTypoRenderer *myGUI = (PMUICanvasTypoRenderer *) gui;

        box2d.init();

        box2d.setGravity(myGUI->getGravityX(), myGUI->getGravityY());
        box2d.createBounds();
        box2d.setFPS(30);
        box2d.setIterations(20, 10);
    }

    typoTimerEnabled = true;
    typoTimer = ofGetElapsedTimeMillis();

    myGUI = (PMUICanvasTypoRenderer *) gui;
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
    if (state != RENDERERSTATE_ON) return;

    PMBaseRenderer::update();

    int _mode = myGUI->getMode();

    if (oldMode != _mode) {
        oldMode = _mode;
        box2d.getWorld()->ClearForces();

    }

    // IF ADDALETTER IS ENABLES IN ENERGY CHANGED ...
    if (addALetter) {
        float minVelocity = 0.01;
        float maxVelocity = 1.0;
        float velocityY = ofMap(gui->getSmoothedPitch(), 0.0, 1.0, minVelocity, maxVelocity, true);
        setYVelocity(velocityY);
        addLetter();
        addALetter = false;
    }

    uint64_t maxAge = myGUI->getMaxAge() * uint64_t(1000);
    list<shared_ptr<PMLetterContainer>>::iterator letterIt;
    for (letterIt = activeLetters.begin(); letterIt != activeLetters.end(); ++letterIt) {
        if (((*letterIt)->getAge() >= maxAge) || ((*letterIt)->getNeedsToBeRemoved())) {
            (*letterIt).get()->destroy();
            activeLetters.erase(letterIt++);
        }
    }


    switch (_mode) {
        case 1 : {
            box2d.setGravity(myGUI->getGravityX(), myGUI->getGravityY());
            oldMode = 1;
            break;
        }
        case 2 : {
            float time = ofGetElapsedTimef();
            float gX = sin(time * myGUI->getSinusFreq()) * myGUI->getSinusAmplitude();
            float gY = cos(time * myGUI->getSinusFreq()) * myGUI->getSinusAmplitude();
            myGUI->setGravityX(gX);
            myGUI->setGravityY(gY);
            box2d.setGravity(gX, gY);
            break;
        }
        case 3 : {
            box2d.setGravity(myGUI->getGravityX(), myGUI->getGravityY());
            oldMode = 3;
            for (letterIt = activeLetters.begin(); letterIt != activeLetters.end(); ++letterIt) {
                ofVec2f mouse(ofGetMouseX(), ofGetMouseY());

                ofVec2f v = ofVec2f(ofGetMouseX() / ofGetWidth(), ofGetMouseY() / ofGetHeight());
                (*letterIt)->addAttractionPoint(mouse, myGUI->getAttractorForce());
            }

        }

        case 4 : {
            box2d.setGravity(myGUI->getGravityX(), myGUI->getGravityY());
            oldMode = 4;

        }
        default :
            break;

    }

    box2d.update();


}

void PMRendererTypography::drawIntoFBO()
{
    if ((state != RENDERERSTATE_ON)) return;

    fbo.begin();
    {
        clearFBOBackground(float(gui->getBackgroundColor().r) / 255.0f, float(gui->getBackgroundColor().g) / 255.0f, float(gui->getBackgroundColor().b) / 255.0f, gui->getBackgroundFade());

        list<shared_ptr<PMLetterContainer>>::iterator letterIt;
        for (letterIt = activeLetters.begin(); letterIt != activeLetters.end(); ++letterIt) {
            (*letterIt).get()->draw();
        }
    }
    fbo.end();
}

void PMRendererTypography::addLetter()
{
    if (somethingInContact) return;

    int iLetter = int(ofRandom(charset.size()));

    float posX = 0, posY = 0;

    if ((myGUI->getMode() == 1) || (myGUI->getMode() == 2)) {
        float posOffset = ofGetWidth() * 0.1f;
        posX = ofRandom(posOffset, ofGetWidth() - 2 * posOffset);
        posY = 1;
    }
    else if (myGUI->getMode() == 4) {
        posX = ofMap(lastPitchReceived, 0.0, 1.0, 10.0, ofGetWidth() - 20);
        posY = 1;
    }

    shared_ptr<PMLetterContainer> letterContainer = shared_ptr<PMLetterContainer>(new PMLetterContainer(ofToString(charset[iLetter]),
            font,
            ofPoint(posX, posY),
            letterSize,
            letterYVelocity,
            &box2d,
            myGUI));

    activeLetters.push_back(letterContainer);
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

    while (iter != lines.end()) {
        if (!(*iter).empty()) {
            string line = (*iter);
            ofStringReplace(line, ",", " ");
            ofStringReplace(line, ";", " ");
            ofStringReplace(line, ":", " ");
            ofStringReplace(line, ".", " ");
            ofStringReplace(line, "-", " ");
            ofStringReplace(line, "!", " ");
            ofStringReplace(line, "?", " ");
            ofStringReplace(line, "'", " ");
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

//    if (typoTimerEnabled)
//    {
//        float diffTimeMs = ofGetElapsedTimeMillis() - typoTimer;
//        if (diffTimeMs > MILLISECONDS_NEXT_LETTER)
//        {
//            typoTimer = ofGetElapsedTimeMillis();
//
//            float minVelocity = 0.01;
//            float maxVelocity = 1.0;
//            float velocityY = ofMap(gui->getSmoothedPitch(), 0.0, 1.0, minVelocity, maxVelocity, true);
//            setYVelocity(velocityY);
//            //addLetter();
//        }
//    }

    lastPitchReceived = myGUI->getSmoothedPitch();
}

void PMRendererTypography::energyChanged(energyParams energyParams)
{
    PMBaseRenderer::energyChanged(energyParams);

    if (gui->getSmoothedEnergy() > myGUI->getAddLetterSensitivity()) {

        float diffTimeMs = ofGetElapsedTimeMillis() - typoTimer;
        if (diffTimeMs > myGUI->getLetterSpeedMs()) {
            typoTimer = ofGetElapsedTimeMillis();
            setLetterSize(gui->getSmoothedEnergy());
            addALetter = true;
        }
        else {
        }
    }
}

void PMRendererTypography::silenceStateChanged(silenceParams &silenceParams)
{
    PMBaseRenderer::silenceStateChanged(silenceParams);
//    
//    typoTimerEnabled = !silenceParams.isSilent;
//    if (typoTimerEnabled)
//        typoTimer = ofGetElapsedTimeMillis();
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

//--------------------------------------------------------------------------------
void PMRendererTypography::keyPressed(ofKeyEventArgs &eventArgs)
{
    if (state == RENDERERSTATE_ON) {
        if (eventArgs.key == 'q')
            addLetter();
    }

}

//--------------------------------------------------------------------------------
void PMRendererTypography::keyReleased(ofKeyEventArgs &eventArgs)
{
    if (state == RENDERERSTATE_ON) {
    }

}
