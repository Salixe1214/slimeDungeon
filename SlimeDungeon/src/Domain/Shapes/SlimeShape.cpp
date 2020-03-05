#include "SlimeShape.h"

namespace shape {

	SlimeShape::SlimeShape(VectorPrimitiveType p_shapeType, float x1, float y1, float x2, float y2,
		ofColor p_fillColor, ofColor p_strokeColor, float p_strokeWidth, glm::vec3 p_rotation)
		:Shape(p_shapeType, x1, y1, x2, y2, p_fillColor, p_strokeColor, p_strokeWidth, p_rotation)
	{
		static int numSlimeShape;
		numSlimeShape++;
		shapeId = "slime" + std::to_string(numSlimeShape);
	}

	//Constructeur pour les formes temporaires
	SlimeShape::SlimeShape(VectorPrimitiveType p_shapeType, float x1, float y1, float x2, float y2,
		ofColor p_fillColor, ofColor p_strokeColor, float p_strokeWidth, bool sampleShape, glm::vec3 p_rotation)
		:Shape(p_shapeType, x1, y1, x2, y2, p_fillColor, p_strokeColor, p_strokeWidth, p_rotation)
	{
	}

	void SlimeShape::draw()
	{
		float sideLengthX = position2.x - position1.x;
		float sideLengthY = position2.y - position1.y;
		float middleX = (position2.x + position1.x) / 2;

		ofFill();
		ofSetLineWidth(0);
		ofSetColor(fillColor);



		//On veut que l'ellipse passe par le bas du bounding box et jusqu'au 2/9 de la hauteur du bounding box
		float diameterY = sideLengthY * 7 / 9;
		float ellipseCenterY = position2.y - diameterY / 2;
		ofDrawEllipse(middleX, ellipseCenterY, position2.x - position1.x, diameterY);

		//Contour ellipse
		ofNoFill();
		ofSetLineWidth(strokeWidth);
		ofSetColor(strokeColor);
		ofDrawEllipse(middleX, ellipseCenterY, position2.x - position1.x, diameterY);

		//Dessin d'un triangle isocèle dont les points sont au sommet du bounding box, ainsi 
		//qu'au 1/3 de la hauteur du bounding box
		ofFill();
		ofSetLineWidth(0);
		ofSetColor(fillColor);
		ofDrawTriangle(middleX, position1.y, middleX - sideLengthX / 4, position1.y + sideLengthY / 3,
			middleX + sideLengthX / 4, position1.y + sideLengthY / 3);

		//Deux côtés du triangle
		ofNoFill();
		ofSetLineWidth(strokeWidth);
		ofSetColor(strokeColor);
		ofDrawLine(middleX, position1.y, middleX - sideLengthX / 4, position1.y + sideLengthY / 3);
		ofDrawLine(middleX, position1.y, middleX + sideLengthX / 4, position1.y + sideLengthY / 3);

		//Ajout de yeux
		ofFill();
		ofSetColor(ofColor::white);
		ofDrawCircle(position1.x + (sideLengthX / 3), position1.y + sideLengthY / 2, ((sideLengthX + sideLengthY)/2)/15);
		ofDrawCircle(position1.x + (2*(sideLengthX / 3)), position1.y + sideLengthY / 2, ((sideLengthX + sideLengthY) / 2) / 15);
		ofSetColor(ofColor::black);
		ofDrawCircle(position1.x + (sideLengthX / 3), position1.y + sideLengthY / 2, ((sideLengthX + sideLengthY) / 2) / 40);
		ofDrawCircle(position1.x + (2 * (sideLengthX / 3)), position1.y + sideLengthY / 2, ((sideLengthX + sideLengthY) / 2) / 40);
	}

	void SlimeShape::highlight()
	{
		float sideLengthX = position2.x - position1.x;
		float sideLengthY = position2.y - position1.y;
		float middleX = (position2.x + position1.x) / 2;

		//On veut que l'ellipse passe par le bas du bounding box et jusqu'au 2/9 de la hauteur du bounding box
		float diameterY = sideLengthY * 7 / 9;
		float ellipseCenterY = position2.y - diameterY / 2;

		//Contour ellipse
		ofNoFill();
		ofSetLineWidth(strokeWidth);
		ofSetColor(highlightColor);
		ofDrawEllipse(middleX, ellipseCenterY, position2.x - position1.x, diameterY);

		//Deux côtés du triangle
		ofNoFill();
		ofSetLineWidth(strokeWidth);
		ofDrawLine(middleX, position1.y, middleX - sideLengthX / 4, position1.y + sideLengthY / 3);
		ofDrawLine(middleX, position1.y, middleX + sideLengthX / 4, position1.y + sideLengthY / 3);
	}

	bool SlimeShape::contains(float x, float y)
	{
		float sideLengthX = position2.x - position1.x;
		float sideLengthY = position2.y - position1.y;
		float middleX = (position2.x + position1.x) / 2;

		//On veut que l'ellipse passe par le bas du bounding box et jusqu'au 2/9 de la hauteur du bounding box
		float diameterY = sideLengthY * 7 / 9;
		float ellipseCenterY = position2.y - diameterY / 2;

		return isPointInTriangle(x, y, middleX, position1.y, middleX - sideLengthX / 4, position1.y + sideLengthY / 3,
			middleX + sideLengthX / 4, position1.y + sideLengthY / 3)
			|| isPointInEllipse(x, y, middleX, ellipseCenterY, position2.x - position1.x, diameterY);
	}

	bool SlimeShape::isPointInEllipse(float x, float y, float centerX, float centerY, float diameterX, float diameterY) {
		return (pow((x - centerX), 2) / pow((diameterX / 2), 2)) + (pow((y - centerY), 2) / pow((diameterY / 2), 2)) <= 1;
	}

	bool SlimeShape::isPointInTriangle(float x, float y, float ax, float ay, float bx, float by, float cx, float cy) {
		//Algorithme tiré de 
	https://stackoverflow.com/questions/2049582/how-to-determine-if-a-point-is-in-a-2d-triangle

		float as_x = x - ax;
		float as_y = y - ay;

		bool s_ab = (bx - ax)*as_y - (by - ay)*as_x > 0;

		if ((cx - ax)*as_y - (cy - ay)*as_x > 0 == s_ab) return false;

		if ((cx - bx)*(y - by) - (cy - by)*(x - bx) > 0 != s_ab) return false;

		return true;
	}
}