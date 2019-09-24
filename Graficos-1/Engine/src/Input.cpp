#include "Input.h"
#include <iostream>
using namespace std;


//======================================== MOVIMIENTO ========================================
float Input::keyW(float posicionY) {

	posicionY += 0.01f;
	return posicionY;
}
float Input::keyA(float posicionY) {

	posicionY -= 0.01f;
	return posicionY;
}
float Input::keyS(float posicionX) {

	posicionX -= 0.01f;
	return posicionX;
}
float Input::keyD(float posicionX) {

	posicionX += 0.01f;
	return posicionX;
}
//======================================== TAMANO ========================================
//Tamano x
float Input::keyUP(float sizeX) {

	sizeX += 0.01f;
	return sizeX;
}
float Input::keyDOWN(float sizeX) {

	sizeX -= 0.01f;
	return sizeX;
}
//Tamano y
float Input::keyLEFT(float sizeY) {

	sizeY -= 0.01f;
	return sizeY;
}
//Tamano z
float Input::keyRIGHT(float sizeY) {

	sizeY += 0.01f;
	return sizeY;
}
//======================================== ROTACIONES ========================================
//Rotaciones x
float Input::keyY(float rotateX) {

	rotateX--;
	return rotateX;
}
float Input::keyU(float rotateX) {

	rotateX++;
	return rotateX;
}
//Rotaciones y
float Input::keyH(float rotateY) {

	rotateY--;
	return rotateY;
}
float Input::keyJ(float rotateY) {

	rotateY++;
	return rotateY;
}
//Rotaciones z
float Input::keyN(float rotateZ) {

	rotateZ--;
	return rotateZ;
}
float Input::keyM(float rotateZ) {

	rotateZ++;
	return rotateZ;
}
//========================================CERRAR VENTANA========================================
void Input::keyEsc(GLFWwindow* window) {
	glfwDestroyWindow(window);
}
