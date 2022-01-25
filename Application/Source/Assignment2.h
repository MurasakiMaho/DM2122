#ifndef ASSIGNMENT_2_H
#define ASSIGNMENT_2_H
#include "Scene.h"
#include "Camera.h"
#include "Mesh.h"
#include "MatrixStack.h"
#include "Light.h"
#include "Camera3.h"
#include <sstream>

class Assignment2 : public Scene
{
	enum GEOMETRY_TYPE
	{
		GEO_LEFT,
		GEO_RIGHT,
		GEO_TOP,
		GEO_BOTTOM,
		GEO_FRONT,
		GEO_BACK,
		GEO_IMAGE,
		GEO_BLEND,

		GEO_AXES,
		GEO_QUAD,
		GEO_CUBE,
		GEO_CIRCLE,
		GEO_RING,
		GEO_CYLINDER,
		GEO_CONE,
		GEO_SPHERE,
		GEO_HEMISPHERE,
		GEO_TORUS,
		GEO_QUARTERTORUS,

		//Drippy
		GEO_RED_CUBE,
		GEO_BLACK_CUBE,
		GEO_YELLOW_CUBE,
		GEO_RED_CYLINDER,
		GEO_YELLOW_CONE,
		GEO_RED_PYRAMID,
		GEO_LEG_SPHERE,
		GEO_YELLOW_SPHERE,
		GEO_YELLOW_HEMISPHERE,
		GEO_WHITE_HEMISPHERE,
		GEO_BLUE_HEMISPHERE,
		GEO_BLACK_HEMISPHERE,
		GEO_RED_TORUS,
		GEO_L_CONNECTOR_TORUS,

		GEO_LIGHTBALL,

		GEO_MODEL1,
		GEO_MODEL2,
		GEO_MODEL3,
		GEO_MODEL4,
		GEO_MODEL5,
		GEO_MODEL6,
		GEO_MODEL7,
		GEO_MODEL8,

		GEO_TEXT,
		GEO_ONSCREENTEXT,
		GEO_FRAMERATE,

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

		U_COLOR_TEXTURE_ENABLED,
		U_COLOR_TEXTURE,

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

		U_TEXT_ENABLED,
		U_TEXT_COLOR,
		U_NUMLIGHTS,
		U_TOTAL,
	};

	MS modelStack, viewStack, projectionStack;

public:
	Assignment2();
	~Assignment2();

	virtual void Init();
	virtual void Update(double dt);
	virtual void Render();
	virtual void Exit();
private:
	unsigned m_vertexArrayID;
	Mesh *meshList[NUM_GEOMETRY];

	unsigned m_programID;
	unsigned m_parameters[U_TOTAL];

	void RenderText(Mesh* mesh, std::string text, Color color);
	void RenderTextOnScreen(Mesh* mesh, std::string text, Color color, float size, float x, float y);

	void RenderMesh(Mesh* mesh, bool enableLight);

	float rotateAngle;
	float fps;

	Light light[1];
	bool bLightEnabled;

	//Drippy
	float bodyX, bodyY, bodyZ;

	float noseAngle, noseAngleX;

	float lLegAngle, rLegAngle;
	float lArmAngle, rArmAngle;

	bool blinking;
	float eyeLidAngle;
	int blinkTemp;
	int blinkTemp1;
	float eyebrowY;

	float lanternX, lanternY, lanternZ, lanternAngle;

	int swayTemp;

	void RenderSkybox();

	Camera3 camera;
};

#endif