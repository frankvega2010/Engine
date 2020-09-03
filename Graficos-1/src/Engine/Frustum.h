#ifndef FRUSTUM_H
#define FRUSTUM_H

#include <glm/glm.hpp>
#include <iostream>

#include "Entity3D.h"
#include "Window.h"
#include "CollisionBox.h"

struct Plane {
	glm::vec3 n;
	float D;
};

class Frustum
{
public:
	Frustum();
	~Frustum();

	void calculate_frustum(Window* w, glm::vec3 right, glm::vec3 up, glm::vec3 front, glm::vec3 pos, float fov, float near, float far);
	bool is_in_frustum(Bounds bounds,vec3 position,string name,const bool isInFrustum);
private:
	std::vector<Plane> planes;
};

#endif FRUSTUM_H
