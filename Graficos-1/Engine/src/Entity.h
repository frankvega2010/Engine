#ifndef ENTITY_H
#define ENTITY_H

#include "Renderer.h"
#include<iostream>

using namespace std;
using namespace glm;

class DLLEXPORT Entity
{
private:
	vec3 pos;
	vec3 rot;
protected:
	static Renderer* renderer;
	mat4 WorldMatrix;
	mat4 TranslateMatrix;
	mat4 RotMatrix;
	mat4 ScaleMatrix;
	void UpdateWorldMatrix();

public:
	static Renderer* GetRenderer();
	vec3 scale;
	Entity(Renderer * renderPTR);
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