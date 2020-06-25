#ifndef LIGHT_H
#define LIGHT_H

#include "glm.hpp"

using namespace glm;

#define DLLEXPORT _declspec(dllexport)

class Shader;

class DLLEXPORT Light
{
protected:
	vec3 position;
	vec3 direction;
	static vec3 ambient;
	static vec3 diffuse;
	static vec3 specular;
	Shader* activeShader;
public:
	Light(vec3 initPos, vec3 initDir, Shader* shad);
	vec3 GetPosition() { return position; };
	vec3 GetDirection() { return direction; };
	void SetPosition(vec3 newPosition);
	void SetDirection(vec3 newDirection);
	virtual void Update() = 0;
	static void SetAmbient(vec3 amb);
	static void SetDiffuse(vec3 dif);
	static void SetSpecular(vec3 spec);
	void SetShader(Shader* shad);
};

#endif

