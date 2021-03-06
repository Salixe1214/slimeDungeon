#include "SlimeDungeonUI.h"

//--------------------------------------------------------------
void SlimeDungeonUI::setup(){
	screenB = false;
	ofSetVerticalSync(true);

	setDefaultParameter();

	//Scene

	// Ajout �ventuel d'un affichage des �l�ments de la sc�ne dans une hi�rarchie
	scene.setup("Scene Managing");
	//scene.setDefaultWidth(scenePanelWidth);
	scene.setPosition(ofGetWidth() - scenePanelWidth, 0); //To the right of the window

	scene.add(hierarchy.setup("Selection", emptySceneMsg));
	scene.add(deleteShapeBtn.setup("Delete selected shape"));
	
	//Transform
	transformToolsGroup.setup("Transform tools");

	transformToolsGroup.add(fillColorScene.set("Selection fill color", ofColor(110, 100, 140), ofColor(0, 0), ofColor(255, 255)));
	transformToolsGroup.add(strokeColorScene.set("Selection stroke color", ofColor(110, 100, 140), ofColor(0, 0), ofColor(255, 255)));
	
	transformToolsGroup.add(extendSelectionX.set("Extend selection by x", 0, -100, 100));
	transformToolsGroup.add(extendSelectionY.set("Extend selection by y", 0, -100, 100));
	transformToolsGroup.add(addTileRow.setup("Add tile row", false));
	transformToolsGroup.add(extendTileRowX.set("Add tile row x", 0, -10, 10));
	transformToolsGroup.add(extendTileRowY.set("Add tile row y", 0, -10, 10));

	//Translation
	translationToolsGroup.setup("Translation tools");
	translationToolsGroup.add(translateX.set("Translate x", 0, -1000, 1000));
	translationToolsGroup.add(translateY.set("Translate y", 0, -1000, 1000));

	transformToolsGroup.add(&translationToolsGroup);

	//Rotation
	rotationToolsGroup.setup("Rotation tools");
	rotationToolsGroup.add(rotateZ.set("Rotation ", 0, -180, 180));

	transformToolsGroup.add(&rotationToolsGroup);

	//Scale
	scalingToolsGroup.setup("Scaling tools");
	scalingToolsGroup.add(scaleX.set("Scaling x", 0, 0.01, 10));
	scalingToolsGroup.add(scaleY.set("Scaling y", 0, 0.01, 10));
	scalingToolsGroup.add(keepScaleProportion.setup("Keep proportion", true));

	transformToolsGroup.add(&scalingToolsGroup);

	scene.add(&transformToolsGroup);

	//Lighting
	lightingGroup.setup("Lighting tools");
	
	lightingGroup.add(activeAmbientLightBtn.setup("Ambient Light On/Off", true));
	lightingGroup.add(activeDirLightBtn.setup("Directionnal Light On/Off", true));
	lightingGroup.add(activePonctLightBtn.setup("Ponctual Light On/Off", true));
	lightingGroup.add(activeSpotLightBtn.setup("Spotlight On/Off", true));
	lightingGroup.add(drawLightGizmoBtn.setup("Draw Lights gizmo", true));

	//Edit Lighting
	editLightingGroup.setup("Edit Lighting");

	editLightingGroup.add(activeLightPosX.set("Active Lights dx", 0, -500, 500));
	editLightingGroup.add(activeLightPosY.set("Active Lights dy", 0, -500, 500));
	editLightingGroup.add(activeLightPosZ.set("Active Lights dz", 0, -500, 500));

	editLightingGroup.add(activeLightDiffuseColor.set("Lights diffuse Color", ofColor(255, 255, 255), ofColor(0, 0), ofColor(255, 255)));
	editLightingGroup.add(activeLightSpecularColor.set("Lights specular Color", ofColor(191, 191, 191), ofColor(0, 0), ofColor(255, 255)));
	
	//Ambient Light specific
	editLightingGroup.add(activeAmbiantLightColor.set("Ambient Lights Color", ofColor(127, 127, 127), ofColor(0, 0), ofColor(255, 255)));

	//Spot Light Specific
	editLightingGroup.add(spotCutoff.set("Spot cutoff", 500, 0, 1000));
	editLightingGroup.add(spotConcentration.set("Spot Concentration", 0.1, 0, 100));

	scene.add(&lightingGroup);
	scene.add(&editLightingGroup);
	

	//gui
	gui.setup("Toolbox"); 

	gui.add(backColor1.set("Fond exterieur",ofColor::green,ofColor(0,0),ofColor(255,255)));
    gui.add(backColor2.set("Fond interieur",ofColor::black,ofColor(0,0),ofColor(255,255)));

	gui.add(screenSize.set("Screen size", ""));

	//PBR sphere
	group_material_factor.setup("PBR sphere");
	
	gui.add(&group_material_factor);
	group_material_factor.add(drawSphere.setup("Draw shpere PBR", false));
	group_material_factor.add(slider_metallic);
	group_material_factor.add(slider_roughness);
	group_material_factor.add(slider_occlusion);
	group_material_factor.add(slider_brightness);

	//Draw tools
	drawToolsGroup.setup("Draw tools");	

	drawToolsGroup.add(drawMode.setup("Draw mode", true));
	drawToolsGroup.add(currentShapeType.setup("Draw : ", "pixel"));
	drawToolsGroup.add(shapeColor2.set("Stroke color", ofColor(110, 100, 140), ofColor(0, 0), ofColor(255, 255)));
	drawToolsGroup.add(filled.set("Remplir", true));
	drawToolsGroup.add(shapeColor1.set("Fill color", ofColor(110, 100, 140), ofColor(0, 0), ofColor(255, 255)));

	//Material
	materialGroup.setup("Shape material");
	materialGroup.add(darkMaterialBtn.setup("Dark", false));
	materialGroup.add(sparklingMaterialBtn.setup("Sparkling", false));
	materialGroup.add(plainMaterialBtn.setup("Plain", false));

	drawToolsGroup.add(&materialGroup);

	//Texture
	ballTextureGroup.setup("Ball texture");
	ballTextureGroup.add(ballScaleTextureBtn.setup("Scale ball", false));
	ballTextureGroup.add(ballSporeTextureBtn.setup("Spore ball", false));
	ballTextureGroup.add(ballMoltenTextureBtn.setup("Molten ball", false));
	drawToolsGroup.add(&ballTextureGroup);


	//Spline
	catRomGroup.setup("Catmull-Rom spline");

	catRomGroup.add(catRomShowBtn.setup("Show spline", true));
	catRomGroup.add(catRomEditBtn.setup("Edit spline", false));
	catRomGroup.add(activeCatRomSpline.setup("Active spline id", noSplineMsg));
	catRomGroup.add(catRomNextSplineBtn.setup("Next spline"));
	catRomGroup.add(catRomAddSplineBtn.setup("Add new spline"));
	catRomGroup.add(catRomDeleteSplineBtn.setup("Delete active spline"));

	drawToolsGroup.add(&catRomGroup);

	//Import Tool
	importToolsGroup.setup("Import tools");
	importToolsGroup.add(importImageBtn.setup("Import images"));
	importToolsGroup.add(BlurImage.setup("Blur Image", false));
	importToolsGroup.add(mapTonalImage.setup("Mappage Tonnal", false));
	importToolsGroup.add(gaussImage.setup("Gaussian Blur", false));
	importToolsGroup.add(bilatImage.setup("Bilateral Smooth", false));

	//Capture Tool
	captureToolsGroup.setup("Capture tools");
	captureToolsGroup.add(screenshotBtn.setup("Screenshot"));
	captureToolsGroup.add(partialScreenshot.set("Partial Screenshot", false));

	//RecordMode
	recordModeTimeLimit = 10; //Time in seconds limit before forced exit of recordMode
	
	gui.add(&drawToolsGroup);
	gui.add(&captureToolsGroup);
	gui.add(&importToolsGroup);
	
	
	sdCtrl.publishSetupEvent(&gui);

	instructions.push_back("Tracez une forme avec votre souris");
	instructions.push_back("Utiliser les chiffres pour tracer differentes formes");
	instructions.push_back("Utiliser 9, 0 et \"-\" pour tracer des formes 3D");
	instructions.push_back("Utiliser \"b\" pour tracer une boule");
	instructions.push_back("Utiliser \"c\" pour tracer un cube");
	instructions.push_back("Utiliser p pour activer le tra�age d'une spline de Catmull-Rom");
	instructions.push_back("h pour cacher l'interface");
	instructions.push_back("x pour enregistrer les parametres");
	instructions.push_back("l pour charger les parametres");
	instructions.push_back("Gauche pour retourner en arriere");
	instructions.push_back("Droite pour annuler le retour en arriere");
	instructions.push_back("\"q\", \"w\", \"e\", \"a\", \"s\", \"d\", ctr gauche\n et alt gauche pour bouger la camera");

	light.setPosition(0, 0, 1000);

	//Listeners
	screenshotBtn.addListener(this, &SlimeDungeonUI::screenshotBtnPressed);
	deleteShapeBtn.addListener(this, &SlimeDungeonUI::deleteShapeBtnPressed);
	importImageBtn.addListener(this, &SlimeDungeonUI::importImageBtnPressed);
	BlurImage.addListener(this, &SlimeDungeonUI::BlurBtnPressed);
	mapTonalImage.addListener(this, &SlimeDungeonUI::mapBtnPressed);
	gaussImage.addListener(this, &SlimeDungeonUI::gaussBtnPressed);
	bilatImage.addListener(this, &SlimeDungeonUI::bilatBtnPressed);
	drawSphere.addListener(this, &SlimeDungeonUI::drawSpherePressed);


	//catRom
	catRomEditBtn.addListener(this, &SlimeDungeonUI::catRomEditBtnPressed);
	catRomShowBtn.addListener(this, &SlimeDungeonUI::catRomShowBtnPressed);
	catRomNextSplineBtn.addListener(this, &SlimeDungeonUI::nextSplineBtnPressed);
	catRomAddSplineBtn.addListener(this, &SlimeDungeonUI::addSplineBtnPressed);
	catRomDeleteSplineBtn.addListener(this, &SlimeDungeonUI::deleteSplineBtnPressed);


	//Light
	drawLightGizmoBtn.addListener(this, &SlimeDungeonUI::drawLightGizmoBtnPressed);
	activeAmbientLightBtn.addListener(this, &SlimeDungeonUI::activeAmbientLightBtnPressed);
	activeDirLightBtn.addListener(this, &SlimeDungeonUI::activeDirLightBtnPressed);
	activePonctLightBtn.addListener(this, &SlimeDungeonUI::activePonctLightBtnPressed);
	activeSpotLightBtn.addListener(this, &SlimeDungeonUI::activeSpotLightBtnPressed);

	//darkMaterialBtn.addListener(this, &SlimeDungeonUI::oneMaterialBtnPressed);
	//sparklingMaterialBtn.addListener(this, &SlimeDungeonUI::oneMaterialBtnPressed);
	//plainMaterialBtn.addListener(this, &SlimeDungeonUI::oneMaterialBtnPressed);
	darkMaterialBtn.addListener(this, &SlimeDungeonUI::darkMaterialBtnPressed);
	sparklingMaterialBtn.addListener(this, &SlimeDungeonUI::sparklingMaterialBtnPressed);
	plainMaterialBtn.addListener(this, &SlimeDungeonUI::plainMaterialBtnPressed);

	mapTon.load("mapage_tonale_330_vs.glsl", "mapage_tonale_330_fs.glsl");

	// Surface de B�zier bicubique
	bezSurface.setup("Surface de Bezier");
	bezSurface.setPosition(gui.getWidth() + 15, 150);
	
	// Parametre pour dessiner ou non la surface
	bezSurface.add(drawSurface.set(false));
	drawSurface.setName("Dessiner la surface");

	// Parametres de modiffication de la courbe
	bezSurface.add(curve.set("Courbe", 0, 0, 3));
	bezSurface.add(point.set("Point", 0, 0, 3));

	bezSurface.add(direction.set("Direction", 0, 0, 5));
	bezSurface.add(move.setup("Bouger"));



}


