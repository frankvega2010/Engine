#include "BaseGame.h"
#include <iostream>
#include "Window.h"
#include "Renderer.h"
#include <ctime>
#include "glew.h"
#include "glfw3.h"

using namespace Basegame;

Renderer r;

void BaseGame::MostrarAlgo()
{
	std::cout << "heh" << std::endl;
}

void BaseGame::Init()
{
	window = new Window(640, 480, "Ventana");
	window->Init();
}

void BaseGame::Update()
{
	glewExperimental = true;
	glewInit();

	r.Init();

	while(!window->GetOpened())
	{
		window->Clear();

		r.SetAttributes();

		if (glfwGetKey(window->GetWindow(), GLFW_KEY_RIGHT) == GLFW_PRESS)
		{
			r.Translate(1.0f, glm::vec3(1.0f, 0.0f, 0.0f));
		}

		if (glfwGetKey(window->GetWindow(), GLFW_KEY_LEFT) == GLFW_PRESS)
		{
			r.Translate(1.0f, glm::vec3(-1.0f, 0.0f, 0.0f));
		}

		if (glfwGetKey(window->GetWindow(), GLFW_KEY_A) == GLFW_PRESS)
		{
			r.Rotate(1.0f, glm::vec3(1.0f, 0.0f, 0.0f));
		}

		if (glfwGetKey(window->GetWindow(), GLFW_KEY_S) == GLFW_PRESS)
		{
			r.Rotate(1.0f, glm::vec3(0.0f, 1.0f, 0.0f));
		}

		if (glfwGetKey(window->GetWindow(), GLFW_KEY_D) == GLFW_PRESS)
		{
			r.Rotate(1.0f, glm::vec3(0.0f, 0.0f, 1.0f));
		}

		glDrawElements(GL_TRIANGLES, 24, GL_UNSIGNED_INT, nullptr);

		window->SwapBuffers();

		window->PollEvents();
	}
}

void BaseGame::DeInit()
{
	r.DeInit();
	window->DeInit();
	delete window;
}