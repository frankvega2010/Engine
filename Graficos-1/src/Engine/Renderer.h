#ifndef RENDERER_H
#define RENDERER_H

#include "Window.h"
#include <gtc/matrix_transform.hpp>
#include <glfw3.h>
#include <iostream>
#include "Entity3D.h"
#include "Camera.h"
#include "Frustum.h"
#include "BSP.h"


using namespace std;
using namespace glm;

class Shader;

class DLLEXPORT Renderer
{
private:
	Window* win;
	unsigned int VertexArrayID;
	unsigned int ColorVertexArrayID;
	glm::mat4 WorldMatrix;
	glm::mat4 ProjectionMatrix;
	glm::mat4 WVP;
	static vector<class BSP> bspPlanes;
	
public:
	bool Start(Window* wnd);
	bool Stop();
	void setClearScreenColor(float r, float g, float b, float a);
	unsigned int GenBuffer(float* buffer, int size);
	void BeginDraw(unsigned int atribID);
	void EndDraw(unsigned int atribID);
	void BindBuffer(unsigned int atribID, unsigned int vtxBuffer, unsigned int size);
	unsigned int ChargeTexture(unsigned int width, unsigned int height, unsigned char * data, bool alpha);
	void BindTexture(unsigned int texture, unsigned int textureID);
	void DrawBuffer(int size, int typeDraw);
	void DestroyBuffer(unsigned int buffer);
	void ClearScreen();
	void SwapBuffer();
	void UpdateWVP();
	glm::mat4& GetWVP();
	void SetWorldMatrix(glm::mat4 matrix);
	void LoadWorldMatrix();
	void MultiplyWorldMatrix(glm::mat4 matrix);
	Camera* GetCam();
	glm::mat4 GetProjMatrix();
	static void AddBSPPlane(class BSP newPlane);
	void CheckSceneVisibility(Entity3D* root);
	void CollectAllRootEntities(list<Entity3D*>& entities, Entity3D* entity);
	void CheckEntityVisibility(Entity3D* toRender);
	bool isBSPEnabled = true;
	bool isFrustumCullingEnabled = true;
	bool IsEntityInCameraSide(Entity3D* entity, BSP currentPlane);
	static Camera* cam;
	
	static Renderer* renderer;
	
	Frustum* f;
	list<Entity3D*> entitiesRendered;

	Renderer();
	~Renderer();
};

#endif