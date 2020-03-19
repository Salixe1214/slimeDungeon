#include "SlimeDungeonUI.h"

//--------------------------------------------------------------
void SlimeDungeonUI::setup(){
	ofSetVerticalSync(true);

	setDefaultParameter();

	//Listeners
	screenshotBtn.addListener(this, &SlimeDungeonUI::screenshotBtnPressed);
	deleteShapeBtn.addListener(this, &SlimeDungeonUI::deleteShapeBtnPressed);
	importImageBtn.addListener(this, &SlimeDungeonUI::importImageBtnPressed);

	//ballScaleTextureBtn.addListener(this, &SlimeDungeonUI::ballTextureScaleBtnPressed);
	//ballSporeTextureBtn.addListener(this, &SlimeDungeonUI::ballTextureSporeBtnPressed);
	//ballMoltenTextureBtn.addListener(this, &SlimeDungeonUI::ballTextureMoltenBtnPressed);

	//Scene

	// Ajout éventuel d'un affichage des éléments de la scène dans une hiérarchie
	scene.setup("Scene Managing");
	//scene.setDefaultWidth(scenePanelWidth);
	scene.setPosition(ofGetWidth() - scenePanelWidth, 0); //To the right of the window

	scene.add(hierarchy.setup("Selection", emptySceneMsg));
	scene.add(deleteShapeBtn.setup("Delete selected shape"));
	
	//Transform
	transformToolsGroup.setup("Transform tools");

	transformToolsGroup.add(fillColorScene.set("Selection fill color", ofColor(110, 100, 140), ofColor(0, 0), ofColor(255, 255)));
	transformToolsGroup.add(strokeColorScene.set("Selection stroke color", ofColor(110, 100, 140), ofColor(0, 0), ofColor(255, 255)));
	
	transformToolsGroup.add(extendSelectionX.set("Extend selection by x", 0, -100, 100));
	transformToolsGroup.add(extendSelectionY.set("Extend selection by y", 0, -100, 100));
	transformToolsGroup.add(addTileRow.setup("Add tile row", false));
	transformToolsGroup.add(extendTileRowX.set("Add tile row x", 0, -10, 10));
	transformToolsGroup.add(extendTileRowY.set("Add tile row y", 0, -10, 10));

	//Translation
	translationToolsGroup.setup("Translation tools");
	translationToolsGroup.add(translateX.set("Translate x", 0, -1000, 1000));
	translationToolsGroup.add(translateY.set("Translate y", 0, -1000, 1000));

	transformToolsGroup.add(&translationToolsGroup);

	//Rotation
	rotationToolsGroup.setup("Rotation tools");
	rotationToolsGroup.add(rotateZ.set("Rotation ", 0, -180, 180));

	transformToolsGroup.add(&rotationToolsGroup);

	//Scale
	scalingToolsGroup.setup("Scaling tools");
	scalingToolsGroup.add(scaleX.set("Scaling x", 0, 0.01, 10));
	scalingToolsGroup.add(scaleY.set("Scaling y", 0, 0.01, 10));
	scalingToolsGroup.add(keepScaleProportion.setup("Keep proportion", true));

	transformToolsGroup.add(&scalingToolsGroup);


	scene.add(&transformToolsGroup);

	//gui
	gui.setup("Toolbox"); 

	gui.add(backColor1.set("Fond exterieur",ofColor::green,ofColor(0,0),ofColor(255,255)));
    gui.add(backColor2.set("Fond interieur",ofColor::black,ofColor(0,0),ofColor(255,255)));

	gui.add(screenSize.set("Screen size", ""));

	//Draw tools
	drawToolsGroup.setup("Draw tools");	

	drawToolsGroup.add(drawMode.setup("Draw mode", true));
	drawToolsGroup.add(currentShapeType.setup("Draw : ", "pixel"));
	drawToolsGroup.add(shapeColor2.set("Stroke color", ofColor(110, 100, 140), ofColor(0, 0), ofColor(255, 255)));
	drawToolsGroup.add(filled.set("Remplir", true));
	drawToolsGroup.add(shapeColor1.set("Fill color", ofColor(110, 100, 140), ofColor(0, 0), ofColor(255, 255)));

	//int tmpHeight = drawToolsGroup.getHeight(); TODO permettre à la légende de s'afficher dans une seule boîte
	//shapeKeyLegend.setDefaultHeight(100);
	//drawToolsGroup.add(shapeKeyLegend.setup("Legend : \n", "1 : pixel \n 2 : line \n 3 : Rectangle \n 4 : Square \n 5 : Ellipse \n 6 : Circle"));
	//drawToolsGroup.setDefaultHeight(tmpHeight);

	ballTextureGroup.setup("Ball texture");
	ballTextureGroup.add(ballScaleTextureBtn.setup("Scale ball", false));
	ballTextureGroup.add(ballSporeTextureBtn.setup("Spore ball", false));
	ballTextureGroup.add(ballMoltenTextureBtn.setup("Molten ball", false));
	drawToolsGroup.add(&ballTextureGroup);

	//Import Tool
	importToolsGroup.setup("Import tools");
	importToolsGroup.add(importImageBtn.setup("Import images"));
	//Capture Tool
	captureToolsGroup.setup("Capture tools");
	captureToolsGroup.add(screenshotBtn.setup("Screenshot"));
	captureToolsGroup.add(partialScreenshot.set("Partial Screenshot", false));

	//RecordMode
	recordModeTimeLimit = 10; //Time in seconds limit before forced exit of recordMode
	
	gui.add(&drawToolsGroup);
	gui.add(&captureToolsGroup);
	gui.add(&importToolsGroup);
	
	
	sdCtrl.publishSetupEvent(&gui);

	instructions.push_back("Tracez une forme avec votre souris");
	instructions.push_back("Utiliser les chiffres pour tracer differentes formes");
	instructions.push_back("Utiliser 9, 0 et \"-\" pour tracer des formes 3D");
	instructions.push_back("Utiliser \"b\" pour tracer une boule");
	instructions.push_back("Utiliser \"c\" pour tracer un cube");
	instructions.push_back("h pour cacher l'interface");
	instructions.push_back("x pour enregistrer les parametres");
	instructions.push_back("l pour charger les parametres");
	instructions.push_back("Gauche pour retourner en arriere");
	instructions.push_back("Droite pour annuler le retour en arriere");
	instructions.push_back("\"q\", \"w\", \"e\", \"a\", \"s\", \"d\", ctr gauche\n et alt gauche pour bouger la camera");

	light.setPosition(ofGetWidth() / 2, ofGetHeight() / 2, 1000);

}