void SlimeDungeonUI::setDefaultParameter() {
	//Scene
	scenePanelWidth = 200;
	emptySceneMsg = "No element in scene";
	//Transform
	prevFillColorScene = (ofColor(110, 100, 140), ofColor(0, 0), ofColor(255, 255));
	prevStrokeColorScene = (ofColor(110, 100, 140), ofColor(0, 0), ofColor(255, 255));
	prevExtendSelectionX = prevExtendSelectionY  = 0.0f;
	prevExtendTileRowX = prevExtendTileRowY = 0;

	//Translate
	prevTranslateX = prevTranslateY = 0.0f;

	//Rotate
	prevRotateZ = 0.0f;

	//Scale
	prevScaleX = prevScaleY = 1.0f;


	//Lighting
	prevActiveLightPosX = 0.0;
	prevActiveLightPosY = 0.0;
	prevActiveLightPosZ = 0.0;
	prevActiveLightDiffuseColor = ofColor(255, 255, 255);
	prevActiveLightSpecularColor = ofColor(191, 191, 191);

	//Ambient Light Specific
	prevActiveAmbientLightColor = ofColor(127, 127, 127);

	//Spot Light specific
	prevSpotCutOff = 500.0;
	prevSpotConcentration = 0.1;

	//drawMode
	prevDrawMode = true;
	prevFill = true;
	bHide = false;

	//Catmull-Rom spline
	noSplineMsg = "No Spline";

	//Texture
	ballScaleTextureFile = "texture/ballTexture/scaleBall.jpg";
	ballSporeTextureFile = "texture/ballTexture/sporeBall.jpg";
	ballMoltenTextureFile = "texture/ballTexture/moltenBall.jpg";
}

