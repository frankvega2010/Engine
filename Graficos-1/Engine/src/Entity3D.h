#ifndef ENTITY3D
#define ENTITY3D

#include <list>
#include <glm.hpp>
#include "Shader.h"

#ifndef DLLEXPORT
#define DLLEXPORT __declspec(dllexport)
#endif // !DLLEXPORT

class Model;

using namespace glm;
using namespace std;

class DLLEXPORT Entity3D
{
private:
	Model* model;
	Entity3D* parent;
	list<Entity3D*> childs;
	vec3 position;
	vec3 rotation;
	vec3 scale;
	glm::mat4 modelMatrix = glm::mat4(1.0f);
public:
	Entity3D();
	Entity3D(string const &path);
	~Entity3D();
	void SetParent(Entity3D* p);
	void SetChild(Entity3D* c);
	void UnsetChild(Entity3D* c);
	void SetPos(vec3 pos);
	vec3 GetPos(){ return position; };
	void SetRot(vec3 rot);
	vec3 GetRot() { return rotation; };
	void SetScale(vec3 sc);
	vec3 GetScale() { return scale; };
	void Draw(Shader shader);
	void Draw();
};

#endif // !ENTITY3D

