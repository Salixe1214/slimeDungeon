#include "LightManager.h"

LightManager *LightManager::lightManager = nullptr;
int LightManager::idDirLight = 1;
int LightManager::idPonctLight = 1;
int LightManager::idSpotLight = 1;

LightManager::LightManager() {
}


LightManager::~LightManager(){
	dirLightVec.clear();
	ponctLightVec.clear();
	spotLightVec.clear();
}


LightManager * LightManager::getLightManager() {
	
	if (!lightManager) {
		lightManager = new LightManager();
	}
	return lightManager;
}


void LightManager::setup(glm::vec3 camInitialPos, glm::vec3 initialOrientation)
{
	glm::vec3 lightPos = camInitialPos;
	setAmbientColorLight(ofColor(127, 127, 127));
	lightPos.z -= 500;
	lightPos.x += ofGetWidth() / 7;
	lightPos.y += ofGetHeight() / 5;
	addDirectionalLight(lightPos, initialOrientation);

	lightPos = camInitialPos;
	lightPos.z -= 500;
	addPonctualLight(lightPos);

	lightPos = camInitialPos;
	lightPos.z = camInitialPos.z * 0.1;
	lightPos.y -= ofGetHeight() /5;
	addSpotLight(lightPos, initialOrientation, 500, 0.1);
	
	isAmbientLightActive = true;
	isDirLightActive = true;
	isPonctLightActive = true;
	isSpotLightActive = true;
	
	drawLightGizmo = true;
}

void LightManager::update()
{
}

void LightManager::draw()
{
	if (drawLightGizmo) {
		ofPushMatrix();
		if (isDirLightActive)
			for (auto light : dirLightVec) light.dirLight.draw();
		if (isPonctLightActive)
			for (auto light : ponctLightVec) light.ponctLight.draw();
		if (isSpotLightActive)
			for (auto light : spotLightVec) {
				//cout << "Drawing spot " << light.spotlight.getPosition().x << endl;
				light.spotlight.draw();
			}
		ofPopMatrix();
	}

}

void LightManager::lightOn()
{
	ofEnableLighting();
	if (isAmbientLightActive)	
		ofSetGlobalAmbientColor(ambientColorLight);
	if (isDirLightActive)	
		for (auto light : dirLightVec) light.dirLight.enable();
	if (isPonctLightActive)
		for (auto light : ponctLightVec) light.ponctLight.enable();
	if (isSpotLightActive)
		for (auto light : spotLightVec) light.spotlight.enable();
}

void LightManager::ambientLightOn()
{
	ofSetGlobalAmbientColor(ambientColorLight);
}

void LightManager::selectedLightOn(string idLight)
{
	ofEnableLighting();
	for (auto light : dirLightVec) {
		if (light.idDirL == idLight) {
			light.dirLight.enable();
			return;
		}
	}
	for (auto light : ponctLightVec) {
		if (light.idPonctL == idLight) {
			light.ponctLight.enable();
			return;
		}
	}
	for (auto light : spotLightVec) {
		if (light.idSpotL == idLight) {
			light.spotlight.enable();
			return;
		}
	}
	cout << "La lumière " << idLight << " est introuvable" << endl;
}

void LightManager::lightOff()
{
	ofSetGlobalAmbientColor(ofColor(0, 0, 0));
	for (auto light : dirLightVec) light.dirLight.disable();
	for (auto light : ponctLightVec) light.ponctLight.disable();
	for (auto light : spotLightVec) light.spotlight.disable();
	ofDisableLighting();
}

void LightManager::ambientLightOff()
{
	ofSetGlobalAmbientColor(ofColor(0, 0, 0));
}

void LightManager::selectedLightOff(string idLight)
{
	for (auto light : dirLightVec) {
		if (light.idDirL == idLight) {
			light.dirLight.disable();
			return;
		}
	}
	for (auto light : ponctLightVec) {
		if (light.idPonctL == idLight) {
			light.ponctLight.disable();
			return;
		}
	}
	for (auto light : spotLightVec) {
		if (light.idSpotL == idLight) {
			light.spotlight.disable();
			return;
		}
	}
	cout << "La lumière " << idLight << " est introuvable" << endl;
}


