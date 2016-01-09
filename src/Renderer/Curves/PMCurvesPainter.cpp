//
// Created by Miquel �ngel Soler on 15/12/15.
//

#include "PMCurvesPainter.h"

static const int POS_MARGIN = 1;
bool drawDebug = false;

PMCurvesPainter::PMCurvesPainter(PMUICanvasCurvesRenderer *_gui,PMRendererCurves* _r)
{
    myRenderer = _r;
    gui = _gui;
    
    // init values
    
    // vector Graphics config
    vec.setColor(255, 255 , 255);
    vec.noFill();
    vec.enableDraw();

    useMouse=false;
}

void PMCurvesPainter::setup()
{
    // create a vector of points already ...
    for(int i=0;i<4;i++)
    {
        ofPoint p = ofPoint(ofGetWidth()/2 + (10*i),ofGetHeight()/2);
        points.push_back(p);
    }
    
}

void PMCurvesPainter::update()
{
    
    float delta = gui->getDelta();
    float mX,mY;
    
    if(useMouse)
    {
        mX = ofClamp(ofGetMouseX(),0.0,ofGetWidth());
        mY = ofClamp(ofGetMouseY(),0.0,ofGetHeight());
    }
    else
    {
//        float getDeltaPitch()         { return pitchParams.deltaPitch; }
//        float getDeltaEnergy()        { return energyParams.deltaEnergy; }
//        float getEnergyMin()          { return energyParams.min; }
//        float getEnergyMax()          { return energyParams.max; }
//        float getPitchMin()           { return pitchParams.min; }
//        float getPitchMax()           { return pitchParams.max; }
//        float getSmoothedPitch()      { return pitchParams.smoothedPitch; }
//        float getSmoothedEnergy()     { return energyParams.smoothedEnergy; }

        float cx = myRenderer->getSmoothedPitch();
        float cy = (PMBaseRenderer*)(myRenderer)->getSmoothedPitch();
        
        mX = ofGetWidth() * cx;
        mY = ofGetHeight() * cy;
    }
    
    float ny = mY / float(ofGetHeight());
    ny -= 0.5f;
    
    bool isNegative=false;
    if(ny<0) isNegative = true;
    
    ny = pow(fabs(ny),gui->getPowExponent());
    
    if(isNegative) ny=-ny;
    
    
    if(gui->getMode()==1)
    {
        if(points.size()>1)
        {
            turnDirection = lineDirection.normalize();
            turnDirection.rotate(gui->getMaxRotation() * ny * ofRandom(0.5,2.5),ofVec3f(0,0,1));
            
            ofPoint p = points[points.size()-1] + turnDirection*gui->getSpeed()*myRenderer->getSmoothedEnergy();
            
            /// DELTA SMOOTHING
            p = (p*delta) + (points[points.size()-1]*(1.0-delta));
            
            controlBounds(p);
        }
    }
    else if(gui->getMode()==2)
    {
        if(points.size()>1)
        {
            //            posX = fmod(posX+10,ofGetWidth());
            posX = posX + (gui->getSpeed()*myRenderer->getSmoothedEnergy());
            ofPoint p = ofPoint(posX,mY );
            
            /// DELTA SMOOTHING
            p = (p*delta) + (points[points.size()-1]*(1.0-delta));
            
            controlBounds(p);
        }
        
    }
    else if(gui->getMode()==3)
    {
        
        if(points.size()>1)
        {
            posY = posY + (gui->getSpeed()* myRenderer->getSmoothedEnergy());
            ofPoint p = ofPoint(mX ,posY);
            
            
            /// DELTA SMOOTHING
            p = (p*delta) + (points[points.size()-1]*(1.0-delta));
            
            controlBounds(p);
        }
        
    }
    
    
    

    
}

