#include "PointLight.h"
#include "Shader.h"

PointLight::PointLight(vec3 initPos, vec3 initDir, Shader* shad, float att) : Light(initPos, initDir, shad)
{
	attenuation = att;
}

void PointLight::Update()
{
	activeShader->setVec3("pointLight.position", position);
	activeShader->setVec3("pointLight.ambient", ambient);
	activeShader->setVec3("pointLight.diffuse", diffuse);
	activeShader->setVec3("pointLight.specular", specular);
	activeShader->setFloat("pointLight.constant", 1.0f);
	activeShader->setFloat("pointLight.linear", 0.09f);
	activeShader->setFloat("pointLight.quadratic", 0.032);
	activeShader->setFloat("pointLight.attenuation", attenuation);
}

void PointLight::SetAttenuation(float att)
{
	if(att>=0.f)
		attenuation = att;
}
