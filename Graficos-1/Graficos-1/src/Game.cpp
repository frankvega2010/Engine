#include "Game.h"
#include "Shape.h"
#include "Input.h"
#include "Sprite.h"

Shape* sq;
Sprite* spr;

bool Game::OnStart()
{
	sq = new Shape(render);
	Material* sqmat = new Material();
	sqmat->LoadShaders("src/ShapeVertexShader.txt", "src/ShapeFragmentShader.txt");
	sq->SetMaterial(sqmat);

	spr = new Sprite(render,0,0);
	Material* sprmat = new Material();
	sprmat->LoadShaders("src/TextureVertexShader.txt", "src/TextureFragmentShader.txt");
	spr->SetMaterial(sprmat);
	spr->LoadMaterial("res/alien.jpg");

	return true;
}

bool Game::OnUpdate()
{
	if(Input::GetKeyPressed(GLFW_KEY_RIGHT))
	{
		sq->Rotate(0.0f, 0.0f, 1.0f);
	}
	if (Input::GetKeyPressed(GLFW_KEY_LEFT))
	{
		spr->SetScale(spr->GetScale().x + 0.1f, spr->GetScale().y + 0.1f, spr->GetScale().z);
	}
	
	return true;
}

void Game::OnDraw()
{
	sq->Draw();
	spr->Draw();
}

bool Game::OnStop()
{
	return true;
}