void LightManager::setAmbientColorLight(ofColor ambiantColor)
{
	ambientColorLight = ambiantColor;
}

void LightManager::addDirectionalLight(glm::vec3 pos, glm::vec3 orientation, ofColor diffuseColor,
										ofColor specularColor)
{
	ofLight light;
	light.setDiffuseColor(diffuseColor);
	light.setSpecularColor(specularColor);
	light.setOrientation(orientation);
	light.setPosition(pos);
	light.setDirectional();
	//light.lookAt(orientation);
	string idDir = "dir" + std::to_string(idDirLight);
	dirLightVec.push_back(directionalLight(idDir, light));
	idDirLight++;
}

void LightManager::addPonctualLight(glm::vec3 pos, ofColor diffuseColor, ofColor specularColor)
{
	ofLight light;
	light.setDiffuseColor(diffuseColor);
	light.setSpecularColor(specularColor);
	light.setPosition(pos);
	light.setPointLight();
	string idPonct = "ponct" + std::to_string(idPonctLight);
	ponctLightVec.push_back(ponctualLight(idPonct, light));
	idPonctLight++;
}

void LightManager::addSpotLight(glm::vec3 pos, glm::vec3 lookAt, float spotCutoff, 
								float spotConcentration, ofColor diffuseColor, ofColor specularColor)
{
	ofLight light;
	light.setDiffuseColor(diffuseColor);
	light.setSpecularColor(specularColor);
	//light.setOrientation(orientation);
	light.setPosition(pos);
	light.setSpotlight(spotCutoff, spotConcentration);
	light.lookAt(lookAt);
	string idSpot = "spot" + std::to_string(idSpotLight);
	spotLightVec.push_back(spotLight(idSpot, light));
	idSpotLight++;
}

void LightManager::configureDirectionalLight(string dirId, glm::vec3 pos, glm::vec3 orientation, ofColor diffuseColor, ofColor specularColor)
{
	for (unsigned int i = 0; i < dirLightVec.size(); i++) {
		if (dirLightVec.at(i).idDirL == dirId) {
			dirLightVec.at(i).dirLight.setDiffuseColor(diffuseColor);
			dirLightVec.at(i).dirLight.setSpecularColor(specularColor);
			dirLightVec.at(i).dirLight.setOrientation(orientation);
			dirLightVec.at(i).dirLight.setPosition(pos);
			return;
		}
	}
	cout << "La dirLight " << dirId << " est inexistant" << endl;
}

void LightManager::configurePonctualLight(string ponctId, glm::vec3 pos, ofColor diffuseColor, ofColor specularColor)
{
	for (unsigned int i = 0; i < ponctLightVec.size(); i++) {
		if (ponctLightVec.at(i).idPonctL == ponctId) {
			ponctLightVec.at(i).ponctLight.setDiffuseColor(diffuseColor);
			ponctLightVec.at(i).ponctLight.setSpecularColor(specularColor);
			ponctLightVec.at(i).ponctLight.setPosition(pos);
			return;
		}
	}
	cout << "La ponctLight " << ponctId << " est inexistante" << endl;
}

void LightManager::configureSpotLight(string spotId, glm::vec3 pos, glm::vec3 orientation, float spotCutoff,
										float spotConcentration, ofColor diffuseColor, ofColor specularColor)
{
	for (unsigned int i = 0; i < spotLightVec.size(); i++) {
		if (spotLightVec.at(i).idSpotL == spotId) {
			spotLightVec.at(i).spotlight.setDiffuseColor(diffuseColor);
			spotLightVec.at(i).spotlight.setSpecularColor(specularColor);
			spotLightVec.at(i).spotlight.setOrientation(orientation);
			spotLightVec.at(i).spotlight.setSpotConcentration(spotConcentration);
			spotLightVec.at(i).spotlight.setSpotlightCutOff(spotCutoff);
			spotLightVec.at(i).spotlight.setPosition(pos);
			return;
		}
	}
	cout << "Le spotlight " << spotId <<  " est inexistant" << endl;
}

