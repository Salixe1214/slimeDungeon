#include "SlimeDungeonController.h"


SlimeDungeonController::SlimeDungeonController()
{

}



void SlimeDungeonController::exportImg(ofImage imgToExport, string filename) const 
{
	ctrlRenderer.exportImg(imgToExport, filename);
}
