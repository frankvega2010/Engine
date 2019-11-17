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
	GLFWwindow * window;
public:
	Window();
	~Window();
	bool Start(int width, int height, const char* name);
	bool Stop();
	GLFWwindow* GetWindowPtr() { return window; }
	bool ShouldClose();
	void PollEvents();	
};
#endif