void SlimeDungeonUI::setDefaultParameter() {
	//Scene
	scenePanelWidth = 200;
	emptySceneMsg = "No element in scene";
	//Transform
	prevFillColorScene = (ofColor(110, 100, 140), ofColor(0, 0), ofColor(255, 255));
	prevStrokeColorScene = (ofColor(110, 100, 140), ofColor(0, 0), ofColor(255, 255));
	prevExtendSelectionX = prevExtendSelectionY  = 0.0f;
	prevExtendTileRowX = prevExtendTileRowY = 0;

	//Translate
	prevTranslateX = prevTranslateY = 0.0f;

	//Rotate
	prevRotateZ = 0.0f;

	//Scale
	prevScaleX = prevScaleY = 1.0f;

	//drawMode
	prevDrawMode = true;
	prevFill = true;
	bHide = false;

	ballScaleTextureFile = "texture/ballTexture/scaleBall.jpg";
	ballSporeTextureFile = "texture/ballTexture/sporeBall.jpg";
	ballMoltenTextureFile = "texture/ballTexture/moltenBall.jpg";
}

//--------------------------------------------------------------
void SlimeDungeonUI::exit(){
	screenshotBtn.removeListener(this, &SlimeDungeonUI::screenshotBtnPressed);
	deleteShapeBtn.removeListener(this, &SlimeDungeonUI::deleteShapeBtnPressed);
	importImageBtn.removeListener(this, &SlimeDungeonUI::importImageBtnPressed);
	//ballScaleTextureBtn.removeListener(this, &SlimeDungeonUI::ballTextureScaleBtnPressed);
	//ballSporeTextureBtn.removeListener(this, &SlimeDungeonUI::ballTextureSporeBtnPressed);
	//ballMoltenTextureBtn.removeListener(this, &SlimeDungeonUI::ballTextureMoltenBtnPressed);

	sdCtrl.publishExitEvent();
}

