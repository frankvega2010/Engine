#ifndef RENDERER_H
#define RENDERER_H

#include "Window.h"

#include <vector>
#include "glm.hpp"
#include "gtc/matrix_transform.hpp"
#include "gtx/transform.hpp"
#include "gtc/type_ptr.hpp"
#include "glew.h"
#include "glfw3.h"

using namespace std;
using namespace glm;

#define DLLEXPORT __declspec(dllexport)

class DLLEXPORT Renderer
{
private:

	Window* window;

	unsigned int vertexArrayID;
	unsigned int colorVertexArrayID;
	mat4 worldMatrix;
	mat4 viewMatrix;
	mat4 projectionMatrix;
	mat4 orthoProjectionMatrix;
	mat4 WVPMatrix;

	vec3 camPos;
	vec3 eyePos;
	vec3 upPos;

public:
	bool Init(Window* w);
	void SetAttributes();
	void DeInit();
	void SetClearColor(float r, float g, float b, float a);
	void ClearScreen();
	void Rotate(float angle, glm::vec3 axis);
	void Translate(float value, glm::vec3 axis);
	void Scale(glm::vec3 scaleValues);
	void BeginDraw(unsigned int attribID);
	void EndDraw(unsigned int attribID);
	void BindBuffer(unsigned int attribID, unsigned int vtxBuffer, unsigned int size);
	void DrawBuffer(int size, int typeDraw);
	void LoadIMatrix();
	void SetWMatrix(glm::mat4 matrix);
	void UpdateWVP();
};

#endif
