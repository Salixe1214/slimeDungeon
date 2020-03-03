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
	void publishExitEvent();
	
	//Selection, etc.
	void checkClickInShape();
	void deleteSelectedShape();
	bool isSelectedShapeEmpty();


	//Draw ---------------
	void rendererDraw(ofParameter<ofColor>, ofParameter<ofColor>);
	void setDrawMode(bool drawMode);
	void setDrawType(int drawType);
	void addShape();
	void setFill(bool fill);

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

