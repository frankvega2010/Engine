#include "BaseGame.h"
#include <iostream>
#include "Window.h"
#include "Renderer.h"
#include <ctime>

using namespace Basegame;

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

	Renderer r;
	r.Init();

	// Identificar el vertex buffer

	// Generar un buffer, poner el resultado en el vertexbuffer que acabamos de crear


	while (!window->GetOpened())
	{
		//window->SetBackgroundColor(rand() % 2, rand() % 2, rand() % 2, 1);

		window->Clear();
		r.SetAttributes();
		// Dibujar el triángulo !
		glDrawArrays(GL_TRIANGLES, 0, 3); // Empezar desde el vértice 0S; 3 vértices en total -> 1 triángulo
		glDisableVertexAttribArray(0);

		window->SwapBuffers();
		window->PollEvents();
	}
}

void BaseGame::KeyCallback(GLFWwindow* window) {
	//======================================== MOVIMIENTO ========================================
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
	{
		gameRender.posicionY = gameInput.keyW(gameRender.posicionY);
	}
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
	{
		gameRender.posicionY = gameInput.keyS(gameRender.posicionY);
	}
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
	{
		gameRender.posicionX = gameInput.keyA(gameRender.posicionX);
	}
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
	{
		gameRender.posicionX = gameInput.keyD(gameRender.posicionX);
	}
	//======================================== TAMANO ========================================

	if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
	{
		gameRender.sizeY = gameInput.keyRIGHT(gameRender.sizeY);
	}
	if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
	{
		gameRender.sizeY = gameInput.keyLEFT(gameRender.sizeY);

	}
	if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS)
	{
		gameRender.sizeX = gameInput.keyDOWN(gameRender.sizeX);
	}
	if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS)
	{
		gameRender.sizeX = gameInput.keyUP(gameRender.sizeX);
	}
	//======================================== ROTACIONES ========================================
	//x
	if (glfwGetKey(window, GLFW_KEY_U) == GLFW_PRESS)
	{
		gameRender.rotateX = gameInput.keyU(gameRender.rotateX);
	}
	if (glfwGetKey(window, GLFW_KEY_Y) == GLFW_PRESS)
	{
		gameRender.rotateX = gameInput.keyY(gameRender.rotateX);
	}
	//y
	if (glfwGetKey(window, GLFW_KEY_H) == GLFW_PRESS)
	{
		gameRender.rotateY = gameInput.keyH(gameRender.rotateY);
	}
	if (glfwGetKey(window, GLFW_KEY_J) == GLFW_PRESS)
	{
		gameRender.rotateY = gameInput.keyJ(gameRender.rotateY);
	}
	//z
	if (glfwGetKey(window, GLFW_KEY_N) == GLFW_PRESS)
	{
		gameRender.rotateZ = gameInput.keyN(gameRender.rotateZ);
	}
	if (glfwGetKey(window, GLFW_KEY_M) == GLFW_PRESS)
	{
		gameRender.rotateZ = gameInput.keyM(gameRender.rotateZ);
	}
	//========================================CERRAR VENTANA========================================
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
	{
		gameInput.keyEsc(window);

	}
}

void BaseGame::DeInit()
{
	window->DeInit();
	delete window;
}