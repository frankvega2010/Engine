#include "Shape.h"

void Shape::SetIndices(GLuint i[3])
{
	for (int x = 0; x < 3; x++)
	{
		indices[x] = i[x];
	}
}
