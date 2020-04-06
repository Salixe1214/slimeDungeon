#include "Shape.h"

namespace shape {
	Shape::Shape(VectorPrimitiveType p_shapeType, float x1, float y1, float x2, float y2,
		ofColor p_fillColor, ofColor p_strokeColor, float p_strokeWidth,  glm::vec3 p_rotation) :
		shapeType(p_shapeType), fillColor(p_fillColor), strokeColor(p_strokeColor), strokeWidth(p_strokeWidth), rotation(p_rotation)
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
		else {
			setPosition1(x1, y1);
			setPosition2(x2, y2);
		}
	}

	Shape::Shape(VectorPrimitiveType p_shapeType, float x1, float y1, float x2, float y2,
					ofColor p_fillColor, ofColor p_strokeColor, float p_strokeWidth, 
						ofMaterial p_material, glm::vec3 p_rotation): shapeMaterial(p_material)
	{
		Shape(p_shapeType, x1, y1, x2, y2,
			 p_fillColor, p_strokeColor, p_strokeWidth, p_rotation);
	}

	Shape::Shape(VectorPrimitiveType p_shapeType, float x1, float y1, float x2, float y2,
		ofColor p_fillColor, ofColor p_strokeColor, float p_strokeWidth, bool filterX2Y2, glm::vec3 p_rotation) :
		shapeType(p_shapeType), fillColor(p_fillColor), strokeColor(p_strokeColor), strokeWidth(p_strokeWidth), rotation(p_rotation)
	{
		setPosition1(x1, y1);
		setPosition2(x2, y2);
	}


	bool Shape::operator== (const Shape& shape) const {
		return this->shapeId == shape.shapeId;
	}

	Shape::Shape(VectorPrimitiveType p_shapeType, ofPoint p_position1, ofPoint p_position2,
		ofColor p_fillColor, ofColor p_strokeColor, float p_strokeWidth, glm::vec3 p_rotation) :
		Shape(p_shapeType, p_position1.x, p_position1.y, p_position2.x, p_position2.y, p_fillColor, p_strokeColor, p_strokeWidth, p_rotation)
	{
	}

	void Shape::translate(float dx, float dy, float dz)
	{
		position1.x += dx;
		position2.x += dx;
		position1.y += dy;
		position2.y += dy;
	}

	void Shape::scale(float sx, float sy, float sz)
	{
		float middleX = (position1.x + position2.x) / 2.0;
		float middleY = (position1.y + position2.y) / 2.0;

		position1.x = middleX + (position1.x - middleX) * sx;
		position2.x = middleX + (position2.x - middleX) * sx;
		position1.y = middleY + (position1.y - middleY) * sy;
		position2.y = middleY + (position2.y - middleY) * sy;
	}

	void Shape::setMaterial(ofMaterial newMaterial)
	{
		shapeMaterial = newMaterial;
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

}
