#include "Material3D.h"
#include  "Shader.h"

Material3D::Material3D(Shader* sha)
{
	activeShader = sha;
}

void Material3D::SetShininess(float sh)
{
	shininess = sh;
}

void Material3D::SetBaseColor(vec3 col)
{
	baseColor = col;
}

void Material3D::SetAmbient(vec3 amb)
{
	ambient = amb;
}

void Material3D::SetDiffuse(vec3 dif)
{
	diffuse = dif;
}

void Material3D::SetSpecular(vec3 spec)
{
	specular = spec;
}

void Material3D::Update()
{
	activeShader->
}


