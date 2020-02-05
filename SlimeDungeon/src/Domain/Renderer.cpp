#include "Renderer.h"


Renderer::Renderer() 
{

}


void Renderer::setup()
{
	mouseIsPressed = false;
	isDrawing = true; //TODO changer ceci pour s'adapter avec le UI
	count = 100;
	head = 0;
	stride = sizeof(VectorPrimitive);
	size = count * stride;
	shapes = (VectorPrimitive*)std::malloc(size);
	shapeType = VectorPrimitiveType::pixel;

	//TODO TEMPORARY ---
	strokeColorR = 148;
	strokeColorG = 0;
	strokeColorB = 211;
	strokeColorA = 255;
	fillColorR = 148;
	fillColorG = 0;
	fillColorB = 211;
	fillColorA = 255; 
	strokeWidthDefault = 4;
	strokeWidth = 4;//----


	mousePress.x = mousePress.y = curMouse.x = curMouse.y = 0;
	//CaptureTool
	recordMode = false;
}

void Renderer::update()
{
}

void Renderer::draw()
{
	
	if(recordMode) drawRecordModeBorder();
	// afficher la zone de s�lection

	if (mouseIsPressed)
	{
		drawZone(mousePress.x, mousePress.y, curMouse.x, curMouse.y);
	}
	drawShapes();


}

void Renderer::drawShapes() {
	for (index = 0; index < count; ++index)
	{
		switch (shapes[index].type)
		{
		case VectorPrimitiveType::pixel:

			ofFill();
			ofSetLineWidth(0);
			ofSetColor(
				shapes[index].strokeColor[0],
				shapes[index].strokeColor[1],
				shapes[index].strokeColor[2]);
			drawPixel(
				shapes[index].position2[0],
				shapes[index].position2[1]);
			break;

		case VectorPrimitiveType::line:

			ofNoFill();
			ofSetLineWidth(shapes[index].strokeWidth);
			ofSetColor(
				shapes[index].strokeColor[0],
				shapes[index].strokeColor[1],
				shapes[index].strokeColor[2]);
			drawLine(
				shapes[index].position1[0],
				shapes[index].position1[1],
				shapes[index].position2[0],
				shapes[index].position2[1]);
			break;

		case VectorPrimitiveType::rectangle:

			ofFill();
			ofSetLineWidth(0);
			ofSetColor(
				shapes[index].fillColor[0],
				shapes[index].fillColor[1],
				shapes[index].fillColor[2]);
			drawRectangle(
				shapes[index].position1[0],
				shapes[index].position1[1],
				shapes[index].position2[0],
				shapes[index].position2[1]);
			ofNoFill();
			ofSetLineWidth(shapes[index].strokeWidth);
			ofSetColor(
				shapes[index].strokeColor[0],
				shapes[index].strokeColor[1],
				shapes[index].strokeColor[2]);
			drawRectangle(
				shapes[index].position1[0],
				shapes[index].position1[1],
				shapes[index].position2[0],
				shapes[index].position2[1]);
			break;
		
		case VectorPrimitiveType::square:
			//TODO
			break;

		case VectorPrimitiveType::ellipse:

			ofFill();
			ofSetLineWidth(0);
			ofSetCircleResolution(48);
			ofSetColor(
				shapes[index].fillColor[0],
				shapes[index].fillColor[1],
				shapes[index].fillColor[2]);
			drawEllipse(
				shapes[index].position1[0],
				shapes[index].position1[1],
				shapes[index].position2[0],
				shapes[index].position2[1]);
			ofNoFill();
			ofSetLineWidth(shapes[index].strokeWidth);
			ofSetColor(
				shapes[index].strokeColor[0],
				shapes[index].strokeColor[1],
				shapes[index].strokeColor[2]);
			drawEllipse(
				shapes[index].position1[0],
				shapes[index].position1[1],
				shapes[index].position2[0],
				shapes[index].position2[1]);
			break;
		case VectorPrimitiveType::circle:
			//TODO
			break;
		default:
			break;
		}
	}
}

/*
* @brief Importe l'image sous le nom de fichier pass� en argument.
*/
ofImage Renderer::imageImport(const string filename) {
	return ofImage(filename);
}


