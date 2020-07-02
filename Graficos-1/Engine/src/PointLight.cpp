#include "PointLight.h"
#include "Shader.h"

int PointLight::pointLightCount = 0;

PointLight::PointLight(vec3 initPos, vec3 initDir, Shader* shad, bool active, float att) : Light(initPos, initDir, shad, active)
{
	attenuation = att;
	pointLightCount++;
}

void PointLight::Update()
{
	for (int i = 0; i < pointLightCount; i++)
	{
		activeShader->setBool("pointLight[" + std::to_string(i) + "].isActive", isActive);
		activeShader->setVec3("pointLight[" + std::to_string(i) + "].position", position);
		activeShader->setVec3("pointLight[" + std::to_string(i) + "].ambient", ambient);
		activeShader->setVec3("pointLight[" + std::to_string(i) + "].diffuse", diffuse);
		activeShader->setVec3("pointLight[" + std::to_string(i) + "].specular", specular);
		activeShader->setFloat("pointLight[" + std::to_string(i) + "].constant", 1.0f);
		activeShader->setFloat("pointLight[" + std::to_string(i) + "].linear", 0.09f);
		activeShader->setFloat("pointLight[" + std::to_string(i) + "].quadratic", 0.032);
		activeShader->setFloat("pointLight[" + std::to_string(i) + "].attenuation", attenuation);
	}
}

void PointLight::SetAttenuation(float att)
{
	if(att>=0.f)
		attenuation = att;
}

int PointLight::GetPointLightCount()
{
	return pointLightCount;
}
