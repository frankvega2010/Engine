#ifndef RENDERER_H
#define RENDERER_H

#include "glm.hpp"
#include "gtc/matrix_transform.hpp"
#include "gtx/transform.hpp"
#include "gtc/type_ptr.hpp"

#define DLLEXPORT __declspec(dllexport)

class DLLEXPORT Renderer
{
private:
	unsigned int uniModel;
	glm::mat4 myMatrix;
public:
	void Init();
	void SetAttributes();
	void DeInit();
	void Rotate(float angle, glm::vec3 axis);
	void Translate(float value, glm::vec3 axis);
	void Scale(glm::vec3 scaleValues);
};

#endif
