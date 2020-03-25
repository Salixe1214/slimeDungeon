#pragma once

#include "ofMain.h"
#include <string>

glm::mat4x3 nx = {
	-1, 1, 1,
	-1, 1, -1,
	-1, -1, -1,
	-1, -1, 1
};

glm::mat4x3 ny = {
	-1, -1, -1,
	1, -1, -1,
	1, -1, 1,
	-1, -1, 1
}; 

glm::mat4x3 nz = {
	-1, 1, -1,
	1, 1, -1,
	1, -1, -1,
	-1, -1, -1
};

glm::mat4x3 px = {
	1, 1, -1,
	1, 1, 1,
	1, -1, 1,
	1, -1, -1
};

glm::mat4x3 py = -1 * ny;

glm::mat4x3 pz = {
	1, 1, 1,
	-1, 1, -1,
	-1, -1, -1,
	1, -1, -1
};

class Cubemap
{
public:
	Cubemap(int p_boxSize = 1000);
	void draw();

private:
	ofTexture faces[6];
	int m_boxSize;
	glm::mat4x3 positions[6];
};

