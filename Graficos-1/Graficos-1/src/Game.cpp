#include "Game.h"
#include "Shape.h"
#include "Input.h"
#include "Sprite.h"
#include "ColisionManager.h"

Shape* sq;
Sprite* spr;

bool Game::OnStart()
{
	sq = new Shape(render);
	Material* sqmat = new Material();
	sqmat->LoadShaders("src/ShapeVertexShader.txt", "src/ShapeFragmentShader.txt");
	sq->SetMaterial(sqmat);
	sq->SetPos(5.0f, 0.0f, 0.0f);

	spr = new Sprite(render,2,1);
	Material* sprmat = new Material();
	sprmat->LoadShaders("src/TextureVertexShader.txt", "src/TextureFragmentShader.txt");
	spr->SetMaterial(sprmat);
	spr->LoadMaterial("res/megaman.png",true);
	spr->SetPos(-10.0f, 0.0f, 0.0f);
	return true;
}

vec2 prevPos;

bool Game::OnUpdate()
{
	if (Input::GetKeyPressed(GLFW_KEY_RIGHT))
	{
		if (!CollisionManager::CheckCollision(spr, sq))
		{
			prevPos = spr->GetPos();
			spr->Translate(0.01f, 0.0f, 0.0f);
		}
		else
			spr->SetPos(prevPos.x,prevPos.y,0.0f);
		
	}
	if (Input::GetKeyPressed(GLFW_KEY_LEFT))
	{
		if (!CollisionManager::CheckCollision(spr, sq))
		{
			prevPos = spr->GetPos();
			spr->Translate(-0.01f, 0.0f, 0.0f);

		}
		else
			spr->SetPos(prevPos.x, prevPos.y, 0.0f);
	}
	if (Input::GetKeyPressed(GLFW_KEY_UP))
	{
		if (!CollisionManager::CheckCollision(spr, sq))
		{
			prevPos = spr->GetPos();
			spr->Translate(0.0f, 0.01f, 0.0f);

		}

		else
			spr->SetPos(prevPos.x, prevPos.y, 0.0f);
	}
	if (Input::GetKeyPressed(GLFW_KEY_DOWN))
	{
		if (!CollisionManager::CheckCollision(spr, sq))
		{
			prevPos = spr->GetPos();
			spr->Translate(0.0f, -0.01f, 0.0f);
		}
		else
			spr->SetPos(prevPos.x, prevPos.y, 0.0f);
	}
	if (Input::GetKeyPressed(GLFW_KEY_B))
	{
		if (!CollisionManager::CheckCollision(spr, sq))
		{
			spr->SetScale(spr->GetScale().x + 0.01f, spr->GetScale().y + 0.01f, spr->GetScale().z);
		}
		
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