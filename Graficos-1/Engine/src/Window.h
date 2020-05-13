#ifndef WINDOW_H
#define WINDOW_H

#include <stdio.h>
#include <stdlib.h>
#include "glew.h"
#include <glfw3.h>
#include <glm.hpp>

#define DLLEXPORT __declspec(dllexport)

class DLLEXPORT Window
{
private: 
	GLFWwindow * glfwWindow;
	int width;
	int heigth;
public:
	Window();
	~Window();
	bool Start(int w, int h, const char* name);
	bool Stop();
	int GetWidth() { return width; }
	int GetHeigth() { return heigth; }
	GLFWwindow* GetGLFWWindowPtr() { return glfwWindow; }
	bool ShouldClose();
	void PollEvents();
};
#endif

