//
// Created by Miquel �ngel Soler on 15/12/15.
//

#include "PMCurvesPainter.h"

static const int POS_MARGIN = 1;
bool drawDebug = false;

PMCurvesPainter::PMCurvesPainter(PMUICanvasCurvesRenderer *_gui)
{
    gui = _gui;

    // init values
    mode = 0;
    

}

void PMCurvesPainter::setup()
{
    // create a vector of points already ...
    for(int i=0;i<4;i++)
    {
        ofPoint p = ofPoint(ofGetWidth()/2 + (10*i),ofGetHeight()/2);
        points.push_back(p);
    }
    
    // vector Graphics config
    vec.setColor(255, 255 , 255);
    vec.noFill();
    vec.enableDraw();
}

void PMCurvesPainter::update()
{
    
    float delta = 0.45;
    float mX = ofClamp(ofGetMouseX(),0.0,ofGetWidth());
    float mY = ofClamp(ofGetMouseY(),0.0,ofGetHeight());
    
    float ny = float(mY / ofGetHeight());
    ny = ny - 0.5;
    
    bool isNegative=false;
    if(ny<0) isNegative = true;
    
    ny = pow(ny,2);
    
    if(isNegative) ny=-ny;
    
    if(mode==0)
    {
        if(points.size()>1)
        {
            
            turnDirection = lineDirection.normalize();
            turnDirection.rotate(90.0 * ny,ofVec3f(0,0,1));
            
            ofPoint p = points[points.size()-1] + turnDirection*5;
            
            /// DELTA SMOOTHING
            p = (p*delta) + (points[points.size()-1]*(1.0-delta));
            
            controlBounds(p);
        }
    }
    else if(mode==1)
    {
        if(points.size()>1)
        {
            //            posX = fmod(posX+10,ofGetWidth());
            posX = posX + 10;
            ofPoint p = ofPoint(posX,mY * ofGetHeight());
            
            /// DELTA SMOOTHING
            p = (p*delta) + (points[points.size()-1]*(1.0-delta));
            
            controlBounds(p);
        }
        
    }
    else if(mode==2)
    {
        if(points.size()>1)
        {
            posY = posY + 10;
            ofPoint p = ofPoint(mX * ofGetWidth(),posY);
            
            
            /// DELTA SMOOTHING
            p = (p*delta) + (points[points.size()-1]*(1.0-delta));
            
            controlBounds(p);
        }
        
    }
    
    
    

    
}

void PMCurvesPainter::draw()
{
    // draw medium line just as reference
    ofSetLineWidth(1.0);
    ofSetColor(0,255,255);
    ofDrawLine(0,ofGetHeight()/2,ofGetWidth(),ofGetHeight()/2);
    
    // draw it
    //-----------------------
    if(points.size()>3)
    {
        
        // DRAW CURVE !!
        /////////////////
        // draw the curve from the last 4 points ...
        ofSetLineWidth(ofMap(ofGetMouseX(),0,ofGetWidth(),0.0,10.0));
        ofSetColor(255,128,0);
        ofEnableSmoothing();
        vec.curve(points[0].x,/* + (ammount * ofNoise(points[0].x)/ofGetWidth()),*/
                  points[0].y,/* + (ammount * ofNoise(points[0].y)/ofGetHeight()),*/
                  points[1].x,/* + (ammount * ofNoise(points[1].x)/ofGetWidth()),*/
                  points[1].y,/* + (ammount * ofNoise(points[1].y)/ofGetHeight()),*/
                  points[2].x,/* + (ammount * ofNoise(points[2].x)/ofGetWidth()),*/
                  points[2].y,/*+ (ammount * ofNoise(points[2].y)/ofGetHeight()),*/
                  points[3].x,/* + (ammount * ofNoise(points[3].x)/ofGetWidth()),*/
                  points[3].y);/* + (ammount * ofNoise(points[3].y)/ofGetHeight()));*/
        ofDisableSmoothing();
        
        
        
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
        
        if(drawDebug)
        {
            // draw the points
            ///////////////////
            glPointSize(10);
            ofSetColor(255,0,0,32);
            glBegin(GL_POINTS);
            glVertex2f(points[0].x,points[0].y);
            glVertex2f(points[1].x,points[1].y);
            glVertex2f(points[2].x,points[2].y);
            glVertex2f(points[3].x,points[3].y);
            glEnd();
            
            /// DRAW lineDirection
            ofSetColor(0,255,255,32);
            ofDrawLine(points[3],points[3] + lineDirection*100);
            
            // DRAW turnDirection
            ofSetColor(0,255,0,32);
            ofDrawLine(points[3],points[3] + turnDirection*50);
        }
        
        
        // clear the points and add the last 3 ... so discarding the 4th
        points.clear();
        points.push_back(pLast1);
        points.push_back(pLast2);
        points.push_back(pLast3);
    }
    
    // print mode in screen
    if      (mode ==0) ofDrawBitmapString("mode 0 : Curve Turn", 10, 10);
    else if (mode ==1) ofDrawBitmapString("mode 1 : Curve X", 10, 10);
    else if (mode ==2) ofDrawBitmapString("mode 2 : Curve Y", 10, 10);
    
    
    /// LINE ADDONS
    // add a small circles arround the vector
    float p = ofRandomuf();
    ofFill();
    ofSetColor(255,138,0);
    if(p<0.05)
    {
        ofDrawCircle(points[points.size()-3].x + ofRandomf()*3,
                     points[points.size()-3].y + ofRandomf()*3,
                     ofMap(ofGetMouseX(),0,ofGetWidth(),0.0,8.0));
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
