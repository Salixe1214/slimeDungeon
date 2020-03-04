#pragma once
#include "Domain/Shapes/Shape.h"

namespace shape {
	class Ellipse : public Shape
	{
	public:
		Ellipse(VectorPrimitiveType p_shapeType, float x1, float y1, float x2, float y2, ofColor p_fillColor, ofColor p_strokeColor,
			float p_strokeWidth);
		Ellipse(VectorPrimitiveType p_shapeType, float x1, float y1, float x2, float y2, ofColor p_fillColor, ofColor p_strokeColor,
			float p_strokeWidth, bool sampleShape);


		void draw() override;
		bool contains(float x, float y) override;
		void highlight() override;

	private:

	};
}
