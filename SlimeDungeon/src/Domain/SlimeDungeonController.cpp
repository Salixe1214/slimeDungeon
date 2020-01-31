#include "SlimeDungeonController.h"


SlimeDungeonController::SlimeDungeonController()
{

}

void SlimeDungeonController::rendererDraw()
{
	ctrlRenderer.draw();
}

void SlimeDungeonController::exportImg(ofImage imgToExport, string filename) const 
{
	ctrlRenderer.exportImg(imgToExport, filename);
}

void SlimeDungeonController::publishEnterRecordModeEvent()
{
	ctrlRenderer.recordMode = true;
}


void SlimeDungeonController::publishExitRecordModeEvent()
{
	ctrlRenderer.recordMode = false;
}
