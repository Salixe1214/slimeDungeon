#include "Shape.h"


Shape::Shape(VectorPrimitiveType p_shapeType, float x1, float y1, float x2, float y2,
			ofColor p_fillColor, ofColor p_strokeColor, float p_strokeWidth):
	shapeType(p_shapeType), fillColor(p_fillColor), strokeColor(p_strokeColor), strokeWidth(p_strokeWidth)
{
	position1 = ofPoint(x1, y1);
	position2 = ofPoint(x2, y2);
}

Shape::Shape(VectorPrimitiveType p_shapeType, ofPoint p_position1, ofPoint p_position2,
	ofColor p_fillColor, ofColor p_strokeColor, float p_strokeWidth) :
	shapeType(p_shapeType), position1(p_position1), position2(p_position2),
	fillColor(p_fillColor), strokeColor(p_strokeColor), strokeWidth(p_strokeWidth)
{
}

void Shape::setPosition1(float x1, float y1)
{
	position1.x = x1;
	position1.y = y1;
}

void Shape::setPosition2(float x2, float y2)
{
	position2.x = x2;
	position2.y = y2;
}
