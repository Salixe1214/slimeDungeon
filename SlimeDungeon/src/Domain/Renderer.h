/**
* @brief Classe qui effectue le rendu des images de l'application
*
*/

#pragma once
#include "ofMain.h"
#include "Domain/LightManager.h"
#include "ofxOpenCv.h"

#include "Domain/Shapes/TileShape.h"
#include "Domain/Shapes/SlimeShape.h"
#include "Domain/Shapes/Circle.h"
#include "Domain/Shapes/Ellipse.h"
#include "Domain/Shapes/Square.h"
#include "Domain/Shapes/Rectangle.h"
#include "Domain/Shapes/Pixel.h"
#include "Domain/Shapes/Line.h"
#include "Domain/Shapes/Shape3D.h"
#include "Domain/Shapes/Box.h"
#include "Domain/Shapes/Ball.h"
#include "Domain/Shapes/Image.h"
#include "Domain/CatmullRomSpline.h"
#include "ofxGui.h"
#include <stack>

#include "Cubemap.h"
#include "Domain\BezierSurface.h"

using namespace shape;

class Renderer
{
public:
	Renderer();
	void setup(ofxPanel*, glm::vec3 camInitialPos = glm::vec3(ofGetWidth() / 2, ofGetHeight() / 2, 1000));
	void update(ofParameter<ofColor>, ofParameter<ofColor>);
	void exit();

	void draw();

	LightManager* lightManager;
	VectorPrimitiveType shapeType;
	std::vector<Shape*> vecShapes;
	std::stack<Shape*> pastVecShapes;
	std::unordered_map<std::string, Shape*> selectedShapes;

	ofCamera camFront, camFig;
	bool isCameraMoveLeft;
	bool is_camera_move_right;
	bool is_camera_move_up;
	bool is_camera_move_down;
	bool is_camera_move_forward;
	bool is_camera_move_backward;

	bool is_camera_tilt_up;
	bool is_camera_tilt_down;
	bool is_camera_pan_left;
	bool is_camera_pan_right;
	bool is_camera_roll_left;
	bool is_camera_roll_right;

	bool is_camera_fov_narrow;
	bool is_camera_fov_wide;


	bool shade;


	float speedDelta;
	float speedTranslation;
	float speedRotation;
	glm::vec3 camInitialPos;
	int screenHeight, screenWidth;
	float cameraOffsetX, cameraOffsetY, offsetAngle;

	float timeCurrent;
	float timeLast;
	float timeElapsed;

	//Camera
	void setCameraMoveDown(bool isMoveDown);
	void setCameraRollLeft(bool isRollLeft);
	void setCameraRollRight(bool isRollRight);
	void setCameraMoveUp(bool isMoveUp);
	void setCameraMoveRight(bool isMoveRight);
	void setCameraMoveLeft(bool cameraMoveLeft);
	void setCameraDollyFront(bool cameraDollyFront);
	void setCameraDollyBack(bool cameraDollyBack);

	int count;
	int size;
	int stride;
	bool partialScreenPressed;
	bool mouseOverGUI;
	bool isBlurOn;

	int index;
	float strokeWidthDefault;
	ofImage cursor1;
	ofImage cursor2;
	ofImage cursor3;
	ofImage cursor4;

	ofImage imageImport(const string filename);
	void exportImg(ofImage imgToExport, string filename) const;

	void windowResizedEvent(int w, int h);

	//Selection, etc.
	void checkClickInShape();
	void highlightSelectedShape();
	void deleteSelectedShape();
	bool isSelectedShapeEmpty();
	void setPartialScreenBool(bool isPartialScreen);
	void setMouseOverGUI(bool overGUI);
	void setSelectionColor(ofColor newfillColor, ofColor newStrokeColor);
	int getSelectedShapeSize();
	string getFirstSelectedShapeName();

	//Transform
	void extendSelectionBorder(float dx, float dy);
	void addTileShapeRow(int addedXRow, int addedYRow);
	void translateSelection(float dx, float dy, float dz);
	void rotateSelectionZ(float thetaZ);
	void scaleSelection(float sx, float sy, float sz);

	void goBack();
	void reDo();


	//drawTool -----------------
	ofPoint curMouse;
	ofPoint mousePress;
	ofParameter<ofColor> fillColor, strokeColor;
	bool mouseIsPressed, isDrawing, fillShape;


	
	void setFill(bool fill);
	void setDrawMode(bool drawMode);
	void setShapeType(VectorPrimitiveType newShapeType);

	void addVectorShape(VectorPrimitiveType type);
	void addImageShape(ofImage image, ofPoint imgPoint);
	void isTheBlurOn(bool isBlur);

	void drawZone(float x1, float y1, float x2, float y2) const;
	void drawCursor(float x, float y) const;
	void removeLastAddedVectorShape();

	//Material
	std::unordered_map<std::string, ofMaterial> materialList;
	string activeMaterialName;
	void initMaterialList();
	void setActiveMaterialName(string p_activeMaterialName);


	// --texture
	string ballTextureFile;
	void setBallTextureFile(string p_ballTextureFile);

	//Vector primitive
	unsigned char strokeColorR, strokeColorG, strokeColorB, strokeColorA;
	unsigned char fillColorR, fillColorG, fillColorB, fillColorA;
	unsigned char prevStrokeColorR, prevStrokeColorG, prevStrokeColorB, prevStrokeColorA;
	float prevStrokeWidth;

	// Parametres des formes (pour le sample entre autre) A.S.
	ofParameter<float> strokeWidth;
	ofParameter<int> tileSize;
	
	void saveStrokeState();
	void restorePrevStrokeState();


	//RecordMode
	bool recordMode;

	void drawRecordModeBorder();
	void videoExport();

	// Color Picker
	ofParameter<ofColor> *color;

	// Cubemap
	Cubemap paysage;
	
	//Catmull-Rom
	std::unordered_map<string, CatmullRomSpline> catRomSplines;
	std::unordered_map<string, CatmullRomSpline>::iterator catRomSplineIt;
	string activeCatRomSplineId;
	bool catmullRomShow;

	void addEmptyCatmullRom();
	void addCatmullRom(std::vector <ofPoint> ctrlPt);
	void drawCatmullRomSplines();
	void addActiveCatmullRomPoint();
	void setCatmullRomShow(bool p_catmullRomShow);
	void setActiveCatRomSplineId(string p_activeCatRomSplineId);
	string getActiveCatRomSplineId();
	void deleteActiveCatRomSpline();
	void nextCatRomSpline();

	// Surface de Bezier
	BezierSurface bs;
	bool dessinerBS;
	
	// images
	bool blOn;
	bool tnOn;
	bool gaOn;
	bool biOn;

	//PBR sphere
	float material_metallic;
	float material_roughness;
	float material_occlusion;
	float material_brightness;
	bool drawSphereOn;
	ofVec3f position_sphere;

	ofImage texture_diffuse;
	ofImage texture_metallic;
	ofImage texture_roughness;
	ofImage texture_occlusion;

	ofShader shader_pbr;
	ofShader* shader;


private:
	void drawShapes();
	void drawSample();
};