//--------------------------------------------------------------
void SlimeDungeonUI::exit(){
	screenshotBtn.removeListener(this, &SlimeDungeonUI::screenshotBtnPressed);
	deleteShapeBtn.removeListener(this, &SlimeDungeonUI::deleteShapeBtnPressed);
	importImageBtn.removeListener(this, &SlimeDungeonUI::importImageBtnPressed);
	BlurImage.removeListener(this, &SlimeDungeonUI::BlurBtnPressed);
	mapTonalImage.removeListener(this, &SlimeDungeonUI::mapBtnPressed);
	gaussImage.removeListener(this, &SlimeDungeonUI::gaussBtnPressed);
	bilatImage.removeListener(this, &SlimeDungeonUI::bilatBtnPressed);


	catRomEditBtn.removeListener(this, &SlimeDungeonUI::catRomEditBtnPressed);
	catRomShowBtn.removeListener(this, &SlimeDungeonUI::catRomShowBtnPressed);
	catRomNextSplineBtn.removeListener(this, &SlimeDungeonUI::nextSplineBtnPressed);
	catRomAddSplineBtn.removeListener(this, &SlimeDungeonUI::addSplineBtnPressed);
	catRomDeleteSplineBtn.removeListener(this, &SlimeDungeonUI::deleteSplineBtnPressed);

	activeAmbientLightBtn.removeListener(this, &SlimeDungeonUI::activeAmbientLightBtnPressed);
	activeDirLightBtn.removeListener(this, &SlimeDungeonUI::activeDirLightBtnPressed);
	activePonctLightBtn.removeListener(this, &SlimeDungeonUI::activePonctLightBtnPressed);
	activeSpotLightBtn.removeListener(this, &SlimeDungeonUI::activeSpotLightBtnPressed);
	drawLightGizmoBtn.removeListener(this, &SlimeDungeonUI::drawLightGizmoBtnPressed);

	darkMaterialBtn.removeListener(this, &SlimeDungeonUI::darkMaterialBtnPressed);
	sparklingMaterialBtn.removeListener(this, &SlimeDungeonUI::sparklingMaterialBtnPressed);
	plainMaterialBtn.removeListener(this, &SlimeDungeonUI::plainMaterialBtnPressed);

	sdCtrl.publishExitEvent();
}

