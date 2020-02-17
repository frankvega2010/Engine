#include "Input.h"

//Window* Input::window = NULL;
Input::Input(Window *window)
{
	win = window;
}

bool Input::SetWindow(Window* w)
{
	win = w;
	if (win)
		return true;

	return false;
}

bool Input::GetKeyPressed(int key)
{
	if (glfwGetKey((GLFWwindow*)win->GetWindowPtr(), key) == GLFW_PRESS)
	{
		return true;
	}
	return false;
}