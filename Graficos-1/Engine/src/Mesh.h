#ifndef MESH_H
#define MESH_H

#define EXPORTDLL _declspec(dllexport)

#include <string>
//#include <fstream>
//#include <sstream>
//#include <iostream>
#include <vector>
#include "Shader.h"
#include <glm.hpp>
//#include <gtc/matrix_transform.hpp>

using namespace std;

class LoadShader;

struct Vertex {
	glm::vec3 position;
	glm::vec3 normal;
	glm::vec2 texCoords;
};

struct Texture {
	unsigned int id;
	string type;
	string path;
};

class EXPORTDLL Mesh {
public:
	// mesh data
	vector<Vertex>       vertices;
	vector<unsigned int> indices;
	vector<Texture>      textures;

	Mesh(vector<Vertex> vertices, vector<unsigned int> indices, vector<Texture> textures);
	void Draw(Shader shader);
private:
	//  render data
	unsigned int VAO, VBO, EBO;

	void SetupMesh();
};
#endif
