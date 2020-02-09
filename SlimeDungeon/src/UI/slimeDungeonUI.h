#pragma once

#include "ofMain.h"
#include "ofxGui.h"
#include "Domain/SlimeDungeonController.h"
#include "Domain/Renderer.h"
#include <utility>

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
	void dragEvent(ofDragInfo info);
	void gotMessage(ofMessage msg);		

	void circleResolutionChanged(int & circleResolution);

	bool bHide;
	ofPoint mousePress, screenshotPtUpperRight;
	ofPoint curMouse, screenshotPtDownLeft;

	//DrawTools------------------------------------------
	ofxGuiGroup drawToolsGroup;
	ofxToggle drawMode;
	ofxTextField currentShapeType;
	ofxTextField shapeKeyLegend;
	
	std::vector<ofParameter<bool>> drawOptionVec;

	//ImportTools--------------------------------------------
	ofxGuiGroup importToolsGroup;
	ofxButton importImageBtn;
	bool importButtonYes;
	string path;

	vector <std::pair<ofImage, ofPoint>> draggedImages;
	ofPoint dragPt;
	ofPoint positionImg;
	ofPoint distance;

	
	//CaptureTools ------------------------------------------
	ofxGuiGroup captureToolsGroup;
	ofImage imgToExport;
	ofxButton screenshotBtn;
	ofParameter<bool> partialScreenshot;
	bool recordMode = false, isWaitingForScreenSelection = false;
	size_t recordModeEntryTime;
	size_t recordModeTimeLimit;
	void exportScreenshot();

	//-----------------------------------------------


	//Parameters
	ofParameter<float> radius;
	ofParameter<ofColor> backColor1;
    ofParameter<ofColor> backColor2;
    ofParameter<ofColor> shapeColor1;
    ofParameter<ofColor> shapeColor2;
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
	void importImageBtnPressed();

};

