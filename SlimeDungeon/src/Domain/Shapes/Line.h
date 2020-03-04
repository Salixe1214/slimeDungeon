#pragma once
#include "Domain/Shapes/Shape.h"

namespace shape {

	class Line : public Shape
	{
	public:
		Line(VectorPrimitiveType p_shapeType, float x1, float y1, float x2, float y2, ofColor p_strokeColor,
			float p_strokeWidth, glm::vec3 p_rotation = { 0,0,0 });
		Line(VectorPrimitiveType p_shapeType, float x1, float y1, float x2, float y2, ofColor p_strokeColor,
			float p_strokeWidth, bool sampleShape, glm::vec3 p_rotation = { 0,0,0 });


		void draw() override;
		bool contains(float x, float y) override;
		void highlight() override;

	private:

	};
}

