#include "Rectangle.h"
namespace shape {

	Rectangle::Rectangle(VectorPrimitiveType p_shapeType, float x1, float y1, float x2, float y2,
		ofColor p_fillColor, ofColor p_strokeColor, float p_strokeWidth, glm::vec3 p_rotation)
		:Shape(p_shapeType, x1, y1, x2, y2, p_fillColor, p_strokeColor, p_strokeWidth, p_rotation)
	{
		static int numRectangle;
		numRectangle++;
		shapeId = "rectangle" + std::to_string(numRectangle);
	}

	//Constructeur pour les formes temporaires
	Rectangle::Rectangle(VectorPrimitiveType p_shapeType, float x1, float y1, float x2, float y2,
		ofColor p_fillColor, ofColor p_strokeColor, float p_strokeWidth, bool sampleShape, glm::vec3 p_rotation)
		:Shape(p_shapeType, x1, y1, x2, y2, p_fillColor, p_strokeColor, p_strokeWidth)
	{
		rotation = glm::vec3(0, 0, 0);
	}

	void Rectangle::draw()
	{
		ofPushMatrix();
		ofFill();
		ofSetLineWidth(0);
		ofSetColor(fillColor);
		ofDrawRectangle(position1.x, position1.y, position2.x - position1.x, position2.y - position1.y);

		ofSetLineWidth(strokeWidth);
		ofSetColor(strokeColor);
		ofNoFill();
		ofDrawRectangle(position1.x, position1.y, position2.x - position1.x, position2.y - position1.y);

		ofDrawBitmapString(to_string(rotation.z) + "\n" + to_string(position1.x) + "\n" + to_string(position1.y), position2);

		ofRotate(rotation.z, 0, 0, 1);
		ofPopMatrix();
	}

	bool Rectangle::contains(float x, float y)
	{
		return (x > position1.x) && (x < position2.x) && (y > position1.y) && (y < position2.y);
	}

	void Rectangle::highlight()
	{
		ofSetColor(highlightColor);
		ofNoFill();
		ofDrawRectangle(position1.x, position1.y, position2.x - position1.x, position2.y - position1.y);
	}
}
