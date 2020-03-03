#include "SlimeDungeonUI.h"

//--------------------------------------------------------------
void SlimeDungeonUI::setup(){
	ofSetVerticalSync(true);

	setDefaultParameter(); 

	//Listeners
	screenshotBtn.addListener(this, &SlimeDungeonUI::screenshotBtnPressed);
	deleteShapeBtn.addListener(this, &SlimeDungeonUI::deleteShapeBtnPressed);

	
	//Scene
	//Ajout éventuel d'un affichage des éléments de la scène.
	scene.setup("Scene Managing");
	//scene.setDefaultWidth(scenePanelWidth);
	scene.setPosition(ofGetWidth() - scenePanelWidth, 0); //To the right of the window

	scene.add(hierarchy.setup("hierarchy", emptySceneMsg));
	scene.add(deleteShapeBtn.setup("Delete Selected Shape"));

	scene.add(fillColorScene.set("Selection fill color", ofColor(110, 100, 140), ofColor(0, 0), ofColor(255, 255)));
	scene.add(strokeColorScene.set("Selection stroke color", ofColor(110, 100, 140), ofColor(0, 0), ofColor(255, 255)));
	
	scene.add(extendSelectionX.set("Extend selection by x", 0, -100, 100));
	scene.add(extendSelectionY.set("Extend selection by y", 0, -100, 100));
	scene.add(addTileRow.setup("Add tile row", false));
	scene.add(extendTileRowX.set("Add tile row x", 0, -10, 10));
	scene.add(extendTileRowY.set("Add tile row y", 0, -10, 10));


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

}

void SlimeDungeonUI::setDefaultParameter() {
	//Scene
	scenePanelWidth = 200;
	emptySceneMsg = "No element in scene";

	prevFillColorScene = (ofColor(110, 100, 140), ofColor(0, 0), ofColor(255, 255));
	prevStrokeColorScene = (ofColor(110, 100, 140), ofColor(0, 0), ofColor(255, 255));
	prevExtendSelectionX = prevExtendSelectionY  = 0.0f;
	prevExtendTileRowX = prevExtendTileRowY = 0;

	//drawMode
	prevDrawMode = true;
	prevFill = true;


	bHide = false;
}

//--------------------------------------------------------------
void SlimeDungeonUI::exit(){
	screenshotBtn.removeListener(this, &SlimeDungeonUI::screenshotBtnPressed);
	deleteShapeBtn.removeListener(this, &SlimeDungeonUI::deleteShapeBtnPressed);
	sdCtrl.publishExitEvent();
}


void SlimeDungeonUI::deleteShapeBtnPressed() {
	if (sdCtrl.isSelectedShapeEmpty()) ofSystemAlertDialog("Select at least one shape");
	else sdCtrl.deleteSelectedShape();
}

//--------------------------------------------------------------
void SlimeDungeonUI::importImageBtnPressed() {

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
		else hierarchy = "Group of shapes";
	}
	else hierarchy = "No shape selected";

	//Drag les images a l'interieure de la window
	//Check width
	

}

	
	

//--------------------------------------------------------------
void SlimeDungeonUI::draw(){
    ofBackgroundGradient(backColor2, backColor1);

	sdCtrl.rendererDraw(shapeColor1, shapeColor2);

	//Change selected Shape color
	if (prevFillColorScene != fillColorScene || prevStrokeColorScene != strokeColorScene) {
		sdCtrl.setSelectionColor(ofColor(fillColorScene), ofColor(strokeColorScene));
		prevFillColorScene = fillColorScene;
		prevStrokeColorScene = strokeColorScene;
	}
	//Change selected Shape border
	if (!sdCtrl.isSelectedShapeEmpty()) {
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
	}
	else {
		extendSelectionX = prevExtendSelectionX = 0.0f;
		extendSelectionY = prevExtendSelectionY = 0.0f;
		extendTileRowX = prevExtendTileRowX = 0;
		extendTileRowY = prevExtendTileRowY = 0;

	}
	

	//draw l'image qui a ete drag dans la window
	float dx = dragPt.x;
	float dy = dragPt.y;

	for (unsigned int k = 0; k < draggedImages.size(); k++) {
		draggedImages.at(k).first.draw(draggedImages.at(k).second.x, draggedImages.at(k).second.y);
	}

	ofSetColor(0);
	ofDrawBitmapString("drag image files into this window", 10, 20);
	
	if( !bHide ){
		gui.draw();
		scene.draw();
	}
}

//--------------------------------------------------------------
void SlimeDungeonUI::keyPressed(int key){
	if( key == 'h' ){
		bHide = !bHide;
	}
	if(key == 's') {
		gui.saveToFile("settings.xml");
	}
	if(key == 'l') {
		gui.loadFromFile("settings.xml");
	}
	if(key == ' '){
		shapeColor1 = ofColor(255);
	}
	if (key == 'o') {
		shapeColor2 = shapeColor1;
	}
	switch (key)
	{
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
	//case 102: // key f
	//	renderer.random_color_fill();
	//	break;

	//case 114: // key r
	//	renderer.reset();
	//	break;

	//case 115: // key s
	//	renderer.random_color_stroke();
	//	break;

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
	positionImg.y = mouseX - distance.y; //ne devrait pas être mouseY plutôt ici? A.B.

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
		screenshotPtUpperRight = mousePress;
		screenshotPtDownLeft = curMouse;
		
		imgToExport.grabScreen(screenshotPtUpperRight.x, screenshotPtUpperRight.y, screenshotPtDownLeft.x - screenshotPtUpperRight.x, screenshotPtDownLeft.y - screenshotPtUpperRight.y);
		isWaitingForScreenSelection = false;
		if (! recordMode) exportScreenshot();
	}
	else{
		if (drawMode) {
			sdCtrl.addShape(); //TODO faut passer les colors des shapes ici
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