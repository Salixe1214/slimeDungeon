#include "Shape.h"


Shape::Shape(VectorPrimitiveType p_shapeType, float x1, float y1, float x2, float y2,
	ofColor p_fillColor, ofColor p_strokeColor, float p_strokeWidth) :
	shapeType(p_shapeType), fillColor(p_fillColor), strokeColor(p_strokeColor), strokeWidth(p_strokeWidth)
{
	//Les points sont organisés afin que le position1 soit le coin supérieur gauche du bounding box et
	// position2 est le coin inférieur droit du bounding box
	if (x2 - x1 > 0 && y2 - y1 < 0) {
		setPosition1(x1, y2);
		setPosition2(x2, y1);
	}
	else if (x2 - x1 < 0 && y2 - y1 >0) {
		setPosition1(x2, y1);
		setPosition2(x1, y2);
	}
	else if (x2 - x1 < 0 && y2 - y1 < 0) {
		setPosition1(x2, y2);
		setPosition2(x1, y1);
	}
	else{
		setPosition1(x1, y1);
		setPosition2(x2, y2);
	}
}

Shape::Shape(VectorPrimitiveType p_shapeType, ofPoint p_position1, ofPoint p_position2,
	ofColor p_fillColor, ofColor p_strokeColor, float p_strokeWidth) :
	Shape(p_shapeType, p_position1.x, p_position1.y, p_position2.x, p_position2.y, p_fillColor, p_strokeColor, p_strokeWidth)
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
