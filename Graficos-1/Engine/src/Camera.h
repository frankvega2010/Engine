#ifndef CAMERA_H
#define CAMERA_H

#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include "Window.h"

class DLLEXPORT Camera
{
private:
	glm::vec3 cameraPos;
	glm::vec3 cameraTarget = glm::vec3(0.0f, 0.0f, 0.0f);
	glm::vec3 up;
	glm::vec3 cameraDirection;
	glm::vec3 cameraRight;
	glm::vec3 cameraUp;

	float cameraSpeed;

	static float yaw;
	static float pitch;

	glm::mat4 viewMatrix;
	Window* actualWindow;
	
	static bool firstMouse;
	static float lastX;
	static float lastY;

	
public:
	static Camera* thisCam;
	glm::vec3 cameraFront;
	Camera(Window* w, glm::vec3 p, glm::vec3 t, glm::vec3 f, glm::vec3 u);
	void LookAt();
	void SetCameraSpeed(float s);
	glm::mat4 GetViewMatrix();
	glm::vec3 GetCameraPosition();
	glm::vec3 GetCameraDirection();
	void UpdateCamera();
	static double xposs;
	static double yposs;
	static void mouse_callback(GLFWwindow* window, double xpos, double ypos);
	void NewCenterCalculation();
};

#endif

