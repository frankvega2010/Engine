#include "Game.h"
#include "Shape.h"
#include "Input.h"
#include "Sprite.h"
#include "CollisionManager.h"
#include "Model.h"
#include "Shader.h"
#include "Entity3D.h"
#include "DirectionalLight.h"
#include "PointLight.h"
#include "SpotLight.h"

Sprite* sq;
Sprite* spr;
Shader* shad;

DirectionalLight* directionalLight;
PointLight* pointLight;
SpotLight* spotLight;

list<Light*>* lightsList;
list<Light*>* lightsToShowList;

vec3 plpos = { 1.5f,0.f,0.f };

bool Game::OnStart()
{	
	render->setClearScreenColor(1.f, 0.f, 1.f,1.f);
	
	sq = new Sprite(render, 1, 1, 1);
	Material* sqmat = new Material();
	sqmat->LoadShaders("res/shaders/TextureVertexShader.txt", "res/shaders/TextureFragmentShader.txt");
	sq->SetMaterial(sqmat);
	sq->LoadMaterial("res/model/alien.jpg", false);
	sq->SetPos(5.0f, 0.0f, -10.0f);

	spr = new Sprite(render,2,1,2);
	Material* sprmat = new Material();
	sprmat->LoadShaders("res/shaders/TextureVertexShader.txt", "res/shaders/TextureFragmentShader.txt");
	spr->SetMaterial(sprmat);
	spr->LoadMaterial("res/model/megaman.png",true);
	spr->SetPos(-10.0f, 0.0f, -10.0f);

	//////////////////////////////////////////////////////////////////////////////////////////////////////
	
	shad = new Shader("res/shaders/3DVertexShader.txt", "res/shaders/3DFragmentShader.txt");

	shad->setVec3("viewPosition", cam->GetCameraPosition());
	shad->setVec3("viewDirection", cam->GetCameraDirection());

	glm::vec3 dir = { 0.f, 0.f, -1.f };
	glm::vec3 ambient = { 0.1f, 0.1f, 0.1f };
	glm::vec3 diffuse = { 0.5f, 0.5f, 0.5f };
	glm::vec3 specular = { 1.f,1.f,1.f };

	cam->SetCameraSpeed(2.5f);
	
	m = new Model("res/model/backpack/backpack.obj", true);

	m2 = new Model("res/model/spider/Only_Spider_with_Animations_Export.obj", true);

	m3 = new Model("res/model/nave/E 45 Aircraft_obj.obj", false);

	m4 = new Model("res/model/nave2/Intergalactic_Spaceship-(Wavefront).obj", false);

	m2->SetPos(vec3(5.f, 0.f, 0.f));

	m3->SetPos(vec3(-5.f, 0.f, 0.f));

	m4->SetPos(vec3(0.f, 0.f, 5.f));

	m2->SetScale(vec3(0.01f));

	m4->SetScale(vec3(0.5f));
	
	/*m2->SetParent(m);
	
	m3->SetParent(m);
	
	m4->SetParent(m);*/

	lightsList = new list<Light*>();
	
	vec3 lightPos = { 0.f,0.f,0.f };

	directionalLight = new DirectionalLight(lightPos, dir, shad, true);
	pointLight = new PointLight(plpos, dir, shad, true);
	spotLight = new SpotLight(cam->GetCameraPosition(), cam->GetCameraDirection(), shad, false);

	shad->setInt("lightsAmount", PointLight::GetPointLightCount());
	
	lightsList->push_front(directionalLight);
	lightsList->push_front(pointLight);
	lightsList->push_front(spotLight);

	for(list<Light*>::iterator iB = lightsList->begin(); iB != lightsList->end(); ++iB)
	{
		(*iB)->SetAmbient(ambient);
		(*iB)->SetDiffuse(diffuse);
		(*iB)->SetSpecular(specular);
	}

	
	return true;
}

vec2 prevPos;


float xPos = 0.0f;
float yRot = 0.0f;

float yRot2 = 0.f;

float at = 1.0f;

vec3 newscale = { 1.f,1.f,1.f };

Entity3D* m5;
Entity3D* m6;

Entity3D* grupo;
Entity3D* gruposub1;
Entity3D* gruposub2;

