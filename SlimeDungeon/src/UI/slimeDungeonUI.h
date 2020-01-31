#pragma once

#include "ofMain.h"
#include "ofxGui.h"
#include "Domain/SlimeDungeonController.h"
#include "Domain/Renderer.h"

class SlimeDungeonUI : public ofBaseApp{
	
public:
	void setup();
	void update();
	void draw();
	
	void exit();

	void keyPressed(int key);
	void keyReleased(int key);
	void mouseMoved(int x, int y );
	void mouseDragged(int x, int y, int button);
	void mousePressed(int x, int y, int button);
	void mouseReleased(int x, int y, int button);
	void mouseEntered(int x, int y);
	void mouseExited(int x, int y);
	void windowResized(int w, int h);
	void dragEvent(ofDragInfo dragInfo);
	void gotMessage(ofMessage msg);		

	void circleResolutionChanged(int & circleResolution);

	bool bHide;

	
	//CaptureTool ------------------------------------------
	ofxGuiGroup captureToolsGroup;

	ofxButton screenshotBtn;
	ofParameter<bool> partialScreenshot;
	bool recordMode = false;
	size_t recordModeEntryTime;
	size_t recordModeTimeLimit;


	//-----------------------------------------------


	//Parameters
	ofParameter<float> radius;
	ofParameter<ofColor> color;
	ofParameter<glm::vec2> center;
	ofParameter<int> circleResolution;
	ofParameter<bool> filled;
	ofParameter<bool> twoCircles;
	ofParameter<string> screenSize;

	int screenWidth, screenHeight;


	//Buttons
	
	ofxButton ringButton;

	ofxPanel gui;

	ofSoundPlayer ring;

private:
	SlimeDungeonController sdCtrl;
	bool hasImgExtension(ofFile file);

	//Pressed
	void ringButtonPressed();
	void screenshotBtnPressed();
};

