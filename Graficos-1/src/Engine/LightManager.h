#ifndef LIGHT_MAGANER_H
#define LIGHT_MAGANER_H

#include <list>

#include "Light.h"
#include "PointLight.h"

class DLLEXPORT LightManager
{
public:
	static std::list<PointLight>* pointLightList;
	static int pointLightCount;
	void UpdatePointLights();
};

#endif
