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

	void Init();
	void SetAttributes();
};

#endif
