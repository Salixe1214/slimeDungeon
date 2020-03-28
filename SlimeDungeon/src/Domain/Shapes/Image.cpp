#include "Image.h"
namespace shape {

	Image::Image(VectorPrimitiveType p_shapeType, float x1, float y1, float x2, float y2, ofImage p_image,
		ofColor p_fillColor, ofColor p_strokeColor, float p_strokeWidth, glm::vec3 p_rotation)
		:Shape(p_shapeType, x1, y1, x2, y2, p_fillColor, p_strokeColor, p_strokeWidth)
	{
		image = p_image;
		static int numImage;
		numImage++;
		shapeId = "Image" + std::to_string(numImage);
		//shader d'image
		gaussianBlur.load("gaussianBlur.glsl");
		
	}

	

	void Image::draw()
	{
		gaussianBlur.begin();
		gaussianBlur.setUniformTexture("texture", image.getTexture(), 1);
		gaussianBlur.setUniform1i("kernelSize", 32);
		gaussianBlur.setUniform1f("strength", 7.0);
		gaussianBlur.setUniform1i("horizontalPass", 1);
		
		
		ofNoFill();
		ofSetColor(ofColor::white);
		ofSetLineWidth(0);
		
		image.draw(position1.x, position1.y);
		gaussianBlur.end();
		//image.draw(position1.x + 500, position1.y);
	}

	bool Image::contains(float x, float y)
	{
		return (x > position1.x) && (x < position2.x) && (y > position1.y) && (y < position2.y);
	}

	void Image::highlight()
	{
		ofSetColor(highlightColor);
		ofNoFill();
		ofDrawRectangle(position1.x, position1.y, position2.x - position1.x, position2.y - position1.y);
	}
}
