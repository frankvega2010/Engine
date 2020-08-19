#include "Sprite.h"

#include "stb_image.h"

Sprite::Sprite(Renderer * render, int columns, int rows, int frames) : Shape(render) {
	onCollision = false;
	vertex = new float[12]
	{
		-3.0f, -3.0f, 0.f,
		-3.0f,  3.0f, 0.f,
		 3.0f, -3.0f, 0.f,
		 3.0f,  3.0f, 0.f
	};
	SetVertices(vertex, 4);

	uvArray = new float[8]
	{
		0.0f,0.0f,
		0.0f,1.0f/rows,
		1.0f/columns,0.0f,
		1.0f/columns,1.0f/rows
	};

	anim = new Animation(columns, rows, frames);

	anim->SetActualFrame(0);
	uvArray = anim->GetFrameUv(0);

	scale[0] = scale[1] = scale[2] = 6.0f;

	SetTextureVertex(uvArray, 4);
}

void Sprite::SetTextureVertex(float * vertices, int count) {
	DisposeTexture();

	uvVtxCount = count;
	shouldDisposeTexture = true;
	uvBufferID = renderer->GenBuffer(vertices, sizeof(float)* count * 2);
}

void Sprite::UpdAnim(float frame) {
	uvArray = anim->GetFrameUv(frame);
	SetTextureVertex(uvArray, 4);
}

void Sprite::SetAnim(int initF, int finishF, float timePerF) {
	//anim->SetAnimation(initF, finishF, timePerF);
}

void Sprite::setCollision()
{
	onCollision = true;
}

bool Sprite::getCollision()
{
	return onCollision;
}

void Sprite::LoadMaterial(const char * texPath, bool alpha) {
	stbi_set_flip_vertically_on_load(true);
	data = stbi_load(texPath, &width, &height, &nrChannels, 0);
	textureID = renderer->ChargeTexture(width, height, data, alpha);
	stbi_image_free(data);
	material->BindTexture("fragmentTexCoords");
}

void Sprite::DisposeTexture() {
	if (shouldDisposeTexture) {
		renderer->DestroyBuffer(uvBufferID);
		shouldDisposeTexture = false;
	}
}

void Sprite::DrawMeshWithTexture(int typeDraw) {
	renderer->LoadWorldMatrix();
	renderer->SetWorldMatrix(WorldMatrix);

	if (material != NULL) {
		material->BindProgram();
		material->Bind("WVP");
		material->SetMatrixProperty(renderer->GetWVP());
	}

	renderer->BindTexture(textureID, uvBufferID);
	renderer->BeginDraw(0);
	renderer->BindBuffer(0, bufferId, 3);
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
	delete[] uvArray;
	delete anim;
}
