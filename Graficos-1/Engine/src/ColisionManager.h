#ifndef COLISIONMANAGER_H
#define COLISIONMANAGER_H

class Shape;

using namespace std;

#define DLLEXPORT _declspec(dllexport)

class DLLEXPORT CollisionManager
{
public:
	CollisionManager() {};
	~CollisionManager() {};
	static bool CheckCollision(Shape* shape1, Shape* shape2);
};

#endif