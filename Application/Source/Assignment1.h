#ifndef ASSIGNMENT_1_H
#define ASSIGNMENT_1_H

#include "Scene.h"
#include "Camera.h"
#include "Mesh.h"
#include "MatrixStack.h"
#include "Light.h"
#include "Camera2.h"

class Assignment1 : public Scene
{
	enum GEOMETRY_TYPE
	{
		GEO_AXES,
		GEO_QUAD,
		GEO_RED_CUBE,
		GEO_BLACK_CUBE,
		GEO_YELLOW_CUBE,
		GEO_RED_CYLINDER,
		GEO_YELLOW_CONE,
		GEO_RED_PYRAMID,
		GEO_SPHERE,
		GEO_YELLOW_SPHERE,
		GEO_HEMISPHERE,
		GEO_WHITE_HEMISPHERE,
		GEO_BLUE_HEMISPHERE,
		GEO_BLACK_HEMISPHERE,
		GEO_RED_TORUS,
		GEO_L_CONNECTOR_TORUS,
		GEO_LIGHTBALL,
		NUM_GEOMETRY,
	};
	enum UNIFORM_TYPE
	{
		U_MVP = 0,
		U_MODELVIEW,
		U_MODELVIEW_INVERSE_TRANSPOSE,
		U_MATERIAL_AMBIENT,
		U_MATERIAL_DIFFUSE,
		U_MATERIAL_SPECULAR,
		U_MATERIAL_SHININESS,
		U_LIGHTENABLED,

		U_LIGHT0_POSITION,
		U_LIGHT0_COLOR,
		U_LIGHT0_POWER,
		U_LIGHT0_KC,
		U_LIGHT0_KL,
		U_LIGHT0_KQ,
		U_LIGHT0_TYPE,
		U_LIGHT0_SPOTDIRECTION,
		U_LIGHT0_COSCUTOFF,
		U_LIGHT0_COSINNER,
		U_LIGHT0_EXPONENT,

		U_LIGHT1_POSITION,
		U_LIGHT1_COLOR,
		U_LIGHT1_POWER,
		U_LIGHT1_KC,
		U_LIGHT1_KL,
		U_LIGHT1_KQ,
		U_LIGHT1_TYPE,
		U_LIGHT1_SPOTDIRECTION,
		U_LIGHT1_COSCUTOFF,
		U_LIGHT1_COSINNER,
		U_LIGHT1_EXPONENT,

		U_NUMLIGHTS,
		U_TOTAL,
	};

	MS modelStack, viewStack, projectionStack;

public:
	Assignment1();
	~Assignment1();

	virtual void Init();
	virtual void Update(double dt);
	virtual void Render();
	virtual void Exit();
private:
	unsigned m_vertexArrayID;
	Mesh *meshList[NUM_GEOMETRY];

	unsigned m_programID;
	unsigned m_parameters[U_TOTAL];

	void RenderMesh(Mesh* mesh, bool enableLight);

	float rotateAngle;
	float bodyX,bodyY,bodyZ;

	float noseAngle, noseAngleX;

	float lLegAngle, rLegAngle;
	float lArmAngle, rArmAngle;

	bool blinking;
	float eyeLidAngle;
	int blinkTemp;
	int blinkTemp1;

	bool walking;
	int walkTemp;
	std::string direction;

	Light light[2];
	float lanternX, lanternY, lanternZ, lanternAngle;
	int swayTemp;

	float timer;
	int timerTemp;

	Camera2 camera;
};

#endif