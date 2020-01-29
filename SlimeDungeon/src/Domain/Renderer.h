/**
* @brief Classe qui effectue le rendu des images de l'application
*
*/

#pragma once
#include "ofMain.h"

class Renderer
{
	ofImage imageImport(const string filename);
	void imageExport(ofImage toExportImg, string filename) const;
};

