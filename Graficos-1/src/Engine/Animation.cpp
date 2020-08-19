#include "Animation.h"

Animation::Animation(float x, float y, int totalframes) : cantX(x), cantY(y), actualFrame(0), frame(new float[totalframes]), frameTotal(totalframes), row(0), column(0)
{
	frameWidth = 1 / cantX;
	frameHeight = 1 / cantY;

	frames = new Frame[totalframes];

	for (int i = 0; i < totalframes; i++)
	{
		frames[i].uvs = new float[8];
		for (int j = 0; j < 8; j++)
		{
			frames[i].uvs[0] = 0.0f + frameWidth * i;
			frames[i].uvs[1] = 0.0f + frameHeight * i;
			frames[i].uvs[2] = 0.0f + frameWidth * i;
			frames[i].uvs[3] = 1.0f/y + frameHeight * i;
			frames[i].uvs[4] = 1.0f/x + frameWidth * i;
			frames[i].uvs[5] = 0.0f + frameHeight * i;
			frames[i].uvs[6] = 1.0f/x + frameWidth * i;
			frames[i].uvs[7] = 1.0f/y + frameHeight * i;
		}
	}
}

Animation::~Animation()
{
	delete frame;
}

void Animation::SetActualFrame(int frame)
{
	actualFrame = frame;
}

int Animation::GetActualFrame()
{
	return actualFrame;
}

float* Animation::GetFrameUv(int frame)
{
	return frames[frame].uvs;
}

float* Animation::CalculateFrame()
{
	return NULL;
}