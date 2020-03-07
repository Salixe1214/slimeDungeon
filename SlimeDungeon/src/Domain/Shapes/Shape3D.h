#pragma once
#include "Domain/Shapes/Shape.h"
#include "ofxAssimpModelLoader.h"

namespace shape {
	class Shape3D : public Shape
	{
	public:
		Shape3D(VectorPrimitiveType p_shapeType, float x, float y, float z, float sizeRatio, 
			ofColor p_fillColor, string modelName, glm::vec3 p_rotation = { 0,0,0 });
		Shape3D(VectorPrimitiveType p_shapeType, float x, float y, float z, float sizeRatio, 
			ofColor p_fillColor,  bool sampleShape, string modelName, glm::vec3 p_rotation = { 0, 270,0 });

		ofPoint position;

		void draw() override;
		bool contains(float x, float y) override;
		void highlight() override;

	private:
		ofxAssimpModelLoader model;
	};
}

