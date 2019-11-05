#include "Renderer.h"
#include "loadShaders.h"
#include "glew.h"
#include "gl/GL.h"
#include "glfw3.h"

#include <iostream>

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

GLuint programID;

bool Renderer::Init(Window* w)
{
	window = w;

	glfwMakeContextCurrent(window->GetWindow());

	if (glewInit() != GLEW_OK)
	{
		cout << "murio glew" << endl;
		return -1;
	}

	cout << glGetString(GL_VERSION) << endl;

	glGenVertexArrays(1, &vertexArrayID);
	glBindVertexArray(vertexArrayID);

	orthoProjectionMatrix = glm::ortho(-10.0f, 10.0f, -10.0f, 10.0f, 0.0f, 100.0f);
	projectionMatrix = orthoProjectionMatrix;

	camPos = glm::vec3(0.0f, 0.0f, 1.0f); //donde esta
	eyePos = glm::vec3(0.0f, 0.0f, 0.0f); //donde mira

	viewMatrix = glm::lookAt(camPos, eyePos, glm::vec3(0.0f, 1.0f, 0.0f));

	worldMatrix = glm::mat4(1.0f);

	UpdateWVP();

	return true;

	/////////////////////////////////////////////////////////////////////

	/*unsigned int texture;
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	glTextureParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTextureParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTextureParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTextureParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	int width, height, nrChannels;

	stbi_set_flip_vertically_on_load(true);

	unsigned char* data = stbi_load("res/alien.jpg", &width, &height, &nrChannels, 0);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);

	glGenerateMipmap(GL_TEXTURE_2D);

	stbi_image_free(data);

	glBindTexture(GL_TEXTURE_2D, texture);

	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 9 * sizeof(float), (void*)(7 * sizeof(float)));*/
}

void Renderer::SetAttributes()
{
}

void Renderer::DeInit()
{
	glDeleteProgram(programID);
}


void Renderer::BeginDraw(unsigned int attribID)
{
	glEnableVertexAttribArray(attribID);
}

void Renderer::EndDraw(unsigned int attribID)
{
	glDisableVertexAttribArray(attribID);
}

void Renderer::BindBuffer(unsigned int attribID, unsigned int vtxBuffer, unsigned int size)
{
	glBindBuffer(GL_ARRAY_BUFFER, vtxBuffer);
	glVertexAttribPointer(attribID, size, GL_FLOAT, GL_FALSE, 0, (void*)0);
}

void Renderer::SetClearColor(float r, float g, float b, float a)
{
	glClearColor(r, g, b, a);
}

void Renderer::ClearScreen()
{
	glClear(GL_COLOR_BUFFER_BIT);
}

void Renderer::DrawBuffer(int size, int typeDraw)
{
	glDrawArrays(typeDraw, 0, size);
}

void Renderer::LoadIMatrix()
{
	worldMatrix = glm::mat4(1.0f);
}

void Renderer::SetWMatrix(glm::mat4 matrix)
{
	worldMatrix = matrix;
	UpdateWVP();
}

void Renderer::UpdateWVP()
{
	WVPMatrix = projectionMatrix * viewMatrix * worldMatrix;
}