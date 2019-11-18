#ifndef BASEGAME_H
#define BASEGAME_H
#include "ColisionManager.h"
#include "Renderer.h"
#include "Window.h"
#include <iostream>

using namespace std;

class DLLEXPORT BaseGame {
private:
	
	double currentFrame;
	double lastFrame;
protected:
	Renderer * render;
	CollisionManager * colisionManager;
	virtual bool OnStart() = 0;
	virtual bool OnStop() = 0;
	virtual bool OnUpdate() = 0;
	virtual void OnDraw() = 0;
	double deltaTime;
public:
	Window * window;
	bool Start(int h, int w, char* name);
	bool Stop();
	void Loop();
	void GetDeltaTime();
	BaseGame();
	~BaseGame();
};

#endif