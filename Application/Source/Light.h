#pragma once
#include "Vertex.h"

struct Light
{
	Position position;
	Color color;
	float power;
	float kC, kL, kQ;
	
	enum LIGHT_TYPE
	{
		LIGHT_POINT = 0,
		LIGHT_DIRECTIONAL,
		LIGHT_SPOT,
	};
	LIGHT_TYPE type;
	Vector3 spotDirection;
	float cosCutoff;
	float cosInner;
	float exponent;

	Light()
	{
		position = (0, 10, 0);
		color = (1, 1, 1);
		power = 1;
		kC = 1;
		kL = 0.1f;
		kQ = 0.01f;
	}
};

