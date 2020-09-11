#include "Entity3D.h"

#include "BaseGame.h"
#include "gtx/quaternion.hpp"
#include "Renderer.h"
#include "Camera.h"
#include "Model.h"

int Entity3D::entitiesInScreen;

Entity3D::Entity3D(Entity3D* newParent)
{
	parent = nullptr;
	position = vec3(0.f);
	rotation = vec3(0.f);
	scale = vec3(1.f);
	isVisible = true;
	isInFrustum = true;
	isRoot = false;
	
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
	AABB = new CollisionBox();
	
	collisionBox->GenerateBoundingBox(bounds);
	AABB->GenerateBoundingBox(bounds);
	//BaseGame::GetRootEntity()->CalculateBoundsWithChilds();
}

Entity3D::Entity3D(string newName)
{
	entityType = entity;
	
	name = newName;
	isVisible = true;
	isInFrustum = true;

	collisionBox = new CollisionBox();
	AABB = new CollisionBox();
	
	collisionBox->GenerateBoundingBox(bounds);
	AABB->GenerateBoundingBox(bounds);

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

list<Entity3D*>& Entity3D::GetChilds()
{
	return childs;
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
	BaseGame::GetRootEntity()->UpdateModelMatAndBoundingBox();
}

void Entity3D::SetRot(float angle, vec3 axis)
{
	rotation.x += angle * axis.x;
	rotation.y += angle * axis.y;
	rotation.z += angle * axis.z;
	
	modelMatrix = glm::rotate(modelMatrix, radians(angle), axis);
	BaseGame::GetRootEntity()->UpdateModelMatAndBoundingBox();
}

void Entity3D::SetScale(vec3 sc)
{
	scale = sc;
	modelMatrix = glm::scale(modelMatrix, scale);
	BaseGame::GetRootEntity()->UpdateModelMatAndBoundingBox();
}

void Entity3D::Draw(Shader shader)
{
	if (name == "root")
	{
		// inicio de chequeo BSP
		Renderer::renderer->CheckSceneVisibility(this);
	}

	for (list<Entity3D*>::iterator itBeg = childs.begin(); itBeg != childs.end(); ++itBeg)
	{
		Entity3D* ent = (*itBeg);

		if (!ent->isBSP)
		{
			if(!ent->isVisible)
				ent->name = ent->name;
		}

		if (!Renderer::renderer->isBSPEnabled)
		{
			ent->isVisible = true;
		}

		if (!Renderer::renderer->isFrustumCullingEnabled)
		{
			ent->isInFrustum = true;
		}

		if (isBSP || (ent->isVisible && ent->isInFrustum))
		{
			if (ent->entityType == mesh)
			{
				Mesh* m = static_cast<Mesh*> (ent);
				if (ent->isBSP)
				{
					m->DrawBSP(shader);
				}
				else
				{
					m->Draw(shader);
				}
				
			}
			else
			{
				ent->Draw(shader);
			}
		}

	}
	
	//AABB->DrawCollisionBox(worldModel);
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

void Entity3D::SetIsInFrustumAll(bool frustumState)
{
	bool canChange = false;
	if (isInFrustum != frustumState)
	{
		canChange = true;
	}

	isInFrustum = frustumState;

	if (GetChilds().size() > 0)
	{
		for (list<Entity3D*>::iterator itBeg = childs.begin(); itBeg != childs.end(); ++itBeg)
		{
			Entity3D* ent = (*itBeg);
			ent->SetIsInFrustumAll(isInFrustum);
		}
	}
}

Bounds Entity3D::UpdateModelMatAndBoundingBox()
{
	if (parent != nullptr)
		worldModel = parent->worldModel * modelMatrix;

	Bounds childBounds;
	
	for (list<Entity3D*>::iterator itBeg = childs.begin(); itBeg != childs.end(); ++itBeg)
	{
		childBounds = CalculateBounds(childBounds, (*itBeg)->UpdateModelMatAndBoundingBox());
	}

	bounds = GenerateBounds(collisionBox->vertices, worldModel);
	
	CalculateBounds(childBounds);
	AABB->GenerateBoundingBox(bounds);
	
	return bounds;
}

void Entity3D::CalculateBoundsWithChilds()
{
	for (list<Entity3D*>::iterator itBeg = childs.begin(); itBeg != childs.end(); ++itBeg)
	{
		(*itBeg)->CalculateBoundsWithChilds();
		bounds = CalculateBounds(bounds,(*itBeg)->bounds);
	}
	
	collisionBox->GenerateBoundingBox(bounds);
}

bool Entity3D::GetBSP()
{
	return isBSP;
}

void Entity3D::SetBSP(bool bspState)
{
	isBSP = bspState;

	for (list<Entity3D*>::iterator itBeg = childs.begin(); itBeg != childs.end(); ++itBeg)
	{
		Entity3D* ent = (*itBeg);
		ent->SetBSP(isBSP);
	}
}

bool Entity3D::IsRootEntity()
{
	return isRoot;
}

void Entity3D::SetIsRoot(bool rootState)
{
	isRoot = rootState;
}

void Entity3D::SetVisibilityAll(int visState)
{
	int initialState = isVisible;

	lastVisibilityState = isVisible;
	isVisible = visState;

	//cout << "IS VISIBLE " << isVisible << " &  IS VISIBLE INITIAL " << initialState << endl;

	if (lastVisibilityState != isVisible)
	{
		if (isVisible)
		{
			if (isInFrustum)
			{
				if (entityType == mesh)
				{
					Entity3D::entitiesInScreen++;
				}
			}

		}
		else
		{
			if (entityType == mesh)
			{
				Entity3D::entitiesInScreen--;
				if (Entity3D::entitiesInScreen < 0)
				{
					Entity3D::entitiesInScreen = 0;
				}
			}

		}

		//cout << "IS VISIBLE " << isVisible << " &  IS IN FRUSTUM " << isInFrustum << endl;
		//cout << "BSP Entities In Screen: " << Entity3D::entitiesInScreen << endl;
	}
	
	if (GetChilds().size() > 0)
	{
		for (list<Entity3D*>::iterator itBeg = childs.begin(); itBeg != childs.end(); ++itBeg)
		{
			Entity3D* ent = (*itBeg);
			ent->SetVisibilityAll(isVisible);
		}
	}

	
}

void Entity3D::SetVisibility(int visState)
{
	int initialState = isVisible;

	lastVisibilityState = isVisible;
	isVisible = visState;

	if (lastVisibilityState != isVisible)
	{

		if (isVisible)
		{
			if (isInFrustum)
			{
				if (entityType == mesh)
				{
					Entity3D::entitiesInScreen++;
				}
				
			}

		}
		else
		{
			if (entityType == mesh)
			{
				Entity3D::entitiesInScreen--;
				if (Entity3D::entitiesInScreen < 0)
				{
					Entity3D::entitiesInScreen = 0;
				}
			}

		}

		//cout << "BSP Entities In Screen: " << Entity3D::entitiesInScreen << endl;
	}

}

bool Entity3D::GetVisibility()
{
	return isVisible;
}

int Entity3D::GetLastVisibilityState()
{
	return lastVisibilityState;
}

bool Entity3D::GetIsInFrustum()
{
	return isInFrustum;
}

void Entity3D::SetIsInFrustum(bool frustumState)
{
	isInFrustum = frustumState;
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

Bounds Entity3D::CalculateBounds(Bounds b1, Bounds b2)
{
	Bounds returnBounds;
	returnBounds.minX = b1.minX < b2.minX ? b1.minX : b2.minX;
	returnBounds.minY = b1.minY < b2.minY ? b1.minY : b2.minY;
	returnBounds.minZ = b1.minZ < b2.minZ ? b1.minZ : b2.minZ;
	returnBounds.maxX = b1.maxX > b2.maxX ? b1.maxX : b2.maxX;
	returnBounds.maxY = b1.maxY > b2.maxY ? b1.maxY : b2.maxY;
	returnBounds.maxZ = b1.maxZ > b2.maxZ ? b1.maxZ : b2.maxZ;
	return returnBounds;
}

Bounds Entity3D::GenerateBounds(vec3 v[], mat4 mat)
{
	vec3 v2[TOTALVERTICES];
	for(int i=0;i<TOTALVERTICES;i++)
	{
		v2[i] = mat * vec4(v[i],1.f);
	}

	return GenerateBoundsByVertex(v2);
}

Bounds Entity3D::GenerateBoundsByVertex(vec3 v[])
{
	Bounds returnBounds;
	for(int i=0;i<TOTALVERTICES;i++)
	{
		returnBounds.minX = v[i].x < returnBounds.minX ? v[i].x : returnBounds.minX;
		returnBounds.minY = v[i].y < returnBounds.minY ? v[i].y : returnBounds.minY;
		returnBounds.minZ = v[i].z < returnBounds.minZ ? v[i].z : returnBounds.minZ;
		returnBounds.maxX = v[i].x > returnBounds.maxX ? v[i].x : returnBounds.maxX;
		returnBounds.maxY = v[i].y > returnBounds.maxY ? v[i].y : returnBounds.maxY;
		returnBounds.maxZ = v[i].z > returnBounds.maxZ ? v[i].z : returnBounds.maxZ;
	}
	return returnBounds;
}

Bounds Entity3D::GenerateBoundsByVertex(vector<vec3> v)
{
	Bounds returnBounds;
	for (int i = 0; i < v.size(); i++)
	{
		returnBounds.minX = v[i].x < returnBounds.minX ? v[i].x : returnBounds.minX;
		returnBounds.minY = v[i].y < returnBounds.minY ? v[i].y : returnBounds.minY;
		returnBounds.minZ = v[i].z < returnBounds.minZ ? v[i].z : returnBounds.minZ;
		returnBounds.maxX = v[i].x > returnBounds.maxX ? v[i].x : returnBounds.maxX;
		returnBounds.maxY = v[i].y > returnBounds.maxY ? v[i].y : returnBounds.maxY;
		returnBounds.maxZ = v[i].z > returnBounds.maxZ ? v[i].z : returnBounds.maxZ;
	}
	return returnBounds;
}
