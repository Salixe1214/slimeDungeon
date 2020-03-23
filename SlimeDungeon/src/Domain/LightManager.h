#pragma once

#include "ofMain.h"

//Singleton
class LightManager
{
public:
	static LightManager* getLightManager();
	static LightManager* lightManager;

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
	void addSpotLight(glm::vec3 pos, glm::vec3 orientation, float spotCutoff = 30, float spotConcentration = 2,
		ofColor diffuseColor = ofColor(191, 191, 191), ofColor specularColor = ofColor(191, 191, 191));

	void configureDirectionalLight(string dirId, glm::vec3 pos, glm::vec3 orientation, ofColor diffuseColor = ofColor(31, 255, 31),
							ofColor specularColor = ofColor(191, 191, 191));
	void configurePonctualLight(string ponctId, glm::vec3 pos, ofColor diffuseCol = ofColor(191, 191, 191),
								ofColor specularColor = ofColor(191, 191, 191));
	void configureSpotLight(string spotId, glm::vec3 pos, glm::vec3 orientation, float spotCutoff = 30, float spotConcentration = 2,
							ofColor diffuseColor= ofColor(191, 191, 191), ofColor specularColor = ofColor(191, 191, 191));

	void setup(glm::vec3 camInitialPos = glm::vec3(ofGetWidth() / 2, ofGetHeight() / 2, 1000));
	void update();
	void draw();

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

