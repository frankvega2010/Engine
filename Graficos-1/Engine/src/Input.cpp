#include "Input.h"

Window* Input::window = NULL;

bool Input::SetWindow(Window* w)
{
	window = w;
	if (window)
		return true;

	return false;
}

bool Input::GetKeyPressed(int key)
{
	if (glfwGetKey(window->GetGLFWWindowPtr(), key) == GLFW_PRESS)
	{
		return true;
	}
	return false;
}