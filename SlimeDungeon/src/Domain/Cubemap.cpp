#include "Cubemap.h"

Cubemap::Cubemap(int p_boxSize): m_boxSize(p_boxSize)
{
	ofDisableAlphaBlending();
	ofEnableDepthTest();
	ofDisableArbTex();

	// Attribution des matrives de positions dans une liste pour le for du draw
	positions[0] = nx;
	positions[1] = nz;
	positions[2] = px;
	positions[3] = pz;
	positions[4] = ny;
	positions[5] = py;

	// Loading textures
	// 0 nx
	// 1 nz
	// 2 px
	// 3 pz
	// 4 ny
	// 5 py
	// p/n_ -> positive/negative + axis
	for (unsigned int i = 0; i < 6; i++) {
		ofLoadImage(faces[i], "skybox\face_" + to_string(i) + ".jpg");
	}
}

void Cubemap::draw()
{
	for (unsigned int i = 0; i < 6; i++) {
		faces[i].draw(positions[i][0], positions[i][1], positions[i][2], positions[i][3]);
	}
}
