#include "Entity3D.h"
#include "gtx/quaternion.hpp"
#include "Renderer.h"
#include "Camera.h"
#include "Model.h"

Entity3D::Entity3D()
{

}

Entity3D::Entity3D(string const &path)
{
	model = new Model(path);
}

Entity3D::~Entity3D()
{

}

void Entity3D::SetParent(Entity3D* p)
{
	if (parent)
	{
		parent->UnsetChild(this);
	}
	parent = p;
	parent->SetChild(this);
}

void Entity3D::SetChild(Entity3D* c)
{
	childs.push_front(c);
}

void Entity3D::UnsetChild(Entity3D* c)
{
	for (list<Entity3D*>::iterator itBeg = childs.begin(); itBeg != childs.end(); ++itBeg)
	{
		if (*itBeg == c)
		{
			childs.remove(*itBeg);
			break;
		}
	}
}

void Entity3D::SetPos(vec3 pos)
{
	position = pos;
	modelMatrix = glm::translate(modelMatrix, position);
}

void Entity3D::SetRot(vec3 rot)
{
	rotation = rot;
	vec3 rotAngle = glm::radians(rot);
	modelMatrix = glm::rotate(modelMatrix, rot.x, vec3(1.0f,0.0f,0.0f));
	modelMatrix = glm::rotate(modelMatrix, rot.y, vec3(0.0f, 1.0f, 0.0f));
	modelMatrix = glm::rotate(modelMatrix, rot.z, vec3(0.0f, 0.0f, 1.0f));
}

void Entity3D::SetScale(vec3 sc)
{
	scale = sc;
	modelMatrix = glm::scale(modelMatrix, scale);
}

void Entity3D::Draw(Shader shader)
{
	shader.use();

	glm::mat4 projection = Renderer::renderer->GetProjMatrix();
	glm::mat4 view = Camera::thisCam->GetViewMatrix();

	shader.setMat4("proj", projection);
	shader.setMat4("view", view);
	shader.setMat4("model", modelMatrix);

	model->Draw(shader);
}