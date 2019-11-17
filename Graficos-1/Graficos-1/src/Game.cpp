#include "Game.h"
#include "Shape.h"

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