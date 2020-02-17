#include "Game.h"
#include "Shape.h"
#include "Input.h"
#include "Sprite.h"
#include "ColisionManager.h"
#include "Tilemap.h"
#include <iostream>

Sprite* sq;
Sprite* spr;
TileMap* myLevel;

bool Game::OnStart()
{
	sq = new Sprite(render, 1, 1);
	Material* sqmat = new Material();
	sqmat->LoadShaders("src/TextureVertexShader.txt", "src/TextureFragmentShader.txt");
	sq->SetMaterial(sqmat);
	sq->LoadMaterial("res/alien.jpg");
	sq->SetPos(5.0f, 0.0f, 0.0f);

	spr = new Sprite(render,2,1);
	Material* sprmat = new Material();
	sprmat->LoadShaders("src/TextureVertexShader.txt", "src/TextureFragmentShader.txt");
	spr->SetMaterial(sprmat);
	spr->LoadMaterial("res/megaman.png");
	spr->SetPos(-10.0f, 0.0f, 0.0f);

	Material* matmap = new Material();
	myLevel = new TileMap(render, matmap, "res/example_11.png", 2, 2);

	//delete sprmat;
	//delete sqmat;

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

		spr->UpdAnim(1);
		
	}
	else
	{
		spr->UpdAnim(0);
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
	myLevel->DrawTiles();
	myLevel->UpdateTilesAnim(0.05f);
	sq->Draw();
	spr->Draw();
}

bool Game::OnStop()
{
	delete spr;
	delete sq;
	delete myLevel;
	return true;
}