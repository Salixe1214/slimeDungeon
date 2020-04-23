#include "Ball.h"

namespace shape {
	Ball::Ball(VectorPrimitiveType p_shapeType, float x1, float y1, float x2, float y2,
		ofColor p_fillColor, ofColor p_strokeColor, float p_strokeWidth, bool p_shade, string p_textureFile,
		glm::vec3 p_rotation)
		:Shape(p_shapeType, x1, y1, x2, y2, p_fillColor, p_strokeColor, p_strokeWidth, p_rotation)
	{
		static int numBallShape;
		numBallShape++;
		shapeId = "circle" + std::to_string(numBallShape);

		float centerX = position1.x + (position2.x - position1.x) / 2;
		float diameter = position2.x - position1.x;
		float centerY = position1.y + (position2.y - position1.y) / 2;
		sphere.setPosition(centerX, centerY, 0);
		sphere.setRadius(diameter/2);

		if (!p_textureFile.empty()) {
			loadTexture(p_textureFile);
		}

		mapage_tonale.load("mapage_tonale_330_vs.glsl", "mapage_tonale_330_fs.glsl");
		shade = p_shade;
	}

	Ball::Ball(VectorPrimitiveType p_shapeType, float x1, float y1, float x2, float y2,
		ofColor p_fillColor, ofColor p_strokeColor, float p_strokeWidth, bool p_shade,
		ofMaterial p_material, string p_textureFile, glm::vec3 p_rotation) :
		Ball(p_shapeType, x1, y1, x2, y2,
			p_fillColor, p_strokeColor, p_strokeWidth, p_shade, p_textureFile, p_rotation)
	{
		setMaterial(p_material);
		mapage_tonale.load("mapage_tonale_330_vs.glsl", "mapage_tonale_330_fs.glsl");
		shade = p_shade;
	}

	//Constructeur pour les formes temporaires
	Ball::Ball(VectorPrimitiveType p_shapeType, float x1, float y1, float x2, float y2,
		ofColor p_fillColor, ofColor p_strokeColor, float p_strokeWidth, bool p_shade, bool sampleShape,
		string p_textureFile, glm::vec3 p_rotation)
		:Shape(p_shapeType, x1, y1, x2, y2, p_fillColor, p_strokeColor, p_strokeWidth, p_rotation)
	{
		float centerX = position1.x + (position2.x - position1.x) / 2;
		float diameter = position2.x - position1.x;
		float centerY = position1.y + (position2.y - position1.y) / 2;
		sphere.setPosition(centerX, centerY, 0);
		sphere.setRadius(diameter/2);

		if (!p_textureFile.empty()) {
			loadTexture(p_textureFile);
		}
		mapage_tonale.load("mapage_tonale_330_vs.glsl", "mapage_tonale_330_fs.glsl");
		shade = p_shade;
	}

	void Ball::draw()
	{
		float centerX = position1.x + (position2.x - position1.x) / 2;
		float diameter = position2.x - position1.x;
		float centerY = position1.y + (position2.y - position1.y) / 2;
		
		ofFill();
		ofSetLineWidth(0);
		ofSetColor(fillColor);

		if (shade) {
			mapage_tonale.begin();
		}
		else {
			shapeMaterial.begin();
		}

		if (texture.isAllocated()) {
			mapage_tonale.setUniformTexture("image", texture, 1);

			//texture.generateMipmap();


			texture.bind();
			sphere.draw();
			texture.unbind();
			
		}
		else {
			//fill
			shapeMaterial.begin();
			sphere.draw();
			shapeMaterial.end();

			//Line
			ofSetLineWidth(strokeWidth);
			ofSetColor(strokeColor);
			ofNoFill();
			sphere.draw();
		}
		mapage_tonale.end();

		shapeMaterial.end();

	}

	bool Ball::contains(float x, float y)
	{
		float centerX = position1.x + (position2.x - position1.x) / 2;
		float diameter = position2.x - position1.x;
		float centerY = position1.y + (position2.y - position1.y) / 2;
		return (pow((x - centerX), 2) / pow((diameter / 2), 2)) + (pow((y - centerY), 2) / pow((diameter / 2), 2)) <= 1;
	}

	void Ball::highlight()
	{
		ofSetColor(highlightColor);
		ofNoFill();
		sphere.draw();
	}

	void Ball::translate(float dx, float dy, float dz)
	{
		Shape::translate(dx, dy, dz);
		float centerX = position1.x + (position2.x - position1.x) / 2;
		float diameter = position2.x - position1.x;
		float centerY = position1.y + (position2.y - position1.y) / 2;
		sphere.setPosition(centerX, centerY, 0);
		sphere.setRadius(diameter / 2);
	}

	void Ball::scale(float sx, float sy, float sz)
	{
		Shape::scale(sx, sy, sz);
		float centerX = position1.x + (position2.x - position1.x) / 2;
		float diameter = position2.x - position1.x;
		float centerY = position1.y + (position2.y - position1.y) / 2;
		sphere.setPosition(centerX, centerY, 0);
		sphere.setRadius(diameter / 2);
	}

	void Ball::loadTexture(string p_textureFile)
	{
		ofDisableArbTex();
		ofLoadImage(texture, p_textureFile);
		textureFile = p_textureFile;
		//if the file exists
		//if (FILE *file = fopen(textureFile.c_str(), "r")) {
		//	fclose(file);
		//ofDisableArbTex();
		//	ofLoadImage(texture, p_textureFile);
		//	textureFile = p_textureFile;
		//}
	}
	
	void Ball::removeTexture() {
		texture.clear();
	}
}

