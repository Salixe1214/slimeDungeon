#pragma once
#include "Domain/Shapes/Shape.h"

class SlimeShape : public Shape
{
public:
	SlimeShape(VectorPrimitiveType p_shapeType, float x1, float y1, float x2, float y2, ofColor p_fillColor, ofColor p_strokeColor,
			float p_strokeWidth);
	void draw();

private:
};

