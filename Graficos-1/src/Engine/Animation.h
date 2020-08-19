#ifndef ANIMATION_H
#define ANIMATION_H

#include <glm.hpp>

using namespace glm;

struct Frame
{
	float* uvs;
};

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
	Frame* frames;
public:
	Animation(float x, float y, int totalframes);
	~Animation();
	void SetActualFrame(int frame);
	int GetActualFrame();
	float* CalculateFrame();
	float* GetFrameUv(int frame);
};
#endif