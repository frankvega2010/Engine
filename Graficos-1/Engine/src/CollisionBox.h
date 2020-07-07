#ifndef COLLISION_BOX_H
#define COLLISION_BOX_H

#include "glm.hpp"

#define DLLEXPORT _declspec(dllexport)

using namespace glm;

#define TOTALBOUNDS 8

class DLLEXPORT CollisionBox
{
private:
	vec3 bounds[TOTALBOUNDS];
public:
	void SetBounds(int boundIndex, vec3 newBoundValue);
};

#endif
