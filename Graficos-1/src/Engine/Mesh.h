#ifndef MESH_H
#define MESH_H

#define DLLEXPORT _declspec(dllexport)

#include <string>
//#include <fstream>
//#include <sstream>
//#include <iostream>
#include <vector>
#include "Shader.h"
#include <glm.hpp>

#include "Entity3D.h"
//#include <gtc/matrix_transform.hpp>

using namespace std;

struct Vertex {
	// position
	glm::vec3 Position;
	// normal
	glm::vec3 Normal;
	// texCoords
	glm::vec2 TexCoords;
	// tangent
	glm::vec3 Tangent;
	// bitangent
	glm::vec3 Bitangent;
};

struct Texture {
	unsigned int id;
	string type;
	string path;
};

class DLLEXPORT Mesh : public Entity3D
{
public:
	// mesh Data
	vector<Vertex>       vertices;
	vector<unsigned int> indices;
	vector<Texture>      textures;
	unsigned int VAO;

	// constructor
	Mesh(vector<Vertex> vertices, vector<unsigned int> indices, vector<Texture> textures, Entity3D* par);

	~Mesh();
	
	// render the mesh
	void Draw(Shader shader);

	void GetVerticesPositions(vector<vec3> &vertices);

private:
	// render data 
	unsigned int VBO, EBO;

	// initializes all the buffer objects/arrays
	void setupMesh();
};
#endif
