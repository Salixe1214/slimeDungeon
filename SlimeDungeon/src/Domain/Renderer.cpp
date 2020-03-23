#include "Renderer.h"

Renderer::Renderer()
{
	lightManager = LightManager::getLightManager();
}



void Renderer::setup(ofxPanel *gui, glm::vec3 p_camInitialPos)
{
	ofSetFrameRate(60);
	ofSetSphereResolution(32);

	// Ajout des paramètres de dessin au gui
	gui->getGroup("Draw tools").add(strokeWidth.set("Epaisseur du trait", 4, 1, 10));
	gui->getGroup("Draw tools").add(tileSize.set("Tile size", 50, 1, 300));

	//color = p_userColor;
	mouseIsPressed = false;
	isDrawing = true;
	camInitialPos = p_camInitialPos;
	fillShape = true;

	//texture --
	ballTextureFile = "";
	//--

	strokeWidthDefault = 4;
	strokeWidth = 4;//----

	screenHeight = ofGetHeight();
	screenWidth = ofGetWidth();
	cameraOffsetX = 0.0;
	cameraOffsetY = 0.0;

	mousePress.x = mousePress.y = curMouse.x = curMouse.y = 0;
	//CaptureTool
	recordMode = false;

	isCameraMoveLeft = false;
	is_camera_move_right = false;
	is_camera_move_up = false;
	is_camera_move_down = false;
	is_camera_move_forward = false;
	is_camera_move_backward = false;

	is_camera_tilt_up = false;
	is_camera_tilt_down = false;
	is_camera_pan_left = false;
	is_camera_pan_right = false;
	is_camera_roll_left = false;
	is_camera_roll_right = false;

	is_camera_fov_narrow = false;
	is_camera_fov_wide = false;

	//load les cursors
	cursor1.load("fleche.png");
	cursor2.load("fleche1.png");
	cursor3.load("hand.png");
	cursor4.load("partialScreenshotCursor.png");
	
	// Camera
	speedDelta = 250.0f;
	camFront.setPosition(camInitialPos); //TODO changer la position de départ
	camFront.lookAt({ ofGetWidth() / 2,ofGetHeight() / 2, 0 });
	camFront.setVFlip(true);
	camFront.setFov(402);

}

void Renderer::update(ofParameter<ofColor> p_fillColor, 
					  ofParameter<ofColor> p_strokeColor)
{
	timeCurrent = ofGetElapsedTimef();
	timeElapsed = timeCurrent - timeLast;
	timeLast = timeCurrent;

	speedTranslation = speedDelta * timeElapsed;
	speedRotation = speedTranslation / 8.0f;

	if (isCameraMoveLeft) {
		camFront.truck(-speedTranslation);
		cameraOffsetX += -speedTranslation;
	}
	if (is_camera_move_right) {
		camFront.truck(speedTranslation);
		cameraOffsetX += speedTranslation;
	}
	if (is_camera_move_up) {
		camFront.boom(speedTranslation);
		cameraOffsetY += speedTranslation;
	}
	if (is_camera_move_down) {;
		camFront.boom(-speedTranslation);
		cameraOffsetY += -speedTranslation;
	}

	if (is_camera_move_forward)
		camFront.dolly(-speedTranslation);
	if (is_camera_move_backward)
		camFront.dolly(speedTranslation);

	if (is_camera_tilt_up)
		camFront.tiltDeg(-speedRotation);
	if (is_camera_tilt_down)
		camFront.tiltDeg(speedRotation);

	if (is_camera_pan_left)
		camFront.panDeg(speedRotation);
	if (is_camera_pan_right)
		camFront.panDeg(-speedRotation);

	if (is_camera_roll_left)
		camFront.rollDeg(-speedRotation);
	if (is_camera_roll_right)
		camFront.rollDeg(speedRotation);

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
	
	camFront.begin();
	lightManager->lightOn();
	lightManager->draw();

	drawShapes();
	highlightSelectedShape();

	lightManager->lightOff();
	camFront.end();

	drawSample();
	
	drawCursor(curMouse.x, curMouse.y);

}

