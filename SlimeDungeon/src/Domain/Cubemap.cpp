#include "Cubemap.h"

Cubemap::Cubemap(int p_boxSize): m_boxSize(p_boxSize)
{
	ofDisableArbTex();

	setPositions();

	// Attribution des matrices de positions dans une liste pour le for du draw
	positions[0] = p_boxSize * nx;
	positions[1] = p_boxSize * nz;
	positions[2] = p_boxSize * px;
	positions[3] = p_boxSize * pz;
	positions[4] = p_boxSize * py;
	positions[5] = p_boxSize * ny;

	// Loading textures
	// 0 nx
	// 1 nz
	// 2 px
	// 3 pz
	// 4 ny
	// 5 py
	// p/n_ -> positive/negative + axis
	ofLoadImage(faces[0], "skybox/face_0.jpg");
	ofLoadImage(faces[1], "skybox/face_1.jpg");
	ofLoadImage(faces[2], "skybox/face_2.jpg");
	ofLoadImage(faces[3], "skybox/face_3.jpg");
	ofLoadImage(faces[5], "skybox/face_4.jpg");
	ofLoadImage(faces[4], "skybox/face_5.jpg");
}

void Cubemap::draw()
{
	ofSetColor(ofColor::white);
	for (unsigned int i = 0; i < 6; i++) {
		faces[i].draw(positions[i][0], positions[i][1], positions[i][2], positions[i][3]);
	}
}

void Cubemap::setPositions()
{
	nx = {
	-1, -1, 1,
	-1, -1, -1,
	-1, 1, -1,
	-1, 1, 1
	};

	ny = {
		-1, -1, 1,
		1, -1, 1,
		1, -1, -1,
		-1, -1, -1
	};

	nz = {
		-1, -1, -1,
		1, -1, -1,
		1, 1, -1,
		-1, 1, -1
	};

	px = {
		1, -1, -1,
		1, -1, 1,
		1, 1, 1,
		1, 1, -1
	};

	py = -1 * ny;

	pz = {
		1, -1, 1,
		-1, -1, 1,
		-1, 1, 1,
		1, 1, 1
	};
}
