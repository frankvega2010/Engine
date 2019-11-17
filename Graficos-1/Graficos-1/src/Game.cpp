#include "Game.h"
#include "Shape.h"
#include "Input.h"

Shape* sq;

bool Game::OnStart()
{
	sq = new Shape(render);
	Material* sqmat = new Material();
	sqmat->LoadShaders("src/SimpleVertexShader.vertexshader", "src/SimpleFragmentShader.fragmentshader");
	sq->SetMaterial(sqmat);
	return true;
}

bool Game::OnUpdate()
{
	if(Input::GetKeyPressed(GLFW_KEY_RIGHT))
	{
		sq->Rotate(0.0f, 0.0f, 1.0f);
	}
	
	return true;
}

void Game::OnDraw()
{
	sq->Draw();
}

bool Game::OnStop()
{
	return true;
}