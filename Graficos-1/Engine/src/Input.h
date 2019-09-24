#ifndef INPUT_H
#define INPUT_H

#include "glfw3.h"

class Input
{
private:

public:
	float keyY(float rotateX);
	float keyU(float rotateX);
	float keyH(float rotateY);
	float keyJ(float rotateY);
	float keyN(float rotateZ);
	float keyM(float rotateZ);
	float keyW(float posicionY);
	float keyS(float posicionY);
	float keyA(float posicionX);
	float keyD(float posicionX);
	float keyUP(float sizeX);
	float keyDOWN(float sizeX);
	float keyRIGHT(float sizeY);
	float keyLEFT(float sizeY);
	void keyEsc(GLFWwindow *window);
};

#endif INPUT_H