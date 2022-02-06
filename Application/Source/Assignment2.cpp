#include "Assignment2.h"
#include "GL\glew.h"

#include "shader.hpp"
#include "Mtx44.h"

#include "Application.h"
#include "MeshBuilder.h"
#include "Utility.h"
#include "LoadTGA.h"
#include "LoadOBJ.h"

Assignment2::Assignment2()
{
}

Assignment2::~Assignment2()
{
}

void Assignment2::Init()
{	
	// Set background color to dark blue
	glClearColor(0.0f, 0.0f, 0.4f, 0.0f);

	//Enable depth buffer and depth testing
	glEnable(GL_DEPTH_TEST);

	//Enable back face culling
	glEnable(GL_CULL_FACE);

	//Enable blending
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	//Default to fill mode
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

	// Generate a default VAO for now
	glGenVertexArrays(1, &m_vertexArrayID);
	glBindVertexArray(m_vertexArrayID);
	
	//Load vertex and fragment shaders
	m_programID = LoadShaders("Shader//Texture.vertexshader", "Shader//Text.fragmentshader");

	// Get a handle for our "textColor" uniform
	m_parameters[U_TEXT_ENABLED] = glGetUniformLocation(m_programID, "textEnabled");
	m_parameters[U_TEXT_COLOR] = glGetUniformLocation(m_programID, "textColor");


	m_parameters[U_COLOR_TEXTURE_ENABLED] = glGetUniformLocation(m_programID, "colorTextureEnabled");
	m_parameters[U_COLOR_TEXTURE] = glGetUniformLocation(m_programID, "colorTexture");


	m_parameters[U_MVP] = glGetUniformLocation(m_programID, "MVP");
	m_parameters[U_MODELVIEW] = glGetUniformLocation(m_programID, "MV");
	m_parameters[U_MODELVIEW_INVERSE_TRANSPOSE] = glGetUniformLocation(m_programID, "MV_inverse_transpose");
	m_parameters[U_MATERIAL_AMBIENT] = glGetUniformLocation(m_programID, "material.kAmbient");
	m_parameters[U_MATERIAL_DIFFUSE] = glGetUniformLocation(m_programID, "material.kDiffuse");
	m_parameters[U_MATERIAL_SPECULAR] = glGetUniformLocation(m_programID, "material.kSpecular");
	m_parameters[U_MATERIAL_SHININESS] = glGetUniformLocation(m_programID, "material.kShininess");
	m_parameters[U_LIGHT0_POSITION] = glGetUniformLocation(m_programID, "lights[0].position_cameraspace");
	m_parameters[U_LIGHT0_COLOR] = glGetUniformLocation(m_programID, "lights[0].color");
	m_parameters[U_LIGHT0_POWER] = glGetUniformLocation(m_programID, "lights[0].power");
	m_parameters[U_LIGHT0_KC] = glGetUniformLocation(m_programID, "lights[0].kC");
	m_parameters[U_LIGHT0_KL] = glGetUniformLocation(m_programID, "lights[0].kL");
	m_parameters[U_LIGHT0_KQ] = glGetUniformLocation(m_programID, "lights[0].kQ");
	m_parameters[U_LIGHTENABLED] = glGetUniformLocation(m_programID, "lightEnabled");
	m_parameters[U_LIGHT0_TYPE] = glGetUniformLocation(m_programID, "lights[0].type");
	m_parameters[U_LIGHT0_SPOTDIRECTION] = glGetUniformLocation(m_programID, "lights[0].spotDirection");
	m_parameters[U_LIGHT0_COSCUTOFF] = glGetUniformLocation(m_programID, "lights[0].cosCutoff");
	m_parameters[U_LIGHT0_COSINNER] = glGetUniformLocation(m_programID, "lights[0].cosInner");
	m_parameters[U_LIGHT0_EXPONENT] = glGetUniformLocation(m_programID, "lights[0].exponent");

	m_parameters[U_LIGHT1_POSITION] = glGetUniformLocation(m_programID, "lights[1].position_cameraspace");
	m_parameters[U_LIGHT1_COLOR] = glGetUniformLocation(m_programID, "lights[1].color");
	m_parameters[U_LIGHT1_POWER] = glGetUniformLocation(m_programID, "lights[1].power");
	m_parameters[U_LIGHT1_KC] = glGetUniformLocation(m_programID, "lights[1].kC");
	m_parameters[U_LIGHT1_KL] = glGetUniformLocation(m_programID, "lights[1].kL");
	m_parameters[U_LIGHT1_KQ] = glGetUniformLocation(m_programID, "lights[1].kQ");
	m_parameters[U_LIGHT1_TYPE] = glGetUniformLocation(m_programID, "lights[1].type");
	m_parameters[U_LIGHT1_SPOTDIRECTION] = glGetUniformLocation(m_programID, "lights[1].spotDirection");
	m_parameters[U_LIGHT1_COSCUTOFF] = glGetUniformLocation(m_programID, "lights[1].cosCutoff");
	m_parameters[U_LIGHT1_COSINNER] = glGetUniformLocation(m_programID, "lights[1].cosInner");
	m_parameters[U_LIGHT1_EXPONENT] = glGetUniformLocation(m_programID, "lights[1].exponent");
	m_parameters[U_NUMLIGHTS] = glGetUniformLocation(m_programID, "numLights");
	glUseProgram(m_programID);
	
	//light[0].type = Light::LIGHT_POINT;
	light[0].type = Light::LIGHT_DIRECTIONAL;
	light[0].position.Set(0, 20, 0);
	light[0].color.Set(1, 1, 1);
	light[0].power = 0.5f;
	light[0].kC = 1.f;
	light[0].kL = 0.01f;
	light[0].kQ = 0.001f;
	light[0].cosCutoff = cos(Math::DegreeToRadian(45));
	light[0].cosInner = cos(Math::DegreeToRadian(30));
	light[0].exponent = 3.f;
	light[0].spotDirection.Set(0.f, 1.f, 0.f);

	lanternX = camera.position.x;
	lanternY = camera.position.y;
	lanternZ = camera.position.z;

	light[1].type = Light::LIGHT_POINT;
	light[1].position.Set(lanternX, lanternY, lanternZ);
	//light[1].color.Set(1, 0.77647, 0.36078);
	light[1].color.Set(1, 1, 1);
	light[1].power = 1;
	light[1].kC = 1.f;
	light[1].kL = 0.01f;
	light[1].kQ = 0.001f;
	light[1].cosCutoff = cos(Math::DegreeToRadian(30));
	light[1].cosInner = cos(Math::DegreeToRadian(15));
	light[1].exponent = 3.f;
	light[1].spotDirection.Set(0.f, 1.f, 0.f);

	glUniform1i(m_parameters[U_LIGHT0_TYPE], light[0].type);
	glUniform3fv(m_parameters[U_LIGHT0_COLOR], 1, &light[0].color.r);
	glUniform1f(m_parameters[U_LIGHT0_POWER], light[0].power);
	glUniform1f(m_parameters[U_LIGHT0_KC], light[0].kC);
	glUniform1f(m_parameters[U_LIGHT0_KL], light[0].kL);
	glUniform1f(m_parameters[U_LIGHT0_KQ], light[0].kQ);
	glUniform1f(m_parameters[U_LIGHT0_COSCUTOFF], light[0].cosCutoff);
	glUniform1f(m_parameters[U_LIGHT0_COSINNER], light[0].cosInner);
	glUniform1f(m_parameters[U_LIGHT0_EXPONENT], light[0].exponent);
	
	glUniform1i(m_parameters[U_LIGHT1_TYPE], light[1].type);
	glUniform3fv(m_parameters[U_LIGHT1_COLOR], 1, &light[1].color.r);
	glUniform1f(m_parameters[U_LIGHT1_POWER], light[1].power);
	glUniform1f(m_parameters[U_LIGHT1_KC], light[1].kC);
	glUniform1f(m_parameters[U_LIGHT1_KL], light[1].kL);
	glUniform1f(m_parameters[U_LIGHT1_KQ], light[1].kQ);
	glUniform1f(m_parameters[U_LIGHT1_COSCUTOFF], light[1].cosCutoff);
	glUniform1f(m_parameters[U_LIGHT1_COSINNER], light[1].cosInner);
	glUniform1f(m_parameters[U_LIGHT1_EXPONENT], light[1].exponent);
	glUniform1i(m_parameters[U_NUMLIGHTS], 2);

	//variable to rotate geometry
	rotateAngle = 0;

	inAnotherWorld = false;
	transporttimer = 0.f;
	transportCD = false;

	//Initialize camera settings
	camera.Init(Vector3(0, 0, 25), Vector3(0, 0, 0), Vector3(0, 1, 0));

	Mtx44 projection;
	projection.SetToPerspective(45.f, 4.f / 3.f, 0.1f, 1000.f);
	projectionStack.LoadMatrix(projection);

	// Init VBO
	for (int i = 0; i < NUM_GEOMETRY; ++i)
	{
		meshList[i] = nullptr;
	}
	meshList[GEO_AXES] = MeshBuilder::GenerateAxes("reference", 1000, 1000, 1000);

	//Ground + others
	{
		meshList[GEO_QUAD] = MeshBuilder::GenerateQuad("!anotherW", Color(1, 1, 1), 1.f);
		meshList[GEO_QUAD]->textureID = LoadTGA("Image//!anotherW.tga");
		meshList[GEO_QUAD]->material.kAmbient.Set(0.5f, 0.5f, 0.5f);
		meshList[GEO_QUAD]->material.kDiffuse.Set(0.5f, 0.5f, 0.5f);
		meshList[GEO_QUAD]->material.kSpecular.Set(0.5f, 0.5f, 0.5f);
		meshList[GEO_QUAD]->material.kShininess = 1.f;

		meshList[GEO_QUAD1] = MeshBuilder::GenerateQuad("anotherW", Color(1, 1, 1), 1.f);
		meshList[GEO_QUAD1]->textureID = LoadTGA("Image//anotherW.tga");
		meshList[GEO_QUAD1]->material.kAmbient.Set(0.5f, 0.5f, 0.5f);
		meshList[GEO_QUAD1]->material.kDiffuse.Set(0.5f, 0.5f, 0.5f);
		meshList[GEO_QUAD1]->material.kSpecular.Set(0.5f, 0.5f, 0.5f);
		meshList[GEO_QUAD1]->material.kShininess = 1.f;

		/*meshList[GEO_CUBE] = MeshBuilder::GenerateCube("cube", Color(1, 1, 1), 1.f);
		meshList[GEO_QUAD]->textureID = LoadTGA("Image//color.tga");
		meshList[GEO_QUAD]->material.kAmbient.Set(0.5f, 0.5f, 0.5f);
		meshList[GEO_QUAD]->material.kDiffuse.Set(0.5f, 0.5f, 0.5f);
		meshList[GEO_QUAD]->material.kSpecular.Set(0.5f, 0.5f, 0.5f);
		meshList[GEO_QUAD]->material.kShininess = 1.f;*/

		meshList[GEO_CIRCLE] = MeshBuilder::GenerateCircle("circle", Color(0, 1, 1), 20, 1.f);

		meshList[GEO_RING] = MeshBuilder::GenerateRing("ring", Color(0, 1, 1), 20, 1.f);

		meshList[GEO_CYLINDER] = MeshBuilder::GenerateCylinder("cylinder", Color(1, 0, 0), 36, 10, 10);
		meshList[GEO_CYLINDER]->material.kAmbient.Set(0.5f, 0.5f, 0.5f);
		meshList[GEO_CYLINDER]->material.kDiffuse.Set(0.5f, 0.5f, 0.5f);
		meshList[GEO_CYLINDER]->material.kSpecular.Set(0.5f, 0.5f, 0.5f);
		meshList[GEO_CYLINDER]->material.kShininess = 1.f;

		meshList[GEO_CONE] = MeshBuilder::GenerateCone("cone", Color(1, 0, 0), 36, 10, 10);
		meshList[GEO_CONE]->material.kAmbient.Set(0.5f, 0.5f, 0.5f);
		meshList[GEO_CONE]->material.kDiffuse.Set(0.5f, 0.5f, 0.5f);
		meshList[GEO_CONE]->material.kSpecular.Set(0.5f, 0.5f, 0.5f);
		meshList[GEO_CONE]->material.kShininess = 1.f;

		meshList[GEO_SPHERE] = MeshBuilder::GenerateSphere("sphere", Color(1, 1, 1), 10, 20);
		meshList[GEO_SPHERE]->textureID = LoadTGA("Image//color.tga");
		meshList[GEO_SPHERE]->material.kAmbient.Set(0.5f, 0.5f, 0.5f);
		meshList[GEO_SPHERE]->material.kDiffuse.Set(0.5f, 0.5f, 0.5f);
		meshList[GEO_SPHERE]->material.kSpecular.Set(0.5f, 0.5f, 0.5f);
		meshList[GEO_SPHERE]->material.kShininess = 1.f;

		meshList[GEO_HEMISPHERE] = MeshBuilder::GenerateHemisphere("hemisphere", Color(1, 0, 0), 10, 20, 5);
		meshList[GEO_HEMISPHERE]->material.kAmbient.Set(0.5f, 0.5f, 0.5f);
		meshList[GEO_HEMISPHERE]->material.kDiffuse.Set(0.5f, 0.5f, 0.5f);
		meshList[GEO_HEMISPHERE]->material.kSpecular.Set(0.5f, 0.5f, 0.5f);
		meshList[GEO_HEMISPHERE]->material.kShininess = 1.f;

		meshList[GEO_TORUS] = MeshBuilder::GenerateTorus2("torus", Color(1, 0, 0), 20, 20, 10, 5);
		meshList[GEO_TORUS]->material.kAmbient.Set(0.5f, 0.5f, 0.5f);
		meshList[GEO_TORUS]->material.kDiffuse.Set(0.5f, 0.5f, 0.5f);
		meshList[GEO_TORUS]->material.kSpecular.Set(0.5f, 0.5f, 0.5f);
		meshList[GEO_TORUS]->material.kShininess = 1.f;

		meshList[GEO_QUARTERTORUS] = MeshBuilder::GenerateQuarterTorus2("quartertorus", Color(1, 0, 0), 20, 20, 10, 5);
		meshList[GEO_QUARTERTORUS]->material.kAmbient.Set(0.5f, 0.5f, 0.5f);
		meshList[GEO_QUARTERTORUS]->material.kDiffuse.Set(0.5f, 0.5f, 0.5f);
		meshList[GEO_QUARTERTORUS]->material.kSpecular.Set(0.5f, 0.5f, 0.5f);
		meshList[GEO_QUARTERTORUS]->material.kShininess = 1.f;
	}

	//Drippy
	{
		meshList[GEO_RED_CUBE] = MeshBuilder::GenerateCube("redCube", Color(0.79215, 0.38823, 0.34510), 1.f);
		meshList[GEO_RED_CUBE]->material.kAmbient.Set(0.5f, 0.5f, 0.5f);
		meshList[GEO_RED_CUBE]->material.kDiffuse.Set(0.5f, 0.5f, 0.5f);
		meshList[GEO_RED_CUBE]->material.kSpecular.Set(0.2f, 0.2f, 0.2f);
		meshList[GEO_RED_CUBE]->material.kShininess = 1.f;

		meshList[GEO_YELLOW_CUBE] = MeshBuilder::GenerateCube("yellowCube", Color(1, 0.77647, 0.36078), 1.f);
		meshList[GEO_YELLOW_CUBE]->material.kAmbient.Set(0.5f, 0.5f, 0.5f);
		meshList[GEO_YELLOW_CUBE]->material.kDiffuse.Set(0.5f, 0.5f, 0.5f);
		meshList[GEO_YELLOW_CUBE]->material.kSpecular.Set(0.2f, 0.2f, 0.2f);
meshList[GEO_YELLOW_CUBE]->material.kShininess = 1.f;

meshList[GEO_RED_CYLINDER] = MeshBuilder::GenerateCylinder("redCylinder", Color(0.79215, 0.38823, 0.34510), 36, 10, 10);
meshList[GEO_RED_CYLINDER]->material.kAmbient.Set(0.5f, 0.5f, 0.5f);
meshList[GEO_RED_CYLINDER]->material.kDiffuse.Set(0.5f, 0.5f, 0.5f);
meshList[GEO_RED_CYLINDER]->material.kSpecular.Set(0.2f, 0.2f, 0.2f);
meshList[GEO_RED_CYLINDER]->material.kShininess = 1.f;

meshList[GEO_YELLOW_CONE] = MeshBuilder::GenerateCone("yellowCone", Color(0.92157, 0.80783, 0.52157), 36, 1, 1);
meshList[GEO_YELLOW_CONE]->material.kAmbient.Set(0.5f, 0.5f, 0.5f);
meshList[GEO_YELLOW_CONE]->material.kDiffuse.Set(1.f, 1.f, 1.f);
meshList[GEO_YELLOW_CONE]->material.kSpecular.Set(0.2f, 0.2f, 0.2f);
meshList[GEO_YELLOW_CONE]->material.kShininess = 1.f;

meshList[GEO_RED_PYRAMID] = MeshBuilder::GenerateCone("redPyramid", Color(0.79215, 0.38823, 0.34510), 4, 1, 1);
meshList[GEO_RED_PYRAMID]->material.kAmbient.Set(0.5f, 0.5f, 0.5f);
meshList[GEO_RED_PYRAMID]->material.kDiffuse.Set(0.5f, 0.5f, 0.5f);
meshList[GEO_RED_PYRAMID]->material.kSpecular.Set(0.2f, 0.2f, 0.2f);
meshList[GEO_RED_PYRAMID]->material.kShininess = 1.f;

meshList[GEO_LEG_SPHERE] = MeshBuilder::GenerateSphere("LEGsphere", Color(0.35294, 0.54117, 0.48627), 10, 36, 1);
meshList[GEO_LEG_SPHERE]->material.kAmbient.Set(0.5f, 0.5f, 0.5f);
meshList[GEO_LEG_SPHERE]->material.kDiffuse.Set(1.f, 1.f, 1.f);
meshList[GEO_LEG_SPHERE]->material.kSpecular.Set(0.2f, 0.2f, 0.2f);
meshList[GEO_LEG_SPHERE]->material.kShininess = 1.f;

meshList[GEO_YELLOW_SPHERE] = MeshBuilder::GenerateSphere("yellowSphere", Color(0.92157, 0.80783, 0.52157), 10, 36, 1);
meshList[GEO_YELLOW_SPHERE]->material.kAmbient.Set(0.5f, 0.5f, 0.5f);
meshList[GEO_YELLOW_SPHERE]->material.kDiffuse.Set(1.f, 1.f, 1.f);
meshList[GEO_YELLOW_SPHERE]->material.kSpecular.Set(0.2f, 0.2f, 0.2f);
meshList[GEO_YELLOW_SPHERE]->material.kShininess = 1.f;

meshList[GEO_YELLOW_HEMISPHERE] = MeshBuilder::GenerateHemisphere("yellowHemisphere", Color(0.92157, 0.80783, 0.52157), 10, 20, 1);
meshList[GEO_YELLOW_HEMISPHERE]->material.kAmbient.Set(0.5f, 0.5f, 0.5f);
meshList[GEO_YELLOW_HEMISPHERE]->material.kDiffuse.Set(1.f, 1.f, 1.f);
meshList[GEO_YELLOW_HEMISPHERE]->material.kSpecular.Set(0.2f, 0.2f, 0.2f);
meshList[GEO_YELLOW_HEMISPHERE]->material.kShininess = 1.f;

meshList[GEO_WHITE_HEMISPHERE] = MeshBuilder::GenerateHemisphere("whiteHemisphere", Color(1, 1, 1), 10, 20, 1);
meshList[GEO_WHITE_HEMISPHERE]->material.kAmbient.Set(0.5f, 0.5f, 0.5f);
meshList[GEO_WHITE_HEMISPHERE]->material.kDiffuse.Set(0.5f, 0.5f, 0.5f);
meshList[GEO_WHITE_HEMISPHERE]->material.kSpecular.Set(0.2f, 0.2f, 0.2f);
meshList[GEO_WHITE_HEMISPHERE]->material.kShininess = 1.f;

meshList[GEO_BLUE_HEMISPHERE] = MeshBuilder::GenerateHemisphere("blueHemisphere", Color(0.44314, 0.74902, 0.67843), 10, 20, 1);
meshList[GEO_BLUE_HEMISPHERE]->material.kAmbient.Set(0.5f, 0.5f, 0.5f);
meshList[GEO_BLUE_HEMISPHERE]->material.kDiffuse.Set(0.5f, 0.5f, 0.5f);
meshList[GEO_BLUE_HEMISPHERE]->material.kSpecular.Set(0.2f, 0.2f, 0.2f);
meshList[GEO_BLUE_HEMISPHERE]->material.kShininess = 1.f;

meshList[GEO_BLACK_HEMISPHERE] = MeshBuilder::GenerateHemisphere("blackHemisphere", Color(0, 0, 0), 10, 20, 1);
meshList[GEO_BLACK_HEMISPHERE]->material.kAmbient.Set(0.5f, 0.5f, 0.5f);
meshList[GEO_BLACK_HEMISPHERE]->material.kDiffuse.Set(0.5f, 0.5f, 0.5f);
meshList[GEO_BLACK_HEMISPHERE]->material.kSpecular.Set(0.2f, 0.2f, 0.2f);
meshList[GEO_BLACK_HEMISPHERE]->material.kShininess = 1.f;

meshList[GEO_RED_TORUS] = MeshBuilder::GenerateTorus2("redTorus", Color(0.79215, 0.38823, 0.34510), 20, 20, 2, 1);
meshList[GEO_RED_TORUS]->material.kAmbient.Set(0.5f, 0.5f, 0.5f);
meshList[GEO_RED_TORUS]->material.kDiffuse.Set(0.5f, 0.5f, 0.5f);
meshList[GEO_RED_TORUS]->material.kSpecular.Set(0.2f, 0.2f, 0.2f);
meshList[GEO_RED_TORUS]->material.kShininess = 1.f;

meshList[GEO_BLACK_CUBE] = MeshBuilder::GenerateCube("BlackCube", Color(0, 0, 0), 1);
meshList[GEO_BLACK_CUBE]->material.kAmbient.Set(0.5f, 0.5f, 0.5f);
meshList[GEO_BLACK_CUBE]->material.kDiffuse.Set(0.5f, 0.5f, 0.5f);
meshList[GEO_BLACK_CUBE]->material.kSpecular.Set(0.2f, 0.2f, 0.2f);
meshList[GEO_BLACK_CUBE]->material.kShininess = 1.f;

meshList[GEO_L_CONNECTOR_TORUS] = MeshBuilder::GenerateTorus2("noseRing", Color(0.55686, 0.49019, 0.42353), 20, 20, 2, 1);
meshList[GEO_L_CONNECTOR_TORUS]->material.kAmbient.Set(0.5f, 0.5f, 0.5f);
meshList[GEO_L_CONNECTOR_TORUS]->material.kDiffuse.Set(0.5f, 0.5f, 0.5f);
meshList[GEO_L_CONNECTOR_TORUS]->material.kSpecular.Set(0.2f, 0.2f, 0.2f);
meshList[GEO_L_CONNECTOR_TORUS]->material.kShininess = 1.f;

swayTemp = 0;
lanternAngle = 0;

blinking = true;
eyeLidAngle = -120;
blinkTemp = 0;
blinkTemp1 = 0;
eyebrowY = 1.2;

bodyX = 0;
bodyY = 1.25;
bodyZ = 10;

noseAngle = 100;
noseAngleX = 0;

lLegAngle = 0;

rLegAngle = -5;


lArmAngle = 30;
rArmAngle = 30;
	}

	//Skybox + Image
	meshList[GEO_FRONT] = MeshBuilder::GenerateQuad("front", Color(1, 1, 1), 1.f);
	meshList[GEO_FRONT]->textureID = LoadTGA("Image//front.tga");

	meshList[GEO_BACK] = MeshBuilder::GenerateQuad("back", Color(1, 1, 1), 1.f);
	meshList[GEO_BACK]->textureID = LoadTGA("Image//back.tga");

	meshList[GEO_LEFT] = MeshBuilder::GenerateQuad("left", Color(1, 1, 1), 1.f);
	meshList[GEO_LEFT]->textureID = LoadTGA("Image//left.tga");

	meshList[GEO_RIGHT] = MeshBuilder::GenerateQuad("right", Color(1, 1, 1), 1.f);
	meshList[GEO_RIGHT]->textureID = LoadTGA("Image//right.tga");

	meshList[GEO_TOP] = MeshBuilder::GenerateQuad("top", Color(1, 1, 1), 1.f);
	meshList[GEO_TOP]->textureID = LoadTGA("Image//top.tga");

	meshList[GEO_BOTTOM] = MeshBuilder::GenerateQuad("bottom", Color(1, 1, 1), 1.f);
	meshList[GEO_BOTTOM]->textureID = LoadTGA("Image//bottom.tga");

	meshList[GEO_FRONT1] = MeshBuilder::GenerateQuad("front1", Color(1, 1, 1), 1.f);
	meshList[GEO_FRONT1]->textureID = LoadTGA("Image//miramar_ft.tga");

	meshList[GEO_BACK1] = MeshBuilder::GenerateQuad("back1", Color(1, 1, 1), 1.f);
	meshList[GEO_BACK1]->textureID = LoadTGA("Image//miramar_bk.tga");

	meshList[GEO_LEFT1] = MeshBuilder::GenerateQuad("left1", Color(1, 1, 1), 1.f);
	meshList[GEO_LEFT1]->textureID = LoadTGA("Image//miramar_lf.tga");

	meshList[GEO_RIGHT1] = MeshBuilder::GenerateQuad("right1", Color(1, 1, 1), 1.f);
	meshList[GEO_RIGHT1]->textureID = LoadTGA("Image//miramar_rt.tga");

	meshList[GEO_TOP1] = MeshBuilder::GenerateQuad("top1", Color(1, 1, 1), 1.f);
	meshList[GEO_TOP1]->textureID = LoadTGA("Image//miramar_up.tga");

	meshList[GEO_BOTTOM1] = MeshBuilder::GenerateQuad("bottom1", Color(1, 1, 1), 1.f);
	meshList[GEO_BOTTOM1]->textureID = LoadTGA("Image//miramar_dn.tga");

	meshList[GEO_IMAGE] = MeshBuilder::GenerateQuad("image", Color(1, 1, 1), 1.f);
	meshList[GEO_IMAGE]->textureID = LoadTGA("Image//nyp.tga");




	meshList[GEO_CAR1] = MeshBuilder::GenerateOBJMTL("taxi", "OBJ//taxi.obj", "OBJ//taxi.mtl");
	
	meshList[GEO_CAR2] = MeshBuilder::GenerateOBJMTL("van", "OBJ//van.obj", "OBJ//van.mtl");

	meshList[GEO_ROAD] = MeshBuilder::GenerateOBJMTL("apple", "OBJ//road_straight.obj", "OBJ//road_straight.mtl");

	meshList[GEO_BTREE] = MeshBuilder::GenerateOBJMTL("big tree", "OBJ//tree_large.obj", "OBJ//tree_large.mtl");

	meshList[GEO_STREE] = MeshBuilder::GenerateOBJMTL("small tree", "OBJ//tree_small.obj", "OBJ//tree_small.mtl");

	//meshList[GEO_MODEL6] = MeshBuilder::GenerateOBJMTL("model6", "OBJ//medieval house demo.obj", "OBJ//medieval house demo.mtl");
	//meshList[GEO_MODEL6]->textureID = LoadTGA("Image//house2.tga");

	meshList[GEO_BIN] = MeshBuilder::GenerateOBJ("bin", "OBJ//bin.obj");

	meshList[GEO_LARGEBUILDINGB] = MeshBuilder::GenerateOBJMTL("large building b", "OBJ//large_buildingB.obj", "OBJ//large_buildingB.mtl");
	meshList[GEO_LARGEBUILDINGC] = MeshBuilder::GenerateOBJMTL("large building c", "OBJ//large_buildingC.obj", "OBJ//large_buildingC.mtl");
	meshList[GEO_LARGEBUILDINGD] = MeshBuilder::GenerateOBJMTL("large building d", "OBJ//large_buildingD.obj", "OBJ//large_buildingD.mtl");
	meshList[GEO_LARGEBUILDINGE] = MeshBuilder::GenerateOBJMTL("large building e", "OBJ//large_buildingE.obj", "OBJ//large_buildingE.mtl");
	meshList[GEO_LARGEBUILDINGF] = MeshBuilder::GenerateOBJMTL("large building f", "OBJ//large_buildingF.obj", "OBJ//large_buildingF.mtl");
	meshList[GEO_LARGEBUILDINGG] = MeshBuilder::GenerateOBJMTL("large building g", "OBJ//large_buildingG.obj", "OBJ//large_buildingG.mtl");
	meshList[GEO_SMALLBUILDINGE] = MeshBuilder::GenerateOBJMTL("small building e", "OBJ//small_buildingE.obj", "OBJ//small_buildingE.mtl");
	meshList[GEO_FENCE] = MeshBuilder::GenerateOBJMTL("fence", "OBJ//fence_wide.obj", "OBJ//fence_wide.mtl");


	meshList[GEO_UMBRELLA] = MeshBuilder::GenerateOBJMTL("umbrella", "OBJ//detail_umbrellaDetailed.obj", "OBJ//detail_umbrellaDetailed.mtl");
	meshList[GEO_APPLE] = MeshBuilder::GenerateOBJMTL("apple", "OBJ//apple.obj", "OBJ//apple.mtl");
	meshList[GEO_REDWINE] = MeshBuilder::GenerateOBJMTL("red wine", "OBJ//wineRed.obj", "OBJ//wineRed.mtl");
	meshList[GEO_WHITEWINE] = MeshBuilder::GenerateOBJMTL("white wine", "OBJ//wineWhite.obj", "OBJ//wineWhite.mtl");
	meshList[GEO_DINNER] = MeshBuilder::GenerateOBJMTL("boxed dinner", "OBJ//styrofoamDinner.obj", "OBJ//styrofoamDinner.mtl");
	meshList[GEO_EMPTYDINNER] = MeshBuilder::GenerateOBJMTL("empty dinner", "OBJ//styrofoam.obj", "OBJ//styrofoam.mtl");
	meshList[GEO_PAPERBALL] = MeshBuilder::GenerateOBJ("paperball", "OBJ//paper_low.obj");
	meshList[GEO_PAPERBALL]->textureID = LoadTGA("Image//paper_Base_Color.tga");

	meshList[GEO_STICK] = MeshBuilder::GenerateOBJMTL("stick", "OBJ//stick.obj", "OBJ//stick.mtl");
	meshList[GEO_STICK]->textureID = LoadTGA("Image//stick.tga");

	hasWand = false;
	dinnerIsEaten = false;
	interactable = false;
	onScreenTimer = 0.f;

	meshList[GEO_LIGHTBALL] = MeshBuilder::GenerateSphere("lightball", Color(1, 1, 1), 10, 20);

	meshList[GEO_TEXT] = MeshBuilder::GenerateText("text", 16, 16);
	meshList[GEO_TEXT]->textureID = LoadTGA("Image//papyrus.tga");

	meshList[GEO_ONSCREENTEXT] = MeshBuilder::GenerateText("textonscreen", 16, 16);
	meshList[GEO_ONSCREENTEXT]->textureID = LoadTGA("Image//comic_sans.tga");

	meshList[GEO_INTERACTTEXT] = MeshBuilder::GenerateText("interact screen", 16, 16);
	meshList[GEO_INTERACTTEXT]->textureID = LoadTGA("Image//comic_sans.tga");

	meshList[GEO_FRAMERATE] = MeshBuilder::GenerateText("fps", 16, 16);
	meshList[GEO_FRAMERATE]->textureID = LoadTGA("Image//GBA_FE.tga");


	Mesh::SetMaterialLoc(m_parameters[U_MATERIAL_AMBIENT],
		m_parameters[U_MATERIAL_DIFFUSE],
		m_parameters[U_MATERIAL_SPECULAR],
		m_parameters[U_MATERIAL_SHININESS]);


	bLightEnabled = true;
}

