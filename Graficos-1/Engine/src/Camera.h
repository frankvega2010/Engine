#ifndef CAMERA_H
#define CAMERA_H

#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include "Window.h"

class DLLEXPORT Camera
{
private:
	glm::vec3 pos;
	glm::vec3 center;
	glm::vec3 up;
	glm::mat4 ViewMatrix;
	Window* actualWindow;
	float lastX;
	float lastY;
	static Camera* thisCam;
public:
	Camera(Window* w);
	void LookAt(glm::vec3 pos, glm::vec3 center, glm::vec3 up);
	void CoutPosVec();
	glm::mat4 GetMatrix();
	glm::vec3 GetCamComponent(char comp);
	glm::vec3 GetCameraPosition();
	static double xposs;
	static double yposs;
	static void mouse_callback(GLFWwindow* window, double xpos, double ypos);
	void NewCenterCalculation();
};

#endif

