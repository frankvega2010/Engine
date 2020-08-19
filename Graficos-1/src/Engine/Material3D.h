#ifndef MATERIAL3D_H
#define MATERIAL3D_H

#define DLLEXPORT _declspec(dllexport)
#include <vec3.hpp>

using namespace glm;

class DLLEXPORT Material3D
{
private:
	float shininess;
	vec3 baseColor;
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
	class Shader* activeShader;
public:
	Material3D(Shader* sha);
	void SetShininess(float sh);
	void SetBaseColor(vec3 col);
	void SetAmbient(vec3 amb);
	void SetDiffuse(vec3 dif);
	void SetSpecular(vec3 spec);
	void Update();
};

#endif
