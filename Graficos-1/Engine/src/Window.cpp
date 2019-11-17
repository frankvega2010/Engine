#include "Window.h"

using namespace glm;

bool Window::Start(int width, int height, const char* name)
{
	if (!glfwInit())
	{
		fprintf(stderr, "Failed to initialize GLFW\n");
		return false;
	}

	glfwWindowHint(GLFW_SAMPLES, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); //macos
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	window = glfwCreateWindow(width, height, name, NULL, NULL);

	if (window == NULL) {
		fprintf(stderr, "Failed to open GLFW window. If you have an Intel GPU, they are not 3.3 compatible. Try the 2.1 version of the tutorials.\n");
		glfwTerminate();
		return false;
	}

	

	return true;
}

bool Window::Stop()
{
	if (window != NULL)
		glfwDestroyWindow((GLFWwindow*)window);
	window = NULL;
	glfwTerminate();
	return true;
}

bool Window::ShouldClose()
{
	if(window)
		return glfwWindowShouldClose((GLFWwindow*)window);
	
}

void Window::PollEvents()
{
	glfwPollEvents();
}

Window::Window()
{
}

Window::~Window()
{
}