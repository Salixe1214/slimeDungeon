#pragma once

#include "ofMain.h"
#include "ofxGui.h"
#include "Domain/SlimeDungeonController.h"
#include <utility> 
#include <vector>
#include <string>

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

	bool bHide;
	ofPoint mousePress, screenshotPtUpperLeft;
	ofPoint curMouse, screenshotPtDownRight, guiPosition, gui2Position;

	//DrawTools------------------------------------------
	ofxGuiGroup drawToolsGroup;
	ofxToggle drawMode;
	bool prevDrawMode;
	ofxTextField currentShapeType;
	ofxTextField shapeKeyLegend;
	

	//ImportTools--------------------------------------------
	ofxGuiGroup importToolsGroup;
	ofxButton importImageBtn;

	vector <std::pair<ofImage, ofPoint>> draggedImages;
	ofPoint dragPt;
	ofPoint positionImg;
	ofPoint distance;
	ofImage imageImport;
	bool ifImageImport;

	
	//CaptureTools ------------------------------------------
	ofxGuiGroup captureToolsGroup;
	ofImage imgToExport;
	ofxButton screenshotBtn;
	ofParameter<bool> partialScreenshot;
	bool recordMode = false, isWaitingForScreenSelection = false;
	size_t recordModeEntryTime;
	size_t recordModeTimeLimit;

	void exportScreenshot();
	void enterRecordMode();
	void exitRecordMode();

	//-----------------------------------------------


	//Parameters
	ofParameter<float> radius;
	ofParameter<ofColor> backColor1;
    ofParameter<ofColor> backColor2;
    ofParameter<ofColor> shapeColor1;
    ofParameter<ofColor> shapeColor2;
	//ofParameter<int> tileSize;
	ofParameter<glm::vec2> center;
	ofParameter<bool> filled;
	bool prevFill;
	ofParameter<string> screenSize;

	int screenWidth, screenHeight;


	//Scene
	//Overview
	ofxTextField hierarchy;
	string emptySceneMsg;
	int scenePanelWidth;
	ofxButton deleteShapeBtn;
	void deleteShapeBtnPressed();

	//Transform selectedShape 
	ofxGuiGroup transformToolsGroup;
	ofParameter<ofColor> fillColorScene, strokeColorScene;
	ofColor prevFillColorScene, prevStrokeColorScene;
	ofParameter<float> extendSelectionX,  extendSelectionY;
	float prevExtendSelectionX, prevExtendSelectionY;
	ofParameter<int> extendTileRowX, extendTileRowY;
	ofxToggle addTileRow;
	int prevExtendTileRowX, prevExtendTileRowY;
	
	//Translate
	ofxGuiGroup translationToolsGroup;
	ofParameter<float> translateX, translateY;
	float prevTranslateX, prevTranslateY;

	//Rotate
	ofxGuiGroup  rotationToolsGroup;
	ofParameter<float> rotateZ;
	float prevRotateZ;

	//Scale
	ofxGuiGroup scalingToolsGroup;
	ofxToggle keepScaleProportion;
	ofParameter<float> scaleX, scaleY;
	float prevScaleX, prevScaleY;

	//Panel
	ofxPanel gui;
	ofxPanel scene;



private:
	SlimeDungeonController sdCtrl;
	bool hasImgExtension(ofFile file);
	

	//Pressed
	void setDefaultParameter();
	void screenshotBtnPressed();
	void importImageBtnPressed();

	//Instructions pour l'utilisateur
	std::vector<string> instructions;
};
