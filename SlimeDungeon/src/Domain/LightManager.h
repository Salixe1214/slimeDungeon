#pragma once

#include "ofMain.h"

//Singleton
class LightManager
{
public:
	static LightManager* getLightManager();
	static LightManager* lightManager;
	bool isAmbientLightActive, isDirLightActive, isPonctLightActive, isSpotLightActive;
	bool drawLightGizmo;

	void setup(glm::vec3 camInitialPos = glm::vec3(ofGetWidth() / 2, ofGetHeight() / 2, 1000),
				glm::vec3 initialOrientation = glm::vec3(0, 0, 0));
	void update();
	void draw();

	void lightOn();
	void ambientLightOn();
	void selectedLightOn(string idLight);
	void lightOff();
	void ambientLightOff();
	void selectedLightOff(string idLight);

	void setAmbientColorLight(ofColor ambiantColor);

	void addDirectionalLight(glm::vec3 pos, glm::vec3 orientation, ofColor diffuseColor = ofColor(31,255,31), 
							ofColor specularColor = ofColor(191, 191, 191));
	void addPonctualLight(glm::vec3 pos, ofColor diffuseColor = ofColor(255, 255, 255), 
							ofColor specularColor = ofColor(191, 191, 191));
	void addSpotLight(glm::vec3 pos, glm::vec3 lookAt, float spotCutoff = 500, float spotConcentration = 0.1,
		ofColor diffuseColor = ofColor(191, 191, 191), ofColor specularColor = ofColor(191, 191, 191));

	void configureDirectionalLight(string dirId, glm::vec3 pos, glm::vec3 orientation, ofColor diffuseColor = ofColor(31, 255, 31),
							ofColor specularColor = ofColor(191, 191, 191));
	void configurePonctualLight(string ponctId, glm::vec3 pos, ofColor diffuseCol = ofColor(191, 191, 191),
								ofColor specularColor = ofColor(191, 191, 191));
	void configureSpotLight(string spotId, glm::vec3 pos, glm::vec3 orientation, float spotCutoff = 250, float spotConcentration = 1,
							ofColor diffuseColor= ofColor(191, 191, 191), ofColor specularColor = ofColor(191, 191, 191));

	void setDrawLightGizmo(bool p_drawLightGizmo);
	void setAmbientLightActive(bool p_isAmbientLightActive);
	void setDirLightActive(bool p_isDirLightActive);
	void setPonctLightActive(bool p_isPonctLightActive);
	void setSpotLightActive(bool p_isSpotLightActive);

	//editLights
	void setActiveLightDiffuseColor(ofColor diffuseColor);
	void setActiveLightSpecularColor(ofColor specularColor);
	void translateActiveLightPosX(float dx);
	void translateActiveLightPosY(float dy);
	void translateActiveLightPosZ(float dz);

	// getter
	glm::vec3 getAmbiant() const;
	glm::vec3 getDiffuse() const;
	glm::vec3 getSpecular() const;
	glm::vec3 getPosition() const;
	//float getBright() const;


	LightManager(const LightManager&) = delete;
	LightManager& operator=(const LightManager&) = delete;

private:
	LightManager();
	~LightManager();

	ofColor ambientColorLight;
	static int idDirLight;
	struct directionalLight {
		ofLight dirLight;
		string idDirL;
		directionalLight(string p_idDirLight, ofLight p_dirLight) {
			idDirL = p_idDirLight;
			dirLight = p_dirLight;
		}
	};
	std::vector<directionalLight> dirLightVec;

	static int idPonctLight;
	struct ponctualLight {
		ofLight ponctLight;
		string idPonctL;
		ponctualLight(string p_idPonctualLight, ofLight p_ponctualLight) {
			idPonctL = p_idPonctualLight;
			ponctLight = p_ponctualLight;
		}
	};
	std::vector<ponctualLight> ponctLightVec;

	static int idSpotLight;
	struct spotLight {
		ofLight spotlight;
		string idSpotL;
		spotLight(string p_idSpotLight, ofLight p_spotLight) {
			idSpotL = p_idSpotLight;
			spotlight = p_spotLight;
		}
	};
	std::vector<spotLight> spotLightVec;
};

