#include "Renderer.h"
#include <glew.h>

using namespace std;

Renderer* Renderer::renderer = nullptr;
Camera* Renderer::cam = new Camera();
vector<BSP> Renderer::bspPlanes;


bool Renderer::Start(Window* wnd) {
	cout << "Renderer::Start()" << endl;
	win = wnd;
	glfwMakeContextCurrent((GLFWwindow*)wnd->GetGLFWWindowPtr());

	glEnable(GL_BLEND);
	//glEnable(GL_CULL_FACE);
	glEnable(GL_DEPTH_TEST);
	glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);

	if (glewInit() != GLEW_OK) {
		cout << "Falló al inicializar GLEW\n" << endl;
		return -1;
	}

	glGenVertexArrays(1, &VertexArrayID);
	glBindVertexArray(VertexArrayID);
	//ProjectionMatrix = glm::ortho(-10.0f, 10.0f, -10.0f, 10.0f, 0.0f, 100.f);

	ProjectionMatrix = glm::perspectiveFov(glm::radians(45.0f), 640.0f, 480.0f, 1.0f, 100.0f);

	//cam = new Camera(win, glm::vec3(0, 0, 3), glm::vec3(0, 0, 0), glm::vec3(0.0f, 0.0f, -1.0f), glm::vec3(0, 1, 0));
	cam->SetCamera(win, glm::vec3(0, 0, 3), glm::vec3(0, 0, 0), glm::vec3(0.0f, 0.0f, -1.0f), glm::vec3(0, 1, 0));
	cam->cameraFar = 1000.0f;
	cam->cameraNear = 1.0f;
	cam->cameraFOV = 45.0f;
	//cam->cameraFOV = 45.0f;

	WorldMatrix = glm::mat4(1.0f);

	UpdateWVP();

	f = new Frustum(cam->GetViewMatrix() * GetProjMatrix());

	renderer = this;
	return true;
}

bool Renderer::Stop() {
	cout << "Renderer::Stop()" << endl;
	return true;
}

void Renderer::setClearScreenColor(float r, float g, float b, float a) {
	glClearColor(r, g, b, a);
}

unsigned int Renderer::GenBuffer(float * buffer, int size)
{
	unsigned int vertexBuffer;
	glGenBuffers(1, &vertexBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, size, buffer, GL_STATIC_DRAW);
	return vertexBuffer;
}


void Renderer::BeginDraw(unsigned int atribID) {
	glEnableVertexAttribArray(atribID);
}

void Renderer::EndDraw(unsigned int atribID) {
	glDisableVertexAttribArray(atribID);
}

void Renderer::BindBuffer(unsigned int atribID, unsigned int vtxBuffer, unsigned int size) {
	glBindBuffer(GL_ARRAY_BUFFER, vtxBuffer);
	glVertexAttribPointer(
		atribID,            // debe corresponder en el shader.
		size,                  // tamaño
		GL_FLOAT,           // tipo
		GL_FALSE,           // normalizado?
		0,                  // Paso
		(void*)0            // desfase del buffer
	);
}

unsigned int Renderer::ChargeTexture(unsigned int width, unsigned int height, unsigned char * data, bool alpha)
{
	unsigned int textureID;
	glGenTextures(1, &textureID);
	glBindTexture(GL_TEXTURE_2D, textureID);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	if (data)
	{
		if(!alpha)
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
		else
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
		cout << "cargo tex" << endl;
	}
	else
		cout << "fallo tex" << endl;

	return textureID;
}

void Renderer::BindTexture(unsigned int texture, unsigned int textureID)
{
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture);
	glUniform1i(textureID, 0);
}

void Renderer::DrawBuffer(int size, int typeDraw)
{
	glDrawArrays(typeDraw, 0, size);
}

void Renderer::DestroyBuffer(unsigned int buffer)
{
	glDeleteBuffers(1, &buffer);
}

void Renderer::ClearScreen() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Renderer::SwapBuffer() {
	glfwSwapBuffers((GLFWwindow*)win->GetGLFWWindowPtr());
}

void Renderer::UpdateWVP()
{
	WVP = ProjectionMatrix * cam->GetViewMatrix() * WorldMatrix;
}

glm::mat4 & Renderer::GetWVP()
{
	return WVP;
}

void Renderer::LoadWorldMatrix()
{
	WorldMatrix = glm::mat4(1.0f);
}

void Renderer::SetWorldMatrix(glm::mat4 matrix)
{
	WorldMatrix = matrix;
	UpdateWVP();
}

void Renderer::MultiplyWorldMatrix(glm::mat4 matrix)
{
	WorldMatrix *= matrix;
	UpdateWVP();
}

Camera* Renderer::GetCam()
{
	return cam;
}

glm::mat4 Renderer::GetProjMatrix()
{
	return ProjectionMatrix;
}

void Renderer::AddBSPPlane(BSP newPlane)
{
	bspPlanes.push_back(newPlane);
}