//void SlimeDungeonUI::ballTextureScaleBtnPressed(bool &ballScaleTextureBtnPressed) {
//	
//	cout << "Scale " << ballScaleTextureBtnPressed << endl;
//	if (ballScaleTextureBtnPressed) {
//		sdCtrl.setBallTextureFile("");
//		ballScaleTextureBtn = false;
//	}
//	else {
//		sdCtrl.setBallTextureFile(ballScaleTextureFile);
//		ballScaleTextureBtn = true;
//	}
//	ballSporeTextureBtn = false;
//	ballMoltenTextureBtn = false;
//
//}
//
//ballScaleTextureBtn.addListener(this, &SlimeDungeonUI::ballTextureScaleBtnPressed);
//ballSporeTextureBtn.addListener(this, &SlimeDungeonUI::ballTextureSporeBtnPressed);
//ballMoltenTextureBtn.addListener(this, &SlimeDungeonUI::ballTextureMoltenBtnPressed);
//
//void SlimeDungeonUI::ballTextureSporeBtnPressed(bool &ballSporeTextureBtnPressed) {
//	cout << "Spore " << ballSporeTextureBtnPressed << endl;
//	if (ballSporeTextureBtnPressed) sdCtrl.setBallTextureFile("");
//	else sdCtrl.setBallTextureFile(ballSporeTextureFile);
//	ballScaleTextureBtn = false;
//	ballMoltenTextureBtn = false;
//	ballScaleTextureBtn.
//}
//
//void SlimeDungeonUI::ballTextureMoltenBtnPressed(bool &ballMoltenTextureBtnPressed) {
//	cout << "Molten " << ballMoltenTextureBtnPressed << endl;
//	if (ballMoltenTextureBtnPressed) sdCtrl.setBallTextureFile("");
//	else {
//		sdCtrl.setBallTextureFile(ballMoltenTextureFile);
//	}
//	ballScaleTextureBtn = false;
//	ballSporeTextureBtn = false;
//
//}



void SlimeDungeonUI::deleteShapeBtnPressed() {
	if (sdCtrl.isSelectedShapeEmpty()) ofSystemAlertDialog("Select at least one shape");
	else sdCtrl.deleteSelectedShape();
}

//--------------------------------------------------------------
void SlimeDungeonUI::importImageBtnPressed() {
	ofSystemAlertDialog("Select the image you want to import");
	ofFileDialogResult loadFileResult = ofSystemLoadDialog("Load your file", false);
	if (loadFileResult.bSuccess) {
		string loadPath = loadFileResult.getPath();
		imageImport.load(loadPath);
		ifImageImport = true;
	}
	else {
		ofSystemAlertDialog("You did not select the image properly.");
	}


}

void SlimeDungeonUI::screenshotBtnPressed()
{
	if (!isWaitingForScreenSelection) {
		if (partialScreenshot) {
			//try {
			//	int screenshotWidth = stoi(ofSystemTextBoxDialog("Size of screenshot", "Width"));
			//	int screenshotHeight = stoi(ofSystemTextBoxDialog("Size of screenshot", "Height"));
			ofSystemAlertDialog("Select the portion of the screen you want to export");
			isWaitingForScreenSelection = true;
			sdCtrl.setPartialScreenBool(true);
		}
		else {
			imgToExport.grabScreen(0, 0, screenWidth, screenHeight);
			exportScreenshot();
			
		}
		
	}
	
}

//Export the imgToExport
void SlimeDungeonUI::exportScreenshot() {
	if (imgToExport.isAllocated()) {
		ofFileDialogResult saveFileResult = ofSystemSaveDialog(ofGetTimestampString(), "Save your file");
		ofFile file = saveFileResult.getPath();
		if (hasImgExtension(file)) {
			if (saveFileResult.bSuccess) {
				sdCtrl.exportImg(imgToExport, saveFileResult.filePath);
			}
		}
		else {
			ofSystemAlertDialog("Error: The file extension is incorrect");
		}
	}
}