void PMCurvesPainter::draw()
{
//    // draw medium line just as reference
//    ofSetLineWidth(1.0);
//    ofSetColor(0,255,255);
//    ofDrawLine(0,ofGetHeight()/2,ofGetWidth(),ofGetHeight()/2);
    
    // draw it
    //-----------------------
    if(points.size()>3)
    {
        
        // DRAW CURVE !!
        /////////////////
        // draw the curve from the last 4 points ...
        ofSetLineWidth(gui->getThickness()*myRenderer->getSmoothedEnergy());
        ofSetColor(gui->getCurveColor());
       
        //ofEnableSmoothing();
        
        ofNoFill();

        vec.curve(points[0].x,/* + (ammount * ofNoise(points[0].x)/ofGetWidth()),*/
                  points[0].y,/* + (ammount * ofNoise(points[0].y)/ofGetHeight()),*/
                  points[1].x,/* + (ammount * ofNoise(points[1].x)/ofGetWidth()),*/
                  points[1].y,/* + (ammount * ofNoise(points[1].y)/ofGetHeight()),*/
                  points[2].x,/* + (ammount * ofNoise(points[2].x)/ofGetWidth()),*/
                  points[2].y,/*+ (ammount * ofNoise(points[2].y)/ofGetHeight()),*/
                  points[3].x,/* + (ammount * ofNoise(points[3].x)/ofGetWidth()),*/
                  points[3].y);/* + (ammount * ofNoise(points[3].y)/ofGetHeight()));*/
        //ofDisableSmoothing();
        
//        cout << "points.....mode = " << gui->getMode() << endl;
//        cout << points[0] << " ___ " << points[1] << "  ___  " << points[2] << "  ___  " << points[3] << "  ___  " << endl;
//        cout << "............" << endl;
        
        // LINE DIRECTIONS
        //////////////////////////////////////
        // we keep the values of the last 3 poins added (the last 4th is discarded)
        ofPoint pLast3 = points[3];
        ofPoint pLast2 = points[2];
        ofPoint pLast1 = points[1];
        
        vector<ofPoint> interPointDirections;
        
        // we've 4 points ... calculate the directions for each pair of vertex vector
        for(int i=0;i<3;i++)
        {
            ofVec2f v = ofVec2f(points[i+1]-points[i]);
            v.normalize();
            interPointDirections.push_back(v);
        }
        
        // calculate the average direction of this 4 point curve (3 vec in between vertices)
        for(int i=0;i<3;i++)
        {
            lineDirection = lineDirection + interPointDirections[i];
            
        }
        lineDirection = (lineDirection/3.0).normalize();
        
        
        
        /// DRAW DEBUG
        /////////////////
        
        // draw the points
        ///////////////////
        glPointSize(gui->getThickness()*myRenderer->getSmoothedEnergy());
        ofSetColor(gui->getCurveColor());
        glBegin(GL_POINTS);
        glVertex2f(points[0].x,points[0].y);
        glVertex2f((points[0].x + points[1].x)/2 ,(points[0].y + points[1].y)/2 );
        glVertex2f(points[1].x,points[1].y);
        glVertex2f((points[1].x + points[2].x)/2 ,(points[1].y + points[2].y)/2 );
        glVertex2f(points[2].x,points[2].y);
        glVertex2f((points[2].x + points[3].x)/2 ,(points[2].y + points[3].y)/2 );
        glVertex2f(points[3].x,points[3].y);
        glEnd();
        
        if(drawDebug)
        {
            
            /// DRAW lineDirection
            ofSetColor(0,255,255,64);
            ofDrawLine(points[3],points[3] + lineDirection*100);
            
            // DRAW turnDirection
            ofSetColor(0,255,0,64);
            ofDrawLine(points[3],points[3] + turnDirection*50);
        }
        
        
        // clear the points and add the last 3 ... so discarding the 4th
        points.clear();
        points.push_back(pLast1);
        points.push_back(pLast2);
        points.push_back(pLast3);
    }
    
//    // print mode in screen
//    if      (gui->getMode() ==1) ofDrawBitmapString("mode 0 : Curve Turn", 10, 10);
//    else if (gui->getMode() ==2) ofDrawBitmapString("mode 1 : Curve X", 10, 10);
//    else if (gui->getMode() ==3) ofDrawBitmapString("mode 2 : Curve Y", 10, 10);

    /// LINE ADDONS
    //////////////////
    
    // add a small circles arround the vector
    float p = ofRandomuf();
    ofFill();
    ofSetColor(gui->getCurveColor());
    if(p<0.75)
    {
        ofDrawCircle(points[points.size()-3].x + ofRandomf()*3,
                     points[points.size()-3].y + ofRandomf()*3,
                     gui->getThickness()*myRenderer->getSmoothedEnergy()*gui->getBubbleness());
    }
    ofNoFill();
    
    
}




void PMCurvesPainter::setColor(ofColor _color)
{
    color = ofColor(_color.r, _color.g, _color.b, _color.a);
}

void PMCurvesPainter::clear()
{
    points.clear();
    
    // create a vector of points already ...
    for(int i=0;i<4;i++)
    {
        ofPoint p = ofPoint(ofGetWidth()/2*i,ofGetHeight()/2);
        points.push_back(p);
    }

}

void PMCurvesPainter::controlBounds(ofPoint p)
{
    float margin=10;
    
    ofPoint res =  p ; //ofPoint(ofGetWidth()/2, ofGetHeight()/2);
    if(points.size()>1)
    {
        if ( ( p.x > ofGetWidth() + margin ) || (p.x < -margin) )
        {
            // we're out !! bounce !!
            ofPoint lastPoint = points[points.size()-1];
            ofPoint lastVec = p - lastPoint;
            ofPoint newOrigin;
            
            if(p.x<0)
            {
                newOrigin = ofPoint(ofGetWidth()+margin,lastPoint.y);
            }
            else
            {
                newOrigin = ofPoint(-margin,lastPoint.y);
            }
            
            
            points.clear();
            points.push_back(newOrigin + lastVec * 0.0);
            points.push_back(newOrigin + lastVec * 0.33);
            points.push_back(newOrigin + lastVec * 0.66);
            points.push_back(newOrigin + lastVec * 1.0);
            
            if(gui->getMode()==2) posX=0;
            else if (gui->getMode()==3) posY=0;
            
            return;
        }
        
        
        else if ( ( p.y > ofGetHeight()+ margin ) || (p.y < - margin) )
        {
            // we're out !! bounce !!
            ofPoint lastPoint = points[points.size()-1];
            ofPoint lastVec = p - lastPoint;
            ofPoint newOrigin;
            
            if(p.y<0)
            {
                newOrigin = ofPoint(lastPoint.x,ofGetHeight()+margin);
            }
            else
            {
                newOrigin = ofPoint(lastPoint.x,-margin);
            }
            
            if(gui->getMode()==2) posX=0;
            else if (gui->getMode()==3) posY=0;
            
            
            points.clear();
            points.push_back(newOrigin + lastVec * 0.0);
            points.push_back(newOrigin + lastVec * 0.33);
            points.push_back(newOrigin + lastVec * 0.66);
            points.push_back(newOrigin + lastVec * 1.0);
            
            return;
        }
        else
        {
            ofPoint newP = p;
            //p.x = p.x + ofRandom(-1,1)*500;
            //p.y = p.y + ofRandom(-1,1)*500;
            points.push_back(newP);
        }
    }
    
}



