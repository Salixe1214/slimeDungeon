#pragma once
#include "Domain/Shapes/Shape.h"

namespace shape {

	class Pixel : public Shape
	{
	public:
		Pixel(VectorPrimitiveType p_shapeType, float x1, float y1, ofColor p_fillColor);
		Pixel(VectorPrimitiveType p_shapeType, float x1, float y1, ofColor p_fillColor,  bool sampleShape);


		void draw() override;
		bool contains(float x, float y) override;
		void highlight() override;

	private:

	};
}