//--------------------------------------------------------------
void SlimeDungeonUI::update() {

	if (recordMode) { //Timer to force exit of recordMode
		if (recordModeEntryTime + recordModeTimeLimit <= (size_t)ofGetSeconds()) {
			exitRecordMode();
		}
		else {
		}
	}
	if (drawMode != prevDrawMode) {
		sdCtrl.setDrawMode(drawMode);
		prevDrawMode = drawMode;
	}
	if (filled != prevFill) {
		sdCtrl.setFill(filled);
		prevFill = filled;
	}
	int numShape = sdCtrl.getSelectedShapeSize();
	if (numShape > 0) {
		if (numShape == 1)		hierarchy = sdCtrl.getFirstSelectedShapeName();
		else hierarchy = "Shapes group";
	}
	else hierarchy = "No shape selected";

	//--texture
	updateBallTexture();

	//Drag les images a l'interieure de la window
	//Check width

	//Change selected Shape color
	if (prevFillColorScene != fillColorScene || prevStrokeColorScene != strokeColorScene) {
		sdCtrl.setSelectionColor(ofColor(fillColorScene), ofColor(strokeColorScene));
		prevFillColorScene = fillColorScene;
		prevStrokeColorScene = strokeColorScene;
	}

	//Transform selected shapes
	if (!sdCtrl.isSelectedShapeEmpty()) {
		//Change selected shapes border
		if ((!ofIsFloatEqual(prevExtendSelectionX, (float)extendSelectionX) || !ofIsFloatEqual(prevExtendSelectionY, (float)extendSelectionY))
			&& !addTileRow)
		{
			sdCtrl.extendSelectionBorder((float)extendSelectionX - prevExtendSelectionX,
				(float)extendSelectionY - prevExtendSelectionY);
			prevExtendSelectionX = extendSelectionX;
			prevExtendSelectionY = extendSelectionY;
		}
		else if (addTileRow) { 
			sdCtrl.addTileShapeRow(extendTileRowX - prevExtendTileRowX,
				extendTileRowY - prevExtendTileRowY);
			prevExtendTileRowX = extendTileRowX;
			prevExtendTileRowY = extendTileRowY;
		}

		//Translate
		if (!ofIsFloatEqual(prevTranslateX, (float)translateX) || !ofIsFloatEqual(prevTranslateY, (float)translateY)) {
			sdCtrl.translateSelection(translateX - prevTranslateX, translateY - prevTranslateY);
			prevTranslateX = translateX;
			prevTranslateY = translateY;
		}

		//Rotate
		if (!ofIsFloatEqual(prevRotateZ, (float)rotateZ)) {
			sdCtrl.rotateSelectionZ(rotateZ - prevRotateZ);
			prevRotateZ = rotateZ;
		}

		//Scale
		if (!ofIsFloatEqual(prevScaleX, (float)scaleX) || !ofIsFloatEqual(prevScaleY, (float)scaleY)) {
			if (keepScaleProportion) {
				scaleY = scaleX;
			}
			sdCtrl.scaleSelection(scaleX/prevScaleX, scaleY/prevScaleY);
			prevScaleX = scaleX;
			prevScaleY = scaleY;
		}
	}
	else {
		extendSelectionX = prevExtendSelectionX = 0.0f;
		extendSelectionY = prevExtendSelectionY = 0.0f;
		extendTileRowX = prevExtendTileRowX = 0;
		extendTileRowY = prevExtendTileRowY = 0;

		translateX = prevTranslateX = 0.0f;
		translateY = prevTranslateY = 0.0f;

		rotateZ = prevRotateZ = 0.0f;

		scaleX = prevScaleX = 1.0f;
		scaleY = prevScaleY = 1.0f;

	}
}

