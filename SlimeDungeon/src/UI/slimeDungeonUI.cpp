#include "SlimeDungeonUI.h"


//--------------------------------------------------------------
void SlimeDungeonUI::setup(){
	ofSetVerticalSync(true);
	
	sdCtrl.publishSetupEvent();
	//Listeners
	circleResolution.addListener(this, &SlimeDungeonUI::circleResolutionChanged);
	ringButton.addListener(this,&SlimeDungeonUI::ringButtonPressed);
	screenshotBtn.addListener(this, &SlimeDungeonUI::screenshotBtnPressed);



	gui.setup("Toolbox"); // most of the time you don't need a name but don't forget to call setup
	gui.add(filled.set("Remplir", true));
	gui.add(radius.set("Rayon", 140, 10, 300 ));
	gui.add(center.set("Centrer",glm::vec2(ofGetWidth()*.5,ofGetHeight()*.5),glm::vec2(0,0),glm::vec2(ofGetWidth(),ofGetHeight())));
	gui.add(backColor1.set("Fond exterieur",ofColor::green,ofColor(0,0),ofColor(255,255)));
    gui.add(backColor2.set("Fond interieur",ofColor::black,ofColor(0,0),ofColor(255,255)));
	gui.add(circleResolution.set("Resolution du cercle", 5, 3, 90));
	gui.add(twoCircles.set("Deux cercles", false));
	gui.add(ringButton.setup("Cloche"));
	gui.add(screenSize.set("Screen size", ""));


	//Draw tools
	drawToolsGroup.setup("Draw tools");	
	drawToolsGroup.add(drawMode.setup("Draw mode", true));
	drawToolsGroup.add(currentShapeType.setup("Draw : ", "pixel"));
	drawToolsGroup.add(shapeColor1.set("Fill color", ofColor(110, 100, 140), ofColor(0, 0), ofColor(255, 255)));
	drawToolsGroup.add(shapeColor2.set("Stroke color", ofColor(110, 100, 140), ofColor(0, 0), ofColor(255, 255)));

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
	bHide = false;

	ring.load("ring.wav");
}

//--------------------------------------------------------------
void SlimeDungeonUI::exit(){
	ringButton.removeListener(this,&SlimeDungeonUI::ringButtonPressed);
	screenshotBtn.removeListener(this, &SlimeDungeonUI::screenshotBtnPressed);
}

//--------------------------------------------------------------
void SlimeDungeonUI::circleResolutionChanged(int & circleResolution){
	ofSetCircleResolution(circleResolution);
}

//--------------------------------------------------------------
void SlimeDungeonUI::ringButtonPressed(){
	ring.play();
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
		/*ofFile file = saveFileResult.getPath();
		if (hasImgExtension(file)) {
			if (saveFileResult.bSuccess) {
				sdCtrl.exportImg(imgToExport, saveFileResult.filePath);
			}
		}
		else {
			ofSystemAlertDialog("Error: The file extension is incorrect");
		}*/
	}
}

//--------------------------------------------------------------
void SlimeDungeonUI::update() {

	if (recordMode) { //Timer to force exit of recordMode
		if (recordModeEntryTime + recordModeTimeLimit <= (size_t) ofGetSeconds()) {
			sdCtrl.publishExitRecordModeEvent();
			cout << "Exiting Record mode" << endl;
			recordMode = false;
		}
	}
	//Drag les images a l'interieure de la window
	//Check width
	

}

	
	

//--------------------------------------------------------------
void SlimeDungeonUI::draw(){
    ofBackgroundGradient(backColor2, backColor1);
	sdCtrl.rendererDraw(ofColor(shapeColor1), ofColor(shapeColor2)); // TODO Il ne faut pas passer les colors des shapes ici, parce que ça change la couleur des shapes précédentes
	

	//draw l'image qui a ete drag dans la window
	float dx = dragPt.x;
	float dy = dragPt.y;

	for (unsigned int k = 0; k < draggedImages.size(); k++) {
		draggedImages.at(k).first.draw(draggedImages.at(k).second.x, draggedImages.at(k).second.y);
	}

	ofSetColor(0);
	ofDrawBitmapString("drag image files into this window", 10, 20);
    
	if( filled ){
		ofFill();
	}else{
		ofNoFill();
	}

	ofSetColor(shapeColor1);
	if(twoCircles){
		ofDrawCircle(center->x-radius*.5, center->y, radius );
		ofDrawCircle(center->x+radius*.5, center->y, radius );
	}else{
		ofDrawCircle((glm::vec2)center, radius );
	}
	
	if( !bHide ){
		gui.draw();
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

}

//--------------------------------------------------------------
void SlimeDungeonUI::keyReleased(int key){
	if (key == 'r') {
		if (recordMode) {
			cout << "Exiting Record mode" << endl;
			recordMode = false;
			sdCtrl.publishExitRecordModeEvent();
		}
		else {
			cout << "Entering Record mode" << endl;
			recordMode = true;
			recordModeEntryTime = ofGetSeconds();
			sdCtrl.publishEnterRecordModeEvent();
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

