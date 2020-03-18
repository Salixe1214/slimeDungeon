#include "Square.h"

namespace shape {

	Square::Square(VectorPrimitiveType p_shapeType, float x1, float y1, float x2, float y2,
		ofColor p_fillColor, ofColor p_strokeColor, float p_strokeWidth, glm::vec3 p_rotation)
		:Shape(p_shapeType, x1, y1, x2, y2, p_fillColor, p_strokeColor, p_strokeWidth, p_rotation)
	{
		static int numSquare;
		numSquare++;
		shapeId = "square" + std::to_string(numSquare);
	}

	//Constructeur pour les formes temporaires
	Square::Square(VectorPrimitiveType p_shapeType, float x1, float y1, float x2, float y2,
		ofColor p_fillColor, ofColor p_strokeColor, float p_strokeWidth, bool sampleShape, glm::vec3 p_rotation)
		:Shape(p_shapeType, x1, y1, x2, y2, p_fillColor, p_strokeColor, p_strokeWidth, p_rotation)
	{
	}

	void Square::draw()
	{
		ofFill();
		ofSetLineWidth(0);
		ofSetColor(fillColor);
		ofDrawRectangle(position1.x, position1.y, position2.x - position1.x, position2.y - position1.y);

		ofSetLineWidth(strokeWidth);
		ofSetColor(strokeColor);
		ofNoFill();
		ofDrawRectangle(position1.x, position1.y, position2.x - position1.x, position2.y - position1.y);
	}

	bool Square::contains(float x, float y)
	{
		return (x > position1.x) && (x < position2.x) && (y > position1.y) && (y < position2.y);
	}

	void Square::highlight()
	{
		ofSetColor(highlightColor);
		ofNoFill();
		ofDrawRectangle(position1.x, position1.y, position2.x - position1.x, position2.y - position1.y);
	}

	void Square::scale(float sx, float sy, float sz)
	{
		float middleX = (position1.x + position2.x) / 2.0;
		float middleY = (position1.y + position2.y) / 2.0;

		position1.x = middleX + (position1.x - middleX) * sx;
		position2.x = middleX + (position2.x - middleX) * sx;
		position1.y = middleY + (position1.y - middleY) * sx;
		position2.y = middleY + (position2.y - middleY) * sx;
	}
}