#pragma once
#include "ofMain.h"
namespace shape {
	enum class VectorPrimitiveType { none, pixel, line, rectangle, square, ellipse, circle, slime, 
									tiles, slime3d, monster3d, ballFace, cube, ball}; //TODO rename

	class Shape
	{
	public:
		Shape(VectorPrimitiveType p_shapeType, float x1, float y1, float x2, float y2,
			ofColor p_fillColor, ofColor p_strokeColor, float p_strokeWidth, glm::vec3 p_rotation = { 0,0,0 });
		Shape(VectorPrimitiveType p_shapeType, ofPoint p_position1, ofPoint p_position2,
			ofColor p_fillColor, ofColor p_strokeColor, float p_strokeWidth, glm::vec3 p_rotation = { 0,0,0 });
		Shape(VectorPrimitiveType p_shapeType, float x1, float y1, float x2, float y2,
			ofColor p_fillColor, ofColor p_strokeColor, float p_strokeWidth, bool filterX2Y2, glm::vec3 p_rotation = { 0,0,0 });

		ofPoint                  position1;    // 2 * 4 = 8  octets
		ofPoint                  position2;    // 2 * 4 = 8  octets
		float                  strokeWidth;    // 1 * 4 = 4  octets
		ofColor                fillColor;
		ofColor                strokeColor;
		VectorPrimitiveType shapeType;
		Shape* parent;
		std::vector<Shape*> childs;
		string shapeId;
		glm::vec3 rotation;

		virtual void draw() {};
		virtual bool contains(float x, float y) { return false; };
		virtual void highlight() {};
		bool operator== (const Shape& shape) const;

		void setPosition1(float x1, float y1);
		void setPosition2(float x2, float y2);

		ofColor highlightColor = ofColor::blueSteel;

	};
}
