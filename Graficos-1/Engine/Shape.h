#ifndef SHAPE_H
#define SHAPE_H
#include "glew.h"
#include "glfw3.h"
#include "gl/GL.h"

#define DLLEXPORT __declspec(dllexport)

class Vertex
{
private:
	GLfloat x;
	GLfloat y;
public:
	void SetX(GLfloat newx) { x = newx; }
	void SetY(GLfloat newy) { y = newy; }
	GLfloat GetX() { return x; }
	GLfloat GetY() { return y; }
};

class DLLEXPORT Shape
{
private:
	GLuint indices[3];
public:
	void SetIndices(GLuint i[3]);
};

#endif

