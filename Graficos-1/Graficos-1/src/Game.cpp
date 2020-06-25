#include "Game.h"
#include "Shape.h"
#include "Input.h"
#include "Sprite.h"
#include "CollisionManager.h"
#include "Model.h"
#include "Shader.h"
#include "Entity3D.h"
#include "DirectionalLight.h"

Sprite* sq;
Sprite* spr;

Entity3D* m;
Shader* shad;

Light* light;

Entity3D* m2;

bool Game::OnStart()
{
	render->setClearScreenColor(0.f, 0.f, 0.f,0.f);
	
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

	glm::vec3 dir = { 0.f, 0.f, -1.f };
	glm::vec3 ambient = { 0.5f, 0.5f, 0.5f };
	glm::vec3 diffuse = { 0.4f, 0.4f, 0.4f };
	glm::vec3 specular = { 1.f,1.f,1.f };

	cam->SetCameraSpeed(2.5f);

	m = new Entity3D("res/backpack/backpack.obj");

	m2 = new Entity3D("res/backpack/backpack.obj");

	vec3 lightPos = { 0.f,0.f,0.f };

	light = new DirectionalLight(lightPos, dir, shad);
	light->SetAmbient(ambient);
	light->SetDiffuse(diffuse);
	light->SetSpecular(specular);


	m2->SetPos(vec3(5.f, 0.f, 0.f));
	return true;
}

vec2 prevPos;

float xPos = 0.0f;
float yRot = 0.0f;

vec3 plpos = { 3.f,0.f,-1.f };
float at = 1.0f;
bool Game::OnUpdate()
{
	shad->setVec3("viewPosition", cam->GetCameraPosition());
	shad->setVec3("viewDirection", glm::normalize(cam->GetCameraDirection()));
	

	glm::vec3 objColor = { 1.0f,1.0f,1.0f };

	//light->Update();
	shad->setVec3("objectColor", objColor);
	vec3 dir = light->GetDirection();
	m->SetScale(vec3(1.0f, 1.0f, 1.0f));
	cam->UpdateCamera();


	


	
	shad->setVec3("pointLight.position", plpos);
	shad->setVec3("pointLight.ambient", 0.5f, 0.5f, 0.5f);
	shad->setVec3("pointLight.diffuse", 0.8f, 0.8f, 0.8f);
	shad->setVec3("pointLight.specular", 0.f, 0.f, 0.f);
	shad->setFloat("pointLight.constant", 1.0f);
	shad->setFloat("pointLight.linear", 0.09f);
	shad->setFloat("pointLight.quadratic", 0.032);
	shad->setFloat("pointLight.attenuation", at);





	
	if(Input::GetKeyPressed(GLFW_KEY_I))
	{
		plpos.z += BaseGame::GetDeltaTime() * 10.0f;
	}
	if (Input::GetKeyPressed(GLFW_KEY_K))
	{
		plpos.z -= BaseGame::GetDeltaTime() * 10.0f;
	}
	if (Input::GetKeyPressed(GLFW_KEY_J))
	{
		plpos.x -= BaseGame::GetDeltaTime() * 10.0f;
	}
	if (Input::GetKeyPressed(GLFW_KEY_L))
	{
		plpos.x += BaseGame::GetDeltaTime() * 10.0f;
	}


	if (Input::GetKeyPressed(GLFW_KEY_4))
	{
		at--;
	}


	if (Input::GetKeyPressed(GLFW_KEY_5))
	{
		at++;
	}
	
	
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

		if (yRot < 0.0f)
			yRot = 0.0f;
		
		yRot = 10.0f * BaseGame::GetDeltaTime();
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

		if(yRot>0.0f)
			yRot = 0.0f;
		
		yRot = -10.0f * BaseGame::GetDeltaTime();
		m->SetRot(vec3(0.0f, yRot, 0.0f));
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
	m2->Draw(*shad);
}

bool Game::OnStop()
{
	delete spr;
	delete sq;
	return true;
}