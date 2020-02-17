#ifndef COLISIONMANAGER_H
#define COLISIONMANAGER_H
#include "Exports.h"
class Shape;

using namespace std;

//#define DLLEXPORT _declspec(dllexport)

class ENGINE_API CollisionManager
{
public:
	CollisionManager() {};
	~CollisionManager() {};
	static bool CheckCollision(Shape* shape1, Shape* shape2);
};

#endif