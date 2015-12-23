#include "PMRendererTextBox.h"
#include "PMSettingsManagerPoem.h"


// TODO : finish to get Text from poems ... something does'nt work with getText() !!?!!


//--------------------------------------------------------------
PMRendererTextBox::PMRendererTextBox() : PMBaseRenderer(RENDERERTYPE_TEXTBOX)
{
    // GUI
    {
        gui = new PMUICanvasTextBoxRenderer(UI_RENDERERTYPE_TYPOGRAPHY, "TEXT_BOX",OFX_UI_FONT_MEDIUM);
        gui->init(100, 500, 200, 300);
        
    }
    myGUI = (PMUICanvasTextBoxRenderer *)gui;
    myGUI->setVisible(false);

    ofAddListener(ofEvents().keyPressed, this, &PMRendererTextBox::keyPressed);

    font.setup("./fonts/verdana.ttf", 1.25, 2048, false, 8, 2);
    
    fontSize = 40;
    boxMargins = ofVec2f(ofGetWidth()*.15,ofGetHeight()*.15);
    boxMargins = ofVec2f(100,200);
    
    text = "Oh, que cansat \n estic de la meva covarda, vella, tan salvatge terra, i com m’agradaria allunyar-me’n, nord enllà, on diuen que la gent és neta i noble, culta, rica, lliure, desvetllada i feliç! Aleshores, a la congregació, els germans dirien desaprovant: “Com l’ocell que deixa el niu, així l’home que se’n va del seu indret”, mentre jo, ja ben lluny, em riuria de la llei i de l’antiga saviesa d’aquest meu àrid poble. Però no he de seguir mai el meu somni. I em quedaré aquí fins a la mort. Car sóc també molt covard i salvatge i estimo a més amb un desesperat dolor aquesta meva pobra, bruta, trista, dissortada pàtria.";
    
    //getText();

}

//--------------------------------------------------------------
void PMRendererTextBox::setup()
{
    PMBaseRenderer::setup();
    
    logoImage.load("./images/logo.png");

    //----------------------------
    setState(RENDERERSTATE_ON);

}


//--------------------------------------------------------------
void PMRendererTextBox::update()
{
    PMBaseRenderer::update();

    if (state != RENDERERSTATE_ON) return;
    
    

}

//--------------------------------------------------------------
void PMRendererTextBox::drawIntoFBO()
{
    
    if (state != RENDERERSTATE_ON) return;

    PMUICanvasTextBoxRenderer *myGUI = (PMUICanvasTextBoxRenderer *)gui;

    fbo.begin();
    {
        float pitchSmooth = gui->getSmoothedPitch();
        float energySmooth = gui->getSmoothedEnergy();
        int s = 1 ;
        switch (s)
        {
            case 1 :
            {
//                ofSetColor(255,0,0);
//                ofSetCircleResolution(256);
//                ofDrawCircle(ofGetWidth()/2,ofGetHeight()/2,(ofGetHeight()/2)*0.5);
                ofSetColor(255);
                
                //                textBox.draw();
                int numLines = 0;
                bool wordsWereCropped;
                ofRectangle column;
                column = font.drawMultiLineColumn(text,			/*string*/
                                                  fontSize,	/*size*/
                                                  boxMargins.x, boxMargins.y,		/*where*/
                                                  ofGetWidth()-2*boxMargins.x, /*column width*/
                                                  numLines,	/*get back the number of lines*/
                                                  false,		/* if true, we wont draw (just get bbox back) */
                                                  125,			/* max number of lines to draw, crop after that */
                                                  true,		/*get the final text formatting (by adding \n's) in the supplied string;
                                                             BE ARWARE that using TRUE in here will modify your supplied string! */
                                                  &wordsWereCropped /* this bool will b set to true if the box was to small to fit all text*/
                                                  );

                
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
    
    // drawing logos
    int marginY = 30;;
    ofSetColor(255);
    ofDrawRectangle(0,ofGetHeight()-logoImage.getHeight() - marginY*2, ofGetWidth(),logoImage.getHeight()+ marginY*2);
    
    ofEnableAlphaBlending();
    logoImage.draw(ofGetWidth()/2 - logoImage.getWidth()/2,ofGetHeight()-logoImage.getHeight()- marginY);
    ofDisableAlphaBlending();
    
    fbo.end();

// Miquel: commented because it's already done in PMBaseRenderer::draw()
//    fbo.draw(0, 0);
}
//--------------------------------------------------------------------------------
void PMRendererTextBox::keyPressed ( ofKeyEventArgs& eventArgs )
{
    if (eventArgs.key == 'q')
    {
    }
}

//--------------------------------------------------------------------------------
void PMRendererTextBox::toggleGUIVisible()
{
    gui->setVisible(!gui->isVisible());
}



//--------------------------------------------------------------------------------
void PMRendererTextBox::getText()
{
    PMSettingsManagerPoem *poemSettings = &PMSettingsManagerPoem::getInstance();
    
    string strPoemFolder = poemSettings->getFolderPath();
    string strPoemFilename = poemSettings->getPoemFilename();
    
    ofBuffer buffer = ofBufferFromFile(strPoemFolder + "/" + strPoemFilename);
    
    ofBuffer::Lines lines = buffer.getLines();
    ofBuffer::Line iter = lines.begin();
    
    text = "";
    
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
            for (int i = 0; i < words.size(); ++i)
            {
                text.append(words[i]);
                text.append(" ");

//                string word = words[i];
//                string::iterator it;
//                for (it = word.begin(); it != word.end(); ++it)
//                {
//                    bool found = ofIsStringInString(charset, ofToString(*it));
//                    if (!found)
//                        charset += ofToString(*it);
//                }
            }
        }
        ++iter;
    }
    
    cout << text << endl;
}