void LightManager::setDrawLightGizmo(bool p_drawLightGizmo)
{
	drawLightGizmo = p_drawLightGizmo;
}

void LightManager::setAmbientLightActive(bool p_isAmbientLightActive)
{
	isAmbientLightActive = p_isAmbientLightActive;
}

void LightManager::setDirLightActive(bool p_isDirLightActive)
{
	isDirLightActive = p_isDirLightActive;
}

void LightManager::setPonctLightActive(bool p_isPonctLightActive)
{
	isPonctLightActive = p_isPonctLightActive;
}

void LightManager::setSpotLightActive(bool p_isSpotLightActive)
{
	isSpotLightActive = p_isSpotLightActive;
}

void LightManager::setActiveLightDiffuseColor(ofColor diffuseColor)
{
	if (isPonctLightActive) {
		for (auto light : ponctLightVec) {
				light.ponctLight.setDiffuseColor(diffuseColor);
		}
	}
	if (isDirLightActive) {
		for (auto light : dirLightVec) {
				light.dirLight.setDiffuseColor(diffuseColor);
		}
	}

	if (isSpotLightActive) {
		for (auto light : spotLightVec) {
				light.spotlight.setDiffuseColor(diffuseColor);
		}
	}
}

void LightManager::setActiveLightSpecularColor(ofColor specularColor)
{
	if (isPonctLightActive) {
		for (auto light : ponctLightVec) {
			light.ponctLight.setSpecularColor(specularColor);
		}
	}
	if (isDirLightActive) {
		for (auto light : dirLightVec) {
			light.dirLight.setSpecularColor(specularColor);
		}
	}

	if (isSpotLightActive) {
		for (auto light : spotLightVec) {
			light.spotlight.setSpecularColor(specularColor);
		}
	}
}

