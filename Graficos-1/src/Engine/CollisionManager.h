#ifndef COLLISIONMANAGER_H
#define COLLISIONMANAGER_H

class Shape;

using namespace std;

#define DLLEXPORT _declspec(dllexport)

class DLLEXPORT CollisionManager
{
public:
	static bool CheckCollision(Shape* shape1, Shape* shape2);
};

#endif