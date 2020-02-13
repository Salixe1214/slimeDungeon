/**
* @brief Classe qui effectue le rendu des images de l'application
*
*/

#pragma once
#include "ofMain.h"
#include "ofxGui.h"

// énumération des différents types de primitives vectorielles
enum class VectorPrimitiveType { none, pixel, line, rectangle, square, ellipse, circle };

// structure de primitive vectorielle générique
struct VectorPrimitive
{
	VectorPrimitiveType type;            // 1 * 4 = 4  octets
	float                  position1[2];    // 2 * 4 = 8  octets
	float                  position2[2];    // 2 * 4 = 8  octets
	float                  strokeWidth;    // 1 * 4 = 4  octets
	// unsigned char       strokeColor[4]; // 4 * 1 = 4  octets
	// unsigned char       fillColor[4];   // 4 * 1 = 4  octets

	// Utilisation de ofColor pour la couleur (facilite le colorPicker)
	ofColor                fillColor;
	ofColor                strokeColor;
};                                        //       = 32 octets




class Renderer
{
public:
	Renderer();

	VectorPrimitiveType shapeType;
	VectorPrimitive *shapes;
	int count;
	int size;
	int stride;

	int index;
	int head;
	float strokeWidthDefault;

	ofImage imageImport(const string filename);
	void exportImg(ofImage imgToExport, string filename) const;
	
	void setup(ofxPanel*);
	void update(ofParameter<ofColor>, ofParameter<ofColor>);


	void draw();

	//drawTool -----------------
	ofPoint curMouse;
	ofPoint mousePress;
	ofParameter<ofColor> fillColor, strokeColor;
	bool mouseIsPressed, isDrawing; //TODO isDrawing n'est peut-être pas requis

	void setShapeType(VectorPrimitiveType newShapeType);

	// Fonctions inspirées des exemples du cours (Module 2/Ex04)
	void addVectorShape(VectorPrimitiveType);
	
	void drawPixel(float x, float y) const;
	void drawLine(float x1, float y1, float x2, float y2) const;
	void drawRectangle(float x1, float y1, float x2, float y2) const;
	void drawSquare(float x1, float y1, float x2, float y2) const;
	void drawEllipse(float x1, float y1, float x2, float y2) const;
	void drawCircle(float  x1, float y1, float x2, float y2) const;

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

