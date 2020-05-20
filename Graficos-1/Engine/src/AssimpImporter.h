/* http://assimp.sourceforge.net/lib_html/data.htmlhttp://assimp.sourceforge.net/lib_html/materials.htmlhttp://assimp.sourceforge.net/lib_html/annotated.htmlhttps://learnopengl.com/Lighting/Colorshttps://learnopengl.com/Lighting/Basic-Lightinghttps://learnopengl.com/Lighting/Materials */

#ifndef  ASSIMP_IMPORTER_H
#define ASSIMP_IMPORTER_H

#include <string>
#include <scene.h>   

class Mesh;

class AssimpImporter
{
public:
	bool DoTheImportThing(const std::string& pFile);
	const aiScene* ImportModel(std::string path);
};

#endif // ! ASSIMP_IMPORTER
