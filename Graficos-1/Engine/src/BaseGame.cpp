#include "BaseGame.h"
#include "Input.h"
#include "ColisionManager.h"
BaseGame::BaseGame() {

}
BaseGame::~BaseGame() {
}
bool BaseGame::Start(int h, int w, char* name) {
	cout << "GameBase::Start()" << endl;

	window = new Window();
	if (!window->Start(w, h, name))
		return false;

	/*collisionManager = new ColisionManager();*/
	 
	render = new Renderer();
	if (!render->Start(window))
		return false;
	render->setClearScreenColor(0.0f, 0.0f, 4.0f, 0.0f);
	render->ClearScreen();

	Input::SetWindow(window);

	return OnStart();
}
void BaseGame::Loop() {
	bool loop = true;
	while (loop && !window->ShouldClose()) {
		GetDeltaTime();
		loop = OnUpdate();
		render->ClearScreen();
		OnDraw();
		render->SwapBuffer();
		window->PollEvents();
		/*collisionManager->CheckCollision(shape1, shape2);*/
	}
}

void BaseGame::GetDeltaTime() {
	currentFrame = glfwGetTime();
	deltaTime = currentFrame - lastFrame;
	lastFrame = currentFrame;
}

bool BaseGame::Stop() {
	cout << "GameBase::Stop()" << endl;
	OnStop();
	render->Stop();
	window->Stop();

	delete render;
	delete window;
	return true;
}


