#include "Window.h"
#include <iostream>
#include "glew.h"
#include "glfw3.h"

using namespace std;


	Window::Window(int w, int h, const char* n)
	{
		width = w;
		height = h;
		name = n;
	}

	Window::~Window()
	{
		//delete window;
	}

	void Window::Init()
	{
		glfwInit();
		
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_COMPAT_PROFILE);

		
		window = glfwCreateWindow(width, height, name, NULL, NULL);
		if (!window)
			glfwTerminate();
		
		
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
		glfwSwapBuffers(window);//cambia los front buffers y los back buffers
	}

	void Window::PollEvents()
	{
		glfwPollEvents();//espera inputs o "events"
	}

	void Window::SetBackgroundColor(int r, int g, int b, int a)
	{
		glClearColor(r, g, b, a);
	}

	GLFWwindow* Window::GetWindow()
	{
		return window;
	}
