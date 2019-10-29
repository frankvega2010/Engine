#include "Renderer.h"
#include "loadShaders.h"
#include "glew.h"
#include "glfw3.h"
#include "gl/GL.h"

#include <iostream>

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

GLuint programID;

void Renderer::Init()
{
	GLfloat g_vertex_buffer_data[] = {
		-160.0f, -120.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f,
		   0.0f, -120.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.5f, 0.0f,
		 160.0f, -120.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f,
		 160.0f,    0.0f, 0.0f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f, 0.5f,
		 160.0f,  120.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f,
		   0.0f,  120.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.5f, 1.0f,
		-160.0f,  120.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f,
		-160.0f,    0.0f, 0.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f, 0.5f,
		   0.0f,    0.0f, 0.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.5f, 0.5f
	};

	unsigned int indices[] = {
		0,1,7,
		1,8,7,
		1,2,3,
		3,8,1,
		3,4,5,
		3,8,5,
		5,6,7,
		5,8,7
	};

	GLuint vertexbuffer;
	glGenBuffers(1, &vertexbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data), g_vertex_buffer_data, GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	//1rst attribute buffer : vértices
	//glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
	glVertexAttribPointer(
		0,                  // atributo 0. No hay razón particular para el 0, pero debe corresponder en el shader.
		4,                  // tamaño
		GL_FLOAT,           // tipo
		GL_FALSE,           // normalizado?
		9 * sizeof(float),  // Paso
		(void*)0            // desfase del buffer
	);

	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 9 * sizeof(float), (void*)(4 * sizeof(float)));

	GLuint indexBufferObject;
	glGenBuffers(1, &indexBufferObject);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBufferObject);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	programID = LoadShaders("src/SimpleVertexShader.vertexshader", "src/SimpleFragmentShader.fragmentshader");
	glUseProgram(programID);

	myMatrix = glm::mat4(1.0f);

	glm::mat4 proj = glm::ortho(-320.0f, 320.0f, -240.0f, 240.0f, -100.0f, 100.0f);

	GLuint pMat = glGetUniformLocation(programID, "u_P");
	glUniformMatrix4fv(pMat, 1, GL_FALSE, glm::value_ptr(proj));

	glm::mat4 view = glm::translate(myMatrix, glm::vec3(0.0f, 0.0f, 0.0f));

	GLuint vMat = glGetUniformLocation(programID, "u_V");
	glUniformMatrix4fv(vMat, 1, GL_FALSE, glm::value_ptr(view));

	uniModel = glGetUniformLocation(programID, "u_M");
	glUniformMatrix4fv(uniModel, 1, GL_FALSE, glm::value_ptr(myMatrix));

	/////////////////////////////////////////////////////////////////////

	unsigned int texture;
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
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 9 * sizeof(float), (void*)(7 * sizeof(float)));
}

void Renderer::SetAttributes()
{
}

void Renderer::DeInit()
{
	glDeleteProgram(programID);
}

void Renderer::Rotate(float angle, glm::vec3 axis)
{
	myMatrix = glm::rotate(myMatrix, glm::radians(angle), axis);
	glUniformMatrix4fv(uniModel, 1, GL_FALSE, glm::value_ptr(myMatrix));
}

void Renderer::Scale(glm::vec3 scaleValues)
{
	myMatrix = glm::scale(myMatrix, scaleValues);
	glUniformMatrix4fv(uniModel, 1, GL_FALSE, glm::value_ptr(myMatrix));
}

void Renderer::Translate(float value, glm::vec3 axis)
{
	myMatrix = glm::translate(myMatrix, value * axis);
	glUniformMatrix4fv(uniModel, 1, GL_FALSE, glm::value_ptr(myMatrix));
}