void LightManager::translateActiveLightPosX(float dx)
{
	ofPushMatrix();
	ofLight ligh;
	glm::vec3 pos;
	if (isPonctLightActive) {
		for (auto light : ponctLightVec) {
			pos = light.ponctLight.getPosition();
			pos.x += dx;
			ligh.setPosition(pos);
			ligh.setDiffuseColor(light.ponctLight.getDiffuseColor());
			ligh.setSpecularColor(light.ponctLight.getSpecularColor());
			//light.dirLight.setPosition(pos);
		}
		ponctLightVec.clear();
		addPonctualLight(ligh.getPosition(),ligh.getDiffuseColor(), ligh.getSpecularColor());
	}
	if (isDirLightActive) {
		for (auto light : dirLightVec) {
			pos = light.dirLight.getPosition();
			pos.x += dx;
			ligh.setPosition(pos);
			ligh.setOrientation(light.dirLight.getOrientationEulerDeg());
			ligh.setDiffuseColor(light.dirLight.getDiffuseColor());
			ligh.setSpecularColor(light.dirLight.getSpecularColor());
			//light.dirLight.setPosition(pos);
		}
		dirLightVec.clear();
		addDirectionalLight(ligh.getPosition(), { 0,0,0 }, ligh.getDiffuseColor(), ligh.getSpecularColor());
	}
	
	if (isSpotLightActive) {
		for (auto light : spotLightVec) {
			/*cout << "reached here dx " << dx << endl;*/
			pos = light.spotlight.getPosition();
			pos.x += dx;
			ligh.setPosition(pos);

			ligh.setOrientation(light.spotlight.getOrientationEulerDeg());
			ligh.setDiffuseColor(light.spotlight.getDiffuseColor());
			ligh.setSpecularColor(light.spotlight.getSpecularColor());
			ligh.setSpotlight(light.spotlight.getSpotlightCutOff(), light.spotlight.getSpotConcentration());
			//cout << "posx before " << light.spotlight.getPosition().x << endl;
			//light.spotlight.setPosition(pos);
			//light.setSpot(ligh);
			//light.spotlight = ligh;
			//light.spotlight.setGlobalPosition(pos);
			//cout << "posx after " << light.spotlight.getPosition().x << endl;
		}
		//TODO this is ugly. Pourquoi je ne peux pas changer la position??
		spotLightVec.clear();
		addSpotLight(ligh.getPosition(), { 0,0,0 }, ligh.getSpotlightCutOff(), ligh.getSpotConcentration(),
			ligh.getDiffuseColor(), ligh.getSpecularColor());
		
	}
	ofPopMatrix();
}
void LightManager::translateActiveLightPosY(float dy)
{
	ofPushMatrix();
	ofLight ligh;
	glm::vec3 pos;
	if (isPonctLightActive) {
		for (auto light : ponctLightVec) {
			pos = light.ponctLight.getPosition();
			pos.y += dy;
			ligh.setPosition(pos);
			ligh.setDiffuseColor(light.ponctLight.getDiffuseColor());
			ligh.setSpecularColor(light.ponctLight.getSpecularColor());
			//light.dirLight.setPosition(pos);
		}
		ponctLightVec.clear();
		addPonctualLight(ligh.getPosition(), ligh.getDiffuseColor(), ligh.getSpecularColor());
	}
	if (isDirLightActive) {
		for (auto light : dirLightVec) {
			pos = light.dirLight.getPosition();
			pos.y += dy;
			ligh.setPosition(pos);
			ligh.setOrientation(light.dirLight.getOrientationEuler());
			ligh.setDiffuseColor(light.dirLight.getDiffuseColor());
			ligh.setSpecularColor(light.dirLight.getSpecularColor());
			//light.dirLight.setPosition(pos);
		}
		dirLightVec.clear();
		addDirectionalLight(ligh.getPosition(), { 0,0,0 }, ligh.getDiffuseColor(), ligh.getSpecularColor());
	}

	if (isSpotLightActive) {
		for (auto light : spotLightVec) {
			/*cout << "reached here dx " << dx << endl;*/
			pos = light.spotlight.getPosition();
			pos.y += dy;
			ligh.setPosition(pos);

			ligh.setOrientation(light.spotlight.getOrientationEuler());
			ligh.setDiffuseColor(light.spotlight.getDiffuseColor());
			ligh.setSpecularColor(light.spotlight.getSpecularColor());
			ligh.setSpotlight(light.spotlight.getSpotlightCutOff(), light.spotlight.getSpotConcentration());
			//cout << "posx before " << light.spotlight.getPosition().x << endl;
			//light.spotlight.setPosition(pos);
			//light.setSpot(ligh);
			//light.spotlight = ligh;
			//light.spotlight.setGlobalPosition(pos);
			//cout << "posx after " << light.spotlight.getPosition().x << endl;
		}
		//TODO this is ugly. Pourquoi je ne peux pas changer la position??
		spotLightVec.clear();
		addSpotLight(ligh.getPosition(), { 0,0,0 }, ligh.getSpotlightCutOff(), ligh.getSpotConcentration(),
			ligh.getDiffuseColor(), ligh.getSpecularColor());

	}
	ofPopMatrix();
}
void LightManager::translateActiveLightPosZ(float dz)
{
	ofPushMatrix();
	ofLight ligh;
	glm::vec3 pos;
	if (isPonctLightActive) {
		for (auto light : ponctLightVec) {
			pos = light.ponctLight.getPosition();
			pos.z += dz;
			ligh.setPosition(pos);
			ligh.setDiffuseColor(light.ponctLight.getDiffuseColor());
			ligh.setSpecularColor(light.ponctLight.getSpecularColor());
			//light.dirLight.setPosition(pos);
		}
		ponctLightVec.clear();
		addPonctualLight(ligh.getPosition(), ligh.getDiffuseColor(), ligh.getSpecularColor());
	}
	if (isDirLightActive) {
		for (auto light : dirLightVec) {
			pos = light.dirLight.getPosition();
			pos.z += dz;
			ligh.setPosition(pos);
			ligh.setOrientation(light.dirLight.getOrientationEuler());
			ligh.setDiffuseColor(light.dirLight.getDiffuseColor());
			ligh.setSpecularColor(light.dirLight.getSpecularColor());
			//light.dirLight.setPosition(pos);
		}
		dirLightVec.clear();
		addDirectionalLight(ligh.getPosition(), { 0,0,0 }, ligh.getDiffuseColor(), ligh.getSpecularColor());
	}

	if (isSpotLightActive) {
		for (auto light : spotLightVec) {
			/*cout << "reached here dx " << dx << endl;*/
			pos = light.spotlight.getPosition();
			pos.z += dz;
			ligh.setPosition(pos);

			ligh.setOrientation(light.spotlight.getOrientationEulerDeg());
			ligh.setDiffuseColor(light.spotlight.getDiffuseColor());
			ligh.setSpecularColor(light.spotlight.getSpecularColor());
			ligh.setSpotlight(light.spotlight.getSpotlightCutOff(), light.spotlight.getSpotConcentration());
			//cout << "posx before " << light.spotlight.getPosition().x << endl;
			//light.spotlight.setPosition(pos);
			//light.setSpot(ligh);
			//light.spotlight = ligh;
			//light.spotlight.setGlobalPosition(pos);
			//cout << "posx after " << light.spotlight.getPosition().x << endl;
		}
		//TODO this is ugly. Pourquoi je ne peux pas changer la position??
		spotLightVec.clear();
		addSpotLight(ligh.getPosition(), { 0,0,0 }, ligh.getSpotlightCutOff(), ligh.getSpotConcentration(),
			ligh.getDiffuseColor(), ligh.getSpecularColor());

	}
	ofPopMatrix();
}

