#include "ofMain.h"
#include "UI/SlimeDungeonUI.h"


//========================================================================
int main( ){
    ofGLFWWindowSettings windowSettings;
    windowSettings.numSamples = 4;
    ofCreateWindow(windowSettings);
	ofRunApp(new SlimeDungeonUI());

}
