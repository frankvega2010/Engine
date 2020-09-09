#include "Game.h"
#include <iostream>

void main()
{
	Game* g = new Game();
	

	if (g->Start(600, 800, (char*) "BOCA JUNIORS"))
	{
		g->Loop();
	}
	
	g->Stop();

	delete g;

	std::cin.get();
}