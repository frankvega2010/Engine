#include "LightManager.h"
#include "Shader.h"

int LightManager::pointLightCount = 0;

std::list<PointLight>* LightManager::pointLightList = nullptr;

void LightManager::UpdatePointLights(Shader* s)
{
	for (std::list<PointLight>::iterator iB = pointLightList->begin(); iB != pointLightList->end(); ++iB)
	{
		(*iB).Update();
	}
}
