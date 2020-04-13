#include "CatmullRomSpline.h"
#include <math.h>


CatmullRomSpline::CatmullRomSpline(float p_alpha):
	alpha(p_alpha)
{
	static int idCRSpline;
	idCRSpline++;
	catRomId = "catmullRom" + std::to_string(idCRSpline);
	ctrlPts = std::vector<ofPoint>{};
	CRPoints.clear();
	setDefaultSplineParameter();
}

CatmullRomSpline::CatmullRomSpline(std::vector<ofPoint> p_ctrlPts, float p_alpha)
	:CatmullRomSpline(alpha)
{
	ctrlPts = p_ctrlPts;
	updateSpline();
}

CatmullRomSpline::~CatmullRomSpline() {
	ctrlPts.clear();
}

string CatmullRomSpline::getId()
{
	return catRomId;
}

std::vector<ofPoint> CatmullRomSpline::getControlPoints()
{
	return ctrlPts;
}

void CatmullRomSpline::addPoint(float x, float y, float z)
{
	addPoint(ofPoint(x, y, z));
	updateSpline();
}

void CatmullRomSpline::addPoint(ofPoint newPoint)
{
	ctrlPts.push_back(newPoint);
	updateSpline();
}

void CatmullRomSpline::removePoint(int index)
{
	ctrlPts.erase(ctrlPts.begin() + index);
	updateSpline();
}

void CatmullRomSpline::changePoint(int index, float x, float y, float z)
{
	changePoint(index, ofPoint(x, y, z));
	updateSpline();
}

void CatmullRomSpline::changePoint(int index, ofPoint newPoint)
{
	ctrlPts.at(index) = newPoint;
	updateSpline();
}

void CatmullRomSpline::setAlpha(float newAlpha)
{
	alpha = newAlpha;
}


void CatmullRomSpline::draw()
{
	if (ctrlPts.size() > 0) {
		ofFill();
		ofSetLineWidth(0);
		//edgeControlPoint
		ofSetColor(edgeCtrlPtColor);
		ofDrawCircle(ctrlPts.at(0).x, ctrlPts.at(0).y, ctrlPts.at(0).z, ptRadius);
		ofDrawCircle(ctrlPts.back().x, ctrlPts.back().y, ctrlPts.back().z, ptRadius);

		//CtrlPoint
		ofSetColor(ctrlPtColor);
		for (unsigned int i = 1; i < ctrlPts.size() - 1; i++) {
			ofDrawCircle(ctrlPts.at(i).x, ctrlPts.at(i).y, ctrlPts.at(i).z, ptRadius);
		}

		if (ctrlPts.size() > 3 && CRPoints.size() > 3) {
			//Spline
			ofNoFill();
			ofSetColor(lineColor);
			ofSetLineWidth(lineWidth);
			for (unsigned int i = 0; i < CRPoints.size() - 1; i++) {
				ofDrawLine(CRPoints.at(i).x, CRPoints.at(i).y,
					CRPoints.at(i + 1).x, CRPoints.at(i + 1).y);
			}
		}
	}
}

//Algorithme tiré de : https://en.wikipedia.org/wiki/Centripetal_Catmull%E2%80%93Rom_spline
void CatmullRomSpline::updateSpline()
{
	if (ctrlPts.size() > 3) {
		CRPoints.clear();
		for (unsigned int j = 0; j < ctrlPts.size() - 3; j++) {
			ofPoint p0 = ctrlPts.at(j);
			ofPoint p1 = ctrlPts.at(j + 1);
			ofPoint p2 = ctrlPts.at(j + 2);
			ofPoint p3 = ctrlPts.at(j + 3);

			float t0 = 0.0f;
			float t1 = getT(t0, p0, p1);
			float t2 = getT(t1, p1, p2);
			float t3 = getT(t2, p2, p3);
			//for (float t = t1; t < t2; t += ((t2 - t1) / (float)ctrlPts.size()))
			for (float t = t1; t < t2; t += ((t2 - t1) / (float)nbApproxPt))
			{
				ofPoint A1 = (t1 - t) / (t1 - t0)*p0 + (t - t0) / (t1 - t0)*p1;
				ofPoint A2 = (t2 - t) / (t2 - t1)*p1 + (t - t1) / (t2 - t1)*p2;
				ofPoint A3 = (t3 - t) / (t3 - t2)*p2 + (t - t2) / (t3 - t2)*p3;

				ofPoint B1 = (t2 - t) / (t2 - t0)*A1 + (t - t0) / (t2 - t0)*A2;
				ofPoint B2 = (t3 - t) / (t3 - t1)*A2 + (t - t1) / (t3 - t1)*A3;

				ofPoint C = (t2 - t) / (t2 - t1)*B1 + (t - t1) / (t2 - t1)*B2;

				CRPoints.push_back(C);
			}
		}
	}
	else {
		CRPoints.clear();
	}
}


float CatmullRomSpline::getT(float t, ofPoint p0, ofPoint p1)
{
	float a = pow((p1.x - p0.x), 2.0f) + pow((p1.y - p0.y), 2.0f) + pow((p1.z - p0.z), 2.0f);
	float b = pow(a, 0.5f);
	float c = pow(b, alpha);

	return (c + t);
}

void CatmullRomSpline::setDefaultSplineParameter()
{
	edgeCtrlPtColor = ofColor::red;
	ctrlPtColor = ofColor::orangeRed;
	lineColor = ofColor::peachPuff;
	nbApproxPt = 20;
	ptRadius = 5;
	lineWidth = 5;
}