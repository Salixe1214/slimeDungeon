#include "SlimeShape.h"

SlimeShape::SlimeShape(VectorPrimitiveType p_shapeType, float x1, float y1, float x2, float y2,
		ofColor p_fillColor, ofColor p_strokeColor, float p_strokeWidth)
	:Shape(p_shapeType, x1, y1, x2, y2, p_fillColor, p_strokeColor, p_strokeWidth)
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
}
