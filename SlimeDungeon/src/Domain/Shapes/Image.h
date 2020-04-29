#pragma once
#include "Domain/Shapes/Shape.h"
#include "ofxOpenCv.h"

namespace shape {

	class Image : public Shape
	{
	public:
		Image(VectorPrimitiveType p_shapeType, float x1, float y1, float x2, float y2, ofImage p_image, ofColor p_fillColor, ofColor p_strokeColor,
			float p_strokeWidth, bool bl, bool tn, glm::vec3 p_rotation = { 0,0,0 });
		
		//shader d'image
		
		ofShader shader;
		ofShader tonalMapping;
		ofImage image;
		void draw() override;
		bool contains(float x, float y) override;
		void highlight() override;

		bool blurOn;
		bool tonalOn;

	private:

	};

}