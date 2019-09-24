#ifndef BASEGAME_H
#define BASEGAME_H

#define DLLEXPORT __declspec(dllexport)

#include "Window.h"
#include "Input.h"
#include "Renderer.h"

namespace Basegame
{
	class DLLEXPORT BaseGame
	{
	private:
		Window* window;
		Input gameInput;
		Renderer gameRender;
	public:
		void Init();
		void MostrarAlgo();
		void Update();
		void KeyCallback(GLFWwindow* window);
		void DeInit();
	};
}

#endif
