#include "ofMain.h"
#include "Domain/Renderer.h"

/** @brief classe qui lie le domaine et le UI
*/
class SlimeDungeonController
{

public:
	SlimeDungeonController();
	void exportImg(ofImage imgToExport, string filename) const;


private:
	Renderer ctrlRenderer;
	
};

