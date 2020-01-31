#include "Renderer.h"


Renderer::Renderer() 
{

}


void Renderer::setup()
{
	//CaptureTool
	recordMode = false;
}

void Renderer::update()
{
}

void Renderer::draw()
{
}


/*
* @brief Importe l'image sous le nom de fichier passé en argument.
*/
ofImage Renderer::imageImport(const string filename) {
	return ofImage(filename);
}


/*
* @brief Exporte une image sous le nom passé en argument.
*/
void Renderer::exportImg(ofImage imgToExport, string filename) const
{
	imgToExport.save(filename);
}

void Renderer::videoExport() {
	//TODO
}


