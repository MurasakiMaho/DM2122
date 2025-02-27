#ifndef SCENE_3_H
#define SCENE_3_H

#include "Scene.h"
#include "Mtx44.h"

class Scene3 : public Scene
{
public:
	Scene3();
	~Scene3();

	virtual void Init();
	virtual void Update(double dt);
	virtual void Render();
	virtual void Exit();

	enum GEOMETRY_TYPE
	{
		GEO_TRIANGLE_1 = 0,
		GEO_TRIANGLE_2,
		GEO_TRIANGLE_3,
		GEO_TRIANGLE_4,
		GEO_TRIANGLE_5,
		GEO_TRIANGLE_6,
		GEO_TRIANGLE_7,
		GEO_TRIANGLE_8,
		GEO_TRIANGLE_9 ,
		GEO_TRIANGLE_10,
		GEO_TRIANGLE_11,
		GEO_TRIANGLE_12,
		GEO_TRIANGLE_13,
		GEO_TRIANGLE_14,
		GEO_TRIANGLE_15,
		GEO_TRIANGLE_16,
		GEO_TRIANGLE_17,
		GEO_TRIANGLE_18,
		GEO_TRIANGLE_19,
		GEO_TRIANGLE_20,
		GEO_TRIANGLE_21,
		GEO_TRIANGLE_22,
		GEO_TRIANGLE_23,
		GEO_TRIANGLE_24,
		GEO_TRIANGLE_25,
		GEO_TRIANGLE_26,
		NUM_GEOMETRY,
	};

	enum UNIFORM_TYPE
	{
		U_MVP = 0,
		U_TOTAL,
	};

private:
	unsigned m_vertexArrayID;
	unsigned m_vertexBuffer[NUM_GEOMETRY];
	unsigned m_colorBuffer[NUM_GEOMETRY];
	unsigned m_programID;
	unsigned m_parameters[U_TOTAL];
	float rotateAngle;
	float translateX;
	float translateY;
	float scaleAll;
	float translateFoxY;

};




#endif