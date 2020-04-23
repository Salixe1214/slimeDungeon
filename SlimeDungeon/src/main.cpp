#include "ofMain.h"
#include "UI/SlimeDungeonUI.h"


//========================================================================
int main( ){
	ofGLFWWindowSettings settings;
	settings.setGLVersion(3, 3); //we define the OpenGL version we want to use
	settings.setSize(1024, 768);
	ofCreateWindow(settings);
	ofRunApp(new SlimeDungeonUI());

}
