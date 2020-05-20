#include "Game.h"
#include "Shape.h"
#include "Input.h"
#include "Sprite.h"
#include "ColisionManager.h"
#include "Model.h"

Sprite* sq;
Sprite* spr;

Model* m;

bool Game::OnStart()
{
	sq = new Sprite(render, 1, 1, 1);
	Material* sqmat = new Material();
	sqmat->LoadShaders("src/TextureVertexShader.txt", "src/TextureFragmentShader.txt");
	sq->SetMaterial(sqmat);
	sq->LoadMaterial("res/alien.jpg", false);
	sq->SetPos(5.0f, 0.0f, -10.0f);

	spr = new Sprite(render,2,1,2);
	Material* sprmat = new Material();
	sprmat->LoadShaders("src/TextureVertexShader.txt", "src/TextureFragmentShader.txt");
	spr->SetMaterial(sprmat);
	spr->LoadMaterial("res/megaman.png",true);
	spr->SetPos(-10.0f, 0.0f, -10.0f);

	cam->SetCameraSpeed(2.5f);

	//m = new Model("res/backpack/backpack.obj");

	//delete sprmat;
	//delete sqmat;

	return true;
}

vec2 prevPos;
glm::vec3 camPos;

bool Game::OnUpdate()
{

	/*if (Input::GetKeyPressed(GLFW_KEY_W))
	{
		cam->LookAt(cam->GetCamComponent('p') + glm::vec3(0.0f,0.0f,0.01f), cam->GetCamComponent('c'), cam->GetCamComponent('u'));
	}
	if (Input::GetKeyPressed(GLFW_KEY_S))
	{
		cam->LookAt(cam->GetCamComponent('p') + glm::vec3(0.0f, 0.0f, -0.01f), cam->GetCamComponent('c'), cam->GetCamComponent('u'));
	}
	if (Input::GetKeyPressed(GLFW_KEY_A))
	{
		cam->LookAt(cam->GetCamComponent('p') + glm::vec3(-0.01f, 0.0f, 0.0f), cam->GetCamComponent('c'), cam->GetCamComponent('u'));
	}
	if (Input::GetKeyPressed(GLFW_KEY_D))
	{
		cam->LookAt(cam->GetCamComponent('p') + glm::vec3(0.01f, 0.0f, 0.0f), cam->GetCamComponent('c'), cam->GetCamComponent('u'));
	}*/

	//m->Draw();

	cam->UpdateCamera();

	if (Input::GetKeyPressed(GLFW_KEY_RIGHT))
	{
		if (!CollisionManager::CheckCollision(spr, sq))
		{
			prevPos = spr->GetPos();
			spr->Translate(0.01f, 0.0f, 0.0f);
		}
		else
			spr->SetPos(prevPos.x,prevPos.y, spr->GetPos().z);

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
			spr->SetPos(prevPos.x, prevPos.y, spr->GetPos().z);
	}
	if (Input::GetKeyPressed(GLFW_KEY_UP))
	{
		if (!CollisionManager::CheckCollision(spr, sq))
		{
			prevPos = spr->GetPos();
			spr->Translate(0.0f, 0.01f, 0.0f);

		}

		else
			spr->SetPos(prevPos.x, prevPos.y, spr->GetPos().z);
	}
	if (Input::GetKeyPressed(GLFW_KEY_DOWN))
	{
		if (!CollisionManager::CheckCollision(spr, sq))
		{
			prevPos = spr->GetPos();
			spr->Translate(0.0f, -0.01f, 0.0f);
		}
		else
			spr->SetPos(prevPos.x, prevPos.y, spr->GetPos().z);
	}
	
	if (Input::GetKeyPressed(GLFW_KEY_ESCAPE))
	{
		return false;
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
	delete spr;
	delete sq;
	return true;
}