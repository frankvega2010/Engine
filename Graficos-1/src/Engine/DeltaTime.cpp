#include "DeltaTime.h"

DeltaTime* DeltaTime::instance = NULL;

DeltaTime::DeltaTime()
{
	lastTime = 0;
}

DeltaTime::~DeltaTime()
{
}

double DeltaTime::GetDeltaTime()
{
	return deltaTime;
}

void DeltaTime::SetCurrentTime(double time)
{
	currentTime = time;
}

void DeltaTime::SetLastTime(double time)
{
	lastTime = time;
}

double DeltaTime::CalculateDeltaTime()
{
	return currentTime - lastTime;
}

void DeltaTime::Update()
{
	currentTime = glfwGetTime();
	deltaTime = CalculateDeltaTime();
	lastTime = currentTime;
}

void DeltaTime::DestroyInstance()
{
	delete instance;
}