void Assignment2::Update(double dt)
{
	static const float LSPEED = 10.f;

	if(Application::IsKeyPressed('1')) //enable back face culling
		glEnable(GL_CULL_FACE);
	if(Application::IsKeyPressed('2')) //disable back face culling
		glDisable(GL_CULL_FACE);
	if(Application::IsKeyPressed('3'))
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL); //default fill mode
	if(Application::IsKeyPressed('4'))
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); //wireframe mode
	if (Application::IsKeyPressed('5'))
	{
		light[0].type = Light::LIGHT_POINT;
		glUniform1i(m_parameters[U_LIGHT0_TYPE], light[0].type);
	}
	else if (Application::IsKeyPressed('6'))
	{
		light[0].type = Light::LIGHT_DIRECTIONAL;
		glUniform1i(m_parameters[U_LIGHT0_TYPE], light[0].type);
	}
	else if (Application::IsKeyPressed('7'))
	{
		light[0].type = Light::LIGHT_SPOT;
		glUniform1i(m_parameters[U_LIGHT0_TYPE], light[0].type);
	}
	if (Application::IsKeyPressed('9'))
		bLightEnabled = false;
	if (Application::IsKeyPressed('0'))
		bLightEnabled = true;
	/*static bool bButton9State = false;
	if (!bButton9State && Application::IsKeyPressed('9'))
	{
		bButton9State = true;
		bLightEnabled = !bLightEnabled;
	}		
	else if (bButton9State && Application::IsKeyPressed('9'))
	{
		bButton9State = false;
	}*/
	if (Application::IsKeyPressed('I'))
		light[0].position.z -= (float)(LSPEED * dt);
	if (Application::IsKeyPressed('K'))
		light[0].position.z += (float)(LSPEED * dt);
	if (Application::IsKeyPressed('J'))
		light[0].position.x -= (float)(LSPEED * dt);
	if (Application::IsKeyPressed('L'))
		light[0].position.x += (float)(LSPEED * dt);
	if (Application::IsKeyPressed('O'))
		light[0].position.y -= (float)(LSPEED * dt);
	if (Application::IsKeyPressed('P'))
		light[0].position.y += (float)(LSPEED * dt);

	if (transporttimer < 10.f)
		transporttimer += 0.016667;

	if (onScreenTimer < 20.f)
		onScreenTimer += 0.016667;

	if (!interactable)
	{
		onScreenTimer = 20.f;
	}

	if (camera.position.z < 20 && camera.position.z > 10 && camera.position.x < 10 && camera.position.x > -10) //Drippy
	{
		interactable = true;
	}
	else if (camera.position.z < 42 && camera.position.z > 38 && camera.position.x < 50 && camera.position.x > 40 && !inAnotherWorld) //Dinner
	{
		interactable = true;
	}
	else if (camera.position.z < 49 && camera.position.z > 45 && camera.position.x < -2 && camera.position.x > -6 && !inAnotherWorld)
	{
		interactable = true;
	}
	else
	{
		interactable = false;
	}

	//Drippy
	if (Application::IsKeyPressed('E') && camera.position.z < 20 && camera.position.z > 10 && camera.position.x < 10 && camera.position.x > -10)
	{
		onScreen = true;
		onScreenTimer = 0.f;
	}
	
	//Dinner
	if (Application::IsKeyPressed('E') && camera.position.z < 42 && camera.position.z > 38 && camera.position.x < 50 && camera.position.x > 40 && !inAnotherWorld)
	{
		onScreen = true;
		onScreenTimer = 0.f;
		dinnerIsEaten = true;
	}

	//Wand
	if (Application::IsKeyPressed('E') && camera.position.z < 49 && camera.position.z > 45 && camera.position.x < -2 && camera.position.x > -6 && !inAnotherWorld)
	{
		onScreen = true;
		onScreenTimer = 0.f;
		hasWand = true;
	}

	std::cout << onScreenTimer << std::endl;
	//std::cout << camera.position.x << " " << camera.position.z << std::endl;

	if (onScreen && onScreenTimer >= 20.0f)
	{
		onScreen = false;
	}

	//Transport 10sec cd --- Gateway
	if (Application::IsKeyPressed('Q') && hasWand)
	{
		if (transportCD == false)
		{
			if (!inAnotherWorld)
			{
				inAnotherWorld = true;
				transporttimer = 0.f;
				transportCD = true;
			}
			else
			{
				inAnotherWorld = false;
				camera.Init(Vector3(0, 0, 25), Vector3(0, 0, 0), Vector3(0, 1, 0));
				transporttimer = 0.f;
				transportCD = true;
			}
		}
	}
	
	//std::cout << transporttimer << std::endl;
	if (transporttimer > 10.f && transportCD == true)
		transportCD = false;

	rotateAngle += (float)(10 * dt);

	fps = 1.0f / dt;

	if (Application::IsKeyPressed('V'))
		hasWand = true;
	else if (Application::IsKeyPressed('B'))
		hasWand = false;

	if (dinnerIsEaten)
	{
		camera.updateSpeed(30.f);
	}

	//Drippy
	{
		//Blinking
		if (blinking)
		{
			if (blinkTemp1 == 3)
			{
				//blinking = false;
				blinkTemp1 = 0;
			}
			else if (blinkTemp == 0)
			{
				eyeLidAngle -= 1;
				eyebrowY += 0.00075;
				if (eyeLidAngle < -120)
				{
					blinkTemp = 1;
					blinkTemp1++;
				}
			}
			else if (blinkTemp == 1)
			{
				eyeLidAngle += 1;
				eyebrowY -= 0.00075;
				if (eyeLidAngle >= 10)
				{
					blinkTemp = 0;
					blinkTemp1++;
				}
			}
		}

		//Swaying
		if (swayTemp == 0)
		{
			lanternAngle += 0.25;
			lanternX -= 0.0075;
			noseAngleX -= 0.075;
			if (lanternAngle >= 10)
			{
				swayTemp = 1;
			}
		}
		else if (swayTemp == 1)
		{
			lanternAngle -= 0.25;
			lanternX += 0.0075;
			noseAngleX += 0.075;
			if (lanternAngle <= -10)
			{
				swayTemp = 0;
			}
		}
	}

	light[1].position.Set(camera.position.x, camera.position.y, camera.position.z);
	
	camera.Update(dt);
	camera.updateInAnotherWorld(inAnotherWorld);
}

