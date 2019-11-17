#ifndef SPRITE_H
#define SPRITE_H

#include "Shape.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

class DLLEXPORT Sprite : public Shape
{
private:

	//BMPheader texture;

	int width;
	int height;
	int nrChannels;
	unsigned char* data;
	float * uvArray;
	unsigned int uvBufferID;
	unsigned int textureID;
	int uvVtxCount;
	bool shouldDisposeTexture;
	//Animation * anim;

	bool onCollision;
public:
	void Draw() override;
	void DrawMeshWithTexture(int typeDraw);
	void LoadMaterial(const char * bmpFile);
	void DisposeTexture();
	void SetTextureVertex(float * vertices, int count);

	void UpdAnim(float deltaTime);
	void SetAnim(int initF, int finishF, float timePerF);

	void setCollision();
	bool getCollision();

	Sprite(Renderer * render, int columns, int rows);
	~Sprite();
};

#endif