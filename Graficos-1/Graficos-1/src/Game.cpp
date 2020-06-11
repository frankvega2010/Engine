#include "Game.h"
#include "Shape.h"
#include "Input.h"
#include "Sprite.h"
#include "CollisionManager.h"
#include "Model.h"
#include "Shader.h"
#include "Entity3D.h"

Sprite* sq;
Sprite* spr;

Entity3D* m;
Shader* shad;

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

	shad = new Shader("src/3DVertexShader.txt", "src/3DFragmentShader.txt");

	shad->setVec3("viewPosition", cam->GetCameraPosition());
	shad->setVec3("viewDirection", cam->GetCameraDirection());

	glm::vec3 dir = { 0.f,0.f,1.f };
	glm::vec3 ambient = { 1.f,1.f,1.f };
	glm::vec3 diffuse = { 1.f,1.f,1.f };
	glm::vec3 specular = { 1.f,1.f,1.f };

	shad->setVec3("lightDirection", dir);
	shad->setVec3("lightAmbient", ambient);
	shad->setVec3("lightDiffuse", diffuse);
	shad->setVec3("lightSpecular", specular);

	cam->SetCameraSpeed(2.5f);

	m = new Entity3D("res/backpack/backpack.obj");
	

	return true;
}

vec2 prevPos;

float xPos = 0.0f;
float yRot = 0.0f;

bool Game::OnUpdate()
{

	glm::vec3 dir = { 0.f,0.5f,-1.f };
	glm::vec3 ambient = { 0.1f,0.1f,0.1f };
	glm::vec3 diffuse = { 0.8f,0.5f,0.5f };
	glm::vec3 specular = { 1.f,1.f,1.f };
	glm::vec3 objColor = { 1.0f,1.0f,1.0f };

	shad->setVec3("lightDirection", dir);
	shad->setVec3("lightAmbient", ambient);
	shad->setVec3("lightDiffuse", diffuse);
	shad->setVec3("lightSpecular", specular);
	shad->setVec3("objectColor", objColor);

	m->SetScale(vec3(1.0f, 1.0f, 1.0f));
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
		yRot += 0.01f * BaseGame::GetDeltaTime();
		m->SetRot(vec3(0.0f, yRot, 0.0f));
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

		xPos += 0.01f * BaseGame::GetDeltaTime();
		m->SetPos(vec3(xPos, 0.0f, 0.0f));
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
	m->Draw(*shad);
}

bool Game::OnStop()
{
	delete spr;
	delete sq;
	return true;
}