//
// Created by Miquel Àngel Soler on 16/11/15.
//

#include "PMRendererTypography.h"

#include "PMSettingsManagerPoem.h"

static const unsigned int MAX_LETTERS = 10;

PMRendererTypography::PMRendererTypography(unsigned int numInputs) : PMBaseRenderer(RENDERERTYPE_TYPOGRAPHY, numInputs)
{

//    charset = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
//    charset = "aeiou";
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

////    letterFont->setLineHeight(18.0f);
////    letterFont->setLetterSpacing(1.037);

        fontCharset.push_back(letterFont);
    }

    ofAddListener(ofEvents().keyPressed, this, &PMRendererTypography::keyPressed);
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
}

void PMRendererTypography::drawIntoFBO()
{
    fbo.begin();
    {
        ofSetColor(255, 255, 255, 1);
        ofDrawRectangle(0, 0, ofGetWidth(), ofGetHeight());

        ofEnableBlendMode(OF_BLENDMODE_ALPHA);

        list<PMLetterContainer *>::iterator letterIt;
        for (letterIt = activeLetters.begin(); letterIt != activeLetters.end(); ++letterIt)
            (*letterIt)->draw();

        ofDisableBlendMode();
    }
    fbo.end();

    ofSetColor(255, 255, 255, 255);

    fbo.draw(0, 0);
}

void PMRendererTypography::addLetter()
{
    int iLetter = int(ofRandom(charset.size()));

//    PMLetterContainer *letterContainer = new PMLetterContainer("5inq_-_Handserif.ttf", ofToString(charset[iLetter]));
    PMLetterContainer *letterContainer = new PMLetterContainer(ofToString(charset[iLetter]), fontCharset[iLetter]);
    letterContainer->setPosition(ofRandom(0.1, 0.9), ofRandom(0.1, 0.9));
    letterContainer->setSize(1.0);

    activeLetters.push_back(letterContainer);

    if (activeLetters.size() > MAX_LETTERS)
    {
        delete *(activeLetters.begin());
        activeLetters.pop_front();
    }
}

void PMRendererTypography::keyPressed ( ofKeyEventArgs& eventArgs )
{
    if (eventArgs.key == 'q')
        addLetter();
}

void PMRendererTypography::buildCharsetFromPoem()
{
    PMSettingsManagerPoem *poemSettings = &PMSettingsManagerPoem::getInstance();

    string strPoemFolder = poemSettings->getFolderPath();
    string strPoemFilename = poemSettings->getPoemFilename();

    ofBuffer buffer = ofBufferFromFile(strPoemFolder + "/" + strPoemFilename);
    string poemText = buffer.getText();

    charset = "";

    ofBuffer::Lines lines = buffer.getLines();
    ofBuffer::Line iter = lines.begin();

    while (iter != lines.end())
    {
        if (!(*iter).empty())
        {
            string line = (*iter);
            cout << "LINE: " << (*iter) << endl;
            ofStringReplace(line, ",", " ");
            ofStringReplace(line, ";", " ");
            ofStringReplace(line, ".", " ");
            ofStringReplace(line, "-", " ");
            ofStringReplace(line, "!", " ");
            ofStringReplace(line, "?", " ");
            ofStringReplace(line, "'", " ");
            vector<string> words = ofSplitString(line, " ", true, true);
            for (int i=0; i<words.size(); ++i)
            {
                string word = words[i];
                for (int j=0; j<word.length(); ++j)
                {
                    bool found = ofIsStringInString(charset, ofToString(word[j]));
                    if (!found)
                        charset += word[j];
                }
            }
        }
        ++iter;
    }

    cout << charset << endl;
    int a = 0;
}
