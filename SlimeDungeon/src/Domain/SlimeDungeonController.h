#include "ofMain.h"
#include "Domain/Renderer.h"
#include "Domain/LightManager.h"


#pragma once

/** @brief classe qui lie le domaine et le UI
*/
class SlimeDungeonController
{

public:
	SlimeDungeonController();
	void publishSetupEvent(ofxPanel*);
	void publishExitEvent();
	void publishWindowResizedEvent(int w, int h);

	void setPartialScreenBool(bool isPartialScreen);
	void setMouseOverGUI(bool overGUI);
	

	//Camera
	void setCameraMoveDown(bool isMoveDown);
	void setCameraRollLeft(bool isRollLeft);
	void setCameraRollRight(bool isRollRight);
	void setCameraMoveUp(bool isMoveUp);
	void setCameraMoveRight(bool isMoveDown);
	void setCameraMoveLeft(bool isCameraMoveLeft);
	void setCameraDollyFront(bool isCameraDollyFront);
	void setCameraDollyBack(bool isCameraDollyBack);


	//Selection, etc.
	void checkClickInShape();
	void deleteSelectedShape();
	bool isSelectedShapeEmpty();
	void changeState(bool);
	
	// Transform
	void setSelectionColor(ofColor fillColorScene, ofColor strokeColorScene);
	int getSelectedShapeSize();
	string getFirstSelectedShapeName();
	void extendSelectionBorder(float dx, float dy);
	void addTileShapeRow(int addedXRow, int addedYRow);
	
	void translateSelection(float dx, float dy, float dz =0);
	void rotateSelectionZ(float thetaZ);
	void scaleSelection(float sx, float sy, float sz=1);

	//Light
	void setDrawLightGizmo(bool drawLightGizmo);
	void setAmbientLightActive(bool isAmbientLightActive);
	void setDirLightActive(bool isDirLightActive);
	void setPonctLightActive(bool isPonctLightActive);
	void setSpotLightActive(bool isSpotLightActive);

	//Draw ---------------
	void rendererDraw(ofParameter<ofColor>, ofParameter<ofColor>);
	void setDrawMode(bool drawMode);
	void setDrawType(int drawType);
	void addShape();
	void addImage(ofImage image, ofPoint imgPoint);
	void setFill(bool fill);

	void exportImg(ofImage imgToExport, string filename) const;

	// -- texture
	void setBallTextureFile(string p_ballTextureFile);


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
	LightManager* lightManager;
	
};

