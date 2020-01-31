/**
* @brief Classe qui effectue le rendu des images de l'application
*
*/

#pragma once
#include "ofMain.h"

class Renderer
{
public:
	Renderer();
	ofImage imageImport(const string filename);
	void exportImg(ofImage imgToExport, string filename) const;
	
	void setup();
	void update();


	void draw();
	//Vector primitive
	unsigned char strokeColorR, strokeColorG, strokeColorB, strokeColorA;
	unsigned char prevStrokeColorR, prevStrokeColorG, prevStrokeColorB, prevStrokeColorA;
	float strokeWidth, prevStrokeWidth;
	
	void saveStrokeState();
	void restorePrevStrokeState();
	void drawRectangle(float x1, float y1, float x2, float y2) const;




	//RecordMode
	bool recordMode;

	void drawRecordModeBorder();
	void videoExport();

};

