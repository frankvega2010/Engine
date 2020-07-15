#include "SpotLight.h"
#include "Shader.h"

SpotLight::SpotLight(vec3 initPos, vec3 initDir, Shader* shad, bool active, float bAngle, float sAngle) : Light(initPos, initDir, shad, active)
{
	SetBigAngle(bAngle);
	SetSmallAngle(sAngle);
}

void SpotLight::Update()
{
	activeShader->use();
	activeShader->setBool("spotLight.isActive", isActive);
	activeShader->setVec3("spotLight.position", position);
	activeShader->setVec3("spotLight.direction", direction);
	activeShader->setVec3("spotLight.ambient", ambient);
	activeShader->setVec3("spotLight.diffuse", diffuse);
	activeShader->setVec3("spotLight.specular", specular);
	activeShader->setFloat("spotLight.constant", 1.0f);
	activeShader->setFloat("spotLight.linear", 0.09);
	activeShader->setFloat("spotLight.quadratic", 0.032);
	activeShader->setFloat("spotLight.cutOff", glm::cos(smallAngle));
	activeShader->setFloat("spotLight.outerCutOff", glm::cos(bigAngle));
}

void SpotLight::SetBigAngle(float angle)
{
	bigAngle = glm::radians(angle);
}

void SpotLight::SetSmallAngle(float angle)
{
	smallAngle = glm::radians(angle);
}


