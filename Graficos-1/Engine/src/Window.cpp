#include "Window.h"
#include <iostream>

namespace Basegame
{
	Window::Window(int w, int h, const char* n)
	{
		width = w;
		height = h;
		name = n;
	}

	Window::~Window()
	{

	}

	void Window::Init()
	{
		glfwInit();
		window = glfwCreateWindow(width, height, name, NULL, NULL);
		if (!window)
			glfwTerminate();

		glfwMakeContextCurrent(window);
	}

	void Window::DeInit()
	{
		glfwTerminate();
	}

	bool Window::GetOpened()
	{
		return glfwWindowShouldClose(window);
	}

	void Window::Clear()
	{
		glClear(GL_COLOR_BUFFER_BIT);
	}

	void Window::SwapBuffers()
	{
		glfwSwapBuffers(window);
	}

	void Window::PollEvents()
	{
		glfwPollEvents();
	}

	void Window::SetBackgroundColor(int r, int g, int b, int a)
	{
		glClearColor(r, g, b, a);
	}
}