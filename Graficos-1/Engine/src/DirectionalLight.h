#ifndef DIRECTIONAL_LIGHT_H
#define DIRECTIONAL_LIGHT_H

#include "light.h"

class DLLEXPORT DirectionalLight : public Light
{
public:
	DirectionalLight(vec3 initPos, vec3 initDir, Shader* shad, bool active);
	void Update() override;
};

#endif