void SlimeDungeonUI::BlurBtnPressed(bool &isBlurBtnPressed) {
	sdCtrl.BlurOn(isBlurBtnPressed);
}

void SlimeDungeonUI::mapBtnPressed(bool& isMapBtnPressed) {
	sdCtrl.mapTonOn(isMapBtnPressed);
}

void SlimeDungeonUI::gaussBtnPressed(bool& isGaussBtnPressed) {
	sdCtrl.gaussOn(isGaussBtnPressed);
}

void SlimeDungeonUI::bilatBtnPressed(bool& isBilatBtnPressed) {
	sdCtrl.bilatOn(isBilatBtnPressed);
}


void SlimeDungeonUI::catRomEditBtnPressed(bool &isCatRomEditBtnPressed) {
	if (isCatRomEditBtnPressed) {
		drawMode = false;
		prevDrawMode = false;
	}
}

void SlimeDungeonUI::catRomShowBtnPressed(bool &isCatRomShowBtnPressed) {
	sdCtrl.setCatRomShow(isCatRomShowBtnPressed);
}

void SlimeDungeonUI::addSplineBtnPressed()
{
	sdCtrl.addEmptyCatRom();
	string tmp = sdCtrl.getActiveCatRomId();
	if (tmp.empty()) activeCatRomSpline = noSplineMsg;
	else activeCatRomSpline = tmp;
}

void SlimeDungeonUI::nextSplineBtnPressed()
{
	sdCtrl.nextCatRomSpline();
	string tmp = sdCtrl.getActiveCatRomId();
	if (tmp.empty()) activeCatRomSpline = noSplineMsg;
	else activeCatRomSpline = tmp;
}

void SlimeDungeonUI::deleteSplineBtnPressed()
{
	sdCtrl.deleteActiveCatRomSpline();
	string tmp = sdCtrl.getActiveCatRomId();
	if (tmp.empty()) activeCatRomSpline = noSplineMsg;
	else activeCatRomSpline = tmp;
}


//void SlimeDungeonUI::oneMaterialBtnPressed(string materialName, bool materialBtnPressed) {
//
//	if (materialBtnPressed) {
//		for (auto materialBtn : materialBtns) {
//			materialBtn = false;
//		}
//		cout << materialName<< " turned on" << endl;
//		//sdCtrl.setActiveMaterialName(materialName);
//	}
//}

void SlimeDungeonUI::darkMaterialBtnPressed(bool &darkMaterialBtnPressed) {
	if (darkMaterialBtnPressed) {
		sparklingMaterialBtn = false;
		plainMaterialBtn = false;
		sdCtrl.setActiveMaterialName(darkMaterialBtn.getName());
	}
	else sdCtrl.setActiveMaterialName("");
}

void SlimeDungeonUI::sparklingMaterialBtnPressed(bool &sparklingMaterialBtnPressed) {
	if (sparklingMaterialBtnPressed) {
		darkMaterialBtn = false;
		plainMaterialBtn = false;
		sdCtrl.setActiveMaterialName(sparklingMaterialBtn.getName());
	}
	else sdCtrl.setActiveMaterialName("");
}

void SlimeDungeonUI::plainMaterialBtnPressed(bool &plainMaterialBtnPressed) {
	if (plainMaterialBtnPressed) {
		darkMaterialBtn = false;
		sparklingMaterialBtn = false;
		sdCtrl.setActiveMaterialName(plainMaterialBtn.getName());
	}
	else sdCtrl.setActiveMaterialName("");
}



void SlimeDungeonUI::drawLightGizmoBtnPressed(bool &drawLightGizmoPressed) {
	sdCtrl.setDrawLightGizmo(drawLightGizmoPressed);
	prevActiveLightPosX = activeLightPosX = 0.0;
	prevActiveLightPosY = activeLightPosY = 0.0;
	prevActiveLightPosZ = activeLightPosZ = 0.0;
}

void SlimeDungeonUI::activeAmbientLightBtnPressed(bool &activeAmbientLightPressed) {
	sdCtrl.setAmbientLightActive(activeAmbientLightPressed);
}

void SlimeDungeonUI::activeDirLightBtnPressed(bool &activeDirLightPressed) {
	sdCtrl.setDirLightActive(activeDirLightPressed);
}

void SlimeDungeonUI::activePonctLightBtnPressed(bool &activePonctLightPressed) {
	sdCtrl.setPonctLightActive(activePonctLightPressed);
}

void SlimeDungeonUI::activeSpotLightBtnPressed(bool &activeSpotLightPressed) {
	sdCtrl.setSpotLightActive(activeSpotLightPressed);
}

