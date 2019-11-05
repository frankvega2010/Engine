#ifndef ENTITY_H
#define ENTITY_H

#include "glm.hpp"

using namespace glm;

class Renderer;

#define DLLEXPORT __declspec(dllexport)

class DLLEXPORT Entity
{
private:
	vec3 pos;
	vec3 rot;
	vec3 scale;

protected:
	Renderer* renderer;
	mat4 WorldMatrix;
	mat4 TranslateMatrix;
	mat4 RotationMatrix;
	mat4 ScaleMatrix;
	void UpdateWorldMatrix();

public:
	Entity(Renderer* r);
	virtual void Draw() = 0;
	void SetPos(float x, float y, float z);
	void SetRot(float x, float y, float z);
	void SetScale(float x, float y, float z);
	void Translate(float x, float y, float z);
	void Rotate(float x, float y, float z);
	vec3 GetPos();
	vec3 GetRot();
	vec3 GetScale();
};

#endif
