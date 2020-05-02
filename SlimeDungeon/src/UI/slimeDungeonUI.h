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

	// --Shape Material
	ofxGuiGroup materialGroup;
	ofxToggle darkMaterialBtn;
	ofxToggle sparklingMaterialBtn;
	ofxToggle plainMaterialBtn;

	//void oneMaterialBtnPressed(string materialName, bool materialBtnPressed);
	void darkMaterialBtnPressed(bool &darkMaterialBtnPressed);
	void sparklingMaterialBtnPressed(bool &sparklingMaterialBtnPressed);
	void plainMaterialBtnPressed(bool &plainMaterialBtnPressed);


	// --Ball texture --
	ofxGuiGroup ballTextureGroup;
	ofxToggle ballScaleTextureBtn;
	ofxToggle ballSporeTextureBtn;
	ofxToggle ballMoltenTextureBtn;
	bool ballScaleTextureActive;
	bool ballSporeTextureActive;
	bool ballMoltenTextureActive;
	string ballScaleTextureFile;
	string ballSporeTextureFile;
	string ballMoltenTextureFile;
	
	void updateBallTexture();
	//void ballTextureScaleBtnPressed(bool &earthTextureBtnPressed);
	//void ballTextureSporeBtnPressed(bool &earthTextureBtnPressed);
	//void ballTextureMoltenBtnPressed(bool &earthTextureBtnPressed);
	
	

	//ImportTools--------------------------------------------
	ofxGuiGroup importToolsGroup;
	ofxButton importImageBtn;
	ofxToggle BlurImage;
	ofxToggle mapTonalImage;
	ofxToggle gaussImage;
	ofxToggle bilatImage;
	bool isBlur;
	void BlurBtnPressed(bool& isBlurBtnPressed);
	void mapBtnPressed(bool& isMapBtnPressed);
	void gaussBtnPressed(bool& isGaussBtnPressed);
	void bilatBtnPressed(bool& isBilatBtnPressed);

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

	//PBR sphere
	ofxGuiGroup group_material_factor;
	ofParameter<float> slider_metallic;
	ofParameter<float> slider_roughness;
	ofParameter<float> slider_occlusion;
	ofParameter<float> slider_brightness;
	ofxToggle drawSphere;
	void drawSpherePressed(bool& drawSpherePressed);



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

	//Lighting
	ofxGuiGroup lightingGroup;
	ofxToggle drawLightGizmoBtn;
	ofxToggle activeAmbientLightBtn;
	ofxToggle activeDirLightBtn;
	ofxToggle activePonctLightBtn;
	ofxToggle activeSpotLightBtn;

	void drawLightGizmoBtnPressed(bool &drawLightGizmoPressed);
	void activeAmbientLightBtnPressed(bool &activeAmbientLightPressed);
	void activeDirLightBtnPressed(bool &activeDirLightPressed);
	void activePonctLightBtnPressed(bool &activePonctLightPressed);
	void activeSpotLightBtnPressed(bool &activeSpotLightPressed);

	//Edit Lighting
	ofxGuiGroup editLightingGroup;
	ofParameter<float> activeLightPosX, activeLightPosY, activeLightPosZ;
	float prevActiveLightPosX, prevActiveLightPosY, prevActiveLightPosZ;
	ofParameter<ofColor> activeLightDiffuseColor, activeLightSpecularColor;
	ofColor prevActiveLightDiffuseColor, prevActiveLightSpecularColor;
	
	//Ambiant Light Specific
	ofParameter<ofColor> activeAmbiantLightColor;
	ofColor prevActiveAmbientLightColor;

	//Spot Light Specific
	ofParameter<float> spotCutoff, spotConcentration;
	float prevSpotCutOff, prevSpotConcentration;

	//Catmull-Rom
	bool catRomEdit;
	string noSplineMsg;
	ofxGuiGroup catRomGroup;
	ofxToggle catRomEditBtn;
	ofxToggle catRomShowBtn;
	ofxTextField activeCatRomSpline;
	ofxButton catRomNextSplineBtn;
	ofxButton catRomAddSplineBtn;
	ofxButton catRomDeleteSplineBtn;

	void catRomShowBtnPressed(bool &isCatRomShowBtnPressed);
	void catRomEditBtnPressed(bool &isCatRomEditBtnPressed);
	void addSplineBtnPressed();
	void nextSplineBtnPressed();
	void deleteSplineBtnPressed();
	

	//Panel
	ofxPanel gui;
	ofxPanel scene;
	ofxPanel bezSurface;


	ofShader mapTon;
	ofImage screen;
	bool screenB;


	// Surface de Bézier
	ofParameter<bool> drawSurface;
	ofParameter<int> curve;
	ofParameter<int> point;
	ofParameter<int> direction;
	ofxButton move;


private:
	SlimeDungeonController sdCtrl;
	bool hasImgExtension(ofFile file);
	

	//Pressed
	void setDefaultParameter();
	void screenshotBtnPressed();
	void importImageBtnPressed();

	//Instructions pour l'utilisateur
	std::vector<string> instructions;

	ofLight light;
};
