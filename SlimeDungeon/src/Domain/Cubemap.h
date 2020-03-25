#pragma once

#include "ofMain.h"
#include <string>


class Cubemap
{
public:
	Cubemap(int p_boxSize = 750);
	void draw();

private:
	glm::mat4x3 nx, ny, nz, px, py, pz;
	void setPositions();
	ofTexture faces[6];
	int m_boxSize;
	glm::mat4x3 positions[6];
};

