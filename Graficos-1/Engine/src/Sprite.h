#ifndef SPRITE_H
#define SPRITE_H

#include "Shape.h"

class DLLEXPORT Sprite : public Shape
{
private:

	//BMPheader texture;
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