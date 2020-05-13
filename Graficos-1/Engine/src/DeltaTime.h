#ifndef DELTATIME_H
#define DELTATIME_H
#include "glfw3.h"
#include <iostream>
class DeltaTime
{
private:
	static DeltaTime* instance;
	double lastTime;
	double currentTime;
	double deltaTime;
public:
	DeltaTime();
	~DeltaTime();
	double GetDeltaTime();
	void SetLastTime(double time);
	void SetCurrentTime(double time);
	double CalculateDeltaTime();
	void Update();
	void DestroyInstance();

	static DeltaTime* Instance()
	{
		if (instance == NULL)
		{
			instance = new DeltaTime();
		}
		return instance;
	}
};
#endif