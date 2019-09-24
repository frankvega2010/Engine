#ifndef RENDERER_H
#define RENDERER_H

#include "../libs/GLEW/include/glew.h"
#include "../libs/GLFW/include/glfw3.h"
#include "gl/GL.h"

class Renderer
{
private:
	GLuint VertexArrayID;
	GLuint vertexbuffer;
public:

	float rotateX = 0.0f;
	float rotateY = 0.0f;
	float rotateZ = 0.0f;
	float posicionX = 0.0f;
	float posicionY = 0.0f;
	float posicionZ = 0.0f;
	float sizeX = 0.5f;
	float sizeY = 0.5f;
	float sizeZ = 0.5f;
	void Init();
	void SetAttributes();
};

#endif
