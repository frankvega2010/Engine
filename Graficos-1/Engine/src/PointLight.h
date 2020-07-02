#ifndef POINTLIGHT_H
#define POINTLIGHT_H

#include "Light.h"

class DLLEXPORT PointLight : public Light
{
private:
	float attenuation;
	static int pointLightCount;
public:
	PointLight(vec3 initPos, vec3 initDir, Shader* shad, bool active, float att = 1.f);
	void Update() override;
	void SetAttenuation(float att);
	static int GetPointLightCount();
};

#endif

