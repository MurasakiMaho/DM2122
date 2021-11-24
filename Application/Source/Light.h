#pragma once
#include "Vertex.h"

struct Light
{
	Position position;
	Color color;
	float power;
	float kC, kL, kQ;
	Light()
	{
		position = (0, 10, 0);
		color = (1, 1, 1);
		power = 1;
		kC = 1;
		kL = 1;
		kQ = 1;
	}
};

