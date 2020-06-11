#include "CollisionManager.h"

#include "Shape.h"

bool CollisionManager::CheckCollision(Shape* shape1, Shape* shape2)
{
	return (shape1->GetPos().x - shape1->GetScale().x / 2 < shape2->GetPos().x + shape2->GetScale().x / 2 &&
		shape1->GetPos().x + shape1->GetScale().x / 2 > shape2->GetPos().x - shape2->GetScale().x / 2 &&
		shape1->GetPos().y - shape1->GetScale().y / 2 < shape2->GetPos().y + shape2->GetScale().y / 2 &&
		shape1->GetPos().y + shape1->GetScale().y / 2 > shape2->GetPos().y - shape2->GetScale().y / 2);
}