void Renderer::windowResizedEvent(int w, int h)
{
	//La caméra est centré de nouveau 

	cameraOffsetX = 0;
	cameraOffsetY = 0;

	//cameraOffsetX -= w/2 - screenWidth/2;
	//cameraOffsetY -= h/2 - screenHeight/2;

	if (w != (int)screenWidth && h != (int)screenHeight) {
		float zoom = w / h;
		camFront.setPosition({ ofGetWidth() / 2, ofGetHeight() / 2, 500 });
		camFront.lookAt({ ofGetWidth() / 2,ofGetHeight() / 2, 0 });
		camInitialPos = { ofGetWidth() / 2, ofGetHeight() / 2, 500 };
		camFront.setFov(glm::degrees(2 * atanf(1 / zoom)));
	}
	screenWidth = w;
	screenHeight = h;
}


void Renderer::drawShapes() {

	//Draw vector shapes
	for (unsigned int i = 0; i < vecShapes.size(); i++) {
		if (vecShapes.at(i)->rotation.z != 0.0) {
			ofPushMatrix();
			ofTranslate((vecShapes.at(i)->position1.x + vecShapes.at(i)->position2.x) /2.0,
				(vecShapes.at(i)->position1.y + vecShapes.at(i)->position2.y) / 2.0); //Rotation par rapport au centre de la shape
			ofRotateZDeg(vecShapes.at(i)->rotation.z);
			ofTranslate(-(vecShapes.at(i)->position1.x + vecShapes.at(i)->position2.x) / 2.0,
				-(vecShapes.at(i)->position1.y + vecShapes.at(i)->position2.y) / 2.0);
			vecShapes.at(i)->draw();
			ofPopMatrix();
		}
		else vecShapes.at(i)->draw();
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
	case VectorPrimitiveType::pixel:
		shape::Pixel(shapeType, origineX, origineY, ofColor(fillColor), sampleShape).draw();
		break;

	case VectorPrimitiveType::slime:
		shape::SlimeShape(shapeType, origineX, origineY, origineX + deltaX, origineY + deltaY,
			ofColor(fillColor), ofColor(strokeColor), strokeWidth, sampleShape).draw();
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
	case VectorPrimitiveType::slime3d:
		Shape3D(VectorPrimitiveType::slime3d, (origineX + deltaX)/2, (origineY + deltaY)/2, 0, 
			((deltaX + deltaY) / 2) / ((ofGetHeight() + ofGetWidth())/2),ofColor::white, sampleShape,
			"slime1.dae", glm::vec3({ 0, 270, 0 })).draw();
		break;
	case VectorPrimitiveType::monster3d:
		Shape3D(VectorPrimitiveType::monster3d, (origineX + deltaX) / 2, (origineY + deltaY) / 2, 0,
			((deltaX + deltaY) / 2) / ((ofGetHeight() + ofGetWidth()) / 2), ofColor::white, sampleShape,
			"monster.dae", glm::vec3({ 0, 270, 0 })).draw();
		break;
	case VectorPrimitiveType::ballFace:
		Shape3D(VectorPrimitiveType::ballFace, origineX + (deltaX / 2), (origineY + deltaY) / 2, 0,
			((deltaX + deltaY) / 2) / ((ofGetHeight() + ofGetWidth()) / 2), ofColor::white, sampleShape,
			"ball.dae", glm::vec3({ 0, 270, 0 })).draw();
		break;
	case VectorPrimitiveType::ball:
		Ball(shapeType, origineX, origineY, origineX + deltaX, origineY + deltaX,
			ofColor(fillColor), ofColor(strokeColor), strokeWidth, sampleShape).draw();
		break;
	case VectorPrimitiveType::cube:
		shape::Box(shapeType, origineX, origineY, origineX + deltaX, origineY + deltaX,
			ofColor(fillColor), ofColor(strokeColor), strokeWidth, sampleShape).draw();
		break;
	default:
		break;
	}
}