void SlimeDungeonUI::drawSpherePressed(bool& drawSpherePressed) {
	sdCtrl.drawSphereOn(drawSpherePressed);
}


void SlimeDungeonUI::deleteShapeBtnPressed() {
	if (sdCtrl.isSelectedShapeEmpty()) ofSystemAlertDialog("Select at least one shape");
	else sdCtrl.deleteSelectedShape();
}

//--------------------------------------------------------------
void SlimeDungeonUI::importImageBtnPressed() {
	ofSystemAlertDialog("Select the image you want to import");
	ofFileDialogResult loadFileResult = ofSystemLoadDialog("Load your file", false);
	if (loadFileResult.bSuccess) {
		string loadPath = loadFileResult.getPath();
		imageImport.load(loadPath);
		ifImageImport = true;
	}
	else {
		ofSystemAlertDialog("You did not select the image properly.");
	}


}

void SlimeDungeonUI::screenshotBtnPressed()
{
	if (!isWaitingForScreenSelection) {
		if (partialScreenshot) {
			//try {
			//	int screenshotWidth = stoi(ofSystemTextBoxDialog("Size of screenshot", "Width"));
			//	int screenshotHeight = stoi(ofSystemTextBoxDialog("Size of screenshot", "Height"));
			ofSystemAlertDialog("Select the portion of the screen you want to export");
			isWaitingForScreenSelection = true;
			sdCtrl.setPartialScreenBool(true);
		}
		else {
			imgToExport.grabScreen(0, 0, screenWidth, screenHeight);
			exportScreenshot();
			
		}
		
	}
	
}

