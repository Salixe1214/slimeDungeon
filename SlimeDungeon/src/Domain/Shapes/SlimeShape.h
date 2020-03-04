#pragma once
#include "Domain/Shapes/Shape.h"
namespace shape {
	class SlimeShape : public Shape
	{
	public:
		SlimeShape(VectorPrimitiveType p_shapeType, float x1, float y1, float x2, float y2, ofColor p_fillColor, ofColor p_strokeColor,
			float p_strokeWidth, glm::vec3 p_rotation = { 0,0,0 });
		SlimeShape(VectorPrimitiveType p_shapeType, float x1, float y1, float x2, float y2, ofColor p_fillColor, ofColor p_strokeColor,
			float p_strokeWidth, bool sampleShape, glm::vec3 p_rotation = { 0,0,0 });

		void draw() override;
		void highlight() override;
		bool contains(float x, float y) override;


	private:
		bool isPointInTriangle(float x, float y, float ax, float ay, float bx, float by, float cx, float cy);
		bool isPointInEllipse(float x, float y, float centerx, float centery, float diameterX, float diameterY);
	};
}
