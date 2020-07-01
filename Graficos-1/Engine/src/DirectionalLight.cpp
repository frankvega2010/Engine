#include "DirectionalLight.h"

#include "Shader.h"

DirectionalLight::DirectionalLight(vec3 initPos, vec3 initDir, Shader* shad) : Light(initPos, initDir, shad)
{
	
}


void DirectionalLight::Update()
{
	activeShader->setVec3("lightDirection", direction);
	activeShader->setVec3("lightAmbient", ambient);
	activeShader->setVec3("lightDiffuse", diffuse);
	activeShader->setVec3("lightSpecular", specular);
}
