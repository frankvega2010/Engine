#ifndef GAME_H
#define GAME_H

#include "BaseGame.h"

class Game : public BaseGame
{
private:
public:
	bool OnStart();
	bool OnStop();
	bool OnUpdate();
	void OnDraw();
};

#endif
