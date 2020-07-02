#include "Light.h"
#include "Shader.h"

Light::Light(vec3 initPos, vec3 initDir, Shader* shad, bool active)
{
	ambient = { 0.f,0.f,0.f };
	diffuse = { 0.f,0.f,0.f };
	specular = { 0.f,0.f,0.f };
	SetPosition(initPos);
	SetDirection(initDir);
	SetShader(shad);
	SetActive(active);
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

void Light::SetActive(bool active)
{
	isActive = active;
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
	
}
