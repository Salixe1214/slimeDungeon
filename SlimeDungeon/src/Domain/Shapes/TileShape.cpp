#include "TileShape.h"

TileShape::TileShape(VectorPrimitiveType p_shapeType, float x1, float y1, float x2, float y2,
		ofColor p_fillColor, ofColor p_strokeColor, float p_strokeWidth, int p_tileSize)
	:Shape(p_shapeType, x1, y1, x2, y2, p_fillColor, p_strokeColor, p_strokeWidth), tileSize(p_tileSize)
{
	//try {

	//} Pour les shapes de taille invalides (trop petite)

	//catch (...) {
	//	
	//}
	//On va rectifier la position de x2 et y2 afin d'obtenir un quadrillage parfait
	position2.x  -= int(x2 - x1) % (tileSize);
	position2.y  -= int(y2 - y1) % (tileSize);
}

void TileShape::draw()
{
	ofFill();
	ofSetLineWidth(0);
	ofSetColor(fillColor);
	ofDrawRectangle(position1.x, position1.y, position2.x - position1.x, position2.y - position1.y);

	int curX = position1.x + tileSize, curY = position1.y + tileSize;
	int prevX = position1.x, prevY = position1.y;
	ofSetLineWidth(strokeWidth);
	ofSetColor(strokeColor);
	ofNoFill();
	ofDrawRectangle(position1.x, position1.y, position2.x - position1.x, position2.y - position1.y);

	while (curY <= position2.y) {
		ofDrawLine(position1.x, curY, position2.x, curY);
		curY += tileSize;
	}
	//drawLine
	while (curX <= position2.x) {
		ofDrawLine(curX, position1.y, curX, position2.y);
		curX += tileSize;
	}
}

int TileShape::getNbTile()
{
	return (position2.x - position1.x )/ tileSize * (position2.y - position1.y) / tileSize;
}