void Assignment2::Render()
{
	// Render VBO here
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	if (light[0].type == Light::LIGHT_DIRECTIONAL)
	{
		Vector3 lightDir(light[0].position.x, light[0].position.y, light[0].position.z);
		Vector3 lightDirection_cameraspace = viewStack.Top() * lightDir;
		glUniform3fv(m_parameters[U_LIGHT0_POSITION], 1, &lightDirection_cameraspace.x);
	}
	else if (light[0].type == Light::LIGHT_SPOT)
	{
		Position lightPosition_cameraspace = viewStack.Top() * light[0].position;
		glUniform3fv(m_parameters[U_LIGHT0_POSITION], 1, &lightPosition_cameraspace.x);
		Vector3 spotDirection_cameraspace = viewStack.Top() * light[0].spotDirection;
		glUniform3fv(m_parameters[U_LIGHT0_SPOTDIRECTION], 1, &spotDirection_cameraspace.x);
	}
	else
	{
		Position lightPosition_cameraspace = viewStack.Top() * light[0].position;
		glUniform3fv(m_parameters[U_LIGHT0_POSITION], 1, &lightPosition_cameraspace.x);
	}

	Position lightPosition_cameraspace = viewStack.Top() * light[1].position;
	glUniform3fv(m_parameters[U_LIGHT1_POSITION], 1, &lightPosition_cameraspace.x);

	viewStack.LoadIdentity();
	viewStack.LookAt(
		camera.position.x, camera.position.y, camera.position.z,
		camera.target.x, camera.target.y, camera.target.z,
		camera.up.x, camera.up.y, camera.up.z);

	RenderSkybox();

	modelStack.LoadIdentity();
	
	//RenderMesh(meshList[GEO_AXES], false);

	/*modelStack.PushMatrix();
	{
		modelStack.Translate(light[0].position.x, light[0].position.y, light[0].position.z);
		RenderMesh(meshList[GEO_LIGHTBALL], false);
	}
	modelStack.PopMatrix();*/

	//QUAD
	modelStack.PushMatrix();
	{
		modelStack.Translate(0, -5, 0);
		modelStack.Rotate(-90, 1, 0, 0);
		modelStack.Scale(500, 500, 100);
		if (!inAnotherWorld)
			RenderMesh(meshList[GEO_QUAD], bLightEnabled);
		else
			RenderMesh(meshList[GEO_QUAD1], bLightEnabled);
	}
	modelStack.PopMatrix();
	//QUAD

	//Drippy
	modelStack.PushMatrix();
	{
		modelStack.Translate(bodyX, bodyY, bodyZ);
		modelStack.Rotate(0, 0, 0, 1);
		modelStack.Scale(3.5, 3, 3.5);
		RenderMesh(meshList[GEO_BLUE_HEMISPHERE], true);


		modelStack.Scale(0.28571, 0.33333, 0.28571);
		modelStack.Translate(0, 0, 0);
		modelStack.Rotate(180, 0, 0, 1);
		modelStack.Scale(3.5, 5, 3.5);
		RenderMesh(meshList[GEO_BLUE_HEMISPHERE], true);

		modelStack.Rotate(-180, 0, 0, 1);
		//Head
		modelStack.PushMatrix();
		{
			modelStack.Scale(0.25, 0.16667, 0.25);
			modelStack.Translate(0, 1, 0);
			modelStack.Rotate(0, 0, 0, 1);
			modelStack.Scale(3.5, 6, 3.5);
			RenderMesh(meshList[GEO_YELLOW_HEMISPHERE], true);

			//Nose
			modelStack.PushMatrix();
			{
				modelStack.Scale(0.28571, 0.16667, 0.28571);
				modelStack.Translate(0, 4.3, 2.4);
				modelStack.Rotate(noseAngle, 1, 0, 0);
				modelStack.Rotate(noseAngleX, 0, 0, 1);
				modelStack.Scale(1.5, 4, 1.5);
				RenderMesh(meshList[GEO_YELLOW_SPHERE], true);

				modelStack.PushMatrix();
				{
					modelStack.Rotate(0, 0, 0, 1);
					modelStack.Translate(0, 1.1, 0);
					modelStack.Scale(0.8, 1, 0.8);
					RenderMesh(meshList[GEO_YELLOW_CONE], true);

					//Lantern Connector
					//Ring
					modelStack.PushMatrix();
					{
						modelStack.Scale(0.83333, 0.25, 0.83333);
						modelStack.Rotate(100, -1, 0, 0);
						modelStack.Rotate(90, 1, 0, 0);
						modelStack.Translate(0, 1.1, 0.5);
						modelStack.Scale(0.15, 0.15, 0.15);
						RenderMesh(meshList[GEO_L_CONNECTOR_TORUS], true);

						//Lantern
						modelStack.PushMatrix();
						{
							modelStack.Scale(6.66667, 6.66667, 6.66667);
							modelStack.Rotate(90, 0, 0, -1);
							modelStack.Rotate(lanternAngle, 1, 0, 0);
							modelStack.Translate(0, 0, 0.25);
							modelStack.Scale(0.1, 0.1, 0.1);
							RenderMesh(meshList[GEO_RED_TORUS], true);
							modelStack.Translate(0, 0, -2.5);
							modelStack.PushMatrix();
							{
								modelStack.Scale(10, 10, 10);
								modelStack.Rotate(90, 1, 0, 0);
								modelStack.Translate(0, 0.5, 0);
								modelStack.Scale(0.1, 0.1, 0.1);
								RenderMesh(meshList[GEO_RED_TORUS], true);

							}
							modelStack.PopMatrix();
							modelStack.PushMatrix();
							{
								modelStack.Scale(10, 10, 10);
								modelStack.Rotate(90, -1, 0, 0);
								modelStack.Rotate(45, 0, 1, 0);
								modelStack.Translate(0, -1.25, 0);
								modelStack.Scale(1.5, 1.5, 1.5);
								RenderMesh(meshList[GEO_RED_PYRAMID], true);
							}
							modelStack.PopMatrix();
							modelStack.PushMatrix();
							{
								modelStack.Scale(10, 10, 10);
								modelStack.Rotate(90, -1, 0, 0);
								modelStack.Rotate(0, 0, 1, 0);
								modelStack.Translate(0, -2.5, 0);
								modelStack.Scale(1.5, 1.8, 1.5);
								RenderMesh(meshList[GEO_YELLOW_CUBE], false);
							}
							modelStack.PopMatrix();
							//Pillars
							modelStack.PushMatrix();
							{
								modelStack.Scale(10, 10, 10);
								modelStack.Rotate(90, -1, 0, 0);
								modelStack.Rotate(0, 0, 1, 0);
								modelStack.Translate(0.8, -2.7, 0.8);
								modelStack.Scale(0.025, 0.15, 0.025);
								RenderMesh(meshList[GEO_RED_CYLINDER], true);
							}
							modelStack.PopMatrix();
							modelStack.PushMatrix();
							{
								modelStack.Scale(10, 10, 10);
								modelStack.Rotate(90, -1, 0, 0);
								modelStack.Rotate(0, 0, 1, 0);
								modelStack.Translate(-0.8, -2.7, 0.8);
								modelStack.Scale(0.025, 0.15, 0.025);
								RenderMesh(meshList[GEO_RED_CYLINDER], true);
							}
							modelStack.PopMatrix();
							modelStack.PushMatrix();
							{
								modelStack.Scale(10, 10, 10);
								modelStack.Rotate(90, -1, 0, 0);
								modelStack.Rotate(0, 0, 1, 0);
								modelStack.Translate(-0.8, -2.7, -0.8);
								modelStack.Scale(0.025, 0.15, 0.025);
								RenderMesh(meshList[GEO_RED_CYLINDER], true);
							}
							modelStack.PopMatrix();
							modelStack.PushMatrix();
							{
								modelStack.Scale(10, 10, 10);
								modelStack.Rotate(90, -1, 0, 0);
								modelStack.Rotate(0, 0, 1, 0);
								modelStack.Translate(0.8, -2.7, -0.8);
								modelStack.Scale(0.025, 0.15, 0.025);
								RenderMesh(meshList[GEO_RED_CYLINDER], true);
							}
							modelStack.PopMatrix();
							//Pillars

							//Bottom
							modelStack.PushMatrix();
							{
								modelStack.Scale(10, 10, 10);
								modelStack.Rotate(90, -1, 0, 0);
								modelStack.Rotate(0, 0, 1, 0);
								modelStack.Translate(0, -3.5, 0);
								modelStack.Scale(2, 0.35, 2);
								RenderMesh(meshList[GEO_RED_CUBE], true);
							}
							modelStack.PopMatrix();
							//Bottom
						}
						modelStack.PopMatrix();
						//Lantern
					}
					modelStack.PopMatrix();
					//Ring
					//Lanturn Connector
				}
				modelStack.PopMatrix();
			}
			modelStack.PopMatrix();
			//Nose

			//Eyes
			{
				//Left
				modelStack.PushMatrix();
				{
					modelStack.Scale(0.28571, 0.16667, 0.28571);
					modelStack.Rotate(45, 0, 0, 1);
					modelStack.Translate(2, 4, 1);
					modelStack.Scale(1, 1, 1);
					RenderMesh(meshList[GEO_WHITE_HEMISPHERE], true);

					//Pupil
					modelStack.PushMatrix();
					{
						modelStack.Rotate(45, 1, 0, 0);
						modelStack.Translate(0, 0.6, 0);
						modelStack.Scale(0.5, 0.5, 0.5);
						RenderMesh(meshList[GEO_BLACK_HEMISPHERE], true);
					}
					modelStack.PopMatrix();
					//Pupil

					//EyeLid
					modelStack.PushMatrix();
					{
						modelStack.Rotate(-45, 0, 1, -1);
						//modelStack.Translate(-2, -4, -1);

						modelStack.Rotate(eyeLidAngle, 1, 0, 0);
						//modelStack.Translate(1, 4, 2);
						modelStack.Scale(1.15, 1.15, 1.15);
						RenderMesh(meshList[GEO_YELLOW_HEMISPHERE], true);
					}
					modelStack.PopMatrix();
					//Eyelid

				}
				modelStack.PopMatrix();
				//Left

				//Right
				modelStack.PushMatrix();
				{
					modelStack.Scale(0.28571, 0.16667, 0.28571);
					modelStack.Rotate(-45, 0, 0, 1);
					modelStack.Translate(-2, 4, 1);
					modelStack.Scale(1, 1, 1);
					RenderMesh(meshList[GEO_WHITE_HEMISPHERE], true);

					//Pupil
					modelStack.PushMatrix();
					{
						modelStack.Rotate(0, -90, -90, 1);
						modelStack.Rotate(45, 45, 0, 1);
						modelStack.Translate(0, 0.6, 0);
						modelStack.Scale(0.5, 0.5, 0.5);
						RenderMesh(meshList[GEO_BLACK_HEMISPHERE], true);
					}
					modelStack.PopMatrix();
					//Pupil

					//EyeLid
					modelStack.PushMatrix();
					{
						modelStack.Rotate(45, 0, 1, -1);
						//modelStack.Translate(-2, -4, -1);

						modelStack.Rotate(eyeLidAngle, 1, 0, 0);
						//modelStack.Translate(1, 4, 2);
						modelStack.Scale(1.15, 1.15, 1.15);
						RenderMesh(meshList[GEO_YELLOW_HEMISPHERE], true);
					}
					modelStack.PopMatrix();
					//Eyelid


				}
				modelStack.PopMatrix();
				//Right
			}
			//Eyes
		}
		modelStack.PopMatrix();
		//Head

		//Arms
		modelStack.PushMatrix();
		{
			modelStack.Scale(0.28571, 0.2, 0.28571);
			//Left
			modelStack.PushMatrix();
			{
				modelStack.Rotate(lArmAngle, 0, 0, 1);
				modelStack.Translate(2.8, -2.8, 0);
				modelStack.Scale(0.2, 1, 0.2);
				RenderMesh(meshList[GEO_YELLOW_SPHERE], true);
			}
			modelStack.PopMatrix();
			//Left

			//Right
			modelStack.PushMatrix();
			{
				modelStack.Rotate(rArmAngle, 0, 0, -1);
				modelStack.Translate(-2.8, -2.8, 0);
				modelStack.Scale(0.2, 1, 0.2);
				RenderMesh(meshList[GEO_YELLOW_SPHERE], true);
			}
			modelStack.PopMatrix();
			//Right
		}
		modelStack.PopMatrix();
		//Arms

		//Legs
		modelStack.PushMatrix();
		{
			modelStack.Scale(0.28571, 0.2, 0.28571);
			//Right
			modelStack.PushMatrix();
			{
				modelStack.Rotate(rLegAngle, 1, 0, 0);
				modelStack.Translate(-1, -4.5, 0);
				modelStack.Scale(0.2, 1, 0.2);
				RenderMesh(meshList[GEO_LEG_SPHERE], true);

				//Foot
				modelStack.PushMatrix();
				{
					modelStack.Scale(5, 1, 5);
					modelStack.Translate(0, -1.2, -0.2);
					modelStack.Rotate(35, 1, 0, 0);

					modelStack.Scale(0.2, 1, 0.2);
					modelStack.Scale(0.8, 0.5, 0.8);
					RenderMesh(meshList[GEO_LEG_SPHERE], true);
				}
				modelStack.PopMatrix();
				//Foot
			}
			modelStack.PopMatrix();
			//Right

			//Left
			modelStack.PushMatrix();
			{
				modelStack.Rotate(lLegAngle, 1, 0, 0);
				modelStack.Translate(1, -4.5, 0);
				modelStack.Scale(0.2, 1, 0.2);
				RenderMesh(meshList[GEO_LEG_SPHERE], true);

				//Foot
				modelStack.PushMatrix();
				{
					modelStack.Scale(5, 1, 5);
					modelStack.Translate(0, -1.2, -0.2);
					modelStack.Rotate(35, 1, 0, 0);

					modelStack.Scale(0.2, 1, 0.2);
					modelStack.Scale(0.8, 0.5, 0.8);
					RenderMesh(meshList[GEO_LEG_SPHERE], true);
				}
				modelStack.PopMatrix();
				//Foot
			}
			modelStack.PopMatrix();
			//Left
		}
		modelStack.PopMatrix();
		//Legs

		//Face
		modelStack.PushMatrix();
		{
			//Mouth
			modelStack.PushMatrix();
			{

				modelStack.Translate(0, 0.4, 0.83);
				modelStack.Rotate(0, 1, 0, 0);
				modelStack.Scale(0.5, 0.025, 0.04);

				RenderMesh(meshList[GEO_BLACK_CUBE], true);
			}
			modelStack.PopMatrix();
			modelStack.PushMatrix();
			{

				modelStack.Translate(0.33, 0.4, 0.75);
				modelStack.Rotate(25, 0, 1, 0);
				modelStack.Rotate(25, 1, 0, 0);
				modelStack.Scale(0.25, 0.025, 0.05);

				RenderMesh(meshList[GEO_BLACK_CUBE], true);
			}
			modelStack.PopMatrix();
			modelStack.PushMatrix();
			{

				modelStack.Translate(-0.33, 0.4, 0.75);
				modelStack.Rotate(25, 0, -1, 0);
				modelStack.Rotate(25, 1, 0, 0);
				modelStack.Scale(0.25, 0.025, 0.05);

				RenderMesh(meshList[GEO_BLACK_CUBE], true);
			}
			modelStack.PopMatrix();
			//Mouth

			//EyeBrows
			modelStack.PushMatrix();
			{

				modelStack.Translate(0.33, eyebrowY, 0.1);
				modelStack.Rotate(40, 0, 1, 0);
				modelStack.Scale(0.25, 0.0125, 0.025);

				RenderMesh(meshList[GEO_BLACK_CUBE], true);
			}
			modelStack.PopMatrix();
			modelStack.PushMatrix();
			{

				modelStack.Translate(-0.33, eyebrowY, 0.1);
				modelStack.Rotate(40, 0, -1, 0);
				modelStack.Scale(0.25, 0.0125, 0.025);

				RenderMesh(meshList[GEO_BLACK_CUBE], true);
			}
			modelStack.PopMatrix();
			//EyeBrows
		}
		modelStack.PopMatrix();
		//Face

	}
	modelStack.PopMatrix();
	//Drippy

	//Scene
	if (!inAnotherWorld)
	{
		//road
		{
			//taxi
			modelStack.PushMatrix();
			{
				//scale, translate, rotate
				modelStack.Translate(35, -5, -2);
				modelStack.Rotate(90, 0, 1, 0);
				modelStack.Scale(10, 10, 10);
				RenderMesh(meshList[GEO_CAR1], bLightEnabled);
			}
			modelStack.PopMatrix();

			//van
			modelStack.PushMatrix();
			{
				//scale, translate, rotate
				modelStack.Translate(-12, -5, -18);
				modelStack.Rotate(90, 0, -1, 0);
				modelStack.Scale(10, 10, 10);
				RenderMesh(meshList[GEO_CAR2], bLightEnabled);
			}
			modelStack.PopMatrix();

			//road
			modelStack.PushMatrix();
			{
				//scale, translate, rotate
				modelStack.Translate(0, -5, -10);
				modelStack.Scale(500, 10, 40);
				RenderMesh(meshList[GEO_ROAD], bLightEnabled);
			}
			modelStack.PopMatrix();
		}
		
		//buildings
		{
			modelStack.PushMatrix();
			{
				//scale, translate, rotate
				modelStack.Translate(62, -5, 33);
				modelStack.Rotate(90, 0, -1, 0);
				modelStack.Scale(25, 25, 25);
				RenderMesh(meshList[GEO_SMALLBUILDINGE], bLightEnabled);
			}
			modelStack.PopMatrix();

			modelStack.PushMatrix();
			{
				//scale, translate, rotate
				modelStack.Translate(62, -5, 65);
				modelStack.Rotate(90, 0, -1, 0);
				modelStack.Scale(25, 25, 25);
				RenderMesh(meshList[GEO_LARGEBUILDINGB], bLightEnabled);
			}
			modelStack.PopMatrix();

			modelStack.PushMatrix();
			{
				//scale, translate, rotate
				modelStack.Translate(35, -5, 70);
				modelStack.Rotate(180, 0, 1, 0);
				modelStack.Scale(25, 25, 25);
				RenderMesh(meshList[GEO_LARGEBUILDINGE], bLightEnabled);
			}
			modelStack.PopMatrix();

			modelStack.PushMatrix();
			{
				//scale, translate, rotate
				modelStack.Translate(0, -5, 65);
				modelStack.Rotate(180, 0, 1, 0);
				modelStack.Scale(20, 20, 20);
				RenderMesh(meshList[GEO_LARGEBUILDINGF], bLightEnabled);
			}
			modelStack.PopMatrix();

			modelStack.PushMatrix();
			{
				//scale, translate, rotate
				modelStack.Translate(-35, -5, 70);
				modelStack.Rotate(180, 0, 1, 0);
				modelStack.Scale(25, 25, 25);
				RenderMesh(meshList[GEO_LARGEBUILDINGE], bLightEnabled);
			}
			modelStack.PopMatrix();

			modelStack.PushMatrix();
			{
				//scale, translate, rotate
				modelStack.Translate(-62, -5, 65);
				modelStack.Rotate(90, 0, 1, 0);
				modelStack.Scale(25, 25, 25);
				RenderMesh(meshList[GEO_LARGEBUILDINGB], bLightEnabled);
			}
			modelStack.PopMatrix();

			modelStack.PushMatrix();
			{
				//scale, translate, rotate
				modelStack.Translate(-62, -5, 33);
				modelStack.Rotate(90, 0, 1, 0);
				modelStack.Scale(25, 25, 25);
				RenderMesh(meshList[GEO_SMALLBUILDINGE], bLightEnabled);
			}
			modelStack.PopMatrix();
		}

		/*modelStack.PushMatrix();
		{
			modelStack.Translate(0, 1, 25);
			modelStack.Rotate(180, 0, -1, 0);
			modelStack.Scale(10, 10, 10);
			RenderMesh(meshList[GEO_STICK], true);
		}
		modelStack.PopMatrix();*/
		//Objects near buildings
		{
			modelStack.PushMatrix();
			{
				//scale, translate, rotate
				modelStack.Translate(45, -5, 45);
				modelStack.Rotate(90, 0, -1, 0);
				modelStack.Scale(25, 25, 25);
				RenderMesh(meshList[GEO_UMBRELLA], bLightEnabled);
			}
			modelStack.PopMatrix();

			modelStack.PushMatrix();
			{
				//scale, translate, rotate
				modelStack.Translate(45, -2, 42);
				modelStack.Rotate(90, 0, -1, 0);
				modelStack.Scale(2, 2, 2);
				if (!dinnerIsEaten)
					RenderMesh(meshList[GEO_DINNER], bLightEnabled);
				else
					RenderMesh(meshList[GEO_EMPTYDINNER], bLightEnabled);
			}
			modelStack.PopMatrix();

			modelStack.PushMatrix();
			{
				//scale, translate, rotate
				modelStack.Translate(43, -2, 43);
				modelStack.Rotate(90, 0, -1, 0);
				modelStack.Scale(3, 3, 3);
				RenderMesh(meshList[GEO_APPLE], bLightEnabled);
			}
			modelStack.PopMatrix();

			modelStack.PushMatrix();
			{
				//scale, translate, rotate
				modelStack.Translate(-18, -4.8, 49);
				modelStack.Rotate(90, 0, -1, 0);
				modelStack.Scale(3, 3, 3);
				RenderMesh(meshList[GEO_REDWINE], bLightEnabled);
			}
			modelStack.PopMatrix();

			modelStack.PushMatrix();
			{
				//scale, translate, rotate
				modelStack.Translate(-20, -4.8, 51);
				modelStack.Rotate(90, 1, 0, 1);
				modelStack.Scale(3, 3, 3);
				RenderMesh(meshList[GEO_WHITEWINE], bLightEnabled);
			}
			modelStack.PopMatrix();
		}

		//bins
		{
			modelStack.PushMatrix();
			{
				//scale, translate, rotate
				modelStack.Translate(-8, -4.8, 51);
				modelStack.Scale(1, 1, 1);
				RenderMesh(meshList[GEO_BIN], bLightEnabled);
				modelStack.Translate(0, 1, 0);
				RenderMesh(meshList[GEO_PAPERBALL], bLightEnabled);
			}
			modelStack.PopMatrix();

			modelStack.PushMatrix();
			{
				//scale, translate, rotate
				modelStack.Translate(-12, -4.8, 51);
				modelStack.Scale(1, 1, 1);
				RenderMesh(meshList[GEO_BIN], bLightEnabled);
				modelStack.Translate(0, 1, 0);
				RenderMesh(meshList[GEO_PAPERBALL], bLightEnabled);
			}
			modelStack.PopMatrix();

			modelStack.PushMatrix();
			{
				//scale, translate, rotate
				modelStack.Translate(-16, -4.8, 51);
				modelStack.Scale(1, 1, 1);
				RenderMesh(meshList[GEO_BIN], bLightEnabled);
				modelStack.Translate(0, 1, 0);
				RenderMesh(meshList[GEO_PAPERBALL], bLightEnabled);
			}
			modelStack.PopMatrix();

			modelStack.PushMatrix();
			{
				//scale, translate, rotate
				modelStack.Translate(-4, -4.8, 51);
				modelStack.Scale(1, 1, 1);
				RenderMesh(meshList[GEO_BIN], bLightEnabled);

				if (!hasWand)
				{
					modelStack.Translate(-0, 2, 0);
					modelStack.Rotate(180, 0, -1, 0);
					modelStack.Rotate(40, 0, 0, -1);
					modelStack.Scale(10, 10, 10);
					RenderMesh(meshList[GEO_STICK], true);
				}
			}
			modelStack.PopMatrix();

			modelStack.PushMatrix();
			{
				//scale, translate, rotate
				modelStack.Translate(-0, -4.8, 51);
				modelStack.Scale(1, 1, 1);
				RenderMesh(meshList[GEO_BIN], bLightEnabled);
				modelStack.Translate(0, 1, 0);
				RenderMesh(meshList[GEO_PAPERBALL], bLightEnabled);
			}
			modelStack.PopMatrix();

			modelStack.PushMatrix();
			{
				//scale, translate, rotate
				modelStack.Translate(4, -4.8, 51);
				modelStack.Scale(1, 1, 1);
				RenderMesh(meshList[GEO_BIN], bLightEnabled);
				modelStack.Translate(0, 1, 0);
				RenderMesh(meshList[GEO_PAPERBALL], bLightEnabled);
			}
			modelStack.PopMatrix();

			modelStack.PushMatrix();
			{
				//scale, translate, rotate
				modelStack.Translate(8, -4.8, 51);
				modelStack.Scale(1, 1, 1);
				RenderMesh(meshList[GEO_BIN], bLightEnabled);
				modelStack.Translate(0, 1, 0);
				RenderMesh(meshList[GEO_PAPERBALL], bLightEnabled);
			}
			modelStack.PopMatrix();

			modelStack.PushMatrix();
			{
				//scale, translate, rotate
				modelStack.Translate(12, -4.8, 51);
				modelStack.Scale(1, 1, 1);
				RenderMesh(meshList[GEO_BIN], bLightEnabled);
				modelStack.Translate(0, 1, 0);
				RenderMesh(meshList[GEO_PAPERBALL], bLightEnabled);
			}
			modelStack.PopMatrix();

			modelStack.PushMatrix();
			{
				//scale, translate, rotate
				modelStack.Translate(16, -4.8, 51);
				modelStack.Scale(1, 1, 1);
				RenderMesh(meshList[GEO_BIN], bLightEnabled);
				modelStack.Translate(0, 1, 0);
				RenderMesh(meshList[GEO_PAPERBALL], bLightEnabled);
			}
			modelStack.PopMatrix();
		}
	
		//fence
		modelStack.PushMatrix();
		{
			//scale, translate, rotate
			modelStack.Translate(0, -5, -50);
			modelStack.Rotate(0, 0, -1, 0);
			modelStack.Scale(250, 25, 1);
			RenderMesh(meshList[GEO_FENCE], bLightEnabled);
		}

		//Dinner Text
		if (camera.position.z < 42 && camera.position.z > 38 && camera.position.x < 50 && camera.position.x > 40 && onScreenTimer <= 5.f && onScreen)
		{
			modelStack.PushMatrix();
			//scale, translate, rotate
			modelStack.Translate(10, 0, 10);
			RenderTextOnScreen(meshList[GEO_INTERACTTEXT], "Someone is going hungry today...", Color(0.184, 0.184, 0.184), 4, 10, 20);
			modelStack.PopMatrix();
		}
		//Wand Text
		if (camera.position.z < 49 && camera.position.z > 45 && camera.position.x < -2 && camera.position.x > -6 && onScreen)
		{
			modelStack.PushMatrix();
			//scale, translate, rotate
			modelStack.Translate(10, 0, 10);
			if (onScreenTimer <= 3.f)
			{
				RenderTextOnScreen(meshList[GEO_INTERACTTEXT], "The bin is now empty...", Color(0.184, 0.184, 0.184), 4, 15, 20);
			}
			else if (onScreenTimer <= 8.f)
			{
				RenderTextOnScreen(meshList[GEO_INTERACTTEXT], "Like your soul", Color(0.184, 0.184, 0.184), 4, 20, 20);
			}
			modelStack.PopMatrix();
		}
		//Drippy Text
		if (camera.position.z < 20 && camera.position.z > 10 && camera.position.x < 10 && camera.position.x > -10 && onScreen)
		{
			if (hasWand)
			{
				if (onScreenTimer <= 5.f)
				{
					modelStack.PushMatrix();
					//scale, translate, rotate
					modelStack.Translate(10, 0, 10);
					RenderTextOnScreen(meshList[GEO_INTERACTTEXT], "Blimey! You got youer flippin wand!", Color(0.050, 0.353, 0.871), 4, 5, 20);
					modelStack.PopMatrix();
				}
				else if (onScreenTimer <= 8.f)
				{
					modelStack.PushMatrix();
					//scale, translate, rotate
					modelStack.Translate(10, 0, 10);
					RenderTextOnScreen(meshList[GEO_INTERACTTEXT], "There's proper tidy, en't it?", Color(0.050, 0.353, 0.871), 4, 10, 20);
					modelStack.PopMatrix();
				}
				else if (onScreenTimer <= 10.f)
				{
					modelStack.PushMatrix();
					//scale, translate, rotate
					modelStack.Translate(10, 0, 10);
					RenderTextOnScreen(meshList[GEO_INTERACTTEXT], "What are you waitin for?", Color(0.050, 0.353, 0.871), 4, 15, 20);
					modelStack.PopMatrix();
				}
				else if (onScreenTimer <= 20.f)
				{
					modelStack.PushMatrix();
					//scale, translate, rotate
					modelStack.Translate(10, 0, 10);
					RenderTextOnScreen(meshList[GEO_INTERACTTEXT], "Press 'Q' to cast Gateway, ya bunting!", Color(0.050, 0.353, 0.871), 4, 5, 20);
					modelStack.PopMatrix();
				}

			}
			else
			{
				if (onScreenTimer <= 5.f)
				{
					modelStack.PushMatrix();
					//scale, translate, rotate
					modelStack.Translate(10, 0, 10);
					RenderTextOnScreen(meshList[GEO_INTERACTTEXT], "You forgot how use cast flippin Gateway?!", Color(0.050, 0.353, 0.871), 4, 0, 20);
					modelStack.PopMatrix();
				}
				else if (onScreenTimer <= 10.f)
				{
					modelStack.PushMatrix();
					//scale, translate, rotate
					modelStack.Translate(10, 0, 10);
					RenderTextOnScreen(meshList[GEO_INTERACTTEXT], "You en't even have youer wand ya bunting!", Color(0.050, 0.353, 0.871), 4, 0, 20);
					modelStack.PopMatrix();
				}
				else if (onScreenTimer <= 15.f)
				{
					modelStack.PushMatrix();
					//scale, translate, rotate
					modelStack.Translate(10, 0, 10);
					RenderTextOnScreen(meshList[GEO_INTERACTTEXT], "Find it then talk to me again, mun", Color(0.050, 0.353, 0.871), 4, 10, 20);
					modelStack.PopMatrix();
				}
			}
		}
	}
	else
	{




		//Drippy Text
		if (camera.position.z < 20 && camera.position.z > 10 && camera.position.x < 10 && camera.position.x > -10 && onScreen)
	{
		if (onScreenTimer <= 5.f)
		{
			modelStack.PushMatrix();
			//scale, translate, rotate
			modelStack.Translate(10, 0, 10);
			RenderTextOnScreen(meshList[GEO_INTERACTTEXT], "This place is pretty tidy, en't it", Color(0.050, 0.353, 0.871), 4, 5, 20);
			modelStack.PopMatrix();
		}
	}
	}


	modelStack.PushMatrix();
	//scale, translate, rotate
	modelStack.LoadIdentity();
	modelStack.Translate(bodyX - 2, 10, bodyZ);
	//modelStack.Scale(0.5 , 0.5, 0.5);
	RenderText(meshList[GEO_TEXT], "DRIPPY", Color(0.050, 0.353, 0.871));
	modelStack.PopMatrix();

	if (interactable) 
	{
		modelStack.PushMatrix();
		//scale, translate, rotate
		modelStack.Translate(10, 0, 10);
		RenderTextOnScreen(meshList[GEO_ONSCREENTEXT], "Press 'E' to Interact", Color(0.337, 0.902, 0.396), 4, 20, 10);
		modelStack.PopMatrix();
	}


	

	// Text on screen
	std::ostringstream ss;
	ss.str("");
	ss << "FPS: " << fps;
	modelStack.PushMatrix();
	modelStack.Translate(10, 0, 10);
	RenderTextOnScreen(meshList[GEO_FRAMERATE], ss.str(), Color(0, 0, 0), 3, 1, 56);
	modelStack.PopMatrix();


	////QUAD
	//modelStack.PushMatrix();
	//{
	//	modelStack.Translate(0, 0, 0);
	//	modelStack.Rotate(180, 0, 0, 1);
	//	modelStack.Scale(10, 10, 10);
	//	RenderMesh(meshList[GEO_IMAGE], bLightEnabled);
	//}
	//modelStack.PopMatrix();
	////QUAD
}

