//
// Created by Eduard Frigola on 23/11/15.
//

#include "PMParticle.h"

//------------------------------------------------------------------
PMParticle::PMParticle(ofPoint position, ofPoint prevPosition, ofImage *_image){
	attractPoints = NULL;
    originalPos=position;
//    vel=originalPos-prevPosition;
//    cout<<vel<<endl;
//    vel.x=-originalPos.x+prevPosition.x;
//    vel.y=originalPos.y-prevPosition.y;
    
    image=_image;
    
    uniqueVal = ofRandom(-10000, 10000);
    
    lifetime=5;
    
    pos.x = originalPos.x;
    pos.y = originalPos.y;
    
//    vel.x = ofRandom(-0.9, 0.9);
//    vel.y = ofRandom(-0.9, 0.9);
    velocity=0.9;
    
    vel.x = ofRandom(-velocity, velocity);
    vel.y = ofRandom(-velocity, velocity);
    
    frc   = ofPoint(0,0,0);
    
    scale = ofRandom(0.5, 1.0);
    
    drag  = ofRandom(0.95, 0.998);
    
    bornTime=ofGetElapsedTimeMillis();
}

//------------------------------------------------------------------
void PMParticle::update(){
    
    
    alphaValue=(int)(ofGetElapsedTimeMillis()-bornTime);
    alphaValue/=lifetime;
    alphaValue=255-alphaValue;
    if(alphaValue<=0){
        bornTime=0.0f;
    }
    vel *= drag;
    pos += vel;


//	//1 - APPLY THE FORCES BASED ON WHICH MODE WE ARE IN
//	
//	if( mode == PARTICLE_MODE_ATTRACT ){
//		ofPoint attractPt(ofGetMouseX(), ofGetMouseY());
//		frc = attractPt-pos; // we get the attraction force/vector by looking at the mouse pos relative to our pos
//		frc.normalize(); //by normalizing we disregard how close the particle is to the attraction point 
//		
//		vel *= drag; //apply drag
//		vel += frc * 0.6; //apply force
//	}
//	else if( mode == PARTICLE_MODE_REPEL ){
//		ofPoint attractPt(ofGetMouseX(), ofGetMouseY());
//		frc = attractPt-pos; 
		
		//let get the distance and only repel points close to the mouse
//		float dist = frc.length();
//		frc.normalize(); 
//		
//		vel *= drag; 
//		if( dist < 150 ){
//			vel += -frc * 0.6; //notice the frc is negative 
//		}else{
//			//if the particles are not close to us, lets add a little bit of random movement using noise. this is where uniqueVal comes in handy. 			
//			frc.x = ofSignedNoise(uniqueVal, pos.y * 0.01, ofGetElapsedTimef()*0.2);
//			frc.y = ofSignedNoise(uniqueVal, pos.x * 0.01, ofGetElapsedTimef()*0.2);
//			vel += frc * 0.04;
//		}
//    
    
    
//	}
//	else if( mode == PARTICLE_MODE_NOISE ){
//		//lets simulate falling snow 
//		//the fake wind is meant to add a shift to the particles based on where in x they are
//		//we add pos.y as an arg so to prevent obvious vertical banding around x values - try removing the pos.y * 0.006 to see the banding
//		float fakeWindX = ofSignedNoise(pos.x * 0.003, pos.y * 0.006, ofGetElapsedTimef() * 0.6);
//		
//		frc.x = fakeWindX * 0.25 + ofSignedNoise(uniqueVal, pos.y * 0.04) * 0.6;
//		frc.y = ofSignedNoise(uniqueVal, pos.x * 0.006, ofGetElapsedTimef()*0.2) * 0.09 + 0.18;
//
//		vel *= drag; 
//		vel += frc * 0.4;
//		
//		//we do this so as to skip the bounds check for the bottom and make the particles go back to the top of the screen
//		if( pos.y + vel.y > ofGetHeight() ){
//			pos.y -= ofGetHeight();
//		}
//	}
//	else if( mode == PARTICLE_MODE_NEAREST_POINTS ){
//		
//		if( attractPoints ){
//
//			//1 - find closest attractPoint 
//			ofPoint closestPt;
//			int closest = -1; 
//			float closestDist = 9999999;
//			
//			for(unsigned int i = 0; i < attractPoints->size(); i++){
//				float lenSq = ( attractPoints->at(i)-pos ).lengthSquared();
//				if( lenSq < closestDist ){
//					closestDist = lenSq;
//					closest = i;
//				}
//			}
//			
//			//2 - if we have a closest point - lets calcuate the force towards it
//			if( closest != -1 ){
//				closestPt = attractPoints->at(closest);				
//				float dist = sqrt(closestDist);
//				
//				//in this case we don't normalize as we want to have the force proportional to distance 
//				frc = closestPt - pos;
//		
//				vel *= drag;
//				 
//				//lets also limit our attraction to a certain distance and don't apply if 'f' key is pressed
//				if( dist < 300 && dist > 40 && !ofGetKeyPressed('f') ){
//					vel += frc * 0.003;
//				}else{
//					//if the particles are not close to us, lets add a little bit of random movement using noise. this is where uniqueVal comes in handy. 			
//					frc.x = ofSignedNoise(uniqueVal, pos.y * 0.01, ofGetElapsedTimef()*0.2);
//					frc.y = ofSignedNoise(uniqueVal, pos.x * 0.01, ofGetElapsedTimef()*0.2);
//					vel += frc * 0.4;
//				}
//				
//			}
//		
//		}
//		
//	}

	
	//2 - UPDATE OUR POSITION
	
	
//	
//	//3 - (optional) LIMIT THE PARTICLES TO STAY ON SCREEN 
//	//we could also pass in bounds to check - or alternatively do this at the ofApp level
//	if( pos.x > ofGetWidth() ){
//		pos.x = ofGetWidth();
//		vel.x *= -1.0;
//	}else if( pos.x < 0 ){
//		pos.x = 0;
//		vel.x *= -1.0;
//	}
//	if( pos.y > ofGetHeight() ){
//		pos.y = ofGetHeight();
//		vel.y *= -1.0;
//	}
//	else if( pos.y < 0 ){
//		pos.y = 0;
//		vel.y *= -1.0;
//	}	

}

//------------------------------------------------------------------
void PMParticle::draw(){

//    ofSetColor(255, 63, 180, alphaValue);
    ofSetColor(color, alphaValue);
			
	ofDrawCircle(pos.x, pos.y, scale * 4.0f);
//    image->draw(pos, scale, scale);
}

void PMParticle::setVelocity(float _velocity)
{
    if(_velocity!=velocity){
        velocity=_velocity;
        vel.x = ofRandom(-velocity, velocity);
        vel.y = ofRandom(-velocity, velocity);
    }
}

void PMParticle::setLife(float life)
{
    lifetime=life;
}

void PMParticle::setBounceWalls(bool bouncy)
{
    bounceWalls=bouncy;
}