#include "Renderer.h"


/*
* @brief Importe l'image sous le nom de fichier passé en argument.
*/
ofImage Renderer::imageImport(const string filename) {
	return ofImage(filename);
}


/*
* @brief Exporte une image sous le nom passé en argument.
*/
void Renderer::imageExport(ofImage toExportImg, string filename) const
{
	toExportImg.save(filename);
}