void Assignment2::RenderSkybox() 
{
	// Render VBO here
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	modelStack.LoadIdentity();

	if (inAnotherWorld)
	{
		modelStack.PushMatrix();
		{
			modelStack.Translate(camera.position.x, camera.position.y, -499 + camera.position.z);
			modelStack.Rotate(180, 0, 0, 1);
			modelStack.Scale(1000, 1000, 1000);
			RenderMesh(meshList[GEO_FRONT], false);
		}
		modelStack.PopMatrix();

		modelStack.PushMatrix();
		{
			modelStack.Translate(camera.position.x, camera.position.y, 499 + camera.position.z);
			modelStack.Rotate(180, 0, 0, 1);
			modelStack.Rotate(180, 0, 1, 0);
			modelStack.Scale(1000, 1000, 1000);
			RenderMesh(meshList[GEO_BACK], false);
		}
		modelStack.PopMatrix();

		modelStack.PushMatrix();
		{
			modelStack.Translate(-499 + camera.position.x, camera.position.y, camera.position.z);
			modelStack.Rotate(90, 0, 1, 0);
			modelStack.Rotate(180, 0, 0, 1);
			modelStack.Scale(1000, 1000, 1000);
			RenderMesh(meshList[GEO_LEFT], false);
		}
		modelStack.PopMatrix();

		modelStack.PushMatrix();
		{
			modelStack.Translate(499 + camera.position.x, camera.position.y, camera.position.z);
			modelStack.Rotate(-90, 0, 1, 0);
			modelStack.Rotate(180, 0, 0, 1);
			modelStack.Scale(1000, 1000, 1000);
			RenderMesh(meshList[GEO_RIGHT], false);
		}
		modelStack.PopMatrix();

		modelStack.PushMatrix();
		{
			modelStack.Translate(camera.position.x, 499 + camera.position.y, camera.position.z);
			modelStack.Rotate(90, 1, 0, 0);
			modelStack.Rotate(270, 0, 0, 1);
			modelStack.Scale(1000, 1000, 1000);
			RenderMesh(meshList[GEO_TOP], false);
		}
		modelStack.PopMatrix();

		modelStack.PushMatrix();
		{
			modelStack.Translate(camera.position.x, -499 + camera.position.y, camera.position.z);
			modelStack.Rotate(-90, 1, 0, 0);
			modelStack.Rotate(90, 0, 0, 1);
			modelStack.Scale(1000, 1000, 1000);
			RenderMesh(meshList[GEO_BOTTOM], false);
		}
		modelStack.PopMatrix();
	}
	else
	{
		modelStack.PushMatrix();
		{
			modelStack.Translate(camera.position.x, camera.position.y, -499 + camera.position.z);
			modelStack.Rotate(180, 0, 0, 1);
			modelStack.Scale(1000, 1000, 1000);
			RenderMesh(meshList[GEO_FRONT1], false);
		}
		modelStack.PopMatrix();

		modelStack.PushMatrix();
		{
			modelStack.Translate(camera.position.x, camera.position.y, 499 + camera.position.z);
			modelStack.Rotate(180, 0, 0, 1);
			modelStack.Rotate(180, 0, 1, 0);
			modelStack.Scale(1000, 1000, 1000);
			RenderMesh(meshList[GEO_BACK1], false);
		}
		modelStack.PopMatrix();

		modelStack.PushMatrix();
		{
			modelStack.Translate(-499 + camera.position.x, camera.position.y, camera.position.z);
			modelStack.Rotate(90, 0, 1, 0);
			modelStack.Rotate(180, 0, 0, 1);
			modelStack.Scale(1000, 1000, 1000);
			RenderMesh(meshList[GEO_LEFT1], false);
		}
		modelStack.PopMatrix();

		modelStack.PushMatrix();
		{
			modelStack.Translate(499 + camera.position.x, camera.position.y, camera.position.z);
			modelStack.Rotate(-90, 0, 1, 0);
			modelStack.Rotate(180, 0, 0, 1);
			modelStack.Scale(1000, 1000, 1000);
			RenderMesh(meshList[GEO_RIGHT1], false);
		}
		modelStack.PopMatrix();

		modelStack.PushMatrix();
		{
			modelStack.Translate(camera.position.x, 499 + camera.position.y, camera.position.z);
			modelStack.Rotate(90, 1, 0, 0);
			modelStack.Rotate(270, 0, 0, 1);
			modelStack.Scale(1000, 1000, 1000);
			RenderMesh(meshList[GEO_TOP1], false);
		}
		modelStack.PopMatrix();

		modelStack.PushMatrix();
		{
			modelStack.Translate(camera.position.x, -499 + camera.position.y, camera.position.z);
			modelStack.Rotate(-90, 1, 0, 0);
			modelStack.Rotate(90, 0, 0, 1);
			modelStack.Scale(1000, 1000, 1000);
			RenderMesh(meshList[GEO_BOTTOM1], false);
		}
		modelStack.PopMatrix();
	}
	
}

