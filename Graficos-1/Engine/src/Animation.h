#ifndef ANIMATION_H
#define ANIMATION_H

#include "DeltaTime.h"
class  Animation
{
private:
	int actualFrame;
	int frameTotal;
	float timer;
	float cantY;
	float cantX;
	float row;
	float column;
	float frameWidth;
	float frameHeight;
	float* frame;
public:
	Animation(float x, float y, int totalframes);
	~Animation();
	void SetActualFrame(int frame);
	int GetActualFrame();
	float* CalculateFrame();
};
#endif