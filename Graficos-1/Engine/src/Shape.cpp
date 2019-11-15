#include "Shape.h"

#include "Renderer.h"
#include "glew.h"
#include "glfw3.h"

Shape::Shape(Renderer* r) : Entity(r)
{
	shouldDispose = false;
	bufferID = -1;
	vertexCount = -1;
	shouldDisposeColor = false;
	colorBufferID = -1;
	colorVertexCount = -1;

	vertex = new float[12]
	{
		-1.0f, -1.0f, 0.0f,
		 1.0f, -1.0f, 0.0f,
		-1.0f,  1.0f, 0.0f,
		 1.0f,  1.0f, 0.0f
	};

	colorVertex = new float[12]
	{
		0.555f, 0.365f, 0.945f,
		0.945f, 0.774f, 0.589f,
		0.110f, 0.411f, 0.912f,
		0.859f, 0.258f, 0.679f,
	};

	SetVertices(vertex, 4);
	SetColorVertex(colorVertex, 4);
}

void Shape::Draw()
{
	DrawMesh(GL_TRIANGLE_STRIP);

}

void Shape::DrawMesh(int typeDraw)
{
	renderer->LoadIMatrix();
	renderer->SetWMatrix(WorldMatrix);

	renderer->BeginDraw(0);
	renderer->BindBuffer(0, bufferID, 3);
	renderer->BeginDraw(1);
	renderer->BindBuffer(1, colorBufferID, 3);
	renderer->DrawBuffer(vertexCount, typeDraw);
	renderer->EndDraw(0);
	renderer->EndDraw(1);
}

void Shape::SetColorVertex(float* vertices, int count)
{
	DisposeColor();
	colorVertexCount = count;
	shouldDisposeColor = true;
	glGenBuffers(1, &colorBufferID);
	glBindBuffer(GL_ARRAY_BUFFER, colorBufferID);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float)*count * 3, vertices, GL_STATIC_DRAW);
}

void Shape::SetIndexVertices(unsigned int* vertices, int count)
{
	idxVtxCount = count;
	shouldDisposeColor = true;
	glGenBuffers(1, &indexBufferID);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBufferID);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(float)*count, &vertices[0], GL_STATIC_DRAW);
}


void Shape::DisposeColor()
{
	if (shouldDisposeColor)
	{
		glDeleteBuffers(1, &colorBufferID);
		shouldDisposeColor = false;
	}
}

Shape::~Shape()
{
	delete[] vertex;
	delete[] colorVertex;

	Dispose();
	DisposeColor();
}
