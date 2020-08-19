#include "Shape.h"

Shape::Shape(Renderer * render) :Entity(render)
{
	shouldDispose = false;
	material = NULL;
	bufferId = -1;
	vertexCount = -1;
	shouldDisposeColor = false;
	colorBufferId = -1;
	colorVertexCount = -1;

	vertex = new float[12]
	{
		-1.0f,-1.0f , 0.0f ,
		1.0f,-1.0f , 0.0f ,
		-1.0f, 1.0f , 0.0f ,
		1.0f, 1.0f , 0.0f
	};

	colorVertex = new float[12]
	{
		0.555f,  0.365f,  0.945f,
		0.945f,  0.774f,  0.589f,
		0.859f,  0.258f,  0.679f,
		0.110f,  0.411f,  0.912f
	};
	SetVertices(vertex, 4);
	SetColorVertex(colorVertex, 4);
}

void Shape::DrawMesh(int typeDraw)
{
	renderer->LoadWorldMatrix(); //rever
	renderer->SetWorldMatrix(WorldMatrix);

	if (material != NULL) {
		material->BindProgram();
		material->Bind("WVP");
		material->SetMatrixProperty(renderer->GetWVP());
	}

	renderer->BeginDraw(0);
	renderer->BindBuffer(0, bufferId, 3);
	renderer->BeginDraw(1);
	renderer->BindBuffer(1, colorBufferId, 3);
	renderer->DrawBuffer(vertexCount, typeDraw);
	renderer->EndDraw(0);
	renderer->EndDraw(1);
}

void Shape::SetVertices(float * vertices, int count)
{
	Dispose();

	vertexCount = count;
	shouldDispose = true;
	bufferId = renderer->GenBuffer(vertices, sizeof(float)* count * 3);
}

void Shape::SetColorVertex(float * vertices, int count)
{
	DisposeColor();

	colorVertexCount = count;
	shouldDisposeColor = true;
	colorBufferId = renderer->GenBuffer(vertices, sizeof(float)* count * 3);
}

void Shape::SetMaterial(Material * mat)
{
	material = mat;
}

void Shape::Dispose()
{
	if (shouldDispose) {
		renderer->DestroyBuffer(bufferId);
		shouldDispose = false;
	}
}

void Shape::DisposeColor()
{
	if (shouldDisposeColor) {
		renderer->DestroyBuffer(colorBufferId);
		shouldDisposeColor = false;
	}
}

void Shape::Draw()
{
	DrawMesh(GL_TRIANGLE_STRIP);
}

Shape::~Shape()
{
	delete[] vertex;
	delete[] colorVertex;
	delete material;
	Dispose();
	DisposeColor();
}
