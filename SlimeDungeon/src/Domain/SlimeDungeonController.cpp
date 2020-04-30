#include "SlimeDungeonController.h"


SlimeDungeonController::SlimeDungeonController()
{
	lightManager = LightManager::getLightManager();
}

void SlimeDungeonController::publishSetupEvent(ofxPanel *gui)
{
	glm::vec3 camInitialPos = glm::vec3(0, 0, 1000);
	lightManager->setup(camInitialPos);
	ctrlRenderer.setup(gui, camInitialPos);
}

void SlimeDungeonController::publishExitEvent()
{
	ctrlRenderer.exit();
}

void SlimeDungeonController::publishWindowResizedEvent(int w, int h)
{
	ctrlRenderer.windowResizedEvent(w, h);
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
	//lightManager->draw(); TODO Not sure yet where is best to put this.
	lightManager->update();

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
	case 9:
		ctrlRenderer.setShapeType(VectorPrimitiveType::slime3d);
		break;
	case 10:
		ctrlRenderer.setShapeType(VectorPrimitiveType::monster3d);
		break;
	case 11:
		ctrlRenderer.setShapeType(VectorPrimitiveType::ballFace);
		break;
	case 12:
		ctrlRenderer.setShapeType(VectorPrimitiveType::cube);
		break;
	case 13:
		ctrlRenderer.setShapeType(VectorPrimitiveType::ball);
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

void SlimeDungeonController::addImage(ofImage image, ofPoint imgPoint) {
	ctrlRenderer.addImageShape(image, imgPoint);
}

void SlimeDungeonController::BlurOn(bool isBlurOn)
{
	ctrlRenderer.blOn = isBlurOn;
	
}

void SlimeDungeonController::mapTonOn(bool isMapOn)
{
	ctrlRenderer.tnOn = isMapOn;

}

void SlimeDungeonController::gaussOn(bool isGaussOn)
{
	ctrlRenderer.gaOn = isGaussOn;

}

void SlimeDungeonController::bilatOn(bool isBilatOn)
{
	ctrlRenderer.biOn = isBilatOn;

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

void SlimeDungeonController::setCameraDollyFront(bool isCameraDollyFront)
{
	ctrlRenderer.setCameraDollyFront(isCameraDollyFront);
}

void SlimeDungeonController::setCameraDollyBack(bool isCameraDollyBack)
{
	ctrlRenderer.setCameraDollyBack(isCameraDollyBack);
}

void SlimeDungeonController::resetCam()
{
	// Recentre la caméra
	ctrlRenderer.camFront.setPosition(0, 0, 1000);
	// Recentre la vue de la caméra
	ctrlRenderer.camFront.lookAt(glm::vec3(0, 0, 0));

	// Reset les offsets pour calculer la position des formes a dessiner
	ctrlRenderer.cameraOffsetX = 0;
	ctrlRenderer.cameraOffsetY = 0;
	ctrlRenderer.offsetAngle = 0;
}

void SlimeDungeonController::exportImg(ofImage imgToExport, string filename) const 
{
	ctrlRenderer.exportImg(imgToExport, filename);
}

void SlimeDungeonController::setActiveMaterialName(string activeMaterialName)
{
	ctrlRenderer.setActiveMaterialName(activeMaterialName);
}

void SlimeDungeonController::setBallTextureFile(string p_ballTextureFile)
{
	ctrlRenderer.setBallTextureFile(p_ballTextureFile);
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

void SlimeDungeonController::setCameraMoveDown(bool isMoveDown)
{
	ctrlRenderer.setCameraMoveDown(isMoveDown);
}

void SlimeDungeonController::setCameraRollLeft(bool isRollLeft)
{
	ctrlRenderer.setCameraRollLeft(isRollLeft);
}

void SlimeDungeonController::setCameraRollRight(bool isRollRight)
{
	ctrlRenderer.setCameraRollRight(isRollRight);
}

void SlimeDungeonController::setCameraMoveUp(bool isMoveUp)
{
	ctrlRenderer.setCameraMoveUp(isMoveUp);
}

void SlimeDungeonController::setCameraMoveRight(bool isMoveRight)
{
	ctrlRenderer.setCameraMoveRight(isMoveRight);
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

void SlimeDungeonController::setDrawLightGizmo(bool drawLightGizmo)
{
	lightManager->setDrawLightGizmo(drawLightGizmo);
}

void SlimeDungeonController::setAmbientLightActive(bool isAmbientLightActive)
{
	lightManager->setAmbientLightActive(isAmbientLightActive);
}

void SlimeDungeonController::setDirLightActive(bool isDirLightActive)
{
	lightManager->setDirLightActive(isDirLightActive);
}

void SlimeDungeonController::setPonctLightActive(bool isPonctLightActive)
{
	lightManager->setPonctLightActive(isPonctLightActive);
}

void SlimeDungeonController::setSpotLightActive(bool isSpotLightActive)
{
	lightManager->setSpotLightActive(isSpotLightActive);
}

void SlimeDungeonController::setActiveLightDiffuseColor(ofColor diffuseColor)
{
	lightManager->setActiveLightDiffuseColor(diffuseColor);
}

void SlimeDungeonController::setActiveLightSpecularColor(ofColor specularColor)
{
	lightManager->setActiveLightSpecularColor(specularColor);
}

void SlimeDungeonController::setActiveAmbientLightColor(ofColor ambiantColor)
{
	lightManager->setAmbientColorLight(ambiantColor);
}

void SlimeDungeonController::translateActiveLightPosX(float dx)
{
	lightManager->translateActiveLightPosX(dx);
}

void SlimeDungeonController::translateActiveLightPosY(float dy)
{
	lightManager->translateActiveLightPosY(dy);
}

void SlimeDungeonController::translateActiveLightPosZ(float dz)
{
	lightManager->translateActiveLightPosZ(dz);
}

void SlimeDungeonController::setCatRomShow(bool catRomShow)
{
	ctrlRenderer.setCatmullRomShow(catRomShow);
}

void SlimeDungeonController::addEmptyCatRom()
{
	ctrlRenderer.addEmptyCatmullRom();
}

string SlimeDungeonController::getActiveCatRomId()
{
	return ctrlRenderer.getActiveCatRomSplineId();
}

void SlimeDungeonController::addCatRomPt()
{
	ctrlRenderer.addActiveCatmullRomPoint();
}

void SlimeDungeonController::nextCatRomSpline()
{
	ctrlRenderer.nextCatRomSpline();
}

void SlimeDungeonController::deleteActiveCatRomSpline()
{
	ctrlRenderer.deleteActiveCatRomSpline();
}

void SlimeDungeonController::communiquerBS(bool b, int c, int p, int d, bool m)
{
	ctrlRenderer.dessinerBS = b;
	ctrlRenderer.bs.selectedCurve = c;
	ctrlRenderer.bs.selectedPoint = p;
	if (m) {
		switch (d)
		{
		case 0: // +x
			ctrlRenderer.bs.ctrPoints[c][p].x += 10;
			break;
		case 1: // -x
			ctrlRenderer.bs.ctrPoints[c][p].x -= 10;
			break;
		case 2: // +y
			ctrlRenderer.bs.ctrPoints[c][p].y += 10;
			break;
		case 3: // -y
			ctrlRenderer.bs.ctrPoints[c][p].y -= 10;
			break;
		case 4: // +z
			ctrlRenderer.bs.ctrPoints[c][p].z += 10;
			break;
		case 5: // -z
			ctrlRenderer.bs.ctrPoints[c][p].z -= 10;
			break;
		default:
			break;
		}
	}
}

void SlimeDungeonController::switchShaders() {
	ctrlRenderer.shade = !ctrlRenderer.shade;
}

