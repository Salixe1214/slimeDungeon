#include "SlimeDungeonUI.h"


//--------------------------------------------------------------
void SlimeDungeonUI::setup(){
	ofSetVerticalSync(true);
	
	//Listeners
	circleResolution.addListener(this, &SlimeDungeonUI::circleResolutionChanged);
	ringButton.addListener(this,&SlimeDungeonUI::ringButtonPressed);
	screenshotBtn.addListener(this, &SlimeDungeonUI::screenshotBtnPressed);

	gui.setup("Toolbox"); // most of the time you don't need a name but don't forget to call setup
	gui.add(filled.set("Remplir", true));
	gui.add(radius.set("Rayon", 140, 10, 300 ));
	gui.add(center.set("Centrer",glm::vec2(ofGetWidth()*.5,ofGetHeight()*.5),glm::vec2(0,0),glm::vec2(ofGetWidth(),ofGetHeight())));
	gui.add(color.set("Couleur",ofColor(100,100,140),ofColor(0,0),ofColor(255,255)));
	gui.add(circleResolution.set("Resolution du cercle", 5, 3, 90));
	gui.add(twoCircles.set("Deux cercles", false));
	gui.add(ringButton.setup("Cloche"));
	gui.add(screenSize.set("Screen size", ""));

	//Import Tool
	importToolsGroup.setup("Import tools");
	importToolsGroup.add(importImageBtn.setup("Import images"));
	//Capture Tool
	captureToolsGroup.setup("Capture tools");
	captureToolsGroup.add(screenshotBtn.setup("Screenshot"));
	captureToolsGroup.add(partialScreenshot.set("Partial Screenshot", false));

	//RecordMode
	recordModeTimeLimit = 10; //Time in seconds limit before forced exit of recordMode
	
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
	ofImage imgToExport;
	//TODO upgrade the selection to take a mouse selected portion of the screen
	if (partialScreenshot) {
		try {
			int screenshotWidth = stoi(ofSystemTextBoxDialog("Size of screenshot", "Width"));
			int screenshotHeight = stoi(ofSystemTextBoxDialog("Size of screenshot", "Height"));
			if (screenshotWidth > 0 && screenshotWidth <= screenWidth &&
				screenshotHeight > 0 && screenshotHeight <= screenHeight)
			{
				imgToExport.grabScreen(0, 0, screenshotWidth, screenshotHeight);
			}
			else {
				ofSystemAlertDialog("Error : The integer must be within the windows size ( Width 0 - "
					+ ofToString(screenWidth) + " Height 0 - " + ofToString(screenHeight));
				return;
			}
		}
		catch (...) {
			ofSystemAlertDialog("Error : You must enter an integer");
			return;
		}

	}
	else imgToExport.grabScreen(0, 0, screenWidth, screenHeight);

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


//--------------------------------------------------------------
void SlimeDungeonUI::update() {

	if (recordMode) { //Timer to force exit of recordMode
		if (recordModeEntryTime + recordModeTimeLimit <= ofGetSeconds()) {
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
    ofBackgroundGradient(ofColor::black, ofColor::green);
	sdCtrl.rendererDraw();
	

	//draw l'image qui a ete drag dans la window
	float dx = dragPt.x;
	float dy = dragPt.y;

	for (unsigned int k = 0; k < draggedImages.size(); k++) {
		draggedImages[k].draw(dx, dy);
		dy += draggedImages[k].getHeight() + 10;
	}

	ofSetColor(0);
	ofDrawBitmapString("drag image files into this window", 10, 20);
    
	if( filled ){
		ofFill();
	}else{
		ofNoFill();
	}

	ofSetColor(color);
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
		color = ofColor(255);
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
}

//--------------------------------------------------------------
void SlimeDungeonUI::mouseMoved(int x, int y ){
	
}

//--------------------------------------------------------------
void SlimeDungeonUI::mouseDragged(int x, int y, int button){
	positionImg.x = mouseX - distance.x;
	positionImg.y = mouseX - distance.y;

}

//--------------------------------------------------------------
void SlimeDungeonUI::mousePressed(int x, int y, int button){
	float dx = dragPt.x;
	float dy = dragPt.y;
	distance.x = mouseX - dragPt.x;
	distance.y = mouseY - dragPt.y;
}

//--------------------------------------------------------------
void SlimeDungeonUI::mouseReleased(int x, int y, int button){
	
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

		draggedImages.assign(info.files.size(), ofImage());
		for (unsigned int k = 0; k < info.files.size(); k++) {
			draggedImages[k].load(info.files[k]);
		}

	}
}

	//--------------------------------------------------------------
	bool SlimeDungeonUI::hasImgExtension(ofFile file) {
		string fileExt = ofToLower(file.getExtension());
		return (fileExt == "png");//|| fileExt == "jpg");
	}

