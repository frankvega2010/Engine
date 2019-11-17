#ifndef BASEGAME_H
#define BASEGAME_H

#include "Renderer.h"
#include "Window.h"
#include <iostream>

using namespace std;

class DLLEXPORT BaseGame {
private:
	Window * window;
	double currentFrame;
	double lastFrame;
protected:
	Renderer * render;
	virtual bool OnStart() = 0;
	virtual bool OnStop() = 0;
	virtual bool OnUpdate() = 0;
	virtual void OnDraw() = 0;
	double deltaTime;
public:
	bool Start(int h, int w, char* name);
	bool Stop();
	void Loop();
	void GetDeltaTime();
	BaseGame();
	~BaseGame();
};

#endif