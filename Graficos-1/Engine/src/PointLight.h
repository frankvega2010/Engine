#ifndef POINTLIGHT_H
#define POINTLIGHT_H

#include "Light.h"

class DLLEXPORT PointLight : public Light
{
private:
	float attenuation;
public:
	PointLight(vec3 initPos, vec3 initDir, Shader* shad, float att = 1.f);
	void Update() override;
	void SetAttenuation(float att);
};



#endif

