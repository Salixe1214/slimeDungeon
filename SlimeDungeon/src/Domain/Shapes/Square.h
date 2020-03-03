#pragma once
#include "Domain/Shapes/Shape.h"

class TileShape : public Shape
{
public:
	TileShape(VectorPrimitiveType p_shapeType, float x1, float y1, float x2, float y2, ofColor p_fillColor, ofColor p_strokeColor,
			float p_strokeWidth, int tileSize);
	TileShape(VectorPrimitiveType p_shapeType, float x1, float y1, float x2, float y2, ofColor p_fillColor, ofColor p_strokeColor,
		float p_strokeWidth, int tileSize, bool sampleShape);


	void draw() override;
	bool contains(float x, float y) override;
	void highlight() override;
	int getNbTile();

private:
	int tileSize;
	
};