bool Game::OnUpdate()
{
	shad->use();
	shad->setVec3("viewPosition", cam->GetCameraPosition());
	shad->setVec3("viewDirection", glm::normalize(cam->GetCameraDirection()));
	

	glm::vec3 objColor = { 1.0f,1.0f,1.0f };

	pointLight->SetAttenuation(at);
	
	//m->SetPos(plpos);

	spotLight->SetPosition(cam->GetCameraPosition());
	spotLight->SetDirection(cam->GetCameraDirection());
	shad->use();
	shad->setInt("lightsAmount", PointLight::GetPointLightCount());
	
	shad->setVec3("objectColor", objColor);

	pointLight->SetPosition(plpos);
	pointLight->SetDiffuse(vec3(1.f, 0.f, 0.f));

	for (list<Light*>::iterator iB = lightsList->begin(); iB != lightsList->end(); ++iB)
	{
		(*iB)->Update();
	}
	
	cam->UpdateCamera();
	
	//point directionalLight input
	if(Input::GetKeyPressed(GLFW_KEY_I))
	{
		plpos.z += BaseGame::GetDeltaTime() * 100.0f;
	}
	if (Input::GetKeyPressed(GLFW_KEY_K))
	{
		plpos.z -= BaseGame::GetDeltaTime() * 100.0f;
	}
	if (Input::GetKeyPressed(GLFW_KEY_J))
	{
		plpos.x -= BaseGame::GetDeltaTime() * 100.0f;
	}
	if (Input::GetKeyPressed(GLFW_KEY_L))
	{
		plpos.x += BaseGame::GetDeltaTime() * 100.0f;
	}
	if (Input::GetKeyPressed(GLFW_KEY_5))
	{
		m5 = BaseGame::GetRootEntity()->GetChild("Cylinder.034__0");
		//GetRootEntity()->GetAllChildsTypes();
		//m2->SetParent(m5);
		m6 = BaseGame::GetRootEntity()->GetChild("Cylinder.029__0");
		m5->SetParent(m6);
	}

	if (Input::GetKeyPressed(GLFW_KEY_6))
	{
		grupo = BaseGame::GetRootEntity()->GetChild("group");
		gruposub1 = BaseGame::GetRootEntity()->GetChild("Cube.037__0");
		gruposub2 = BaseGame::GetRootEntity()->GetChild("Cylinder.033__0");
	}
	
	if(Input::GetKeyPressed(GLFW_KEY_SPACE))
	{
		newscale = vec3(1.f, 1.f, 1.f) + vec3(10.f) * BaseGame::GetDeltaTime();
		m3->SetScale(newscale);
	}
	
	if (Input::GetKeyPressed(GLFW_KEY_C))
	{
		newscale = vec3(1.f, 1.f, 1.f) - vec3(10.f) * BaseGame::GetDeltaTime();
		m3->SetScale(newscale);
	}

	if(Input::GetKeyReleased(GLFW_KEY_F))
	{
		spotLight->SetActive(!spotLight->GetActive());
	}

	if (Input::GetKeyReleased(GLFW_KEY_T))
	{
		grupo->SetPos(vec3(100.f*BaseGame::GetDeltaTime(), 0.f, 0.f));
	}
	if (Input::GetKeyReleased(GLFW_KEY_Y))
	{
		gruposub1->SetPos(vec3(100.f*BaseGame::GetDeltaTime(), 0.f, 0.f));
	}
	if (Input::GetKeyReleased(GLFW_KEY_U))
	{
		gruposub2->SetPos(vec3(-100.f*BaseGame::GetDeltaTime(), 0.f, 0.f));
	}

	if (Input::GetKeyReleased(GLFW_KEY_N))
	{
		newscale = vec3(1.f, 1.f, 1.f) + vec3(10.f) * BaseGame::GetDeltaTime();
		grupo->SetScale(newscale);
	}
	if (Input::GetKeyReleased(GLFW_KEY_M))
	{
		newscale = vec3(1.f, 1.f, 1.f) - vec3(10.f) * BaseGame::GetDeltaTime();
		grupo->SetScale(newscale);
	}
	
	//model translation
	if (Input::GetKeyPressed(GLFW_KEY_RIGHT))
	{
		if (yRot < 0.0f)
			yRot = 0.0f;
		
		yRot = 100.0f * BaseGame::GetDeltaTime();
		if(m5)
			m5->SetPos(vec3(yRot,0.f,0.f));
	}

	if (Input::GetKeyPressed(GLFW_KEY_LEFT))
	{
		if(yRot>0.0f)
			yRot = 0.0f;
		
		yRot = -100.0f * BaseGame::GetDeltaTime();
		if (m5)
			m5->SetPos(vec3(yRot, 0.f, 0.f));
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

		if (yRot2 < 0.0f)
			yRot2 = 0.0f;
		
		yRot2 = 100.0f * BaseGame::GetDeltaTime();
		m->SetRot(yRot2,vec3(0.f,1.f,0.f));
		m2->SetRot(yRot2, vec3(0.f, 1.f, 0.f));
		m3->SetRot(yRot2, vec3(0.f, 1.f, 0.f));
		m4->SetRot(yRot2, vec3(0.f, 1.f, 0.f));
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

		if (yRot2 > 0.0f)
			yRot2 = 0.0f;

		yRot2 = -100.0f * BaseGame::GetDeltaTime();
		m->SetRot(yRot2, vec3(0.f, 1.f, 0.f));
		m2->SetRot(yRot2, vec3(0.f, 1.f, 0.f));
		m3->SetRot(yRot2, vec3(0.f, 1.f, 0.f));
		m4->SetRot(yRot2, vec3(0.f, 1.f, 0.f));
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
	BaseGame::GetRootEntity()->Draw(*shad);
}

bool Game::OnStop()
{
	delete spr;
	delete sq;

	delete lightsList;
	
	return true;
}