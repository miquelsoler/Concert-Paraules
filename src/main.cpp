#include "ofMain.h"
#include "ofApp.h"

#include "Defaults.h"

//========================================================================
int main( ){
	ofSetupOpenGL(DEFAULT_WINDOW_WIDTH, DEFAULT_WINDOW_HEIGHT, DEFAULT_WINDOW_MODE);

	// this kicks off the running of my app
	// can be OF_WINDOW or OF_FULLSCREEN
	// pass in width and height too:
	ofRunApp(new ofApp());
}
