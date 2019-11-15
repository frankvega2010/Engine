#include "Sprite.h"
#include "Renderer.h"
#include "glew.h"
#include "glfw3.h"


Sprite::Sprite(Renderer * r) : Entity(r) {
	vertex = new float[12]
	{
		-1.0f, -1.0f, 0.f,
		-1.0f,  1.0f, 0.f,
		1.0f, -1.0f, 0.f,
		1.0f,  1.0f, 0.f
	};
	SetVertices(vertex, 4);

	SetTextureVertex(uvArray, 4);
}

void Sprite::SetTextureVertex(float * vertices, int count) {
	DisposeTexture();

	uvVtxCount = count;
	shouldDisposeTexture = true;
	uvBufferID = renderer->GenBuffer(vertices, sizeof(float)* count * 2);
}


void Sprite::LoadMaterial(const char * bmpFile) {
	///*TextureImporter::LoadBMP(bmpFile, texture);*/
	//textureID = renderer->ChargeTexture(texture.width, texture.height, texture.data);
	//material->BindTexture("myTextureSampler");
}

void Sprite::DisposeTexture() {
	if (shouldDisposeTexture) {
		renderer->DestroyBuffer(uvBufferID);
		shouldDisposeTexture = false;
	}
}

void Sprite::DrawMeshWithTexture(int typeDraw) {
	renderer->LoadIMatrix();
	renderer->SetWMatrix(WorldMatrix);

	/*if (material != NULL) {
		material->BindProgram();
		material->Bind("WVP");
		material->SetMatrixProperty(renderer->GetWVP());
	}*/

	renderer->BindTexture(textureID, uvBufferID);
	renderer->BeginDraw(0);
	renderer->BindBuffer(0, bufferID, 3);
	renderer->BeginDraw(1);
	renderer->BindBuffer(1, uvBufferID, 2);
	renderer->DrawBuffer(vertexCount, typeDraw);
	renderer->EndDraw(0);
	renderer->EndDraw(1);
}

void Sprite::Draw() {
	DrawMeshWithTexture(GL_TRIANGLE_STRIP);
}

Sprite::~Sprite() {
	delete[] vertex;
	delete[] uvArray;
}