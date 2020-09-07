#ifndef BSP_H
#define BSP_H

#include "glm/glm.hpp"

#define DLLEXPORT _declspec(dllexport)

class DLLEXPORT BSP
{
public:
	BSP(glm::vec3 point1, glm::vec3 point2, glm::vec3 point3);
	bool AreInSameSide(glm::vec3 point1, glm::vec3 point2);
	bool IsInCameraSide(glm::vec3 point1);
	bool IsBoxInCameraSide(glm::vec3 boxMin, glm::vec3 boxMax);
	float CalculateSide(glm::vec3 point);
	void SetCameraSide(float newCameraSide);

private:
	glm::vec4 planeVector;
	float cameraSide;
};

#endif // BSP_H
