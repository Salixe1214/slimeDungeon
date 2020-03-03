#include "Line.h"
namespace shape {

	Line::Line(VectorPrimitiveType p_shapeType, float x1, float y1, float x2, float y2,
		ofColor p_strokeColor, float p_strokeWidth)
		:Shape(p_shapeType, x1, y1, x2, y2, ofColor(0,0,0,0), p_strokeColor, p_strokeWidth, false)
	{
		static int numLine;
		numLine++;
		shapeId = "line" + std::to_string(numLine);
	}

	//Constructeur pour les formes temporaires
	Line::Line(VectorPrimitiveType p_shapeType, float x1, float y1, float x2, float y2,
		 ofColor p_strokeColor, float p_strokeWidth, bool sampleShape)
		:Shape(p_shapeType, x1, y1, x2, y2, ofColor(0,0,0,0), p_strokeColor, p_strokeWidth, false)
	{
	}

	void Line::draw()
	{
		ofSetLineWidth(strokeWidth);
		ofSetColor(strokeColor);
		ofDrawLine(position1.x, position1.y, position2.x, position2.y);
	}

	bool Line::contains(float x, float y)
	{
		cout << shapeId << "Id" << endl;
		float topX = std::max(position1.x, position2.x);
		float botX = std::min(position1.x, position2.x);
		float topY = std::max(position1.y, position2.y);
		float botY = std::min(position1.y, position2.y);
		float slope = (position2.y - position1.y) / (position2.x - position1.x);
		float b1 = position1.y - slope * position1.x  + strokeWidth/2.0;
		float b2 = position1.y - slope * position1.x - strokeWidth/2.0;
		return (y < topY) && (y > botY) && (x > botX) && (x < topX) && (y <= slope * x + b1) && (y >= slope * x + b2);
	}

	void Line::highlight()
	{
		ofSetColor(highlightColor);
		ofNoFill();
		ofDrawLine(position1.x, position1.y, position2.x, position2.y);
	}
}