void Renderer::highlightSelectedShape() {
	for (auto shape : selectedShapes) {
		if (shape.second->rotation.z != 0.0) {
			ofPushMatrix();
			ofTranslate((shape.second->position1.x + shape.second->position2.x) /2.0,
				(shape.second->position1.y + shape.second->position2.y) / 2.0); //Rotation par rapport au centre de la shape
			ofRotateZDeg(shape.second->rotation.z);
			ofTranslate(-(shape.second->position1.x + shape.second->position2.x) / 2.0,
				-(shape.second->position1.y + shape.second->position2.y) / 2.0);

			shape.second->highlight();
			ofPopMatrix();
		}
		else shape.second->highlight();
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


void Renderer::removeLastAddedVectorShape(){

}

void Renderer::setBallTextureFile(string p_ballTextureFile)
{
	ballTextureFile = p_ballTextureFile;
}

void Renderer::setShapeType(VectorPrimitiveType newShapeType)
{
	shapeType = newShapeType;
}

// fonction qui ajoute une primitive vectorielle au tableau
void Renderer::addVectorShape(VectorPrimitiveType type)
{
	ofColor fillingColor;
	//float cameraOffsetX = camFront.getPosition().x - camInitialPos.x;
	//float cameraOffsetY = camFront.getPosition().y - camInitialPos.y;
	float posX1 = mousePress.x + cameraOffsetX;
	float posX2 = curMouse.x + cameraOffsetX;
	float posY1 = mousePress.y + cameraOffsetY;
	float posY2 = curMouse.y + cameraOffsetY;
	
	if (fillShape) fillingColor = fillColor;
	else fillingColor = ofColor(0, 0, 0, 0); //Composante avec transparence maximale
	
	if (type == VectorPrimitiveType::square || type == VectorPrimitiveType::circle) {
		float sideLength = abs(mousePress.x - curMouse.x);
		if (curMouse.x - mousePress.x < 0) posX2 = posX1 - sideLength;
		else  posX2 = posX1 + sideLength;
		if (curMouse.y - mousePress.y < 0) posY2 = posY1 - sideLength;
		else posY2 = posY1 + sideLength;
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
		if (abs(posX2 - posX1) >= tileSize && abs(posY2 - posY1) >= tileSize) {
			vecShapes.push_back(new shape::TileShape(type, posX1, posY1, posX2, posY2,
				fillingColor, ofColor(strokeColor), strokeWidth, tileSize));
		}
		break;
	case VectorPrimitiveType::slime:
		vecShapes.push_back(new shape::SlimeShape(type, posX1, posY1, posX2, posY2,
				fillingColor, ofColor(strokeColor), strokeWidth));
		break;
	case VectorPrimitiveType::slime3d:
		vecShapes.push_back(new shape::Shape3D(type, (posX1 + posX2)/2, (posY1 + posY2)/2, 0, 0.5, 
			fillingColor, "slime1.dae"));
		break;
	case VectorPrimitiveType::monster3d:
		vecShapes.push_back(new shape::Shape3D(type, (posX1 + posX2) / 2, (posY1 + posY2) / 2, 0, 0.5,
			fillingColor, "monster.dae"));
		break;
	case VectorPrimitiveType::ballFace:
		vecShapes.push_back(new shape::Shape3D(type, (posX1 + posX2) / 2, (posY1 + posY2) / 2, 0, 0.5,
			fillingColor, "ball.dae"));
		break;
	case VectorPrimitiveType::cube:
		vecShapes.push_back(new shape::Box(type, posX1, posY1, posX2, posY2,
			fillingColor, ofColor(strokeColor), strokeWidth));
		break;
	case VectorPrimitiveType::ball:
		vecShapes.push_back(new shape::Ball(type, posX1, posY1, posX2, posY2,
			fillingColor, ofColor(strokeColor), strokeWidth, ballTextureFile));
		break;
	default:
		break;
	}

	while (!pastVecShapes.empty())
	{
		delete pastVecShapes.top();
		pastVecShapes.pop();
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
	ofSetColor(ofColor::black);
	if (mouseIsPressed && partialScreenPressed) {
		
		cursor4.draw(x, y, 40,40);

	}
	else if (mouseIsPressed) {
		cursor3.draw(x - 20, y - 20, 40, 40);
	}else{
		if ( /*mouseOverGUI*/(curMouse.x > 0 && curMouse.x < 230 && curMouse.y > 0 && curMouse.y < 390) || (curMouse.x > ofGetWidth() - 250 && curMouse.x < ofGetWidth() && curMouse.y > 0 && curMouse.y < 450)) {
			ofShowCursor();
		}
		else if(partialScreenPressed){
			ofHideCursor();
			cursor4.draw(x, y, 40, 40);
			
		}
		else {
			ofHideCursor();
			
			cursor1.draw(x - 20, y - 20, 40, 40);
		}
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

		while (!pastVecShapes.empty())
		{
			delete pastVecShapes.top();
			pastVecShapes.pop();
		}
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

void Renderer::setSelectionColor(ofColor newFillColor, ofColor newStrokeColor) {
	for (auto shape : selectedShapes) {
		shape.second->fillColor = newFillColor;
		shape.second->strokeColor = newStrokeColor;
	}
}

void Renderer::setPartialScreenBool(bool isPartialScreen) {
	partialScreenPressed = isPartialScreen;
}

void Renderer::setMouseOverGUI(bool overGUI) {
	mouseOverGUI = overGUI;
}


void Renderer::extendSelectionBorder(float dx, float dy) {
	float tileSize;
	for (auto shape : selectedShapes) {
		if (shape.second->position2.x + dx <= shape.second->position1.x + 1
			|| shape.second->position2.y + dy <= shape.second->position1.y + 1) continue;
		switch (shape.second->shapeType)
		{
		case VectorPrimitiveType::square:
			if (dx != 0.0f) {
				shape.second->position2.x += dx;
				shape.second->position2.y += dx;
			}
			else {
				shape.second->position2.x += dy;
				shape.second->position2.y += dy;
			}
			break;

		case VectorPrimitiveType::circle:
			if (dx != 0.0f) {
				shape.second->position2.x += dx;
				shape.second->position2.y += dx;
			}
			else {
				shape.second->position2.x += dy;
				shape.second->position2.y += dy;
			}
			break;
			
		default:
			shape.second->position2.x += dx;
			shape.second->position2.y += dy;
			break;
		}
	}
}

void Renderer::addTileShapeRow(int addedXRow, int addedYRow)
{
	float tileSize;
	for (auto shape : selectedShapes) {
		if (shape.second->shapeType == VectorPrimitiveType::tiles) {
			tileSize = ((shape::TileShape*) shape.second)->tileSize;

			if (addedXRow > 0 ) shape.second->position2.x += tileSize; //Ajout row X
			else if (addedXRow < 0 && shape.second->position2.x > shape.second->position1.x + tileSize) //Retrait row x 
				shape.second->position2.x -= tileSize;
			if (addedYRow > 0) shape.second->position2.y += tileSize; //Ajout row y
			else if (addedYRow < 0 && shape.second->position2.y > shape.second->position1.y + tileSize) //Retrait row y 
				shape.second->position2.y -= tileSize; 
		}
	}
}

void Renderer::translateSelection(float dx, float dy, float dz)
{
	for (auto shape : selectedShapes) shape.second->translate(dx, dy, dz);
}

void Renderer::rotateSelectionZ(float thetaZ)
{
	for (auto shape : selectedShapes) {
		shape.second->rotation[2] += thetaZ;
	}
}

void Renderer::scaleSelection(float sx, float sy, float sz)
{
	for (auto shape : selectedShapes) shape.second->scale(sx, sy, sz);
}

int Renderer::getSelectedShapeSize()
{
	return selectedShapes.size();
}

string Renderer::getFirstSelectedShapeName()
{
	return selectedShapes.begin()->second->shapeId;
}


void Renderer::setCameraMoveDown(bool isMoveDown)
{
	is_camera_move_down = isMoveDown;
}

void Renderer::setCameraRollLeft(bool isRollLeft)
{
	is_camera_roll_left = isRollLeft;
}

void Renderer::setCameraRollRight(bool isRollRight)
{
	is_camera_roll_right = isRollRight;
}

void Renderer::setCameraMoveUp(bool isMoveUp)
{
	is_camera_move_up = isMoveUp;
}

void Renderer::setCameraMoveRight(bool isMoveRight)
{
	is_camera_move_right = isMoveRight;
}

void Renderer::setCameraMoveLeft(bool cameraMoveLeft)
{
	isCameraMoveLeft = cameraMoveLeft;
}

void Renderer::setCameraDollyFront(bool cameraDollyFront)
{
	is_camera_move_forward = cameraDollyFront;
}

void Renderer::setCameraDollyBack(bool cameraDollyBack)
{
	is_camera_move_backward = cameraDollyBack;
}