//Export the imgToExport
void SlimeDungeonUI::exportScreenshot() {
	if (imgToExport.isAllocated()) {
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
}


//--------------------------------------------------------------
void SlimeDungeonUI::update() {

	

	if (recordMode) { //Timer to force exit of recordMode
		if (recordModeEntryTime + recordModeTimeLimit <= (size_t)ofGetSeconds()) {
			exitRecordMode();
		}
		else {
		}
	}
	if (drawMode != prevDrawMode) {
		sdCtrl.setDrawMode(drawMode);
		prevDrawMode = drawMode;
		catRomEditBtn = false;
	}

	if (filled != prevFill) {
		sdCtrl.setFill(filled);
		prevFill = filled;
	}
	int numShape = sdCtrl.getSelectedShapeSize();
	if (numShape > 0) {
		if (numShape == 1)		hierarchy = sdCtrl.getFirstSelectedShapeName();
		else hierarchy = "Shapes group";
	}
	else hierarchy = "No shape selected";

	//--texture
	updateBallTexture();

	//Drag les images a l'interieure de la window
	//Check width

	//Change selected Shape color
	if (prevFillColorScene != fillColorScene || prevStrokeColorScene != strokeColorScene) {
		sdCtrl.setSelectionColor(ofColor(fillColorScene), ofColor(strokeColorScene));
		prevFillColorScene = fillColorScene;
		prevStrokeColorScene = strokeColorScene;
	}

	//Transform selected shapes
	if (!sdCtrl.isSelectedShapeEmpty()) {
		//Change selected shapes border
		if ((!ofIsFloatEqual(prevExtendSelectionX, (float)extendSelectionX) || !ofIsFloatEqual(prevExtendSelectionY, (float)extendSelectionY))
			&& !addTileRow)
		{
			sdCtrl.extendSelectionBorder((float)extendSelectionX - prevExtendSelectionX,
				(float)extendSelectionY - prevExtendSelectionY);
			prevExtendSelectionX = extendSelectionX;
			prevExtendSelectionY = extendSelectionY;
		}
		else if (addTileRow) { 
			sdCtrl.addTileShapeRow(extendTileRowX - prevExtendTileRowX,
				extendTileRowY - prevExtendTileRowY);
			prevExtendTileRowX = extendTileRowX;
			prevExtendTileRowY = extendTileRowY;
		}

		//Translate
		if (!ofIsFloatEqual(prevTranslateX, (float)translateX) || !ofIsFloatEqual(prevTranslateY, (float)translateY)) {
			sdCtrl.translateSelection(translateX - prevTranslateX, translateY - prevTranslateY);
			prevTranslateX = translateX;
			prevTranslateY = translateY;
		}

		//Rotate
		if (!ofIsFloatEqual(prevRotateZ, (float)rotateZ)) {
			sdCtrl.rotateSelectionZ(rotateZ - prevRotateZ);
			prevRotateZ = rotateZ;
		}

		//Scale
		if (!ofIsFloatEqual(prevScaleX, (float)scaleX) || !ofIsFloatEqual(prevScaleY, (float)scaleY)) {
			if (keepScaleProportion) {
				scaleY = scaleX;
			}
			sdCtrl.scaleSelection(scaleX/prevScaleX, scaleY/prevScaleY);
			prevScaleX = scaleX;
			prevScaleY = scaleY;
		}
	}
	else {
		extendSelectionX = prevExtendSelectionX = 0.0f;
		extendSelectionY = prevExtendSelectionY = 0.0f;
		extendTileRowX = prevExtendTileRowX = 0;
		extendTileRowY = prevExtendTileRowY = 0;

		translateX = prevTranslateX = 0.0f;
		translateY = prevTranslateY = 0.0f;

		rotateZ = prevRotateZ = 0.0f;

		scaleX = prevScaleX = 1.0f;
		scaleY = prevScaleY = 1.0f;

	}

	//Edit Lighting
	bool aLightIsActive = activeSpotLightBtn || activeDirLightBtn || activePonctLightBtn;
	if (aLightIsActive) {
		if (prevActiveLightDiffuseColor != activeLightDiffuseColor) {
			sdCtrl.setActiveLightDiffuseColor(activeLightDiffuseColor);
			prevActiveLightDiffuseColor = activeLightDiffuseColor;
		}

		if (prevActiveLightSpecularColor != activeLightSpecularColor) {
			sdCtrl.setActiveLightSpecularColor(activeLightSpecularColor);
			prevActiveLightSpecularColor = activeLightSpecularColor;
		}

		if (prevActiveLightPosX != activeLightPosX) {
			sdCtrl.translateActiveLightPosX(activeLightPosX - prevActiveLightPosX);
			prevActiveLightPosX = activeLightPosX;
		}
		if (prevActiveLightPosY != activeLightPosY) {
			sdCtrl.translateActiveLightPosY(activeLightPosY - prevActiveLightPosY);
			prevActiveLightPosY = activeLightPosY;
		}
		if (prevActiveLightPosZ != activeLightPosZ) {
			sdCtrl.translateActiveLightPosZ(activeLightPosZ - prevActiveLightPosZ);
			prevActiveLightPosZ = activeLightPosZ;
		}
	}
	if (activeAmbientLightBtn) {
		if (prevActiveAmbientLightColor != activeAmbiantLightColor) {
			sdCtrl.setActiveAmbientLightColor(activeAmbiantLightColor);
			prevActiveAmbientLightColor = activeAmbiantLightColor;
		}
	}

	sdCtrl.communiquerBS(drawSurface, curve, point, direction, move);

	sdCtrl.setMetallic(slider_metallic);
	sdCtrl.setRoughness(slider_roughness);
	sdCtrl.setOcclusion(slider_occlusion);
	sdCtrl.setBrightness(slider_brightness);

}

void SlimeDungeonUI::updateBallTexture() {

	//Scale has change
	if (ballScaleTextureActive != ballScaleTextureBtn) {
		if (ballScaleTextureBtn) {
			ballScaleTextureActive = true;
			sdCtrl.setBallTextureFile(ballScaleTextureFile);
		}
		else {
			ballScaleTextureActive = false;
			sdCtrl.setBallTextureFile("");
		}
		ballSporeTextureActive = false;
		ballSporeTextureBtn = false;
		ballMoltenTextureActive = false;
		ballMoltenTextureBtn = false;
	}

	else if (ballSporeTextureActive != ballSporeTextureBtn) {
		if (ballSporeTextureBtn) {
			ballSporeTextureActive = true;
			sdCtrl.setBallTextureFile(ballSporeTextureFile);
		}
		else {
			ballSporeTextureActive = false;
			sdCtrl.setBallTextureFile("");
		}
		ballScaleTextureActive = false;
		ballScaleTextureBtn = false;
		ballMoltenTextureActive = false;
		ballMoltenTextureBtn = false;
	}
	else if (ballMoltenTextureActive != ballMoltenTextureBtn) {
		if (ballMoltenTextureBtn) {
			ballMoltenTextureActive = true;
			sdCtrl.setBallTextureFile(ballMoltenTextureFile);
		}
		else {
			ballMoltenTextureActive = false;
			sdCtrl.setBallTextureFile("");
		}
		ballScaleTextureActive = false;
		ballScaleTextureBtn = false;
		ballSporeTextureActive = false;
		ballSporeTextureBtn = false;
	}
}
	

//--------------------------------------------------------------
void SlimeDungeonUI::draw(){
	
	if (screenB) {
		mapTon.begin();
		mapTon.setUniformTexture("image", screen.getTexture(), 1);
	}
	light.enable();
    ofBackgroundGradient(backColor2, backColor1);

	sdCtrl.rendererDraw(shapeColor1, shapeColor2);
	//draw l<image importer par le boutton
	if (ifImageImport) {
		ofSetColor(ofColor::white);
		imageImport.draw(500, 300);
	}

	//si la mouse est over un des GUI, renvoir un bool au renderer NE MARCHE PAS ENCORE!
	guiPosition = gui.getPosition();
	gui2Position = scene.getPosition();
	if ((curMouse.x > guiPosition.x && curMouse.x < guiPosition.x + gui.getWidth() + 100 && curMouse.y > guiPosition.y && curMouse.y < guiPosition.y + gui.getHeight() + 100) || 
		(curMouse.x > gui2Position.x && curMouse.x < gui2Position.x + scene.getWidth() + 100 && curMouse.y > gui2Position.y && curMouse.y < gui2Position.y + scene.getHeight() + 100)) 
	{
		
		sdCtrl.setMouseOverGUI(true);
	}
	else {
		sdCtrl.setMouseOverGUI(false);
	}

	ofSetColor(0);
	ofDrawBitmapString("drag image files into this window", 10, ofGetHeight() - 20);
	
	if( !bHide ){
		gui.draw();
		scene.draw();
		bezSurface.draw();

		// Writing instructions
		for (unsigned int i = 0; i < instructions.size() ; i++) {
			ofDrawBitmapString(instructions[i], 10, gui.getHeight() + 30 + ( i * 12));
		}

		ofDrawBitmapString("- Pour afficher la surface \n"
						   "  de B�zier bicubique,\n"
						   "  appuyer sur \"Dessiner \n"
						   "  la surface\"\n"
						   "- Vous pouvez choisir la\n"
						   "  courbe a modiffier avec\n"
						   "  le slider \"Courbe\"\n"
						   "- Vous pouvez choisir le\n"
						   "  point de controle a\n"
						   "  modiffier avec le slider\n"
						   "  \"Point\"\n"
						   "- Pour deplacer un point de\n"
						   "  controle, vous devez choisir\n"
						   "  une direction avec le slider\n"
						   "  \"Direction\" et appuyer sur\n"
						   "  \"Bouger\"\n"
						   "- Directions:\n"
						   "   0 = x positifs\n"
						   "   1 = x negatifs\n"
						   "   2 = y positifs\n"
						   "   3 = y negatifs\n"
						   "   4 = z positifs\n"
						   "   5 = z negatifs",
			bezSurface.getPosition().x, bezSurface.getPosition().y + bezSurface.getHeight() + 12);
	}
	mapTon.end();
}

//--------------------------------------------------------------
void SlimeDungeonUI::keyPressed(int key){
	switch (key)
	{
	case 'h':
		bHide = !bHide;
		break;

	case 'a':
		sdCtrl.setCameraMoveLeft(true);
		break;
	case 'd':
		sdCtrl.setCameraMoveRight(true);
		break;
	case 'w': // touche w
		sdCtrl.setCameraMoveDown(true);
		break;

	case 's': // touche s
		sdCtrl.setCameraMoveUp(true);
		break;
	case 'x':
		gui.saveToFile("settings.xml");
		break;
	case 'l':
		gui.loadFromFile("settings.xml");
		break;

	case 101: // touche e
		sdCtrl.setCameraRollRight(true);
		break;
	case OF_KEY_LEFT_CONTROL:
		sdCtrl.setCameraDollyFront(true);
		break;
	case OF_KEY_LEFT_ALT:
		sdCtrl.setCameraDollyBack(true);
		break;

	//case 104: // touche h
	//	is_key_press_h = true;
	//	break;

	//case 105: // touche i
	//	is_key_press_i = true;
	//	break;

	//case 106: // touche j
	//	is_key_press_j = true;
	//	break;

	//case 107: // touche k
	//	is_key_press_k = true;
	//	break;

	case 113: // touche q
		sdCtrl.setCameraRollLeft(true);
		break;

	//case 117: // touche u
	//	is_key_press_u = true;
	//	break;



	//case 120: // touche x
	//	is_key_press_x = true;
	//	break;

	//case 121: // touche y
	//	is_key_press_y = true;
	//	break;

	//case 122: // touche z
	//	is_key_press_z = true;
	//	break;
	case OF_KEY_LEFT:
		sdCtrl.changeState(true);
		break;
	case OF_KEY_RIGHT:
		sdCtrl.changeState(false);
		break;
	case OF_KEY_TAB:
		sdCtrl.resetCam();
		break;
	case 't':
		sdCtrl.switchShaders();
		break;
	/*case 'm':
		screen.grabScreen(0, 0, ofGetWidth(), ofGetHeight());
		screenB = true;
		break;*/
	default:
		break;
	}

}

//--------------------------------------------------------------
void SlimeDungeonUI::keyReleased(int key){
	if (key == 'r') {
		if (recordMode) {
			exitRecordMode();
		}
		else {
			enterRecordMode();
		}
	}
	switch (key)
	{
	case 49:  // key 1
		currentShapeType = "pixel";
		sdCtrl.setDrawType(1);
		break;

	case 50:  // key 2
		currentShapeType = "line";
		sdCtrl.setDrawType(2);
		break;

	case 51:  // key 3
		currentShapeType = "rectangle";
		sdCtrl.setDrawType(3);
		break;

	case 52:  // key 4
		currentShapeType = "square";
		sdCtrl.setDrawType(4);
		break;

	case 53:  // key 5
		currentShapeType = "ellipse";
		sdCtrl.setDrawType(5);
		break;

	case 54:  // key 6
		currentShapeType = "circle";
		sdCtrl.setDrawType(6);
		break;

	case 55:  // key 7
		currentShapeType = "tiles";
		sdCtrl.setDrawType(7);
		break;
	case 56:  // key 8
		currentShapeType = "slime";
		sdCtrl.setDrawType(8);
		break;
	case 57:  // Key 9
		currentShapeType = "slime3d1";
		sdCtrl.setDrawType(9);
		break;
	case 48:  // Key 0
		currentShapeType = "slime3d2";
		sdCtrl.setDrawType(10);
		break;
	case '-':
		currentShapeType = "slime3d3";
		sdCtrl.setDrawType(11);
		break;
	case 'c':
		currentShapeType = "cube";
		sdCtrl.setDrawType(12);
		break;
	case 'b':
		currentShapeType = "ball";
		sdCtrl.setDrawType(13);
		break;

	case 101: // touche e
		sdCtrl.setCameraRollRight(false);
		break;

	case 113: // touche q
		sdCtrl.setCameraRollLeft(false);
		break;
	case 'a':
		sdCtrl.setCameraMoveLeft(false);
		break;
	case 'd':
		sdCtrl.setCameraMoveRight(false);
		break;
	case 's': // touche s
		sdCtrl.setCameraMoveUp(false);
		break;
	case 'w': // touche w
		sdCtrl.setCameraMoveDown(false);
		break;

	case OF_KEY_LEFT_CONTROL:
		sdCtrl.setCameraDollyFront(false);
		break;
	case OF_KEY_LEFT_ALT:
		sdCtrl.setCameraDollyBack(false);
		break;
	case 'p':
		catRomEditBtn = !catRomEditBtn;
		break;
	default:
		break;
	}

}

//--------------------------------------------------------------
void SlimeDungeonUI::mouseMoved(int x, int y ){
	sdCtrl.setCurMouse(ofPoint(x,y));
}

//--------------------------------------------------------------
void SlimeDungeonUI::mouseDragged(int x, int y, int button){
	positionImg.x = mouseX - distance.x;
	positionImg.y = mouseX - distance.y; 

	sdCtrl.setCurMouse(ofPoint(x,y));
}

// Appell� quand un bouton de la souris est enfonc�
void SlimeDungeonUI::mousePressed(int x, int y, int button){

	distance.x = mouseX - dragPt.x;
	distance.y = mouseY - dragPt.y;

	curMouse = ofPoint(x, y);
	mousePress = ofPoint(x, y);
	sdCtrl.setRendererIsMousePressed(true);
	sdCtrl.setCurMouse(curMouse);
	sdCtrl.setMousePress(mousePress);
}

//--------------------------------------------------------------
void SlimeDungeonUI::mouseReleased(int x, int y, int button){
	
	sdCtrl.setRendererIsMousePressed(false);
	curMouse = ofPoint(x, y);
	sdCtrl.setCurMouse(curMouse);
	if (isWaitingForScreenSelection) {
		screenshotPtUpperLeft = mousePress;
		screenshotPtDownRight = curMouse;
		float tmpX, tmpY;
		//Triage des points
		if (screenshotPtDownRight.x - screenshotPtUpperLeft.x > 0 && screenshotPtDownRight.y - screenshotPtUpperLeft.y < 0) {
			tmpY = screenshotPtUpperLeft.y;
			screenshotPtUpperLeft.y = screenshotPtDownRight.y;
			screenshotPtDownRight.y = tmpY;
		}
		else if (screenshotPtDownRight.x - screenshotPtUpperLeft.x < 0 && screenshotPtDownRight.y - screenshotPtUpperLeft.y >0) {
			tmpX = screenshotPtUpperLeft.x;
			screenshotPtUpperLeft.x = screenshotPtDownRight.x;
			screenshotPtDownRight.x = tmpX;
		}
		else if (screenshotPtDownRight.x - screenshotPtUpperLeft.x < 0 && screenshotPtDownRight.y - screenshotPtUpperLeft.y < 0) {
			tmpX = screenshotPtUpperLeft.x;
			tmpY = screenshotPtUpperLeft.y;
			screenshotPtUpperLeft = screenshotPtDownRight;
			screenshotPtDownRight.x = tmpX;
			screenshotPtDownRight.y = tmpY;
		}

		imgToExport.grabScreen(screenshotPtUpperLeft.x, screenshotPtUpperLeft.y, screenshotPtDownRight.x - screenshotPtUpperLeft.x, screenshotPtDownRight.y - screenshotPtUpperLeft.y);
		isWaitingForScreenSelection = false;
		sdCtrl.setPartialScreenBool(false);

		if (! recordMode) exportScreenshot();
	}
	else{
		if (drawMode) {
			sdCtrl.addShape();
		}
		else if (catRomEditBtn) {
			sdCtrl.addCatRomPt();
		}
		else {
			sdCtrl.checkClickInShape();
		}
	}
	
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
	scene.setPosition(w - scenePanelWidth, 0);
	sdCtrl.publishWindowResizedEvent(w, h);
}

//--------------------------------------------------------------
void SlimeDungeonUI::gotMessage(ofMessage msg){
	
}

//--------------------------------------------------------------
void SlimeDungeonUI::dragEvent(ofDragInfo info) {
	if (info.files.size() > 0) {
		dragPt = info.position;
		sdCtrl.addImage(ofImage(info.files.at(0)), dragPt);
	}
}

//--------------------------------------------------------------
	bool SlimeDungeonUI::hasImgExtension(ofFile file) {
		string fileExt = ofToLower(file.getExtension());
		return (fileExt == "png");//|| fileExt == "jpg");
	}


	void SlimeDungeonUI::enterRecordMode()
	{
		recordMode = true;
		recordModeEntryTime = ofGetSeconds();
		sdCtrl.publishEnterRecordModeEvent();
		cout << "Entering Record mode" << endl;

	}

	void SlimeDungeonUI::exitRecordMode()
	{
		cout << "Exiting Record mode" << endl;
		recordMode = false;
		sdCtrl.publishExitRecordModeEvent();
	}