//
// Created by Eduard Frigola on 23/11/15.
//

#pragma once
#include "ofMain.h"

class PMParticle{

	public:
		PMParticle(ofPoint position, ofPoint prevPosition, ofImage *image);

		void update();
		void draw();
    
    ofPoint getPosition(){return originalPos;};
    bool isDead(){if(bornTime==0){return true;}else{return false;}};
private:
		ofPoint pos;
        ofPoint originalPos;
		ofPoint vel;
		ofPoint frc;
		
		float drag; 
		float uniqueVal;
		float scale;
		
    
        float bornTime;
        int alphaValue;
    
        ofImage *image;
		
		vector <ofPoint> * attractPoints;
};