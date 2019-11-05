#ifndef BASEGAME_H
#define BASEGAME_H

#define DLLEXPORT __declspec(dllexport)

#include "Window.h"

class Renderer;

class DLLEXPORT BaseGame
{
private:
	Window* window;
	Renderer* renderer;
public:
	bool Init();
	void MostrarAlgo();
	void Update();
	void DeInit();
};

#endif