void Assignment2::Exit()
{
	// Cleanup VBO here
	for (int i = 0; i < NUM_GEOMETRY; ++i)
	{
		if (meshList[i])
		{
			delete meshList[i];
		}
	}
	glDeleteVertexArrays(1, &m_vertexArrayID);
	glDeleteProgram(m_programID);
}

bool Assignment2::getInAnotherWorld()
{
	return inAnotherWorld;
}

void Assignment2::RenderText(Mesh* mesh, std::string text, Color color)
{
	if (!mesh || mesh->textureID <= 0) //Proper error check
		return;
	//glDisable(GL_DEPTH_TEST); //uncomment for RenderTextOnScreen
	glUniform1i(m_parameters[U_TEXT_ENABLED], 1);
	glUniform3fv(m_parameters[U_TEXT_COLOR], 1, &color.r);
	glUniform1i(m_parameters[U_LIGHTENABLED], 0);
	glUniform1i(m_parameters[U_COLOR_TEXTURE_ENABLED], 1);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, mesh->textureID);
	glUniform1i(m_parameters[U_COLOR_TEXTURE], 0);
	for (unsigned i = 0; i < text.length(); ++i)
	{
		Mtx44 characterSpacing;
		characterSpacing.SetToTranslation(i * 1.0f, 0, 0); //1.0f is the spacing of each character, you may change this value
			Mtx44 MVP = projectionStack.Top() * viewStack.Top() *
			modelStack.Top() * characterSpacing;
		glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]);
		mesh->Render((unsigned)text[i] * 6, 6);
	}
	glBindTexture(GL_TEXTURE_2D, 0);
	glUniform1i(m_parameters[U_TEXT_ENABLED], 0);
	//glEnable(GL_DEPTH_TEST); //uncomment for RenderTextOnScreen

}

