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

#ifdef WITH_BOX2D
    // Box2D
    {
        box2d.init();
        box2d.setGravity(0, 10);
        box2d.createBounds();
        box2d.setFPS(60.0);
    }
#endif

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

#ifdef WITH_BOX2D
    box2d.update();
#endif
}

void PMRendererTypography::drawIntoFBO()
{
    fbo.begin();
    {
#ifdef WITH_BOX2D
        ofFloatColor fc = ofFloatColor(1.0,1.0,1.0,1.0);
#else
        ofFloatColor fc = ofFloatColor(1.0,1.0,1.0,guiBaseRenderer->getFadeBackground());
#endif
        ofSetColor(fc);
        ofDrawRectangle(0, 0, ofGetWidth(), ofGetHeight());

        ofEnableBlendMode(OF_BLENDMODE_ALPHA);

#ifdef WITH_BOX2D
        list<shared_ptr<PMLetterContainer>>::iterator letterIt;
#else
        list<PMLetterContainer *>::iterator letterIt;
#endif
        mutexLetters.lock();
        {
#ifdef WITH_BOX2D
            for (int i=0; i<activeLetters.size(); i++)
                activeLetters[i].get()->draw();
#else
            for (letterIt = activeLetters.begin(); letterIt != activeLetters.end(); ++letterIt)
                (*letterIt)->draw();
#endif
        }
        mutexLetters.unlock();

        ofDisableBlendMode();
    }
    fbo.end();

    ofSetColor(255, 255, 255, 255);

//    fbo.draw(0, 0);
}

void PMRendererTypography::addLetter()
{
    int iLetter = int(ofRandom(charset.size()));

//    PMLetterContainer *letterContainer = new PMLetterContainer("5inq_-_Handserif.ttf", ofToString(charset[iLetter]));
#ifdef WITH_BOX2D
    shared_ptr<PMLetterContainer> letterContainer = shared_ptr<PMLetterContainer>(new PMLetterContainer(ofToString(charset[iLetter]), fontCharset[iLetter], &box2d));
#else
    PMLetterContainer *letterContainer = new PMLetterContainer(ofToString(charset[iLetter]), fontCharset[iLetter]);
    letterContainer->setPosition(ofRandom(0.05, 0.95), ofRandom(0.05, 0.95));
    letterContainer->setSize(1.0);
#endif

    mutexLetters.lock();
    {
        activeLetters.push_back(letterContainer);

        if (activeLetters.size() > MAX_LETTERS)
        {
#ifdef WITH_BOX2D
//            activeLetters.begin()->reset();
#else
            delete *(activeLetters.begin());
            activeLetters.pop_front();
#endif
        }
    }
    mutexLetters.unlock();
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

    string poemText = buffer.getText();

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
