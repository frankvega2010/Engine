#ifndef BASEGAME_H
#define BASEGAME_H

#define DLLEXPORT __declspec(dllexport)

#include "Window.h"

namespace Basegame
{
	class DLLEXPORT BaseGame
	{
	private:
		Window* window;
	public:
		void Init();
		void MostrarAlgo();
		void Update();
		void DeInit();
	};
}

#endif