void Assignment2::RenderTextOnScreen(Mesh* mesh, std::string text, Color color, float size, float x, float y)
{
	if (!mesh || mesh->textureID <= 0) //Proper error check
		return;
	glDisable(GL_DEPTH_TEST); //uncomment for RenderTextOnScreen
	Mtx44 ortho;
	ortho.SetToOrtho(0, 80, 0, 60, -10, 10); //size of screen UI
	projectionStack.PushMatrix();
	projectionStack.LoadMatrix(ortho);
	viewStack.PushMatrix();
	viewStack.LoadIdentity(); //No need camera for ortho mode
	modelStack.PushMatrix();
	modelStack.LoadIdentity(); //Reset modelStack
	modelStack.Translate(x, y, 0);
	modelStack.Scale(size, size, size);
	glUniform1i(m_parameters[U_TEXT_ENABLED], 1);
	glUniform3fv(m_parameters[U_TEXT_COLOR], 1, &color.r);
	glUniform1i(m_parameters[U_LIGHTENABLED], 0);
	glUniform1i(m_parameters[U_COLOR_TEXTURE_ENABLED], 1);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, mesh->textureID);
	glUniform1i(m_parameters[U_COLOR_TEXTURE], 0);
	for (unsigned i = 0; i < text.length(); ++i)
	{
		Mtx44 characterSpacing;
		characterSpacing.SetToTranslation(0.5f + i * 0.5f, 0.5f, 0); //1.0f is the spacing of each character, you may change this value
		// original : 0.5f + i * 1.0f, 0.5f, 0
		Mtx44 MVP = projectionStack.Top() * viewStack.Top() *
			modelStack.Top() * characterSpacing;
		glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE,
			&MVP.a[0]);
		mesh->Render((unsigned)text[i] * 6, 6);
	}
	glBindTexture(GL_TEXTURE_2D, 0);
	glUniform1i(m_parameters[U_TEXT_ENABLED], 0);
	projectionStack.PopMatrix();
	viewStack.PopMatrix();
	modelStack.PopMatrix();
	glEnable(GL_DEPTH_TEST); //uncomment for RenderTextOnScreen
}