void SlimeDungeonUI::updateBallTexture() {

	//Scale has change
	if (ballScaleTextureActive != ballScaleTextureBtn) {
		if (ballScaleTextureBtn) {
			ballScaleTextureActive = true;
			sdCtrl.setBallTextureFile(ballScaleTextureFile);
		}
		else {
			ballScaleTextureActive = false;
			sdCtrl.setBallTextureFile("");
		}
		ballSporeTextureActive = false;
		ballSporeTextureBtn = false;
		ballMoltenTextureActive = false;
		ballMoltenTextureBtn = false;
	}

	else if (ballSporeTextureActive != ballSporeTextureBtn) {
		if (ballSporeTextureBtn) {
			ballSporeTextureActive = true;
			sdCtrl.setBallTextureFile(ballSporeTextureFile);
		}
		else {
			ballSporeTextureActive = false;
			sdCtrl.setBallTextureFile("");
		}
		ballScaleTextureActive = false;
		ballScaleTextureBtn = false;
		ballMoltenTextureActive = false;
		ballMoltenTextureBtn = false;
	}
	else if (ballMoltenTextureActive != ballMoltenTextureBtn) {
		if (ballMoltenTextureBtn) {
			ballMoltenTextureActive = true;
			sdCtrl.setBallTextureFile(ballMoltenTextureFile);
		}
		else {
			ballMoltenTextureActive = false;
			sdCtrl.setBallTextureFile("");
		}
		ballScaleTextureActive = false;
		ballScaleTextureBtn = false;
		ballSporeTextureActive = false;
		ballSporeTextureBtn = false;
	}
}
	

//--------------------------------------------------------------
void SlimeDungeonUI::draw(){
	light.enable();
    ofBackgroundGradient(backColor2, backColor1);

	sdCtrl.rendererDraw(shapeColor1, shapeColor2);
	//draw l<image importer par le boutton
	if (ifImageImport) {
		ofSetColor(ofColor::white);
		imageImport.draw(500, 300);
	}

	//si la mouse est over un des GUI, renvoir un bool au renderer NE MARCHE PAS ENCORE!
	guiPosition = gui.getPosition();
	gui2Position = scene.getPosition();
	if ((curMouse.x > guiPosition.x && curMouse.x < guiPosition.x + gui.getWidth() + 100 && curMouse.y > guiPosition.y && curMouse.y < guiPosition.y + gui.getHeight() + 100) || 
		(curMouse.x > gui2Position.x && curMouse.x < gui2Position.x + scene.getWidth() + 100 && curMouse.y > gui2Position.y && curMouse.y < gui2Position.y + scene.getHeight() + 100)) 
	{
		
		sdCtrl.setMouseOverGUI(true);
	}
	else {
		sdCtrl.setMouseOverGUI(false);
	}
	
	
	
	//draw l'image qui a ete drag dans la window
	float dx = dragPt.x;
	float dy = dragPt.y;

	for (unsigned int k = 0; k < draggedImages.size(); k++) {
		ofSetColor(ofColor::white);
		draggedImages.at(k).first.draw(draggedImages.at(k).second.x, draggedImages.at(k).second.y);
	}

	ofSetColor(0);
	ofDrawBitmapString("drag image files into this window", 10, ofGetHeight() - 20);
	
	if( !bHide ){
		gui.draw();
		scene.draw();

		// Writing instructions
		for (unsigned int i = 0; i < instructions.size() ; i++) {
			ofDrawBitmapString(instructions[i], 10, gui.getHeight() + 30 + ( i * 12));
		}
	}
}

//--------------------------------------------------------------
void SlimeDungeonUI::keyPressed(int key){
	switch (key)
	{
	case 'h':
		bHide = !bHide;
		break;

	case 'a':
		sdCtrl.setCameraMoveLeft(true);
		break;
	case 'd':
		sdCtrl.setCameraMoveRight(true);
		break;
	case 'x':
		gui.saveToFile("settings.xml");
		break;
	case 'l':
		gui.loadFromFile("settings.xml");
		break;

	case 101: // touche e
		sdCtrl.setCameraRollRight(true);
		break;
	case OF_KEY_LEFT_CONTROL:
		sdCtrl.setCameraDollyFront(true);
		break;
	case OF_KEY_LEFT_ALT:
		sdCtrl.setCameraDollyBack(true);
		break;

	//case 104: // touche h
	//	is_key_press_h = true;
	//	break;

	//case 105: // touche i
	//	is_key_press_i = true;
	//	break;

	//case 106: // touche j
	//	is_key_press_j = true;
	//	break;

	//case 107: // touche k
	//	is_key_press_k = true;
	//	break;

	case 113: // touche q
		sdCtrl.setCameraRollLeft(true);
		break;

	case 'w': // touche s
		sdCtrl.setCameraMoveDown(true);
		break;

	//case 117: // touche u
	//	is_key_press_u = true;
	//	break;

	case 's': // touche w
		sdCtrl.setCameraMoveUp(true);
		break;

	//case 120: // touche x
	//	is_key_press_x = true;
	//	break;

	//case 121: // touche y
	//	is_key_press_y = true;
	//	break;

	//case 122: // touche z
	//	is_key_press_z = true;
	//	break;
	case OF_KEY_LEFT:
		sdCtrl.changeState(true);
		break;
	case OF_KEY_RIGHT:
		sdCtrl.changeState(false);
		break;
	default:
		break;
	}

}

