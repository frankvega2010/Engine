#include "Animation.h"

Animation::Animation(float x, float y, int totalframes) : cantX(x), cantY(y), actualFrame(0), frame(new float[8]), frameTotal(totalframes), row(0), column(0), timer(20)
{
	frameWidth = 1 / cantX;
	frameHeight = 1 / cantY;
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

float* Animation::CalculateFrame()
{
	if (timer >= 0.3f)
	{
		frame[0] = 0.0f;
		frame[1] = 0.0f;
		frame[2] = frameWidth;
		frame[3] = 0.0f;
		frame[4] = 0.0f;
		frame[5] = -frameHeight;
		frame[6] = frameWidth;
		frame[7] = -frameHeight;

		// Calculo UVs del frame
		frame[0] += frameWidth * column;
		frame[1] += frameHeight * row;
		frame[2] += frameWidth * column;
		frame[3] += frameHeight * row;
		frame[4] += frameWidth * column;
		frame[5] += frameHeight * row;
		frame[6] += frameWidth * column;
		frame[7] += frameHeight * row;

		// Aumento columna para proximo frame
		column++;

		// Aumento numero de proximo frame
		actualFrame++;

		// Chequeo si me salgo de la columna
		if (column >= cantX)
		{
			column = 0;
			row++;
		}

		// Chequeo si necesito reiniciar los frames
		if (actualFrame > frameTotal - 1)
		{
			actualFrame = 0;
			column = 0;
			row = 0;
		}

		timer = 0;
	}
	else
	{
		timer += DeltaTime::Instance()->GetDeltaTime();
	}

	return frame;
}