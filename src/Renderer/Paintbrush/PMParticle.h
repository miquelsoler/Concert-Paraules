#pragma once
#include "ofMain.h"

class PMParticle{

	public:
		demoParticle(int x, int y, ofPoint prevPoint);

		void update();
		void draw();		
		
		ofPoint pos;
        ofPoint originalPos;
		ofPoint vel;
		ofPoint frc;
		
		float drag; 
		float uniqueVal;
		float scale;
		
		particleMode mode;
    
        float bornTime;
        int alphaValue;
		
		vector <ofPoint> * attractPoints;
};