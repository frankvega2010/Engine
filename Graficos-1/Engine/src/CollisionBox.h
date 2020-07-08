#ifndef COLLISION_BOX_H
#define COLLISION_BOX_H

#include <vector>

#include "glm.hpp"

#define DLLEXPORT _declspec(dllexport)

using namespace glm;

#define TOTALVERTICES 8

class Shader;


struct Bounds
{
	float minX = INT32_MAX;
	float minY = INT32_MAX;
	float minZ = INT32_MAX;
	float maxX = INT32_MIN;
	float maxY = INT32_MIN;
	float maxZ = INT32_MIN;
};


class DLLEXPORT CollisionBox
{
private:
	vec3 vertices[TOTALVERTICES];
	unsigned int vao, vbo, ebo;
	std::vector<unsigned int> indicesVector;
public:
	CollisionBox();
	~CollisionBox();
	void GenerateBoundingBox(Bounds b, mat4 modelMat);
	void SetBounds(int boundIndex, vec3 newBoundValue);
	void GenerateBuffers();
	void DrawCollisionBox();
	static Shader* wireframeShader;
	void Setup();
};

#endif
