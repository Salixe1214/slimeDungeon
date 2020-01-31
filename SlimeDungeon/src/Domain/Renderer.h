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

	//RecordMode
	bool recordMode;

	void videoExport();

};

