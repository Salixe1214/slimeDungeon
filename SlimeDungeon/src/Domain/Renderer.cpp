#include "Renderer.h"


Renderer::Renderer()
{

}


void Renderer::setup(ofxPanel *gui)
{
	//Shapes count
	//SlimeShape::numSlimeShape = 0;
	//TileShape::numTileShape = 0;

	// Ajout des param�tres de dessin au gui
	gui->getGroup("Draw tools").add(strokeWidth.set("Epaisseur du trait", 4, 1, 10));
	gui->getGroup("Draw tools").add(tileSize.set("Tile size", 50, 1, 300));
	
	//color = p_userColor;
	mouseIsPressed = false;
	isDrawing = true; //TODO changer ceci pour s'adapter avec le UI
	count = 100;
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
	// Update des couleurs en temps r�el (pour le sample)
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
	// afficher la zone de s�lection

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
		shape::Pixel(shapeType, origineX, origineY, ofColor(fillColor), sampleShape).draw();
		break;

	case VectorPrimitiveType::line:
		shape::Line(shapeType, origineX, origineY, origineX + deltaX, origineY + deltaY,
			 ofColor(strokeColor), strokeWidth, sampleShape).draw();
		break;

	case VectorPrimitiveType::rectangle:
		shape::Rectangle(shapeType, origineX, origineY, origineX + deltaX, origineY + deltaY,
			ofColor(fillColor), ofColor(strokeColor), strokeWidth, sampleShape).draw();
		break;

	case VectorPrimitiveType::square:
		shape::Square(shapeType, origineX, origineY, origineX + deltaX, origineY + deltaX,
			ofColor(fillColor), ofColor(strokeColor), strokeWidth, sampleShape).draw();
		break;

	case VectorPrimitiveType::ellipse:
		shape::Ellipse(shapeType, origineX, origineY, origineX + deltaX, origineY + deltaY,
			ofColor(fillColor), ofColor(strokeColor), strokeWidth, sampleShape).draw();
		break;
	case VectorPrimitiveType::circle:
		Circle(shapeType, origineX, origineY, origineX + deltaX, origineY + deltaX,
			ofColor(fillColor), ofColor(strokeColor), strokeWidth, sampleShape).draw();
		break;

	case VectorPrimitiveType::tiles:
		TileShape(shapeType, origineX, origineY, origineX + deltaX, origineY + deltaY,
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
		ofDrawRectangle(0, 0, ofGetWidth(), ofGetHeight());
		ofFill();
	}
	else ofDrawRectangle(0, 0, ofGetScreenWidth(), ofGetScreenHeight());
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

}

void Renderer::setShapeType(VectorPrimitiveType newShapeType)
{
	shapeType = newShapeType;
}

// fonction qui ajoute une primitive vectorielle au tableau
void Renderer::addVectorShape(VectorPrimitiveType type)
{
	ofColor fillingColor;
	float posX1 = mousePress.x, posX2 = curMouse.x;
	float posY1 = mousePress.y, posY2 = curMouse.y;
	
	if (fillShape) fillingColor = fillColor;
	else fillingColor = ofColor(0, 0, 0, 0); //Composante avec transparence maximale
	
	if (type == VectorPrimitiveType::square || type == VectorPrimitiveType::circle) {
		float sideLength = abs(mousePress.x - curMouse.x);
		posX1 = mousePress.x;
		posY1 = mousePress.y;
		if (curMouse.x - mousePress.x < 0) posX2 = mousePress.x - sideLength;
		else  posX2 = mousePress.x + sideLength;
		if (curMouse.y - mousePress.y < 0) posY2 = mousePress.y - sideLength;
		else posY2 = mousePress.y + sideLength;
	}

	switch (type)
	{
	case VectorPrimitiveType::pixel:
		vecShapes.push_back(new shape::Pixel(type, posX2, posY2,fillingColor));
		break;

	case VectorPrimitiveType::line:
		vecShapes.push_back(new shape::Line(type, posX1, posY1, posX2, posY2,
			 ofColor(strokeColor), strokeWidth));
		break;

	case VectorPrimitiveType::rectangle:
		vecShapes.push_back(new shape::Rectangle(type, posX1, posY1, posX2, posY2,
			fillingColor, ofColor(strokeColor), strokeWidth));
		break;
	case VectorPrimitiveType::square:
		vecShapes.push_back(new shape::Square(type, posX1, posY1, posX2, posY2,
			fillingColor, ofColor(strokeColor), strokeWidth));
		break;
	case VectorPrimitiveType::ellipse:
		vecShapes.push_back(new shape::Ellipse(type, posX1, posY1, posX2, posY2,
			fillingColor, ofColor(strokeColor), strokeWidth));
		break;

	case VectorPrimitiveType::circle:
		vecShapes.push_back(new shape::Circle(type, posX1, posY1, posX2, posY2,
			fillingColor, ofColor(strokeColor), strokeWidth));
		break;

	case VectorPrimitiveType::tiles:
		vecShapes.push_back(new shape::TileShape(type, posX1, posY1, posX2, posY2,
			fillingColor, ofColor(strokeColor), strokeWidth, tileSize));
		break;
	case VectorPrimitiveType::slime:
		vecShapes.push_back(new shape::SlimeShape(type, posX1, posY1, posX2, posY2,
				fillingColor, ofColor(strokeColor), strokeWidth));
		break;

	default:
		break;
	}
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