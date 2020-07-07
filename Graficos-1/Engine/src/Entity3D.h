#ifndef ENTITY3D
#define ENTITY3D

#include <list>
#include <glm.hpp>
#include "Shader.h"

#ifndef DLLEXPORT
#define DLLEXPORT __declspec(dllexport)
#endif // !DLLEXPORT

class Model;

class Mesh;

using namespace glm;
using namespace std;

class DLLEXPORT Entity3D
{
protected:
	Entity3D* parent;
	string name;
	list<Entity3D*> childs;
	vec3 position;
	vec3 rotation;
	vec3 scale;
	glm::mat4 modelMatrix = glm::mat4(1.0f);
	glm::mat4 worldModel = glm::mat4(1.0f);
public:
	Entity3D(Entity3D* newParent = nullptr);
	Entity3D(string newName);
	~Entity3D();
	void SetParent(Entity3D* p);
	void SetChild(Entity3D* c);
	Entity3D* GetChild(string childName);
	void UnsetChild(Entity3D* c);
	void SetPos(vec3 pos);
	vec3 GetPos(){ return position; };
	void SetRot(float angle, vec3 axis);
	vec3 GetRot() { return rotation; };
	void SetScale(vec3 sc);
	vec3 GetScale() { return scale; };
	void Draw(Shader shader);
	void UpdateModelMatrix();
	//////////////////////////
	string GetName() const { return name; }
	void SetName(string newName);
	glm::mat4 GetModelMatrix() const { return modelMatrix; }
	void SetModelMatrix(glm::mat4 newModelMatrix);
	////////////////////////////

	void GetChildNames();
};

#endif // !ENTITY3D

