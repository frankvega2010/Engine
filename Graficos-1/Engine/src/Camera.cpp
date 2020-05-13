#include "Camera.h"
#include <iostream>

using namespace std;

Camera* Camera::thisCam = nullptr;
double Camera::xposs = 0.0f;
double Camera::yposs = 0.0f;

Camera::Camera(Window* w)
{
	actualWindow = w;
	glfwSetCursorPosCallback(w->GetGLFWWindowPtr(), &Camera::mouse_callback);
	thisCam = this;
}

void Camera::LookAt(glm::vec3 p, glm::vec3 c, glm::vec3 u)
{
	pos = p; center = c; up = u;
	ViewMatrix = glm::lookAt(pos, center, up);
}

glm::mat4 Camera::GetMatrix()
{
	return ViewMatrix;
}

void Camera::CoutPosVec()
{
	cout << "x:" << up.x << "y:" << up.y
		<< "z:" << up.z << endl;
}

glm::vec3 Camera::GetCamComponent(char comp)
{
	switch (comp)
	{
	case 'p':
		return pos;
		break;
	case 'c':
		return center;
		break;
	case 'u':
		return up;
		break;
	default:
		return glm::vec3(0.0f, 0.0f, 0.0f);
		break;
	}
}

glm::vec3 Camera::GetCameraPosition()
{
	return pos;
}

void Camera::NewCenterCalculation()
{
	lastX = actualWindow->GetWidth() / 2;
	lastY = actualWindow->GetHeigth() / 2;

	float xoffset = xposs - lastX;
	float yoffset = lastY - yposs; // reversed since y-coordinates range from bottom to top
	lastX = xposs;
	lastY = yposs;

	const float sensitivity = 0.05f;
	xoffset *= sensitivity;
	yoffset *= sensitivity;

	glm::vec3 newCenter = { xoffset, yoffset, center.z };

	LookAt(pos, newCenter, up);
}

void Camera::mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
	xposs = xpos;
	yposs = ypos;
	Camera::thisCam->NewCenterCalculation();
}