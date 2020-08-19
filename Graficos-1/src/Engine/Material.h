#ifndef MATERIAL_H
#define MATERIAL_H

#include "glew.h"
#include "glfw3.h"
#include<glm.hpp>
#include<gtc\matrix_transform.hpp>

#define DLLEXPORT __declspec(dllexport)

using namespace glm;
using namespace std;

class DLLEXPORT Material
{
	unsigned int ProgramID;
	unsigned int matrixID;
	unsigned int textureId;

public:
	Material();
	~Material();
	unsigned int LoadShaders(const char * vertex_file_path, const char * fragment_file_path);
	void Bind(const char* name);
	void SetMatrixProperty(mat4& mat);
	void BindTexture(const char* name);
	void BindProgram();
};

#endif