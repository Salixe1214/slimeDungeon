#pragma once
#include "ofMain.h"
#include <vector>


class BezierSurface
{
public:
	BezierSurface();
	void draw();
	void evalBezierSurface();
	float bernstein(int n, int k, float t);
	void controlPointsInitialized();

	// Parametres
	int selectedPoint;
	int selectedCurve;
	float u; //> Position on curve (from 0 to 1)
	float v; //> Position on curve (from 0 to 1)
	int resolution;

	// Points
	ofPoint ctrPoints[4][4];
	ofPoint curPoint;
	ofPoint allPoints[100*100];

	ofPolyline lr1;
	ofPolyline lr2;
	ofPolyline lr3;
	ofPolyline lr4;

	// Affichage
	ofMesh curveMesh;
	ofPixels pix;
	ofTexture tex;
	ofShader shader;

	int factorial(int n) {
		if (n > 1) return n*factorial(n - 1);
		else return 1;
	}
};

