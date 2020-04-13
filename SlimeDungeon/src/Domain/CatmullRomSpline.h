#pragma once

#include "ofMain.h"
#include <string>


class CatmullRomSpline
{
public:
	CatmullRomSpline(float p_alpha = 0.5);
	CatmullRomSpline(std::vector<ofPoint> p_ctrlPts, float p_alpha = 0.5);
	~CatmullRomSpline();

	string getId();
	std::vector <ofPoint> getControlPoints();

	void addPoint(float x, float y, float z = 0);
	void addPoint(ofPoint newPoint);

	void removePoint(int index);
	void changePoint(int index, float x, float y, float z = 0);
	void changePoint(int index, ofPoint newPoint);
	void setAlpha(float newAlpha);
	void draw();

private:
	string catRomId;
	std::vector<ofPoint> ctrlPts;
	int nbApproxPt;
	//alpha = 0.5 -> centripetal catmull-rom
	//alpha = 1 -> chordal catmull-rom
	//alpha = 0 -> uniform catmull-rom
	float alpha;
	float ptRadius;
	ofColor edgeCtrlPtColor;
	ofColor ctrlPtColor;
	ofColor lineColor;
	float lineWidth;
	std::vector<ofPoint> CRPoints;

	void updateSpline();
	void setDefaultSplineParameter();
	float getT(float t, ofPoint p0, ofPoint p1);
};

