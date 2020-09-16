#include "Game.h"
#include <iostream>

void main()
{
	Game* g = new Game();
	

	if (g->Start(600, 800, (char*) "Boke Engine Mark II"))
	{
		g->Loop();
	}
	
	g->Stop();

	delete g;

	std::cin.get();
}