#include "Renderer.h"


Renderer::Renderer()
{

}


void Renderer::setup(ofxPanel *gui)
{
	// Ajout des paramètres de dessin au gui
	gui->add(strokeWidth.set("Epaisseur du trait", 4, 1, 10));
	
	//color = p_userColor;
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
	strokeColorG = 100;
	strokeColorB = 211;
	strokeColorA = 255;
	fillColorR = 148;
	fillColorG = 255;
	fillColorB = 211;
	fillColorA = 255; 
	strokeWidthDefault = 4;
	strokeWidth = 4;//----


	mousePress.x = mousePress.y = curMouse.x = curMouse.y = 0;
	//CaptureTool
	recordMode = false;
}

void Renderer::update(ofParameter<ofColor> p_fillColor, 
					  ofParameter<ofColor> p_strokeColor)
{
	// Update des couleurs en temps réel (pour le sample)
	fillColor = p_fillColor;
	strokeColor = p_strokeColor;
}

void Renderer::draw()
{
	
	if(recordMode) drawRecordModeBorder();
	// afficher la zone de sélection

	if (mouseIsPressed)
	{
		saveStrokeState();
		strokeColorA = 100;
		if (shapeType == VectorPrimitiveType::circle || shapeType == VectorPrimitiveType::square) {
			if (curMouse.y - mousePress.y < 0)
				drawZone(mousePress.x, mousePress.y, curMouse.x, mousePress.y - fabs(curMouse.x - mousePress.x));
			else drawZone(mousePress.x, mousePress.y, curMouse.x, mousePress.y + fabs(curMouse.x - mousePress.x));
			
		}
		else drawZone(mousePress.x, mousePress.y, curMouse.x, curMouse.y);
		restorePrevStrokeState();
	}

	drawSample();

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
			ofSetColor(shapes[index].strokeColor);
			drawPixel(
				shapes[index].position2[0],
				shapes[index].position2[1]);
			break;

		case VectorPrimitiveType::line:

			ofNoFill();
			ofSetLineWidth(shapes[index].strokeWidth);
			ofSetColor(shapes[index].strokeColor);
			drawLine(
				shapes[index].position1[0],
				shapes[index].position1[1],
				shapes[index].position2[0],
				shapes[index].position2[1]);
			break;

		case VectorPrimitiveType::rectangle:
			ofFill();
			ofSetLineWidth(0);
            ofSetColor(shapes[index].fillColor);
			drawRectangle(
				shapes[index].position1[0],
				shapes[index].position1[1],
				shapes[index].position2[0],
				shapes[index].position2[1]);
			ofNoFill();
			ofSetLineWidth(shapes[index].strokeWidth);
            ofSetColor(shapes[index].strokeColor);
			drawRectangle(
				shapes[index].position1[0],
				shapes[index].position1[1],
				shapes[index].position2[0],
				shapes[index].position2[1]);
			break;
		
		case VectorPrimitiveType::square:
			ofFill();
			ofSetLineWidth(0);
			ofSetColor(shapes[index].fillColor);
			drawSquare(
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
			drawSquare(
				shapes[index].position1[0],
				shapes[index].position1[1],
				shapes[index].position2[0],
				shapes[index].position2[1]);
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
			ofFill();
			ofSetColor(
				shapes[index].fillColor[0],
				shapes[index].fillColor[1],
				shapes[index].fillColor[2]);
			drawCircle(
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
			drawCircle(
				shapes[index].position1[0],
				shapes[index].position1[1],
				shapes[index].position2[0],
				shapes[index].position2[1]);
			break;
		default:
			break;
		}
	}
}

