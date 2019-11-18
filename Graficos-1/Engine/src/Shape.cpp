#include "Shape.h"
#include "ColisionManager.h"
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
	render->LoadIMatrix();
	render->SetWMatrix(WorldMatrix);

	if (material != NULL) {
		material->BindProgram();
		material->Bind("WVP");
		material->SetMatrixProperty(render->GetWVP());
	}

	render->BeginDraw(0);
	render->BindBuffer(0, bufferId, 3);
	render->BeginDraw(1);
	render->BindBuffer(1, colorBufferId, 3);
	render->DrawBuffer(vertexCount, typeDraw);
	render->EndDraw(0);
	render->EndDraw(1);
}

void Shape::SetVertices(float * vertices, int count)
{
	Dispose();

	vertexCount = count;
	shouldDispose = true;
	bufferId = render->GenBuffer(vertices, sizeof(float)* count * 3);
}

void Shape::SetColorVertex(float * vertices, int count)
{
	DisposeColor();

	colorVertexCount = count;
	shouldDisposeColor = true;
	colorBufferId = render->GenBuffer(vertices, sizeof(float)* count * 3);
}

void Shape::SetMaterial(Material * material)
{
	this->material = material;
}

void Shape::Dispose()
{
	if (shouldDispose) {
		render->DestroyBuffer(bufferId);
		shouldDispose = false;
	}
}

void Shape::DisposeColor()
{
	if (shouldDisposeColor) {
		render->DestroyBuffer(colorBufferId);
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
