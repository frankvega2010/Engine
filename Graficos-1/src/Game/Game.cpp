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

Shader* shad;

DirectionalLight* directionalLight;
PointLight* pointLight;
SpotLight* spotLight;

list<Light*>* lightsList;
list<Light*>* lightsToShowList;

vec3 plpos = { 1.5f,0.f,0.f };

bool Game::OnStart()
{	
	render->setClearScreenColor(0.8f, 1.f, 0.8f,1.f);
	
	shad = new Shader("res/shaders/3DVertexShader.txt", "res/shaders/3DFragmentShader.txt");

	shad->setVec3("viewPosition", cam->GetCameraPosition());
	shad->setVec3("viewDirection", cam->GetCameraDirection());

	glm::vec3 dir = { 0.f, 0.f, -1.f };
	glm::vec3 ambient = { 0.1f, 0.1f, 0.1f };
	glm::vec3 diffuse = { 0.5f, 0.5f, 0.5f };
	glm::vec3 specular = { 1.f,1.f,1.f };

	cam->SetCameraSpeed(2.5f);
	
	m = new Model("res/model/nanosuit.obj", false, false);
	m->SetName("Nanosuit");

	/*m2 = new Model("res/model/nanosuit.obj", false, false);
	
	m3 = new Model("res/model/nanosuit.obj", false, false);
	m4 = new Model("res/model/nanosuit.obj", false, false);*/

	planes = new Model("res/model/Planes.fbx", false, true);

	m->SetPos(vec3(0.f, -1.f, 0.f));
	/*m2->SetPos(vec3(-12.f, -1.f, 0.f));
	m3->SetPos(vec3(0.f, -1.f, 12.f));
	m4->SetPos(vec3(0.f, -1.f, -12.f));*/
	m->SetScale(vec3(0.5f, 0.5f, 0.5f));
	/*m2->SetScale(vec3(0.5f, 0.5f, 0.5f));
	m3->SetScale(vec3(0.5f, 0.5f, 0.5f));
	m4->SetScale(vec3(0.5f, 0.5f, 0.5f));*/

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
	
	BaseGame::GetRootEntity();

	return true;
}

bool Game::OnUpdate()
{
	shad->use();
	shad->setVec3("viewPosition", cam->GetCameraPosition());
	shad->setVec3("viewDirection", glm::normalize(cam->GetCameraDirection()));

	glm::vec3 objColor = { 1.0f,1.0f,1.0f };

	pointLight->SetAttenuation(1.0f);
	
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

	if(Input::GetKeyReleased(GLFW_KEY_F))
	{
		spotLight->SetActive(!spotLight->GetActive());
	}

	if (Input::GetKeyReleased(GLFW_KEY_3))
	{
		render->showBSPCulledEntities = !render->showBSPCulledEntities;
	}

	if (Input::GetKeyPressedOnce(GLFW_KEY_1))
	{
		render->isBSPEnabled = !render->isBSPEnabled;

		/*if (!render->isBSPEnabled)
		{
			render->TurnOffEntityCounter();
		}*/
	}

	if (Input::GetKeyPressedOnce(GLFW_KEY_2))
	{
		render->isFrustumCullingEnabled = !render->isFrustumCullingEnabled;
		/*if (!render->isFrustumCullingEnabled)
		{
			render->TurnOffEntityCounter();
		}*/
	}
	
	//model translation
	if (Input::GetKeyPressed(GLFW_KEY_RIGHT))
	{
		m->SetPos(vec3(-25.f * BaseGame::GetDeltaTime(), 0.f, 0.f));
	}

	if (Input::GetKeyPressed(GLFW_KEY_LEFT))
	{
		m->SetPos(vec3(25.f * BaseGame::GetDeltaTime(), 0.f, 0.f));
	}
	
	if (Input::GetKeyPressed(GLFW_KEY_UP))
	{
		m->SetPos(vec3(0.0f, 0.f, 25.f * BaseGame::GetDeltaTime()));
	}
	if (Input::GetKeyPressed(GLFW_KEY_DOWN))
	{
		m->SetPos(vec3(0.0f, 0.f, -25.f * BaseGame::GetDeltaTime()));
	}
	
	if (Input::GetKeyPressed(GLFW_KEY_ESCAPE))
	{
		return false;
	}

	return true;
}

void Game::OnDraw()
{
	BaseGame::GetRootEntity()->Draw(*shad);
}

bool Game::OnStop()
{
	delete lightsList;
	
	return true;
}