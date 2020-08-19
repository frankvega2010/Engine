#ifndef POINTLIGHT_H
#define POINTLIGHT_H

#include <list>

#include "Light.h"

class DLLEXPORT PointLight : public Light
{
private:
	float attenuation;
	int index;
	
public:
	PointLight(vec3 initPos, vec3 initDir, Shader* shad, bool active, float att = 1.f);
	void Update() override;
	void SetAttenuation(float att);
	static int GetPointLightCount();
	void SetPosition(vec3 pos);
};

#endif

