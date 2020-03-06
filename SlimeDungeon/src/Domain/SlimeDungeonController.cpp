#include "SlimeDungeonController.h"


SlimeDungeonController::SlimeDungeonController()
{

}

void SlimeDungeonController::publishSetupEvent(ofxPanel *gui)
{
	ctrlRenderer.setup(gui);
}

void SlimeDungeonController::publishExitEvent()
{
	ctrlRenderer.exit();
}

void SlimeDungeonController::checkClickInShape()
{
	ctrlRenderer.checkClickInShape();
}

void SlimeDungeonController::deleteSelectedShape()
{
	ctrlRenderer.deleteSelectedShape();
}

bool SlimeDungeonController::isSelectedShapeEmpty()
{
	return ctrlRenderer.isSelectedShapeEmpty();
}

void SlimeDungeonController::rendererDraw(ofParameter<ofColor> fillColor, ofParameter<ofColor> strokeColor)
{
	ctrlRenderer.draw();
	ctrlRenderer.update(fillColor, strokeColor);
}

void SlimeDungeonController::setDrawMode(bool drawMode)
{
	ctrlRenderer.setDrawMode(drawMode);
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

	case 7:
		ctrlRenderer.setShapeType(VectorPrimitiveType::tiles);
		break;

	case 8:
		ctrlRenderer.setShapeType(VectorPrimitiveType::slime);
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

void SlimeDungeonController::setFill(bool fill)
{
	ctrlRenderer.setFill(fill);
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

void SlimeDungeonController::setCameraMoveLeft(bool isCameraMoveLeft)
{
	ctrlRenderer.setCameraMoveLeft(isCameraMoveLeft);
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

void SlimeDungeonController::changeState(bool goBack) {
	if (goBack) ctrlRenderer.goBack();
	else ctrlRenderer.reDo();
}

void SlimeDungeonController::setSelectionColor(ofColor fillColorScene, ofColor strokeColorScene)
{
	ctrlRenderer.setSelectionColor(fillColorScene, strokeColorScene);
}

void SlimeDungeonController::setPartialScreenBool(bool isPartialScreen)
{
	ctrlRenderer.setPartialScreenBool(isPartialScreen);
}

void SlimeDungeonController::setMouseOverGUI(bool overGUI)
{
	ctrlRenderer.setMouseOverGUI(overGUI);
}

int SlimeDungeonController::getSelectedShapeSize()
{
	return ctrlRenderer.getSelectedShapeSize();
}

string SlimeDungeonController::getFirstSelectedShapeName()
{
	return ctrlRenderer.getFirstSelectedShapeName();
}

void SlimeDungeonController::extendSelectionBorder(float dx, float dy)
{
	ctrlRenderer.extendSelectionBorder(dx, dy);
}

void SlimeDungeonController::addTileShapeRow(int addedXRow, int addedYRow)
{
	ctrlRenderer.addTileShapeRow(addedXRow, addedYRow);
}

void SlimeDungeonController::translateSelection(float dx, float dy, float dz)
{
	ctrlRenderer.translateSelection(dx, dy, dz);
}

void SlimeDungeonController::rotateSelectionZ(float thetaZ)
{
	ctrlRenderer.rotateSelectionZ(thetaZ);
}

void SlimeDungeonController::scaleSelection(float sx, float sy, float sz)
{
	ctrlRenderer.scaleSelection(sx, sy, sz);
}
