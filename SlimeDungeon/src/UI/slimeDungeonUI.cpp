#include "SlimeDungeonUI.h"

	
//--------------------------------------------------------------
void SlimeDungeonUI::setup(){
	ofSetVerticalSync(true);
	
	// we add this listener before setting up so the initial circle resolution is correct
	circleResolution.addListener(this, &SlimeDungeonUI::circleResolutionChanged);
	ringButton.addListener(this,&SlimeDungeonUI::ringButtonPressed);

	gui.setup("Dongeon Slimy slime"); // most of the time you don't need a name but don't forget to call setup
	gui.add(filled.set("Remplir", true));
	gui.add(radius.set("Rayon", 140, 10, 300 ));
	gui.add(center.set("Centrer",glm::vec2(ofGetWidth()*.5,ofGetHeight()*.5),glm::vec2(0,0),glm::vec2(ofGetWidth(),ofGetHeight())));
	gui.add(color.set("Couleur",ofColor(100,100,140),ofColor(0,0),ofColor(255,255)));
	gui.add(circleResolution.set("Resolution du cercle", 5, 3, 90));
	gui.add(twoCircles.set("Deux cercles", false));
	gui.add(ringButton.setup("Cloche"));
	gui.add(screenSize.set("Taille d'ecran", ""));
	
	bHide = false;

	ring.load("ring.wav");
}

//--------------------------------------------------------------
void SlimeDungeonUI::exit(){
	ringButton.removeListener(this,&SlimeDungeonUI::ringButtonPressed);
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
void SlimeDungeonUI::update(){
}

//--------------------------------------------------------------
void SlimeDungeonUI::draw(){
    ofBackgroundGradient(ofColor::black, ofColor::red);
    
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
	
}

//--------------------------------------------------------------
void SlimeDungeonUI::mouseMoved(int x, int y ){
	
}

//--------------------------------------------------------------
void SlimeDungeonUI::mouseDragged(int x, int y, int button){
}

//--------------------------------------------------------------
void SlimeDungeonUI::mousePressed(int x, int y, int button){
	
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
    screenSize = ofToString(w) + "x" + ofToString(h);
}

//--------------------------------------------------------------
void SlimeDungeonUI::gotMessage(ofMessage msg){
	
}

//--------------------------------------------------------------
void SlimeDungeonUI::dragEvent(ofDragInfo dragInfo){ 
	
}
