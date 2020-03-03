#include "Renderer.h"


Renderer::Renderer()
{

}


void Renderer::setup(ofxPanel *gui)
{
	//Shapes count
	//SlimeShape::numSlimeShape = 0;
	//TileShape::numTileShape = 0;

	// Ajout des paramètres de dessin au gui
	gui->getGroup("Draw tools").add(strokeWidth.set("Epaisseur du trait", 4, 1, 10));
	gui->getGroup("Draw tools").add(tileSize.set("Tile size", 50, 1, 300));
	
	//color = p_userColor;
	mouseIsPressed = false;
	isDrawing = true; //TODO changer ceci pour s'adapter avec le UI
	count = 100;
	head = 0;
	stride = sizeof(VectorPrimitive);
	size = count * stride;
	shapes = (VectorPrimitive*)std::malloc(size);
	shapeType = VectorPrimitiveType::pixel;
	fillShape = true;

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

	//load les cursors
	cursor1.load("fleche.png");
	cursor2.load("fleche1.png");
	cursor3.load("hand.png");
	cursor4.load("hand1.png");
}

void Renderer::update(ofParameter<ofColor> p_fillColor, 
					  ofParameter<ofColor> p_strokeColor)
{
	// Update des couleurs en temps réel (pour le sample)
	fillColor = p_fillColor;
	strokeColor = p_strokeColor;
}

void Renderer::exit() {
	while (!pastVecShapes.empty())
	{
		vecShapes.push_back(pastVecShapes.top());
		pastVecShapes.pop();
	}
	vecShapes.clear();
}