void Renderer::CollectAllRootEntities(list<Entity3D*>& entities, Entity3D* entity)
{
	for (list<Entity3D*>::iterator itBeg = entity->GetChilds().begin(); itBeg != entity->GetChilds().end(); ++itBeg)
	{
		Entity3D* ent = (*itBeg);
		if (!ent->GetBSP() && !ent->IsRootEntity())
		{
			entities.push_back(ent);
		}
				
	}
}

void Renderer::CheckSceneVisibility(Entity3D* root)
{
	list<Entity3D*> entities;
	CollectAllRootEntities(entities, root); // Agarra todas las entities principales (root de modelos)

	if (isBSPEnabled)
	{
		
		for (int i = 0; i < bspPlanes.size(); i++)
		{
			bspPlanes[i].SetCameraSide(bspPlanes[i].CalculateSide(Camera::thisCam->GetCameraPosition()));
			entities.erase(remove_if(entities.begin(), entities.end(), [i](Entity3D* entity) 
			{
				// borra los elementos de la lista (entities en la escena) que devuelvan TRUE.
				// para que el otro plano no lo tenga que chequear de nuevo.

				const bool toRemove = Renderer::renderer->IsEntityInCameraSide(entity, bspPlanes[i]);

				return toRemove;
			}), entities.end());

			if (showBSPCulledEntities)
			{
				cout << "BSP Entities In Screen: " << Entity3D::entitiesInScreen << endl;
			}
			
		}
	}

	if (isFrustumCullingEnabled)
	{
		if (entities.size() > 0)
		{
			for (list<Entity3D*>::iterator itBeg = entities.begin(); itBeg != entities.end(); ++itBeg)
			{
				Entity3D* ent = (*itBeg);
				CheckEntityVisibility(ent);
			}
		}
	}
		
}

bool Renderer::IsEntityInCameraSide(Entity3D* entity, BSP currentPlane)
{
	glm::vec3 min, max;

	min.x = entity->bounds.minX;
	min.y = entity->bounds.minY;
	min.z = entity->bounds.minZ;

	max.x = entity->bounds.maxX;
	max.y = entity->bounds.maxY;
	max.z = entity->bounds.maxZ;

	bool toRemove = !currentPlane.IsBoxInCameraSide(min, max);

	if (toRemove)
	{
		entity->SetVisibilityAll(false);
	}
	else
	{
		entity->SetVisibility(true);

		for (list<Entity3D*>::iterator itBeg = entity->GetChilds().begin(); itBeg != entity->GetChilds().end(); ++itBeg)
		{
			Entity3D* ent = (*itBeg);

			toRemove = IsEntityInCameraSide(ent, currentPlane);
		}
	}

	return toRemove;
}

void Renderer::TurnOffEntityCounter()
{
	Entity3D::entitiesInScreen = 0;
}

void Renderer::CheckEntityVisibility(Entity3D* toRender)
{
	bool initialFrustumState = toRender->GetIsInFrustum();

	if (!toRender->GetBSP() && !toRender->IsRootEntity())
	{
		toRender->SetIsInFrustum(f->IsBoxVisible(toRender->AABB->GetMin(), toRender->AABB->GetMax(), toRender, toRender->GetIsInFrustum()));

		if (isBSPEnabled)
		{
			if (initialFrustumState != toRender->GetIsInFrustum())
			{
				if (toRender->GetVisibility() == toRender->GetLastVisibilityState())
				{
					if (toRender->GetVisibility() && toRender->GetIsInFrustum())
					{
						if (toRender->entityType == mesh)
						{
							Entity3D::entitiesInScreen++;
						}

					}
					else
					{
						Entity3D::entitiesInScreen--;
						if (Entity3D::entitiesInScreen < 0)
						{
							Entity3D::entitiesInScreen = 0;
						}
					}

					cout << "FRUSTUM Entities In Screen: " << Entity3D::entitiesInScreen << endl;
				}
			}
		}
		else
		{
			if (initialFrustumState != toRender->GetIsInFrustum())
			{
				if (toRender->GetIsInFrustum())
				{
					if (toRender->entityType == mesh)
					{
						Entity3D::entitiesInScreen++;
					}
				}
				else
				{

					Entity3D::entitiesInScreen--;
					if (Entity3D::entitiesInScreen < 0)
					{
						Entity3D::entitiesInScreen = 0;
					}
				}

				cout << "Entities In Screen: " << Entity3D::entitiesInScreen << endl;
			}
		}

		if (toRender->GetIsInFrustum())
		{
			if (toRender->GetChilds().size() > 0)
			{
				for (list<Entity3D*>::iterator itBeg = toRender->GetChilds().begin(); itBeg != toRender->GetChilds().end(); ++itBeg)
				{
					Entity3D* ent = (*itBeg);
					CheckEntityVisibility(ent);
				}
			}
		}
		else
		{
			toRender->SetIsInFrustumAll(false);
		}
	}

}

Renderer::Renderer() {
}


Renderer::~Renderer() {
}
