#include "Window.h"

using namespace glm;

bool Window::Start(int w, int h, const char* name)
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
	glfwWindow = glfwCreateWindow(w, h, name, NULL, NULL);

	if (glfwWindow == NULL) {
		fprintf(stderr, "Failed to open GLFW window. If you have an Intel GPU, they are not 3.3 compatible. Try the 2.1 version of the tutorials.\n");
		glfwTerminate();
		return false;
	}

	width = w;
	heigth = h;

	return true;
}

bool Window::Stop()
{
	if (glfwWindow != NULL)
		glfwDestroyWindow((GLFWwindow*)glfwWindow);
	glfwWindow = NULL;
	glfwTerminate();
	return true;
}

bool Window::ShouldClose()
{
	if(glfwWindow)
		return glfwWindowShouldClose((GLFWwindow*)glfwWindow);
	
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