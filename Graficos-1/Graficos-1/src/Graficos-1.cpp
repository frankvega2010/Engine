#include "Game.h"
#include <iostream>

void main()
{
	Game* g = new Game();
	

	if (g->Start(480, 640, (char*) "sisisi"))
	{
		g->Loop();
	}
	
	g->Stop();

	delete g;

	std::cin.get();
}