//--------------------------------------------------------------
void SlimeDungeonUI::keyReleased(int key){
	if (key == 'r') {
		if (recordMode) {
			exitRecordMode();
		}
		else {
			enterRecordMode();
		}
	}
	switch (key)
	{
	case 49:  // key 1
		currentShapeType = "pixel";
		sdCtrl.setDrawType(1);
		break;

	case 50:  // key 2
		currentShapeType = "line";
		sdCtrl.setDrawType(2);
		break;

	case 51:  // key 3
		currentShapeType = "rectangle";
		sdCtrl.setDrawType(3);
		break;

	case 52:  // key 4
		currentShapeType = "square";
		sdCtrl.setDrawType(4);
		break;

	case 53:  // key 5
		currentShapeType = "ellipse";
		sdCtrl.setDrawType(5);
		break;

	case 54:  // key 6
		currentShapeType = "circle";
		sdCtrl.setDrawType(6);
		break;

	case 55:  // key 7
		currentShapeType = "tiles";
		sdCtrl.setDrawType(7);
		break;
	case 56:  // key 8
		currentShapeType = "slime";
		sdCtrl.setDrawType(8);
		break;
	case 57:  // Key 9
		currentShapeType = "slime3d1";
		sdCtrl.setDrawType(9);
		break;
	case 48:  // Key 0
		currentShapeType = "slime3d2";
		sdCtrl.setDrawType(10);
		break;
	case '-':
		currentShapeType = "slime3d3";
		sdCtrl.setDrawType(11);
		break;
	case 'c':
		currentShapeType = "cube";
		sdCtrl.setDrawType(12);
		break;
	case 'b':
		currentShapeType = "ball";
		sdCtrl.setDrawType(13);
		break;

	case 101: // touche e
		sdCtrl.setCameraRollRight(false);
		break;

		//case 104: // touche h
		//	is_key_press_h = true;
		//	break;

		//case 105: // touche i
		//	is_key_press_i = true;
		//	break;

		//case 106: // touche j
		//	is_key_press_j = true;
		//	break;

		//case 107: // touche k
		//	is_key_press_k = true;
		//	break;

	case 113: // touche q
		sdCtrl.setCameraRollLeft(false);
		break;

	case 115: // touche s
		sdCtrl.setCameraMoveDown(false);
		break;

		//case 117: // touche u
		//	is_key_press_u = true;
		//	break;

	case 119: // touche w
		sdCtrl.setCameraMoveUp(false);
		break;

	case 'a':
		sdCtrl.setCameraMoveLeft(false);
		break;
	case 'd':
		sdCtrl.setCameraMoveRight(false);
		break;
	case OF_KEY_LEFT_CONTROL:
		sdCtrl.setCameraDollyFront(false);
		break;
	case OF_KEY_LEFT_ALT:
		sdCtrl.setCameraDollyBack(false);
		break;
	default:
		break;
	}

}

//--------------------------------------------------------------
void SlimeDungeonUI::mouseMoved(int x, int y ){
	sdCtrl.setCurMouse(ofPoint(x,y));
}

//--------------------------------------------------------------
void SlimeDungeonUI::mouseDragged(int x, int y, int button){
	positionImg.x = mouseX - distance.x;
	positionImg.y = mouseX - distance.y; 

	sdCtrl.setCurMouse(ofPoint(x,y));
}

