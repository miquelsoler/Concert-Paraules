#pragma once
#include "ofMain.h"

class PMParticle{

	public:
		PMParticle(int x, int y, ofPoint prevPoint);

		void update();
		void draw();		
		
		ofPoint pos;
        ofPoint originalPos;
		ofPoint vel;
		ofPoint frc;
		
		float drag; 
		float uniqueVal;
		float scale;
		
    
        float bornTime;
        int alphaValue;
		
		vector <ofPoint> * attractPoints;
};