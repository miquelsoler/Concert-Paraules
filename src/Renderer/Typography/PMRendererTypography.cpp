//
// Created by Miquel Àngel Soler on 16/11/15.
//

#include "PMRendererTypography.h"

#include "PMSettingsManagerPoem.h"

//static const string DEFAULT_CHARSET = "?";
static const string DEFAULT_CHARSET = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
//static const string DEFAULT_CHARSET = "aeiouAEIOU";

PMRendererTypography::PMRendererTypography(unsigned int numInputs) : PMBaseRenderer(RENDERERTYPE_TYPOGRAPHY, numInputs)
{
    buildCharsetFromPoem();

    // GUI
    {
        gui = new PMUICanvasTypoRenderer("TYPO_RENDERER",OFX_UI_FONT_MEDIUM);
        gui->init(100, 500, 200, 300);

        ofAddListener(ofEvents().keyPressed, this, &PMRendererTypography::keyPressed);
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
        box2d.setGravity(myGUI->getGravityX(), myGUI->getGravityY());
        box2d.createBounds();
        box2d.setFPS(60);
    }
}

void PMRendererTypography::setup()
{
    PMBaseRenderer::setup();

    if (!activeLetters.empty())
        activeLetters.clear();
}

void PMRendererTypography::update()
{
    PMBaseRenderer::update();

    PMUICanvasTypoRenderer *myGUI = (PMUICanvasTypoRenderer *)gui;

    uint64_t maxAge = myGUI->getMaxAge() * 1000.0f;
    list<shared_ptr<PMLetterContainer>>::iterator letterIt;
    for (letterIt = activeLetters.begin(); letterIt != activeLetters.end(); ++letterIt)
    {
        if ((*letterIt)->getAge() < maxAge) continue;

        (*letterIt).get()->destroy();
        activeLetters.erase(letterIt++);
    }
    
    box2d.setGravity(myGUI->getGravityX(), myGUI->getGravityY());

    box2d.update();
}

void PMRendererTypography::drawIntoFBO()
{
    fbo.begin();
    {
        ofFloatColor fc = ofFloatColor(1.0,1.0,1.0,1.0);
        ofSetColor(fc);
        ofDrawRectangle(0, 0, ofGetWidth(), ofGetHeight());

        ofEnableBlendMode(OF_BLENDMODE_ALPHA);

        list<shared_ptr<PMLetterContainer>>::iterator letterIt;
        mutexActiveLetters.lock();
        {
            for (letterIt = activeLetters.begin(); letterIt != activeLetters.end(); ++letterIt)
                (*letterIt).get()->draw();
        }
        mutexActiveLetters.unlock();

        ofDisableBlendMode();
    }
    fbo.end();
}

void PMRendererTypography::addLetter()
{
    mutexAddLetter.lock();
    {
        int iLetter = int(ofRandom(charset.size()));

        mutexActiveLetters.lock();
        {
            PMUICanvasTypoRenderer *myGUI = (PMUICanvasTypoRenderer *)gui;
//            shared_ptr<PMLetterContainer> letterContainer = shared_ptr<PMLetterContainer>(new PMLetterContainer(ofToString(charset[iLetter]), font, letterSize, letterYVelocity, &box2d, myGUI));
            shared_ptr<PMLetterContainer> letterContainer = shared_ptr<PMLetterContainer>(new PMLetterContainer(ofToString(charset[iLetter]), font, letterSize, letterYVelocity, &box2d, myGUI));
            activeLetters.push_back(letterContainer);
        }
        mutexActiveLetters.unlock();
    }
    mutexAddLetter.unlock();
}

void PMRendererTypography::setLetterSize(float normalizedSize)
{
    letterSize = normalizedSize;
    if (letterSize <= 0) letterSize = 0.01;
    if (letterSize > 1) letterSize = 1.0;
}

void PMRendererTypography::setYVelocity(float normalizedVelocity)
{
    letterYVelocity = normalizedVelocity;
    if (letterYVelocity < 0) letterYVelocity = 0.0;
    if (letterYVelocity > 1) letterYVelocity = 1.0;
}

void PMRendererTypography::keyPressed ( ofKeyEventArgs& eventArgs )
{
    if (eventArgs.key == 'q')
        addLetter();
}

void PMRendererTypography::buildCharsetFromPoem() {
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
//            cout << line << endl;
            ofStringReplace(line, ",", " "); ofStringReplace(line, ";", " ");
            ofStringReplace(line, ":", " "); ofStringReplace(line, ".", " ");
            ofStringReplace(line, "-", " "); ofStringReplace(line, "!", " ");
            ofStringReplace(line, "?", " "); ofStringReplace(line, "'", " ");
            vector<string> words = ofSplitString(line, " ", true, true);
            for (int i = 0; i < words.size(); ++i) {
                string word = words[i];
                string::iterator it;
                for (it = word.begin(); it != word.end(); ++it) {
//                for (int j = 0; j < word.length(); ++j) {
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