//--------------------------------------------------------------
void SlimeDungeonUI::mousePressed(int x, int y, int button){
	float dx = dragPt.x;
	float dy = dragPt.y;
	distance.x = mouseX - dragPt.x;
	distance.y = mouseY - dragPt.y;

	curMouse = ofPoint(x, y);
	mousePress = ofPoint(x, y);
	sdCtrl.setRendererIsMousePressed(true);
	sdCtrl.setCurMouse(curMouse);
	sdCtrl.setMousePress(mousePress);
}

//--------------------------------------------------------------
void SlimeDungeonUI::mouseReleased(int x, int y, int button){
	
	sdCtrl.setRendererIsMousePressed(false);
	curMouse = ofPoint(x, y);
	sdCtrl.setCurMouse(curMouse);
	if (isWaitingForScreenSelection) {
		screenshotPtUpperLeft = mousePress;
		screenshotPtDownRight = curMouse;
		float tmpX, tmpY;
		//Triage des points
		if (screenshotPtDownRight.x - screenshotPtUpperLeft.x > 0 && screenshotPtDownRight.y - screenshotPtUpperLeft.y < 0) {
			tmpY = screenshotPtUpperLeft.y;
			screenshotPtUpperLeft.y = screenshotPtDownRight.y;
			screenshotPtDownRight.y = tmpY;
		}
		else if (screenshotPtDownRight.x - screenshotPtUpperLeft.x < 0 && screenshotPtDownRight.y - screenshotPtUpperLeft.y >0) {
			tmpX = screenshotPtUpperLeft.x;
			screenshotPtUpperLeft.x = screenshotPtDownRight.x;
			screenshotPtDownRight.x = tmpX;
		}
		else if (screenshotPtDownRight.x - screenshotPtUpperLeft.x < 0 && screenshotPtDownRight.y - screenshotPtUpperLeft.y < 0) {
			tmpX = screenshotPtUpperLeft.x;
			tmpY = screenshotPtUpperLeft.y;
			screenshotPtUpperLeft = screenshotPtDownRight;
			screenshotPtDownRight.x = tmpX;
			screenshotPtDownRight.y = tmpY;
		}

		imgToExport.grabScreen(screenshotPtUpperLeft.x, screenshotPtUpperLeft.y, screenshotPtDownRight.x - screenshotPtUpperLeft.x, screenshotPtDownRight.y - screenshotPtUpperLeft.y);
		isWaitingForScreenSelection = false;
		sdCtrl.setPartialScreenBool(false);

		if (! recordMode) exportScreenshot();
	}
	else{
		if (drawMode) {
			sdCtrl.addShape();
		}
		else {
			sdCtrl.checkClickInShape();
		}
	}
	
}

//--------------------------------------------------------------
void SlimeDungeonUI::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void SlimeDungeonUI::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void SlimeDungeonUI::windowResized(int w, int h){
	screenWidth = w;
	screenHeight = h;
    screenSize = ofToString(w) + "x" + ofToString(h);
	scene.setPosition(w - scenePanelWidth, 0);
	sdCtrl.publishWindowResizedEvent(w, h);
}

//--------------------------------------------------------------
void SlimeDungeonUI::gotMessage(ofMessage msg){
	
}

//--------------------------------------------------------------
void SlimeDungeonUI::dragEvent(ofDragInfo info) {
	if (info.files.size() > 0) {
		dragPt = info.position;
		//draggedImages.assign(info.files.size(), ofImage());
		draggedImages.push_back(std::make_pair(ofImage(info.files.at(0)), dragPt));
		for (unsigned int k = 0; k < draggedImages.size(); k++) {
			draggedImages.at(k).first.draw(dragPt.x, dragPt.y);
		}
	}
}

	//--------------------------------------------------------------
	bool SlimeDungeonUI::hasImgExtension(ofFile file) {
		string fileExt = ofToLower(file.getExtension());
		return (fileExt == "png");//|| fileExt == "jpg");
	}


	void SlimeDungeonUI::enterRecordMode()
	{
		recordMode = true;
		recordModeEntryTime = ofGetSeconds();
		sdCtrl.publishEnterRecordModeEvent();
		cout << "Entering Record mode" << endl;

	}

	void SlimeDungeonUI::exitRecordMode()
	{
		cout << "Exiting Record mode" << endl;
		recordMode = false;
		sdCtrl.publishExitRecordModeEvent();
	}