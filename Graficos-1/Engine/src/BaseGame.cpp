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
	

	while(!window->GetOpened())
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

void BaseGame::DeInit()
{
	window->DeInit();
	delete window;
}