//
// Created by Miquel Àngel Soler on 16/11/15.
//

#include "PMRendererTypography.h"

#include "PMSettingsManagerPoem.h"

static const unsigned int MAX_LETTERS = 3;

//static const string DEFAULT_CHARSET = "?";
static const string DEFAULT_CHARSET = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";

PMRendererTypography::PMRendererTypography(unsigned int numInputs) : PMBaseRenderer(RENDERERTYPE_TYPOGRAPHY, numInputs)
{
    buildCharsetFromPoem();

    string fontName = "5inq_-_Handserif.ttf";
    string fontPath = "fonts/" + fontName;

    for (int i=0; i<charset.size(); ++i)
    {
        ofTrueTypeFont *letterFont = new ofTrueTypeFont();
        letterFont->load(fontPath, 80,
                true, // antialiased
                true, // full character set
                true // make contours
        );
        fontCharset.push_back(letterFont);
    }

    // Box2D
    {
        box2d.init();
        box2d.setGravity(0, 10);
        box2d.createBounds();
        box2d.setFPS(60);
    }

    // GUI
    {
        guiBaseRenderer = new PMUICanvasTypoRenderer("TYPO_RENDERER",OFX_UI_FONT_MEDIUM);
        guiBaseRenderer->init(100, 500, 200, 300);

        ofAddListener(ofEvents().keyPressed, this, &PMRendererTypography::keyPressed);
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

    uint64_t maxAge = 30000;
    list<shared_ptr<PMLetterContainer>>::iterator letterIt;
    for (letterIt = activeLetters.begin(); letterIt != activeLetters.end(); ++letterIt)
    {
        if ((*letterIt)->getAge() < maxAge) continue;

        (*letterIt).get()->destroy();
        activeLetters.erase(letterIt++);
    }

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

    ofSetColor(255, 255, 255, 255);

//    fbo.draw(0, 0);
}

void PMRendererTypography::addLetter()
{
    mutexAddLetter.lock();
    {
        int iLetter = int(ofRandom(charset.size()));

        mutexActiveLetters.lock();
        {
            shared_ptr<PMLetterContainer> letterContainer = shared_ptr<PMLetterContainer>(new PMLetterContainer(ofToString(charset[iLetter]), fontCharset[iLetter], &box2d));
            activeLetters.push_back(letterContainer);
        }
        mutexActiveLetters.unlock();
    }
    mutexAddLetter.unlock();
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
            ofStringReplace(line, ",", " "); ofStringReplace(line, ";", " ");
            ofStringReplace(line, ":", " "); ofStringReplace(line, ".", " ");
            ofStringReplace(line, "-", " "); ofStringReplace(line, "!", " ");
            ofStringReplace(line, "?", " "); ofStringReplace(line, "'", " ");
            vector<string> words = ofSplitString(line, " ", true, true);
            for (int i = 0; i < words.size(); ++i) {
                string word = words[i];
                for (int j = 0; j < word.length(); ++j) {
                    bool found = ofIsStringInString(charset, ofToString(word[j]));
                    if (!found)
                        charset += word[j];
                }
            }
        }
        ++iter;
    }

    // FIXME: Charset still includes characters like �.
    charset = DEFAULT_CHARSET;
}
