#include "PointLight.h"
#include "Shader.h"
#include "LightManager.h"

using namespace std;



PointLight::PointLight(vec3 initPos, vec3 initDir, Shader* shad, bool active, float att) : Light(initPos, initDir, shad, active)
{
	attenuation = att;
	if(LightManager::pointLightCount == 0)
	{
		LightManager::pointLightList = new list<PointLight>();
	}
	LightManager::pointLightList->push_front(*this);
	index = LightManager::pointLightCount;
	LightManager::pointLightCount++;
}

void PointLight::Update()
{
	activeShader->use();
	activeShader->setBool("pointLight[" + std::to_string(index) + "].isActive", isActive);
	activeShader->setVec3("pointLight[" + std::to_string(index) + "].position", position);
	activeShader->setVec3("pointLight[" + std::to_string(index) + "].ambient", ambient);
	activeShader->setVec3("pointLight[" + std::to_string(index) + "].diffuse", diffuse);
	activeShader->setVec3("pointLight[" + std::to_string(index) + "].specular", specular);
	activeShader->setFloat("pointLight[" + std::to_string(index) + "].constant", 1.0f);
	activeShader->setFloat("pointLight[" + std::to_string(index) + "].linear", 0.09f);
	activeShader->setFloat("pointLight[" + std::to_string(index) + "].quadratic", 0.032);
	activeShader->setFloat("pointLight[" + std::to_string(index) + "].attenuation", attenuation);
}

void PointLight::SetPosition(vec3 pos)
{
	position = pos;
}

void PointLight::SetAttenuation(float att)
{
	if(att>=0.f)
		attenuation = att;
}

int PointLight::GetPointLightCount()
{
	return LightManager::pointLightCount;
}
