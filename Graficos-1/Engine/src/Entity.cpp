#include "Entity.h"
#include "glew.h"
#include "glfw3.h"
#include "gtc/matrix_transform.hpp"

Entity::Entity(Renderer* r)
{
	renderer = r;
	WorldMatrix = mat4(1.0f);
	TranslateMatrix = mat4(1.0f);
	RotationMatrix = mat4(1.0f);
	ScaleMatrix = mat4(1.0f);

	pos[0] = pos[1] = pos[2] = 0.0f;
	rot[0] = rot[1] = rot[2] = 0.0f;
	scale[0] = scale[1] = scale[2] = 1.0f;
}

void Entity::SetPos(float x, float y, float z)
{
	pos[0] = x;
	pos[1] = y;
	pos[2] = z;

	TranslateMatrix = glm::translate(mat4(1.0f), pos);
	UpdateWorldMatrix();
}

void Entity::SetRot(float x, float y, float z)
{
	rot[0] = x;
	rot[1] = y;
	rot[2] = z;

	RotationMatrix = rotate(mat4(1.0f), x, vec3(1.0f, 0.0f, 0.0f));
	RotationMatrix *= rotate(mat4(1.0f), y, vec3(0.0f, 1.0f, 0.0f));
	RotationMatrix *= rotate(mat4(1.0f), z, vec3(0.0f, 0.0f, 1.0f));

	UpdateWorldMatrix();
}

void Entity::SetScale(float x, float y, float z)
{
	scale[0] = x;
	scale[1] = y;
	scale[2] = z;

	ScaleMatrix = glm::scale(mat4(1.0f), scale);

	UpdateWorldMatrix();
}

void Entity::UpdateWorldMatrix()
{
	WorldMatrix = TranslateMatrix * RotationMatrix * ScaleMatrix;
}

vec3 Entity::GetPos()
{
	return pos;
}

vec3 Entity::GetRot()
{
	return rot;
}

vec3 Entity::GetScale()
{
	return scale;
}

void Entity::Translate(float x, float y, float z)
{
	pos[0] += x;
	pos[1] += y;
	pos[2] += z;

	TranslateMatrix = translate(mat4(1.0f), pos);
	UpdateWorldMatrix();
}

void Entity::Rotate(float x, float y, float z)
{
	rot[0] += x;
	rot[1] += y;
	rot[2] += z;

	RotationMatrix = rotate(mat4(1.0f), rot[0], vec3(1.0f, 0.0f, 0.0f));
	RotationMatrix *= rotate(mat4(1.0f), rot[1], vec3(0.0f, 1.0f, 0.0f));
	RotationMatrix *= rotate(mat4(1.0f), rot[2], vec3(0.0f, 0.0f, 1.0f));

	UpdateWorldMatrix();
}
void Entity::SetVertices(float* vertices, int count)
{
	Dispose();

	vertexCount = count;
	shouldDispose = true;
	glGenBuffers(1, &bufferID);
	glBindBuffer(GL_ARRAY_BUFFER, bufferID);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float)*count * 3, vertices, GL_STATIC_DRAW);

}
void Entity::Dispose()
{
	if (shouldDispose)
	{
		glDeleteBuffers(1, &bufferID);
		shouldDispose = false;
	}
}