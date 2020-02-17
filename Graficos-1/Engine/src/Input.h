#ifndef INPUT_H
#define INPUT_H

#include "glew.h"
#include "glfw3.h"
#include "Window.h"

//#define DLLEXPORT __declspec(dllexport)

class ENGINE_API Input
{
private:
	//static Window* window;
	static Window *win;
public:
	Input(Window *window);
	static bool GetKeyPressed(int key);
	static bool SetWindow(Window* w);
};

#endif