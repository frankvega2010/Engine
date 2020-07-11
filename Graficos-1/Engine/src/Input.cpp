#include "Input.h"

Window* Input::window = NULL;
std::list<int> Input::keysPressedList;

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

bool Input::GetKeyPressedOnce(int key)
{
	if (glfwGetKey(window->GetGLFWWindowPtr(), key) == GLFW_PRESS)
	{
		for(std::list<int>::iterator iterB = keysPressedList.begin();iterB!=keysPressedList.end();++iterB)
		{
			if((*iterB) == key)
			{
				return false;
			}
		}
		keysPressedList.push_front(key);
		return true;
	}
	else
	{
		for (std::list<int>::iterator iterB = keysPressedList.begin(); iterB != keysPressedList.end(); ++iterB)
		{
			if ((*iterB) == key)
			{
				keysPressedList.remove(key);
				return false;
			}
		}
	}
	return false;
}

bool Input::GetKeyReleased(int key)
{
	if (glfwGetKey(window->GetGLFWWindowPtr(), key) == GLFW_PRESS)
	{
		bool found = false;
		for (std::list<int>::iterator iterB = keysPressedList.begin(); iterB != keysPressedList.end(); ++iterB)
		{
			if ((*iterB) == key)
			{
				found = true;
			}
		}
		if (!found)
		{
			keysPressedList.push_front(key);
		}
	}
	else
	{
		for (std::list<int>::iterator iterB = keysPressedList.begin(); iterB != keysPressedList.end(); ++iterB)
		{
			if ((*iterB) == key)
			{
				keysPressedList.remove(key);
				return true;
			}
		}
		
	}
	
	return false;
}
