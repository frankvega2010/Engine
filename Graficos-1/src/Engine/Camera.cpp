#include "Camera.h"
#include <iostream>
#include "Input.h"
#include "BaseGame.h"
using namespace std;

Camera* Camera::thisCam = nullptr;
double Camera::xposs = 0.0f;
double Camera::yposs = 0.0f;

float Camera::yaw = 0.0f;
float Camera::pitch = 0.0f;

bool  Camera::firstMouse = true;
float Camera::lastX = 0.0f;
float Camera::lastY = 0.0f;

Camera::Camera()
{
}

Camera::Camera(Window* w, glm::vec3 p, glm::vec3 t, glm::vec3 f, glm::vec3 u)
{
	actualWindow = w;
	glfwSetCursorPosCallback(w->GetGLFWWindowPtr(), &Camera::mouse_callback);
	thisCam = this;
	worldUp = u;
	cameraPos = p; cameraUp = u; cameraFront = f;
	cameraTarget = t;

	LookAt();
}

void Camera::SetCamera(Window* w, glm::vec3 p, glm::vec3 t, glm::vec3 f, glm::vec3 u)
{
	actualWindow = w;
	glfwSetCursorPosCallback(w->GetGLFWWindowPtr(), &Camera::mouse_callback);
	thisCam = this;
	worldUp = u;
	cameraPos = p; cameraUp = u; cameraFront = f;
	cameraTarget = t;

	LookAt();
}

void Camera::LookAt()
{
	//cameraFront = glm::normalize(cameraPos - cameraTarget);
	cameraRight = glm::normalize(glm::cross(cameraFront, worldUp));
	cameraUp = glm::normalize(glm::cross(cameraRight, cameraFront));
	viewMatrix = glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);
}

glm::mat4 Camera::GetViewMatrix()
{
	return viewMatrix;
}

void Camera::UpdateCamera()
{
	bool moved = false;
	if(Input::GetKeyPressed(GLFW_KEY_W))
	{
		cameraPos += cameraSpeed * BaseGame::GetDeltaTime() * cameraFront;
		moved = true;
	}
	if (Input::GetKeyPressed(GLFW_KEY_S))
	{
		cameraPos -= cameraSpeed * BaseGame::GetDeltaTime() * cameraFront;
		moved = true;
	}
	if (Input::GetKeyPressed(GLFW_KEY_A))
	{
		cameraPos -= glm::normalize(glm::cross(cameraFront, cameraUp)) * BaseGame::GetDeltaTime() * cameraSpeed;
		moved = true;
	}
	if (Input::GetKeyPressed(GLFW_KEY_D))
	{
		cameraPos += glm::normalize(glm::cross(cameraFront, cameraUp)) * BaseGame::GetDeltaTime() * cameraSpeed;
		moved = true;
	}

	if (moved)
	{
		LookAt();
	}
		
}


glm::vec3 Camera::GetCameraPosition()
{
	return cameraPos;
}

glm::vec3 Camera::GetCameraDirection()
{
	return cameraFront;
}

void Camera::SetCameraSpeed(float s)
{
	cameraSpeed = s;
}

void Camera::mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
	if (firstMouse)
	{
		lastX = xpos;
		lastY = ypos;
		firstMouse = false;
	}

	float xoffset = xpos - lastX;
	float yoffset = lastY - ypos;
	lastX = xpos;
	lastY = ypos;

	float sensitivity = 0.05f;
	xoffset *= sensitivity;
	yoffset *= sensitivity;

	yaw += xoffset;
	pitch += yoffset;

	if (pitch > 89.0f)
		pitch = 89.0f;
	if (pitch < -89.0f)
		pitch = -89.0f;

	glm::vec3 direction;
	direction.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
	direction.y = sin(glm::radians(pitch));
	direction.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
	Camera::thisCam->cameraFront = glm::normalize(direction);
	Camera::thisCam->LookAt();

	
}