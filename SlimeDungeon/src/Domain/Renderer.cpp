#include "Renderer.h"


Renderer::Renderer() 
{

}


void Renderer::setup()
{
	//CaptureTool
	recordMode = false;
}

void Renderer::update()
{
}

void Renderer::draw()
{
	
	if(recordMode) drawRecordModeBorder();
	
}


void Renderer::drawRectangle(float x1, float y1, float x2, float y2) const
{
	ofDrawRectangle(x1, y1, x2 - x1, y2 - y1);
}


/*
* @brief Importe l'image sous le nom de fichier passé en argument.
*/
ofImage Renderer::imageImport(const string filename) {
	return ofImage(filename);
}


/*
* @brief Exporte une image sous le nom passé en argument.
*/
void Renderer::exportImg(ofImage imgToExport, string filename) const
{
	imgToExport.save(filename);
}

void Renderer::drawRecordModeBorder()
{
	saveStrokeState();

	ofSetColor(ofColor::red);
	ofSetLineWidth(5);
	if (ofGetFill() == 1) { //Was filling before
		ofNoFill();
		drawRectangle(0, 0, ofGetWidth(), ofGetHeight());
		ofFill();
	}
	else drawRectangle(0, 0, ofGetScreenWidth(), ofGetScreenHeight());
	restorePrevStrokeState();
}

void Renderer::videoExport() {
	//TODO
}

void Renderer::saveStrokeState()
{
	prevStrokeColorR = strokeColorR;
	prevStrokeColorG = strokeColorG;
	prevStrokeColorB = strokeColorB;
	prevStrokeColorA = strokeColorA;
	prevStrokeWidth = strokeWidth;
}

void Renderer::restorePrevStrokeState()
{
	strokeColorR = prevStrokeColorR;
	strokeColorG = prevStrokeColorG;
	strokeColorB = prevStrokeColorB;
	strokeColorA = prevStrokeColorA;
	strokeWidth = prevStrokeWidth;
	ofSetColor(strokeColorR, strokeColorG, strokeColorB, strokeColorA);
	ofSetLineWidth(strokeWidth);
}
