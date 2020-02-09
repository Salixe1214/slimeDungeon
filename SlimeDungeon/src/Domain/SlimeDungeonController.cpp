#include "SlimeDungeonController.h"


SlimeDungeonController::SlimeDungeonController()
{

}

void SlimeDungeonController::publishSetupEvent()
{
	ctrlRenderer.setup();
}

void SlimeDungeonController::rendererDraw(ofColor p_colorationInterne, ofColor p_colorationExterne)
{
	ctrlRenderer.draw(p_colorationInterne, p_colorationExterne);
}

void SlimeDungeonController::setDrawType(int drawType)
{
	switch (drawType) {
	case 0:
		ctrlRenderer.setShapeType(VectorPrimitiveType::none);
		break;
	case 1:
		ctrlRenderer.setShapeType(VectorPrimitiveType::pixel);
		break;
	case 2:
		ctrlRenderer.setShapeType(VectorPrimitiveType::line);
		break;

	case 3:
		ctrlRenderer.setShapeType(VectorPrimitiveType::rectangle);
		break;

	case 4:
		ctrlRenderer.setShapeType(VectorPrimitiveType::square);
		break;

	case 5:
		ctrlRenderer.setShapeType(VectorPrimitiveType::ellipse);
		break;

	case 6:
		ctrlRenderer.setShapeType(VectorPrimitiveType::circle);
		break;

	default:
		ctrlRenderer.setShapeType(VectorPrimitiveType::none);
		break;
	}
}

void SlimeDungeonController::addShape()
{
	ctrlRenderer.addVectorShape(ctrlRenderer.shapeType);
}

void SlimeDungeonController::setCurMouse(ofPoint newMousePos)
{
	ctrlRenderer.curMouse = newMousePos;
}

void SlimeDungeonController::setMousePress(ofPoint newMousePos)
{
	ctrlRenderer.mousePress = newMousePos;
}

void SlimeDungeonController::setCurMouseX(int x)
{
	ctrlRenderer.curMouse.x = x;
}

void SlimeDungeonController::setCurMouseY(int y)
{
	ctrlRenderer.curMouse.y = y;
}

void SlimeDungeonController::setRendererIsMousePressed(bool mouseIsPressed)
{
	ctrlRenderer.mouseIsPressed = mouseIsPressed;
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
