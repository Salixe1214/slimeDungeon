#pragma once
#include "Domain/Shapes/Shape.h"

namespace shape {
	class Box : public Shape
	{
	public:
		Box(VectorPrimitiveType p_shapeType, float x1, float y1, float x2, float y2, ofColor p_fillColor, ofColor p_strokeColor,
			float p_strokeWidth, bool p_doShade, glm::vec3 p_rotation = { 0,0,0 });
		Box(VectorPrimitiveType p_shapeType, float x1, float y1, float x2, float y2, ofColor p_fillColor, ofColor p_strokeColor,
			float p_strokeWidth, bool p_doShade, ofMaterial p_material, glm::vec3 p_rotation = { 0,0,0 });

		Box(VectorPrimitiveType p_shapeType, float x1, float y1, float x2, float y2, ofColor p_fillColor, ofColor p_strokeColor,
			float p_strokeWidth, bool p_doShade, bool sampleShape, glm::vec3 p_rotation = { 0,0,0 });
		

		void draw() override;
		bool contains(float x, float y) override;
		void highlight() override;
		bool doShade;

		ofShader noiseText;
		ofTexture texture;
		ofPixels pixels;

	private:
	};
}
