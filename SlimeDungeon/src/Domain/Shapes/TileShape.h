#pragma once
#include "Domain/Shapes/Shape.h"

namespace shape {

	class TileShape : public Shape
	{
	public:
		TileShape(VectorPrimitiveType p_shapeType, float x1, float y1, float x2, float y2, ofColor p_fillColor, ofColor p_strokeColor,
			float p_strokeWidth, int tileSize, glm::vec3 p_rotation = { 0,0,0 });
		TileShape(VectorPrimitiveType p_shapeType, float x1, float y1, float x2, float y2, ofColor p_fillColor, ofColor p_strokeColor,
			float p_strokeWidth, int tileSize, bool sampleShape, glm::vec3 p_rotation = { 0,0,0 });


		void draw() override;
		bool contains(float x, float y) override;
		void highlight() override;
		int getNbTile();
		int tileSize;

	private:
		

	};
}

