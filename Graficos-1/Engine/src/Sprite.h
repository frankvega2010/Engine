#ifndef SPRITE_H
#define SPRITE_H
#include "Entity.h"

class Sprite : public Entity
{
private:
	bool shouldDispose;
	bool shouldDisposeColor;

	int vertexCount;
	int colorVertexCount;
	int idxVtxCount;

	unsigned int colorBufferID;
	unsigned int bufferID;
	unsigned int indexBufferID;
	unsigned int* indxVertex;
	float* vertex;
	float* colorVertex;
	float * uvArray;
	unsigned int uvBufferID;
	unsigned int textureID;
	int uvVtxCount;
	bool shouldDisposeTexture;
public:
	void Draw() override;
	void DrawMeshWithTexture(int typeDraw);
	void LoadMaterial(const char * bmpFile);
	void DisposeTexture();
	void SetTextureVertex(float * vertices, int count);
	Sprite(Renderer * r);
	~Sprite();
};
#endif
