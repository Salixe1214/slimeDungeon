#pragma once
#include "Shape.h"

namespace shape {
	class Ball : public Shape
	{
	public:
		Ball(VectorPrimitiveType p_shapeType, float x1, float y1, float x2, float y2, ofColor p_fillColor, ofColor p_strokeColor,
			float p_strokeWidth, bool p_shade, string p_textureFile = "", glm::vec3 p_rotation = { 0,0,0 });
		Ball(VectorPrimitiveType p_shapeType, float x1, float y1, float x2, float y2, ofColor p_fillColor, ofColor p_strokeColor,
			float p_strokeWidth, bool p_shade, ofMaterial material, string p_textureFile = "", glm::vec3 p_rotation = { 0,0,0 });

		Ball(VectorPrimitiveType p_shapeType, float x1, float y1, float x2, float y2, ofColor p_fillColor, ofColor p_strokeColor,
			float p_strokeWidth, bool p_shade, bool sampleShape, string p_textureFile = "", glm::vec3 p_rotation = { 0,0,0 });


		void draw() override;
		bool contains(float x, float y) override;
		void highlight() override;
		void translate(float dx, float dy, float dz = 0) override;
		void scale(float sx, float sy, float sz = 0) override;

		void loadTexture(string p_textureFile);
		void removeTexture();


		ofSpherePrimitive sphere;
		ofTexture texture;
		string textureFile;
		ofShader mapage_tonale;
		bool shade;

	private:
	};
}
