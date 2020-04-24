#include "Domain/Shapes/Box.h"

namespace shape {

	Box::Box(VectorPrimitiveType p_shapeType, float x1, float y1, float x2, float y2,
		ofColor p_fillColor, ofColor p_strokeColor, float p_strokeWidth, bool p_doShade, glm::vec3 p_rotation)
		:Shape(p_shapeType, x1, y1, x2, y2, p_fillColor, p_strokeColor, p_strokeWidth, p_rotation)
	{
		static int numBox;
		numBox++;
		shapeId = "box" + std::to_string(numBox);
		doShade = p_doShade;
		noiseText.load("noise_330_vs.glsl", "noise_330_fs.glsl");
		pixels.allocate(x2 - x1, y2 - y1, OF_PIXELS_RGBA);
		texture.allocate(pixels);
	}

	Box::Box(VectorPrimitiveType p_shapeType, float x1, float y1, float x2, float y2, ofColor p_fillColor, ofColor p_strokeColor, float p_strokeWidth, bool p_doShade, ofMaterial p_material, glm::vec3 p_rotation)
		: Box(p_shapeType, x1, y1, x2, y2,
			p_fillColor, p_strokeColor, p_strokeWidth, p_doShade, p_rotation)
	{
		setMaterial(p_material);
		doShade = p_doShade;
	}

	//Constructeur pour les formes temporaires
	Box::Box(VectorPrimitiveType p_shapeType, float x1, float y1, float x2, float y2,
		ofColor p_fillColor, ofColor p_strokeColor, float p_strokeWidth, bool p_doShade, bool sampleShape, glm::vec3 p_rotation)
		:Shape(p_shapeType, x1, y1, x2, y2, p_fillColor, p_strokeColor, p_strokeWidth, p_rotation)
	{
		doShade = false;//p_doShade;
	}

	void Box::draw()
	{
		ofFill();
		ofSetLineWidth(0);
		ofSetColor(fillColor);
		if (doShade) {
			noiseText.begin();
			noiseText.setUniform1f("u_time", ofGetElapsedTimef());
			texture.bind();
			ofDrawBox((position1.x + position2.x) / 2, (position1.y + position2.y) / 2, 0, position2.x - position1.x);
			texture.unbind();
			noiseText.end();
		}
		else {
			shapeMaterial.begin();
			ofDrawBox((position1.x + position2.x) / 2, (position1.y + position2.y) / 2, 0, position2.x - position1.x);
			shapeMaterial.end();

			ofSetLineWidth(strokeWidth);
			ofSetColor(strokeColor);
			ofNoFill();
			ofDrawBox((position1.x + position2.x) / 2, (position1.y + position2.y) / 2, 0, position2.x - position1.x);
		}
	}

	bool Box::contains(float x, float y)
	{
		return (x > position1.x) && (x < position2.x) && (y > position1.y) && (y < position2.y);
	}

	void Box::highlight()
	{
		ofSetColor(highlightColor);
		ofNoFill();
		ofDrawBox((position1.x + position2.x) / 2, (position1.y + position2.y) / 2, 0, position2.x - position1.x);
	}

}