void Renderer::draw()
{	
	if(recordMode) drawRecordModeBorder();
	// afficher la zone de sélection

	if (mouseIsPressed)
	{	
		saveStrokeState();
		strokeColorA = 100;
		if ((shapeType == VectorPrimitiveType::circle || shapeType == VectorPrimitiveType::square) && isDrawing) {
			if (curMouse.y - mousePress.y < 0)
				drawZone(mousePress.x, mousePress.y, curMouse.x, mousePress.y - fabs(curMouse.x - mousePress.x));
			else drawZone(mousePress.x, mousePress.y, curMouse.x, mousePress.y + fabs(curMouse.x - mousePress.x));
			
		}
		else drawZone(mousePress.x, mousePress.y, curMouse.x, curMouse.y);
		restorePrevStrokeState();
	}

	drawCursor(curMouse.x, curMouse.y);
	drawSample();
	drawShapes();
	highlightSelectedShape();
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
			ofSetColor(shapes[index].strokeColor);
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
			ofSetColor(shapes[index].fillColor);
			drawEllipse(
				shapes[index].position1[0],
				shapes[index].position1[1],
				shapes[index].position2[0],
				shapes[index].position2[1]);
			ofNoFill();
			ofSetLineWidth(shapes[index].strokeWidth);
			ofSetColor(shapes[index].strokeColor);
			drawEllipse(
				shapes[index].position1[0],
				shapes[index].position1[1],
				shapes[index].position2[0],
				shapes[index].position2[1]);
			break;
		case VectorPrimitiveType::circle:
			ofFill();
			ofSetColor(shapes[index].fillColor);
			drawCircle(
				shapes[index].position1[0],
				shapes[index].position1[1],
				shapes[index].position2[0],
				shapes[index].position2[1]);
			ofNoFill();
			ofSetLineWidth(shapes[index].strokeWidth);
			ofSetColor(shapes[index].strokeColor);
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

	//Draw vector shapes
	for (unsigned int i = 0; i < vecShapes.size(); i++) {
		vecShapes.at(i)->draw();
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
	bool sampleShape = true;

	switch (shapeType)
	{
	case VectorPrimitiveType::slime:
		SlimeShape(VectorPrimitiveType::slime, origineX, origineY, origineX + deltaX, origineY + deltaX,
			ofColor(fillColor), ofColor(strokeColor), strokeWidth).draw();
		break;	

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
		ofSetColor(fillColor);
		drawSquare(origineX, origineY, origineX + deltaX, origineY + deltaX);
		ofNoFill();
		ofSetLineWidth(strokeWidth);
		ofSetColor(strokeColor);
		drawSquare(origineX, origineY, origineX + deltaX, origineY + deltaX);
		break;

	case VectorPrimitiveType::ellipse:

		ofFill();
		ofSetLineWidth(0);
		ofSetCircleResolution(48);
		ofSetColor(fillColor);
		drawEllipse(origineX, origineY, origineX + deltaX, origineY + deltaY);
		ofNoFill();
		ofSetLineWidth(strokeWidth);
		ofSetColor(strokeColor);
		drawEllipse(origineX, origineY, origineX + deltaX, origineY + deltaY);
		break;
	case VectorPrimitiveType::circle:
		ofFill();
		ofSetColor(fillColor);
		drawCircle(origineX, origineY, origineX + deltaX, origineY + deltaX);
		ofNoFill();
		ofSetLineWidth(strokeWidth);
		ofSetColor(strokeColor);
		drawCircle(origineX, origineY, origineX + deltaX, origineY + deltaX);
		break;

	case VectorPrimitiveType::tiles:
		TileShape(VectorPrimitiveType::tiles, origineX, origineY, origineX + deltaX, origineY + deltaY,
			ofColor(fillColor), ofColor(strokeColor), strokeWidth, (int) deltaX /4, sampleShape).draw();
		break;


	default:
		break;
	}
}


void Renderer::highlightSelectedShape() {
	for (auto shape : selectedShapes) {
		shape.second->highlight();
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
void Renderer::addVectorShape(VectorPrimitiveType type)
{
	shapes[head].type = type;

	shapes[head].strokeColor = ofColor(strokeColor);
	if (fillShape) shapes[head].fillColor = ofColor(fillColor);
	else shapes[head].fillColor = ofColor(0,0,0,0); //Composante avec transparence maximale

	if (type == VectorPrimitiveType::tiles) {
		if (fillShape)
			vecShapes.push_back(new TileShape(type, mousePress.x, mousePress.y, curMouse.x, curMouse.y,
				ofColor(fillColor), ofColor(strokeColor), strokeWidth, tileSize)); 
		else 
			vecShapes.push_back(new TileShape(type, mousePress.x, mousePress.y, curMouse.x, curMouse.y,
				ofColor(0,0,0,0), ofColor(strokeColor), strokeWidth, tileSize));
	}
	if (type == VectorPrimitiveType::slime) {
		if (fillShape) 
			vecShapes.push_back(new SlimeShape(type, mousePress.x, mousePress.y, curMouse.x, curMouse.y,
				ofColor(fillColor), ofColor(strokeColor), strokeWidth));
		else
			vecShapes.push_back(new SlimeShape(type, mousePress.x, mousePress.y, curMouse.x, curMouse.y,
				ofColor(0,0,0,0), ofColor(strokeColor), strokeWidth));
	}

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
	if (mouseIsPressed) {
		/*float length = 15.0f;
		float offset = 10.0f;
		ofSetLineWidth(4);
		ofSetColor(255,0,0);
		ofDrawLine(x + offset, y, x + offset + length, y);
		ofDrawLine(x - offset, y, x - offset - length, y);
		ofDrawLine(x, y + offset, x, y + offset + length);
		ofDrawLine(x, y - offset, x, y - offset - length);*/
		cursor3.draw(x-20, y-20, 40,40);

	}else{
		/*float length = 10.0f;
		float offset = 5.0f;
		ofSetLineWidth(2);
		ofSetColor(31);
		ofDrawLine(x + offset, y, x + offset + length, y);
		ofDrawLine(x - offset, y, x - offset - length, y);
		ofDrawLine(x, y + offset, x, y + offset + length);
		ofDrawLine(x, y - offset, x, y - offset - length);*/
		cursor1.draw(x-20, y-20 ,40,40);
	}
}

void Renderer::checkClickInShape() {

	for (unsigned int i = 0; i < vecShapes.size(); i++) {
		if (vecShapes.at(i)->contains(mousePress.x, mousePress.y)) {
				if (selectedShapes.find(vecShapes.at(i)->shapeId) != selectedShapes.end()) {//Is the shape already selected?
					selectedShapes.erase(selectedShapes.find(vecShapes.at(i)->shapeId)); //Unselect the shape
					return;
				}
				else {
					selectedShapes.insert(std::make_pair(vecShapes.at(i)->shapeId, vecShapes.at(i)));
					return;
				}
		}
	}
	selectedShapes.clear();
}

void Renderer::deleteSelectedShape() {
	if (! selectedShapes.empty()) {
		for (int i = vecShapes.size() - 1; i >= 0; i--) {
			if (selectedShapes.find(vecShapes.at(i)->shapeId) != selectedShapes.end()) { //The shapes is selected
				vecShapes.erase(vecShapes.begin() + i);
			}
		}
		selectedShapes.clear();
	}
}

void Renderer::setFill(bool fill) {
	fillShape = fill;
}

void Renderer::setDrawMode(bool drawMode) {
	isDrawing = drawMode;
}

bool Renderer::isSelectedShapeEmpty() {
	return selectedShapes.empty();
}

void Renderer::goBack() {
	if (vecShapes.size() > 0) {
		pastVecShapes.push(vecShapes.back());
		vecShapes.pop_back();
	}
}

void Renderer::reDo() {
	if (pastVecShapes.size() > 0) {
		vecShapes.push_back(pastVecShapes.top());
		pastVecShapes.pop();
	}
}