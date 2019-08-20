#include "Game.h"
#include <iostream>

void main()
{
	BaseGame g;
	g.Init();
	g.Update();
	g.DeInit();
	std::cin.get();
}