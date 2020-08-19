#ifndef MODEL_H
#define MODEL_H

#ifndef DLLEXPORT
#define DLLEXPORT __declspec(dllexport)
#endif // !DLLEXPORT

#include "Mesh.h"

#include <assimp/scene.h>

#include "Material.h"

#include <vector>

#include "Entity.h"

#include "Entity3D.h"

#include "BaseGame.h"

#include <iostream>

using namespace std;

unsigned int TextureFromFile(const char *path, const string &directory, bool gamma = false);

class DLLEXPORT Model : public Entity3D
{
public:
	// model data 
	vector<Texture> textures_loaded;	// stores all the textures loaded so far, optimization to make sure textures aren't loaded more than once.
	string directory;
	bool gammaCorrection;

	// constructor, expects a filepath to a 3D model.
	Model(string const &path, bool flipUv, Entity3D* newParent = BaseGame::GetRootEntity(), bool gamma = false);
	~Model();

	// draws the model, and thus all its meshes
	virtual void Draw(Shader shader);

private:
	// loads a model with supported ASSIMP extensions from file and stores the resulting meshes in the meshes vector.
	void loadModel(string const &path, bool flipUv);

	// processes a node in a recursive fashion. Processes each individual mesh located at the node and repeats this process on its children nodes (if any).
	void processNode(aiNode *node, const aiScene *scene, Entity3D* par = BaseGame::GetRootEntity());

	Mesh processMesh(aiMesh *mesh, const aiScene *scene, Entity3D* par = BaseGame::GetRootEntity());

	// checks all material textures of a given type and loads the textures if they're not loaded yet.
	// the required info is returned as a Texture struct.
	vector<Texture> loadMaterialTextures(aiMaterial *mat, aiTextureType type, string typeName);
};


#endif