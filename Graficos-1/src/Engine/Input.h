#ifndef INPUT_H
#define INPUT_H

#include <list>

#include "glew.h"
#include "glfw3.h"
#include "Window.h"

#define DLLEXPORT __declspec(dllexport)

class DLLEXPORT Input
{
private:
	static Window* window;
	static std::list<int> keysPressedList;
public:
	static bool GetKeyPressed(int key);
	static bool GetKeyPressedOnce(int key);
	static bool GetKeyReleased(int key);
	static bool SetWindow(Window* w);
};

#endif