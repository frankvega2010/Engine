#ifndef INPUT_H
#define INPUT_H

#include "glew.h"
#include "glfw3.h"
#include "Window.h"

#define DLLEXPORT __declspec(dllexport)

class DLLEXPORT Input
{
private:
	static Window* window;
public:
	static bool GetKeyPressed(int key);
	static bool SetWindow(Window* w);
};

#endif