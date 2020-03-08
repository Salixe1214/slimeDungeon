#include "Ball.h"

namespace shape {
	Ball::Ball(VectorPrimitiveType p_shapeType, float x1, float y1, float x2, float y2,
		ofColor p_fillColor, ofColor p_strokeColor, float p_strokeWidth, glm::vec3 p_rotation)
		:Shape(p_shapeType, x1, y1, x2, y2, p_fillColor, p_strokeColor, p_strokeWidth, p_rotation)
	{
		static int numBallShape;
		numBallShape++;
		shapeId = "circle" + std::to_string(numBallShape);
	}

	//Constructeur pour les formes temporaires
	Ball::Ball(VectorPrimitiveType p_shapeType, float x1, float y1, float x2, float y2,
		ofColor p_fillColor, ofColor p_strokeColor, float p_strokeWidth, bool sampleShape, glm::vec3 p_rotation)
		:Shape(p_shapeType, x1, y1, x2, y2, p_fillColor, p_strokeColor, p_strokeWidth, p_rotation)
	{

	}

	void Ball::draw()
	{
		float centerX = position1.x + (position2.x - position1.x) / 2;
		float diameter = position2.x - position1.x;
		float centerY = position1.y + (position2.y - position1.y) / 2;

		//fill
		ofFill();
		ofSetLineWidth(0);
		ofSetColor(fillColor);

		ofDrawSphere(centerX, centerY, 0, diameter);

		//Line
		ofSetLineWidth(strokeWidth);
		ofSetColor(strokeColor);
		ofNoFill();

		ofDrawSphere(centerX, centerY, 0, diameter);
	}

	bool Ball::contains(float x, float y)
	{
		float centerX = position1.x + (position2.x - position1.x) / 2;
		float diameter = position2.x - position1.x;
		float centerY = position1.y + (position2.y - position1.y) / 2;
		return (pow((x - centerX), 2) / pow((diameter / 2), 2)) + (pow((y - centerY), 2) / pow((diameter / 2), 2)) <= 1;
	}

	void Ball::highlight()
	{
		float centerX = position1.x + (position2.x - position1.x) / 2;
		float diameter = position2.x - position1.x;
		float centerY = position1.y + (position2.y - position1.y) / 2;

		ofSetColor(highlightColor);
		ofNoFill();
		ofDrawSphere(centerX, centerY, 0, diameter);
	}
}

