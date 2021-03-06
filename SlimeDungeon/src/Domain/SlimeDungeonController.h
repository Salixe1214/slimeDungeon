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
	void resetCam();

	void switchShaders();


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

	//edit Lighting
	void setActiveLightDiffuseColor(ofColor diffuseColor);
	void setActiveLightSpecularColor(ofColor specularColor);
	void setActiveAmbientLightColor(ofColor ambiantColor);
	void translateActiveLightPosX(float dx);
	void translateActiveLightPosY(float dy);
	void translateActiveLightPosZ(float dz);


	//Draw ---------------
	void rendererDraw(ofParameter<ofColor>, ofParameter<ofColor>);
	void setDrawMode(bool drawMode);
	void setDrawType(int drawType);
	void addShape();
	void addImage(ofImage image, ofPoint imgPoint);
	void setFill(bool fill);
	void BlurOn(bool isBlurOn);
	void mapTonOn(bool isMapOn);
	void gaussOn(bool isGaussOn);
	void bilatOn(bool isBilatOn);

	void exportImg(ofImage imgToExport, string filename) const;

	// -- Material
	void setActiveMaterialName(string activeMaterialName);

	// -- texture
	void setBallTextureFile(string p_ballTextureFile);

	//PBR sphere
	void setMetallic(float p_metallic);
	void setRoughness(float p_roughness);
	void setOcclusion(float p_occlusion);
	void setBrightness(float p_brightness);
	void drawSphereOn(bool p_sphereOn);


	//Record Mode
	void publishExitRecordModeEvent();
	void publishEnterRecordModeEvent();
	
	//Mouse
	void setCurMouse(ofPoint newMousePos);
	void setMousePress(ofPoint newMousePos);
	void setCurMouseX(int x);
	void setCurMouseY(int y);
	void setRendererIsMousePressed(bool mouseIsPressed);


	//Catmull-Rom
	void setCatRomShow(bool catRomShow);
	void addEmptyCatRom();
	string getActiveCatRomId();
	void addCatRomPt();
	void nextCatRomSpline();
	void deleteActiveCatRomSpline();

	// Bezier Bicubique
	void communiquerBS(bool, int c, int p, int d, bool m);



private:
	Renderer ctrlRenderer;
	LightManager* lightManager;
	
};

