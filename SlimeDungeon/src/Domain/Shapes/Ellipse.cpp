#include "Ellipse.h"

namespace shape {

	Ellipse::Ellipse(VectorPrimitiveType p_shapeType, float x1, float y1, float x2, float y2,
		ofColor p_fillColor, ofColor p_strokeColor, float p_strokeWidth)
		:Shape(p_shapeType, x1, y1, x2, y2, p_fillColor, p_strokeColor, p_strokeWidth)
	{
		static int numEllipseShape;
		numEllipseShape++;
		shapeId = "ellipse" + std::to_string(numEllipseShape);
	}

	//Constructeur pour les formes temporaires
	Ellipse::Ellipse(VectorPrimitiveType p_shapeType, float x1, float y1, float x2, float y2,
		ofColor p_fillColor, ofColor p_strokeColor, float p_strokeWidth, bool sampleShape)
		:Shape(p_shapeType, x1, y1, x2, y2, p_fillColor, p_strokeColor, p_strokeWidth)
	{

	}

	void Ellipse::draw()
	{
		float centerX = position1.x + (position2.x - position1.x) / 2;
		float diameterX = position2.x - position1.x;
		float diameterY = position2.y - position1.y;
		float centerY = position1.y + (position2.y - position1.y) / 2;

		//fill
		ofFill();
		ofSetLineWidth(0);
		ofSetColor(fillColor);

		ofDrawEllipse(centerX, centerY, diameterX, diameterY);

		//Line
		ofSetLineWidth(strokeWidth);
		ofSetColor(strokeColor);
		ofNoFill();

		ofDrawEllipse(centerX, centerY, diameterX, diameterY);
	}

	bool Ellipse::contains(float x, float y)
	{
		float centerX = position1.x + (position2.x - position1.x) / 2;
		float diameterX = position2.x - position1.x;
		float diameterY = position2.y - position1.y;
		float centerY = position1.y + (position2.y - position1.y) / 2;
		return (pow((x - centerX), 2) / pow((diameterX / 2), 2)) + (pow((y - centerY), 2) / pow((diameterY / 2), 2)) <= 1;
	}

	void Ellipse::highlight()
	{
		float centerX = position1.x + (position2.x - position1.x) / 2;
		float diameterX = position2.x - position1.x;
		float diameterY = position2.y - position1.y;
		float centerY = position1.y + (position2.y - position1.y) / 2;

		ofSetColor(highlightColor);
		ofNoFill();
		ofDrawEllipse(centerX, centerY, diameterX, diameterY);
	}
}
