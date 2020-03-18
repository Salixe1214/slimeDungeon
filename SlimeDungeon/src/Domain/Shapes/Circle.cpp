#include "Circle.h"

namespace shape {
	Circle::Circle(VectorPrimitiveType p_shapeType, float x1, float y1, float x2, float y2,
		ofColor p_fillColor, ofColor p_strokeColor, float p_strokeWidth, glm::vec3 p_rotation)
		:Shape(p_shapeType, x1, y1, x2, y2, p_fillColor, p_strokeColor, p_strokeWidth, p_rotation)
	{
		static int numCircleShape;
		numCircleShape++;
		shapeId = "circle" + std::to_string(numCircleShape);
	}

	//Constructeur pour les formes temporaires
	Circle::Circle(VectorPrimitiveType p_shapeType, float x1, float y1, float x2, float y2,
		ofColor p_fillColor, ofColor p_strokeColor, float p_strokeWidth, bool sampleShape, glm::vec3 p_rotation)
		:Shape(p_shapeType, x1, y1, x2, y2, p_fillColor, p_strokeColor, p_strokeWidth, p_rotation)
	{

	}

	void Circle::draw()
	{
		float centerX = position1.x + (position2.x - position1.x) / 2;
		float diameter = position2.x - position1.x;
		float centerY = position1.y + (position2.y - position1.y) / 2;

		//fill
		ofFill();
		ofSetLineWidth(0);
		ofSetColor(fillColor);

		ofDrawEllipse(centerX, centerY, diameter, diameter);

		//Line
		ofSetLineWidth(strokeWidth);
		ofSetColor(strokeColor);
		ofNoFill();

		ofDrawEllipse(centerX, centerY, diameter, diameter);
	}

	bool Circle::contains(float x, float y)
	{
		float centerX = position1.x + (position2.x - position1.x) / 2;
		float diameter = position2.x - position1.x;
		float centerY = position1.y + (position2.y - position1.y) / 2;
		return (pow((x - centerX), 2) / pow((diameter / 2), 2)) + (pow((y - centerY), 2) / pow((diameter / 2), 2)) <= 1;
	}

	void Circle::highlight()
	{
		float centerX = position1.x + (position2.x - position1.x) / 2;
		float diameter = position2.x - position1.x;
		float centerY = position1.y + (position2.y - position1.y) / 2;

		ofSetColor(highlightColor);
		ofNoFill();
		ofDrawEllipse(centerX, centerY, diameter, diameter);
	}
	void Circle::scale(float sx, float sy, float sz)
	{
		float middleX = (position1.x + position2.x) / 2.0;
		float middleY = (position1.y + position2.y) / 2.0;

		position1.x = middleX + (position1.x - middleX) * sx;
		position2.x = middleX + (position2.x - middleX) * sx;
		position1.y = middleY + (position1.y - middleY) * sx;
		position2.y = middleY + (position2.y - middleY) * sx;
	}
}
