#include "BaseGame.h"
#include <iostream>
#include "Window.h"
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
	while(!window->GetOpened())
	{
		window->SetBackgroundColor(rand() % 2, rand() % 2, rand() % 2, 1);
		window->Clear();
		window->SwapBuffers();
		window->PollEvents();
	}
}

void BaseGame::DeInit()
{
	window->DeInit();
}