#include "Pixel.h"
namespace shape {

	Pixel::Pixel(VectorPrimitiveType p_shapeType, float x1, float y1, ofColor p_fillColor)
		:Shape(p_shapeType, floorf(x1), floorf(y1), x1 + 1, y1 + 1, p_fillColor, ofColor(0,0,0,0), 1)
	{
		static int numPixel;
		numPixel++;
		shapeId = "pixel" + std::to_string(numPixel);
	}

	//Constructeur pour les formes temporaires
	Pixel::Pixel(VectorPrimitiveType p_shapeType, float x1, float y1,ofColor p_fillColor, bool sampleShape)
		:Shape(p_shapeType, x1, y1, x1 + 1, y1 + 1, p_fillColor, ofColor(0, 0, 0, 0), 1)
	{
	}

	void Pixel::draw()
	{
		ofFill();
		ofSetLineWidth(0);
		ofSetColor(fillColor);
		ofDrawRectangle(position1.x, position1.y, 1, 1);
	}

	bool Pixel::contains(float x, float y)
	{
		return (x > position1.x) && (x < position2.x) && (y > position1.y) && (y < position2.y);
	}

	void Pixel::highlight()
	{
		ofSetColor(highlightColor);
		ofFill();
		ofDrawRectangle(position1.x, position1.y, 1, 1);
	}
}