/*
* @brief Exporte une image sous le nom pass� en argument.
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


// fonction qui vide le tableau de primitives vectorielles
//void Renderer::reset()
//{
//	for (index = 0; index < count; ++index)
//		shapes[index].type = VectorPrimitiveType::none;
//
//	head = 0;
//
//	ofLog() << "<reset>";
//}

void Renderer::removeLastAddedVectorShape(){
	head--;
	shapes[head].type = VectorPrimitiveType::none;
}

void Renderer::setShapeType(VectorPrimitiveType newShapeType)
{
	shapeType = newShapeType;
}

// fonction qui ajoute une primitive vectorielle au tableau
void Renderer::addVectorShape(VectorPrimitiveType type)
{
	shapes[head].type = type;

	shapes[head].position1[0] = mousePress.x;
	shapes[head].position1[1] = mousePress.y;

	shapes[head].position2[0] = curMouse.x;
	shapes[head].position2[1] = curMouse.y;

	shapes[head].strokeColor[0] = strokeColorR;
	shapes[head].strokeColor[1] = strokeColorG;
	shapes[head].strokeColor[2] = strokeColorB;
	shapes[head].strokeColor[3] = strokeColorA;

	shapes[head].fillColor[0] = fillColorR;
	shapes[head].fillColor[1] = fillColorG;
	shapes[head].fillColor[2] = fillColorB;
	shapes[head].fillColor[3] = fillColorA;

	switch (shapes[head].type)
	{
	case VectorPrimitiveType::pixel:
		shapes[head].strokeWidth = ofRandom(1, 64);
		break;

	case VectorPrimitiveType::line:
		shapes[head].strokeWidth = ofRandom(1, 16);
		break;

	case VectorPrimitiveType::rectangle:
		shapes[head].strokeWidth = strokeWidthDefault;
		break;

	case VectorPrimitiveType::ellipse:
		shapes[head].strokeWidth = strokeWidthDefault;
		break;

	default:
		shapes[head].strokeWidth = strokeWidthDefault;
		break;
	}
	head = ++head >= count ? 0 : head; // boucler sur le tableau si plein
}

// Fonction prise des exemples du cours (Module 2/Ex04)
void Renderer::drawPixel(float x, float y) const
{
	int pixelX = floorf(x);
	int pixelY = floorf(y);

	ofDrawRectangle(pixelX, pixelY, 1, 1);
}

// fonction qui dessine une ligne
void Renderer::drawLine(float x1, float y1, float x2, float y2) const
{
	ofDrawLine(x1, y1, x2, y2);
}

// fonction qui dessine un rectangle
void Renderer::drawRectangle(float x1, float y1, float x2, float y2) const
{
	ofDrawRectangle(x1, y1, x2 - x1, y2 - y1);
}

void Renderer::drawSquare(float x1, float y1, float x2, float y2) const
{
	ofDrawRectangle(x1, y1, x2 - x1, y2 - y1); //TODO
}

// fonction qui dessine une ellipse
void Renderer::drawEllipse(float x1, float y1, float x2, float y2) const
{
	float diameter_x = x2 - x1;
	float diameter_y = y2 - y1;

	ofDrawEllipse(x1 + diameter_x / 2.0f, y1 + diameter_y / 2.0f, diameter_x, diameter_y);
}

// fonction qui dessine un point
void Renderer::drawCircle(float centerX, float centerY, float radius) const
{
	ofDrawEllipse(centerX, centerY, radius, radius);
}


void Renderer::drawZone(float x1, float y1, float x2, float y2) const
{
	float radius = 4.0;
	float x2_clamp = min(max(0.0f, x2), (float)ofGetWidth());
	float y2_clamp = min(max(0.0f, y2), (float)ofGetHeight());

	ofSetLineWidth(radius);
	ofSetColor(255);
	ofNoFill();
	ofDrawRectangle(x1, y1, x2_clamp - x1, y2_clamp - y1);
	ofFill();
	ofDrawEllipse(x1, y1, radius, radius);
	ofDrawEllipse(x1, y2_clamp, radius, radius);
	ofDrawEllipse(x2_clamp, y1, radius, radius);
	ofDrawEllipse(x2_clamp, y2_clamp, radius, radius);
}

void Renderer::drawCursor(float x, float y) const
{
	float length = 10.0f;
	float offset = 5.0f;

	ofSetLineWidth(2);
	ofSetColor(31);
	ofDrawLine(x + offset, y, x + offset + length, y);
	ofDrawLine(x - offset, y, x - offset - length, y);
	ofDrawLine(x, y + offset, x, y + offset + length);
	ofDrawLine(x, y - offset, x, y - offset - length);
}