#ifndef SHAPE_H
#define SHAPE_H

#include "Entity.h"
#include "Material.h"


class DLLEXPORT Shape : public Entity
{
protected:
	Material * material;

	bool shouldDispose;
	bool shouldDisposeColor;

	int vertexCount;
	int colorVertexCount;

	unsigned int colorBufferId;
	unsigned int bufferId;

	float * vertex;
	float * colorVertex;

public:
	Shape(Renderer * render);
	virtual void Draw();
	void DrawMesh(int typeDraw);
	void SetVertices(float * vertices, int count);
	void SetColorVertex(float * vertices, int count);
	void SetMaterial(Material* material);
	void Dispose();
	void DisposeColor();
	~Shape();
};

#endif