void Assignment2::RenderMesh(Mesh* mesh, bool enableLight)
{
	Mtx44 MVP, modelView, modelView_inverse_transpose;

	MVP = projectionStack.Top() * viewStack.Top() * modelStack.Top();
	glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]);
	modelView = viewStack.Top() * modelStack.Top();
	glUniformMatrix4fv(m_parameters[U_MODELVIEW], 1, GL_FALSE, &modelView.a[0]);
	if (enableLight)
	{
		glUniform1i(m_parameters[U_LIGHTENABLED], 1);
		modelView_inverse_transpose = modelView.GetInverse().GetTranspose();
		glUniformMatrix4fv(m_parameters[U_MODELVIEW_INVERSE_TRANSPOSE], 1, GL_FALSE, &modelView_inverse_transpose.a[0]);

		//load material
		glUniform3fv(m_parameters[U_MATERIAL_AMBIENT], 1, &mesh->material.kAmbient.r);
		glUniform3fv(m_parameters[U_MATERIAL_DIFFUSE], 1, &mesh->material.kDiffuse.r);
		glUniform3fv(m_parameters[U_MATERIAL_SPECULAR], 1, &mesh->material.kSpecular.r);
		glUniform1f(m_parameters[U_MATERIAL_SHININESS], mesh->material.kShininess);
	}
	else
	{
		glUniform1i(m_parameters[U_LIGHTENABLED], 0);
	}
	
	if (mesh->textureID > 0)
	{
		glUniform1i(m_parameters[U_COLOR_TEXTURE_ENABLED], 1);
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, mesh->textureID);
		glUniform1i(m_parameters[U_COLOR_TEXTURE], 0);
	}
	else
	{
		glUniform1i(m_parameters[U_COLOR_TEXTURE_ENABLED], 0);
	}
	mesh->Render(); //this line should only be called once
	if (mesh->textureID > 0)
	{
		glBindTexture(GL_TEXTURE_2D, 0);
	}
}
