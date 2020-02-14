#include "TileShape.h"

TileShape::TileShape(VectorPrimitiveType p_shapeType, float x1, float y1, float x2, float y2,
		ofColor p_fillColor, ofColor p_strokeColor, float p_strokeWidth, int p_tileSize)
	:Shape(p_shapeType, x1, y1, x2, y2, p_fillColor, p_strokeColor, p_strokeWidth), tileSize(p_tileSize)
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
	while (curY <= position2.y) {
		ofDrawLine(position1.x, prevY, position2.x, prevY);
		prevY = curY;
		prevX = position1.x;
		curX = position1.x + tileSize;
		curY += tileSize;
	}
	//drawLine
	while (curX <= position2.x) {
		ofDrawLine(prevX, prevY, tileSize, tileSize);
		prevX = curX;
		curX += tileSize;
	}
}