glm::vec3 LightManager::getAmbiant() const
{
	glm::vec3 ambientC = glm::vec3(ambientColorLight.r, ambientColorLight.g, ambientColorLight.b);
	return ambientC;
}

glm::vec3 LightManager::getDiffuse() const
{
	ofColor color = ofColor(1.0);
	if (isPonctLightActive) {
		for (auto light : ponctLightVec) {
			color += light.ponctLight.getDiffuseColor();
		}
		color /= ponctLightVec.size();
	}
	if (isDirLightActive) {
		for (auto light : dirLightVec) {
			color += light.dirLight.getDiffuseColor();
		}
		color /= dirLightVec.size();
	}

	if (isSpotLightActive) {
		for (auto light : spotLightVec) {
			color += light.spotlight.getDiffuseColor();
		}
		color /= spotLightVec.size();
	}
	glm::vec3 diffuseC = glm::vec3(color.r, color.g, color.b);
	return diffuseC;
}

glm::vec3 LightManager::getSpecular() const
{
	ofColor color = ofColor(1.0);
	if (isPonctLightActive) {
		for (auto light : ponctLightVec) {
			color += light.ponctLight.getSpecularColor();
		}
		color /= ponctLightVec.size();
	}
	if (isDirLightActive) {
		for (auto light : dirLightVec) {
			color += light.dirLight.getSpecularColor();
		}
		color /= dirLightVec.size();
	}

	if (isSpotLightActive) {
		for (auto light : spotLightVec) {
			color += light.spotlight.getSpecularColor();
		}
		color /= spotLightVec.size();
	}
	glm::vec3 diffuseC = glm::vec3(color.r, color.g, color.b);
	return diffuseC;
}

glm::vec3 LightManager::getPosition() const
{
	glm::vec3 position = glm::vec3(0.0);
	if (isPonctLightActive) {
		for (auto light : ponctLightVec) {
			position += light.ponctLight.getGlobalPosition();
		}
		position /= ponctLightVec.size();
	}
	if (isDirLightActive) {
		for (auto light : dirLightVec) {
			position += light.dirLight.getGlobalPosition();
		}
		position /= dirLightVec.size();
	}

	if (isSpotLightActive) {
		for (auto light : spotLightVec) {
			position += light.spotlight.getGlobalPosition();
		}
		position /= spotLightVec.size();
	}
	position = (glm::vec4(position, 0.0f)* ofGetCurrentMatrix(OF_MATRIX_MODELVIEW));
	return position;
}

/*float LightManager::getBright() const
{
	return 32.0f;
}*/
