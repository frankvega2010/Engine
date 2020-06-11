#ifndef SPRITE_H
#define SPRITE_H

#include "Shape.h"

#include "Animation.h"

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
	Animation * anim;

	bool onCollision;
public:
	void Draw() override;
	void DrawMeshWithTexture(int typeDraw);
	void LoadMaterial(const char * path, bool alpha);
	void DisposeTexture();
	void SetTextureVertex(float * vertices, int count);

	void UpdAnim(float frame);
	void SetAnim(int initF, int finishF, float timePerF);

	void setCollision();
	bool getCollision();

	Sprite(Renderer * render, int columns, int rows, int frames);
	~Sprite();
};
#endif