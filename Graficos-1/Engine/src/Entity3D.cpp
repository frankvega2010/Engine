#include "Entity3D.h"

#include "BaseGame.h"
#include "gtx/quaternion.hpp"
#include "Renderer.h"
#include "Camera.h"
#include "Model.h"

Entity3D::Entity3D(Entity3D* newParent)
{
	parent = nullptr;
	position = vec3(0.f);
	rotation = vec3(0.f);
	scale = vec3(1.f);
	
	if(newParent)
	{
		SetParent(newParent);
	}
	else if(name != "root" || this != BaseGame::GetRootEntity())
	{	
		SetParent(BaseGame::GetRootEntity());
	}

	entityType = entity;

	collisionBox = new CollisionBox();
}

Entity3D::Entity3D(string newName)
{
	entityType = entity;
	
	name = newName;

	collisionBox = new CollisionBox();

	for (int i = 0; i < TOTALVERTICES; i++)
	{
		collisionBox->SetBounds(i, vec3(0.f));
	}
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
	if (p)
	{
		parent = p;
		modelMatrix = glm::inverse(parent->worldModel) * worldModel;
		parent->SetChild(this);
	}
}

void Entity3D::SetChild(Entity3D* c)
{
	childs.push_front(c);
}

Entity3D* Entity3D::GetChild(string childName)
{
	Entity3D* toGet = nullptr;
	if (name == childName)
	{
		return this;
	}
	else
	{
		for (list<Entity3D*>::iterator itBeg = childs.begin(); itBeg != childs.end(); ++itBeg)
		{
			toGet = (*itBeg)->GetChild(childName);
			if (toGet != nullptr)
				break;
		}
	}
	return toGet;
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
	UpdateModelMatAndBoundingBox();
}

void Entity3D::SetRot(float angle, vec3 axis)
{
	rotation.x += angle * axis.x;
	rotation.y += angle * axis.y;
	rotation.z += angle * axis.z;
	
	modelMatrix = glm::rotate(modelMatrix, radians(angle), axis);
	UpdateModelMatAndBoundingBox();
}

void Entity3D::SetScale(vec3 sc)
{
	scale = sc;
	modelMatrix = glm::scale(modelMatrix, scale);
	UpdateModelMatAndBoundingBox();
}

void Entity3D::Draw(Shader shader)
{
	for (list<Entity3D*>::iterator itBeg = childs.begin(); itBeg != childs.end(); ++itBeg)
	{
		Entity3D* ent = (*itBeg);
		if(ent->entityType == mesh)
		{
			Mesh* m = static_cast<Mesh*> (ent);
			m->Draw(shader);
		}
		else
		{
			ent->Draw(shader);
		}
	}
	//collisionBox->DrawCollisionBox();
}

void Entity3D::UpdateModelMatrix()
{
	if(parent != nullptr)
	{
		worldModel = parent->worldModel * modelMatrix;
	}

	for (list<Entity3D*>::iterator itBeg = childs.begin(); itBeg != childs.end(); ++itBeg)
	{
		(*itBeg)->UpdateModelMatrix();
	}
}

void Entity3D::SetName(string newName)
{
	name = newName;
}

void Entity3D::SetModelMatrix(glm::mat4 newModelMatrix)
{
	modelMatrix = newModelMatrix;
}

void Entity3D::GetAllChildsNames()
{
	cout << name << endl;

	for (list<Entity3D*>::iterator itBeg = childs.begin(); itBeg != childs.end(); ++itBeg)
	{
		(*itBeg)->GetAllChildsNames();
	}
}

void Entity3D::GetAllChildsTypes()
{
	cout << entityType << endl;

	for (list<Entity3D*>::iterator itBeg = childs.begin(); itBeg != childs.end(); ++itBeg)
	{
		(*itBeg)->GetAllChildsTypes();
	}
}

Bounds Entity3D::UpdateModelMatAndBoundingBox()
{
	if (parent != nullptr)
		worldModel = parent->worldModel * modelMatrix;

	for (list<Entity3D*>::iterator itBeg = childs.begin(); itBeg != childs.end(); ++itBeg)
	{
		CalculateBounds((*itBeg)->UpdateModelMatAndBoundingBox());
	}
	
	collisionBox->GenerateBoundingBox(bounds, worldModel);
	return bounds;
}

void Entity3D::CalculateBounds(Bounds otherBounds)
{
	bounds.minX = bounds.minX < otherBounds.minX ? bounds.minX : otherBounds.minX;
	bounds.minY = bounds.minY < otherBounds.minY ? bounds.minY : otherBounds.minY;
	bounds.minZ = bounds.minZ < otherBounds.minZ ? bounds.minZ : otherBounds.minZ;
	bounds.maxX = bounds.maxX > otherBounds.maxX ? bounds.maxX : otherBounds.maxX;
	bounds.maxY = bounds.maxY > otherBounds.maxY ? bounds.maxY : otherBounds.maxY;
	bounds.maxZ = bounds.maxZ > otherBounds.maxZ ? bounds.maxZ : otherBounds.maxZ;
}