void Renderer::drawSample()
{
	// Drawing a sample

	// Differentes valeurs du sample
	float origineX = 230; // Points d'origine
	float origineY = 30;
	float deltaX = 50;    // Tailles en x et en y
	float deltaY = 100;


	switch (shapeType)
	{
	case VectorPrimitiveType::pixel:

		ofFill();
		ofSetLineWidth(0);
		ofSetColor(strokeColor);
		drawPixel(origineX, origineY);
		break;

	case VectorPrimitiveType::line:

		ofNoFill();
		ofSetLineWidth(strokeWidth);
		ofSetColor(strokeColor);
		drawLine(origineX, origineY, origineX + deltaX, origineY + deltaY);
		break;

	case VectorPrimitiveType::rectangle:
		ofFill();
		ofSetLineWidth(0);
		ofSetColor(fillColor);
		drawRectangle(origineX, origineY, origineX + deltaX, origineY + deltaY);
		ofNoFill();
		ofSetLineWidth(strokeWidth);
		ofSetColor(strokeColor);
		drawRectangle(origineX, origineY, origineX + deltaX, origineY + deltaY);
		break;

	case VectorPrimitiveType::square:
		ofFill();
		ofSetLineWidth(0);
		ofSetColor(shapes[index].fillColor);
		drawSquare(
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
		drawSquare(
			shapes[index].position1[0],
			shapes[index].position1[1],
			shapes[index].position2[0],
			shapes[index].position2[1]);
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
		ofFill();
		ofSetColor(
			shapes[index].fillColor[0],
			shapes[index].fillColor[1],
			shapes[index].fillColor[2]);
		drawCircle(
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
		drawCircle(
			shapes[index].position1[0],
			shapes[index].position1[1],
			shapes[index].position2[0],
			shapes[index].position2[1]);
		break;
	default:
		break;
	}
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
void Renderer::addVectorShape(VectorPrimitiveType p_type)
{
	shapes[head].type = type;

	shapes[head].strokeColor = ofColor(strokeColor);
	/*
	shapes[head].strokeColor[0] = strokeColorR;
	shapes[head].strokeColor[1] = strokeColorG;
	shapes[head].strokeColor[2] = strokeColorB;
	shapes[head].strokeColor[3] = strokeColorA;*/

	shapes[head].fillColor = ofColor(fillColor);
	/*
	shapes[head].fillColor[0] = fillColorR;
	shapes[head].fillColor[1] = fillColorG;
	shapes[head].fillColor[2] = fillColorB;
	shapes[head].fillColor[3] = fillColorA;*/
	if (type == VectorPrimitiveType::square || type == VectorPrimitiveType::circle) {
		float sideLength = abs(mousePress.x - curMouse.x);
		shapes[head].position1[0] = mousePress.x;
		shapes[head].position1[1] = mousePress.y;
		if (curMouse.x - mousePress.x < 0) shapes[head].position2[0] = mousePress.x - sideLength;
		else  shapes[head].position2[0] = mousePress.x + sideLength;
		if (curMouse.y - mousePress.y < 0) shapes[head].position2[1] = mousePress.y - sideLength;
		else shapes[head].position2[1] = mousePress.y + sideLength;
	}
	else {
		shapes[head].position1[0] = mousePress.x;
		shapes[head].position1[1] = mousePress.y;

		shapes[head].position2[0] = curMouse.x;
		shapes[head].position2[1] = curMouse.y;
	}

	switch (shapes[head].type)
	{
	case VectorPrimitiveType::pixel:
		shapes[head].strokeWidth = ofRandom(1);
		break;

	case VectorPrimitiveType::line:
		shapes[head].strokeWidth = strokeWidth;
		break;

	case VectorPrimitiveType::rectangle:
		shapes[head].strokeWidth = strokeWidth;
		break;
	case VectorPrimitiveType::square:
		shapes[head].strokeWidth = strokeWidth;
		break;
	case VectorPrimitiveType::ellipse:
		shapes[head].strokeWidth = strokeWidth;
		break;
	case VectorPrimitiveType::circle:
		shapes[head].strokeWidth = strokeWidth;
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
	ofDrawRectangle(x1, y1, x2 - x1, y2 - y1);
}

// fonction qui dessine une ellipse
void Renderer::drawEllipse(float x1, float y1, float x2, float y2) const
{
	float diameter_x = x2 - x1;
	float diameter_y = y2 - y1;

	ofDrawEllipse(x1 + diameter_x / 2.0f, y1 + diameter_y / 2.0f, diameter_x, diameter_y);
}

// fonction qui dessine un point
void Renderer::drawCircle(float  x1, float y1, float x2, float y2) const
{
	float diameterX = x2 - x1;
	float diameterY = y2 - y1;
	ofDrawEllipse(x1 + diameterX / 2.0f, y1 + diameterY / 2.0f, diameterX, diameterY);
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
