/**
* @brief Classe qui effectue le rendu des images de l'application
*
*/

#pragma once
#include "ofMain.h"
//#include "Domain/Shapes/Shape.h"
#include "Domain/Shapes/TileShape.h"
#include "Domain/Shapes/SlimeShape.h"
#include "Domain/Shapes/Circle.h"
#include "Domain/Shapes/Ellipse.h"
#include "Domain/Shapes/Square.h"
#include "Domain/Shapes/Rectangle.h"
#include "Domain/Shapes/Pixel.h"
#include "Domain/Shapes/Line.h"
#include "Domain/Shapes/Shape3D.h"
#include "ofxGui.h"
#include <stack>

using namespace shape;

class Renderer
{
public:
	Renderer();

	VectorPrimitiveType shapeType;
	std::vector<Shape*> vecShapes;
	std::stack<Shape*> pastVecShapes;
	std::unordered_map<std::string, Shape*> selectedShapes;

	ofCamera camFront;
	bool isCameraMoveLeft;
	float speedDelta;
	float speedTranslation;
	float speedRotation;

	float timeCurrent;
	float timeLast;
	float timeElapsed;
	void setCameraMoveLeft(bool cameraMoveLeft);

	int count;
	int size;
	int stride;
	bool partialScreenPressed;
	bool mouseOverGUI;

	int index;
	float strokeWidthDefault;
	ofImage cursor1;
	ofImage cursor2;
	ofImage cursor3;
	ofImage cursor4;

	ofImage imageImport(const string filename);
	void exportImg(ofImage imgToExport, string filename) const;
	
	void setup(ofxPanel*);
	void update(ofParameter<ofColor>, ofParameter<ofColor>);
	void exit();

	void draw();

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

	// Fonctions inspirées des exemples du cours (Module 2/Ex04)
	void addVectorShape(VectorPrimitiveType);

	void drawZone(float x1, float y1, float x2, float y2) const;
	void drawCursor(float x, float y) const;
	void removeLastAddedVectorShape();


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

private:
	void drawShapes();
	void drawSample();
};

