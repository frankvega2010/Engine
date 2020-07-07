#include "CollisionBox.h"

void CollisionBox::SetBounds(int boundIndex, vec3 newBoundValue)
{
	bounds[boundIndex] = newBoundValue;
}
