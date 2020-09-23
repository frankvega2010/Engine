/* http://assimp.sourceforge.net/lib_html/data.html

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