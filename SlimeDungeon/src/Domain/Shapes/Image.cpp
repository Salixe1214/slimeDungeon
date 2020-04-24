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
		// shader d'image
		//gaussianBlur.load("gaussianBlur.glsl");
		tonalMapping.load("mapage_tonale_330_vs.glsl", "mapage_tonale_330_fs.glsl"/*"image_filter_330_vs.glsl", "image_filter_330_fs.glsl"*/);
		
	}

	

	void Image::draw()
	{
		
		tonalMapping.begin();
		tonalMapping.setUniformTexture("image", image.getTexture(), 1);
		// shader.setUniform3f("tint", 159.0f, 178.0f, 0.0f);
		// shader.setUniform1f("factor", 0.618f);
		/*gaussianBlur.begin();
		gaussianBlur.setUniformTexture("texture", image.getTexture(), 1);
		gaussianBlur.setUniform1i("kernelSize", 32);
		gaussianBlur.setUniform1f("strength", 7.0);
		gaussianBlur.setUniform1i("horizontalPass", 1);
		gaussianBlur.setUniform1i("horizontalPass", 0);*/
		
		ofNoFill();
		ofSetColor(ofColor::white);
		ofSetLineWidth(0);
		
		image.draw(position1.x, position1.y);
		tonalMapping.end();
		//gaussianBlur.end();
		
		
		int numPix = image.getWidth() * image.getHeight();
		for (size_t i = 0; i < numPix; i++)
		{
			ofColor colorTmp;
			colorTmp = image.getColor(i);
			colorTmp.setBrightness(50);
			image.setColor(i,colorTmp);
		}
		

		
		
		
		image.draw(position1.x + 500, position1.y);
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
