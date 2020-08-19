#ifndef BASEGAME_H
#define BASEGAME_H
#include "Renderer.h"
#include "Window.h"
#include <iostream>

#include "Entity3D.h"

using namespace std;

class DLLEXPORT BaseGame {
private:
	static double currentFrame;
	static double lastFrame;
protected:
	Camera* cam;
	Renderer * render;
	virtual bool OnStart() = 0;
	virtual bool OnStop() = 0;
	virtual bool OnUpdate() = 0;
	virtual void OnDraw() = 0;
	static double deltaTime;
	bool loop;
	static Entity3D* rootEntity;
public:
	Window * window;
	bool Start(int h, int w, char* name);
	bool Stop();
	void Loop();
	static float GetDeltaTime();
	static Entity3D* GetRootEntity();
	BaseGame();
	~BaseGame();
};

#endif