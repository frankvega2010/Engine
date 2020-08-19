#include "DirectionalLight.h"

#include "Shader.h"

DirectionalLight::DirectionalLight(vec3 initPos, vec3 initDir, Shader* shad, bool active) : Light(initPos, initDir, shad, active)
{
	
}


void DirectionalLight::Update()
{
	activeShader->use();
	activeShader->setBool("dirLight.isActive", isActive);
	activeShader->setVec3("dirLight.direction", direction);
	activeShader->setVec3("dirLight.ambient", ambient);
	activeShader->setVec3("dirLight.diffuse", diffuse);
	activeShader->setVec3("dirLight.specular", specular);
}
