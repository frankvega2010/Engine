#ifndef SPOTLIGHT_H
#define SPOTLIGHT_H

#include "Light.h"

class DLLEXPORT SpotLight : public Light
{
private:
	float bigAngle;
	float smallAngle;
public:
	SpotLight(vec3 initPos, vec3 initDir, Shader* shad, float bAngle = 15.0f, float sAngle = 12.5f);
	void Update() override;
	void SetBigAngle(float angle);
	float GetBigAngle() const { return bigAngle; };
	void SetSmallAngle(float angle);
	float GetSmallAngle() const { return smallAngle; };
};

#endif

