#include "BezierSurface.h"

BezierSurface::BezierSurface()
{
	// Pour la texture
	ofLoadImage(tex, "texture/normalMap/planks_diff.jpg");
	ofLoadImage(normalMap, "texture/normalMap/planks_nm.jpg");
	texShader.load("noise_330_vs.glsl", "noise_330_fs.glsl");
	nmShade.load("nm_330_vs.glsl", "nm_330_fs.glsl");

	// Resolution de la courbe
	resolution = 32;

	// Initialisation des points de controle
	controlPointsInitialized();

	// Initialisation des listes
	for (int i = 0; i < (resolution+1) * (resolution+1); ++i) {
		curveMesh.addVertex(ofPoint());
	}

	// Initialisation des indexes du mesh
	for (int y = 0; y < resolution - 1; y++) {
		for (int x = 0; x < resolution - 1; x++) {
			curveMesh.addIndex(x + y * resolution);               // 0
			curveMesh.addIndex((x + 1) + y * resolution);           // 1
			curveMesh.addIndex(x + (y + 1)*resolution);           // 10

			curveMesh.addIndex((x + 1) + y * resolution);           // 1
			curveMesh.addIndex((x + 1) + (y + 1)*resolution);       // 11
			curveMesh.addIndex(x + (y + 1)*resolution);           // 10
		}
	}

	// Autres paramètres
	curveMesh.setMode(OF_PRIMITIVE_TRIANGLES);
	curveMesh.enableTextures();
	curveMesh.enableColors();

	selectedCurve = selectedPoint = 0;
}

void BezierSurface::draw()
{
	// Parametres OpenGL
	ofDisableArbTex();
	ofDisableAlphaBlending();
	ofEnableDepthTest();

	ofSetColor(ofColor::red);
	for (int i = 0; i < 4; ++i) {
		for (int j = 0; j < 4; ++j) {

			if (i != selectedCurve || j != selectedPoint) {
				texShader.begin();
				texShader.setUniform1f("u_time", ofGetElapsedTimef() / 10);
				ofDrawSphere(ctrPoints[i][j], 3);
				texShader.end();
			}
			else ofDrawSphere(ctrPoints[i][j], 3);
		}
	}



	ofSetColor(ofColor::white);
	evalBezierSurface();
	tex.generateMipmap();

	// Dessin de la courbe
	nmShade.begin();
	nmShade.setUniformTexture("brick", tex, 0);
	nmShade.setUniformTexture("nmTex", normalMap, 1);
	nmShade.setUniform3f("color_ambient", ambient/255.0f);
	cout << ambient.x << endl << ambient.y << endl << ambient.z << endl << endl;
	nmShade.setUniform3f("color_diffuse", diffuse / 255.0f);
	nmShade.setUniform3f("color_specular", specular / 255.0f);
	nmShade.setUniform1f("brightness", 15.0f);
	nmShade.setUniform3f("light_position", glm::vec4(position, 0.0f) * cmvm);

	//ofDrawSphere(250);
	curveMesh.draw();

	nmShade.end();

	ofEnableArbTex();
	ofEnableAlphaBlending();
	ofEnableDepthTest();

}

void BezierSurface::evalBezierSurface()
{
	int k = 0;
	for (int a = 0; a < resolution; ++a) {
		for (int b = 0; b < resolution; ++b) {
			u = a / (float)resolution;
			v = b / (float)resolution;

			allPoints[k] = ofPoint(0, 0, 0);
			for (int i = 0; i <= 3; ++i) {
				for (int j = 0; j <= 3; ++j) {
					allPoints[k] += bernstein(3, j, v) * bernstein(3, i, u) * ctrPoints[j][i];
				}
			}
			curveMesh.setVertex(k, allPoints[k]);
			curveMesh.addTexCoord(glm::vec2(u, v));
			k++;
		}
	}
}

float BezierSurface::bernstein(int n, int k, float t)
{
	return (factorial(n) / (factorial(k)*factorial(n - k)))*pow(t, k)*pow(1 - t, n - k);
}

void BezierSurface::controlPointsInitialized()
{
	ctrPoints[0][0] = ofPoint(0, 0, 0);
	ctrPoints[0][1] = ofPoint(0, 100, 0);
	ctrPoints[0][2] = ofPoint(100, 100, 0);
	ctrPoints[0][3] = ofPoint(100, 0, 0);
	ctrPoints[1][0] = ofPoint(0, 0, 100);
	ctrPoints[1][1] = ofPoint(0, 100, 100);
	ctrPoints[1][2] = ofPoint(100, 100, 100);
	ctrPoints[1][3] = ofPoint(100, 0, 100);
	ctrPoints[2][0] = ofPoint(0, 0, 200);
	ctrPoints[2][1] = ofPoint(0, 100, 200);
	ctrPoints[2][2] = ofPoint(100, 100, 200);
	ctrPoints[2][3] = ofPoint(100, 0, 200);
	ctrPoints[3][0] = ofPoint(0, 0, 300);
	ctrPoints[3][1] = ofPoint(0, 100, 300);
	ctrPoints[3][2] = ofPoint(100, 100, 300);
	ctrPoints[3][3] = ofPoint(100, 0, 300);
}
