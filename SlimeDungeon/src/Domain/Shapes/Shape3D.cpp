#include "Shape3D.h"

namespace shape {



	Shape3D::Shape3D(VectorPrimitiveType p_shapeType, float x, float y, float z, float sizeRatio,
		ofColor p_fillColor, string modelName, glm::vec3 p_rotation) :
		Shape(p_shapeType, x, y, x + sizeRatio, y + sizeRatio, p_fillColor, p_fillColor, 0, p_rotation),
		position(x, y, z)
	{
		model.loadModel(modelName, 20);
		model.setPosition(position.x, position.y, position.z);
		model.setScale(sizeRatio, sizeRatio, sizeRatio);
		model.enableColors();
		light.setPosition(position.x, position.y, position.z);
		model.setRotation(0, rotation.x, 1, 0, 0);
		model.setRotation(0, rotation.y, 0, 1, 0);
		model.setRotation(0, rotation.z, 0, 0, 1);
		light.setup();

	}

	Shape3D::Shape3D(VectorPrimitiveType p_shapeType, float x, float y, float z, float sizeRatio,
		ofColor p_fillColor, bool sampleShape, string modelName, glm::vec3 p_rotation):
		Shape(p_shapeType, x, y, x + sizeRatio, y + sizeRatio, p_fillColor, p_fillColor, 0, p_rotation)
	{
		model.loadModel(modelName, 20);
		model.setPosition(350, 150, 0);
		model.setScale(0.3, 0.3, 0.3);
		model.enableColors();
		light.setPosition(0, 0, 0);
		model.setRotation(0, rotation.y, 0, 1, 0);
		light.setup();
	}

	void Shape3D::draw()
	{
		ofColor(fillColor);
		light.enable();
		model.drawFaces();

	}

	bool Shape3D::contains(float x, float y)
	{
		return false;
	}

	void Shape3D::highlight()
	{
		fillColor = ofColor::blueSteel;
	}

}