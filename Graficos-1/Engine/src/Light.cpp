#include "Light.h"
#include "Shader.h"

vec3 Light::ambient = { 0.f,0.f,0.f };
vec3 Light::diffuse = { 0.5f,0.5f,0.5f };
vec3 Light::specular = { 1.f,1.f,1.f };

Light::Light(vec3 initPos, vec3 initDir, Shader* shad)
{
	SetPosition(initPos);
	SetDirection(initDir);
	SetShader(shad);
}

void Light::SetPosition(vec3 newPosition)
{
	position = newPosition;
}

void Light::SetDirection(vec3 newDirection)
{
	direction = newDirection;
}

void Light::SetShader(Shader* shad)
{
	activeShader = shad;
}

void Light::SetSpecular(vec3 spec)
{
	specular = spec;
}

void Light::SetAmbient(vec3 amb)
{
	ambient = amb;
}

void Light::SetDiffuse(vec3 dif)
{
	diffuse = dif;
}

void Light::Update()
{
	activeShader->setVec3("lightAmbient", ambient);
	activeShader->setVec3("lightDiffuse", diffuse);
	activeShader->setVec3("lightSpecular", specular);
}
