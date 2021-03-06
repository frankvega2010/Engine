#include "BaseGame.h"
#include "Input.h"
#include "CollisionBox.h"

double BaseGame::currentFrame = 0.0f;
double BaseGame::lastFrame = 0.0f;
double BaseGame::deltaTime = 0.0f;


Entity3D* BaseGame::rootEntity = nullptr;


BaseGame::BaseGame() {

}
BaseGame::~BaseGame() {
}
bool BaseGame::Start(int h, int w, char* name) {
	cout << "GameBase::Start()" << endl;

	window = new Window();
	if (!window->Start(w, h, name))
		return false;
	 
	render = new Renderer();
	if (!render->Start(window))
		return false;
	render->setClearScreenColor(0.0f, 1.0f, 0.0f, 1.0f);
	render->ClearScreen();

	Input::SetWindow(window);

	cam = render->GetCam();

	glfwSetInputMode(window->GetGLFWWindowPtr(), GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	lastFrame = 0.0f;

	rootEntity = new Entity3D("root");
	rootEntity->SetIsRoot(true);

	CollisionBox::wireframeShader = new Shader("res/shaders/SimpleVertexShader.txt", "res/shaders/SimpleFragmentShader.txt");
	
	return OnStart();
}

void BaseGame::Loop() {
	loop = true;
	while (loop && !window->ShouldClose()) {
		//------------------------------
		currentFrame = glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;
		//------------------------------
		loop = OnUpdate();
		render->f->UpdateFrustum(render->GetProjMatrix() * cam->GetViewMatrix());
		render->ClearScreen();
		OnDraw();
		render->SwapBuffer();
		window->PollEvents();
		//system("cls");
	}
}

float BaseGame::GetDeltaTime() {

	return deltaTime;
}

Entity3D* BaseGame::GetRootEntity()
{
	return rootEntity;
}

bool BaseGame::Stop() {
	OnStop();
	render->Stop();
	window->Stop();

	delete rootEntity;
	delete render;
	delete window;
	return true;
}


