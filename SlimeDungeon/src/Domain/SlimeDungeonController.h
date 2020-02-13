#include "ofMain.h"
#include "Domain/Renderer.h"

#pragma once

/** @brief classe qui lie le domaine et le UI
*/
class SlimeDungeonController
{

public:
	SlimeDungeonController();
	void publishSetupEvent(ofxPanel*);

	//Draw ---------------
	void rendererDraw(ofParameter<ofColor>, ofParameter<ofColor>);
	void setDrawType(int drawType);
	void addShape();

	void exportImg(ofImage imgToExport, string filename) const;


	//Record Mode
	void publishExitRecordModeEvent();
	void publishEnterRecordModeEvent();
	
	//Mouse
	void setCurMouse(ofPoint newMousePos);
	void setMousePress(ofPoint newMousePos);
	void setCurMouseX(int x);
	void setCurMouseY(int y);
	void setRendererIsMousePressed(bool mouseIsPressed);



private:
	Renderer ctrlRenderer;
	
};

