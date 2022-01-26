#include "Assignment1.h"
#include "GL\glew.h"

#include "shader.hpp"
#include "Mtx44.h"

#include "Application.h"
#include "MeshBuilder.h"
#include "Utility.h"


Assignment1::Assignment1()
{
}

Assignment1::~Assignment1()
{
}

void Assignment1::Init()
{	
	// Set background color to dark blue
	glClearColor(0.0f, 0.0f, 0.4f, 0.0f);

	//Enable depth buffer and depth testing
	glEnable(GL_DEPTH_TEST);

	//Enable back face culling
	glEnable(GL_CULL_FACE);

	//Default to fill mode
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

	// Generate a default VAO for now
	glGenVertexArrays(1, &m_vertexArrayID);
	glBindVertexArray(m_vertexArrayID);
	
	//Load vertex and fragment shaders
	m_programID = LoadShaders("Shader//Shading.vertexshader", "Shader//LightSource.fragmentshader");
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
	
	light[0].type = Light::LIGHT_POINT;
	light[0].position.Set(0, 20, 0);
	light[0].color.Set(1, 1, 1);
	light[0].power = 0.5;
	light[0].kC = 1.f;
	light[0].kL = 0.01f;
	light[0].kQ = 0.001f;
	light[0].cosCutoff = cos(Math::DegreeToRadian(45));
	light[0].cosInner = cos(Math::DegreeToRadian(30));
	light[0].exponent = 3.f;
	light[0].spotDirection.Set(0.f, 1.f, 0.f);

	glUniform1i(m_parameters[U_LIGHT0_TYPE], light[0].type);
	glUniform3fv(m_parameters[U_LIGHT0_COLOR], 1, &light[0].color.r);
	glUniform1f(m_parameters[U_LIGHT0_POWER], light[0].power);
	glUniform1f(m_parameters[U_LIGHT0_KC], light[0].kC);
	glUniform1f(m_parameters[U_LIGHT0_KL], light[0].kL);
	glUniform1f(m_parameters[U_LIGHT0_KQ], light[0].kQ);
	glUniform1f(m_parameters[U_LIGHT0_COSCUTOFF], light[0].cosCutoff);
	glUniform1f(m_parameters[U_LIGHT0_COSINNER], light[0].cosInner);
	glUniform1f(m_parameters[U_LIGHT0_EXPONENT], light[0].exponent);
	glUniform1i(m_parameters[U_NUMLIGHTS], 1);

	lanternX = 0;
	lanternY = 7.5;
	lanternZ = 6.8;

	light[1].type = Light::LIGHT_POINT;
	light[1].position.Set(lanternX, lanternY, lanternZ);
	light[1].color.Set(1, 0.77647, 0.36078);
	light[1].power = 2;
	light[1].kC = 1.f;
	light[1].kL = 0.01f;
	light[1].kQ = 0.001f;
	light[1].cosCutoff = cos(Math::DegreeToRadian(30));
	light[1].cosInner = cos(Math::DegreeToRadian(15));
	light[1].exponent = 3.f;
	light[1].spotDirection.Set(0.f, 1.f, 0.f);

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

	//variable to transform geometry
	rotateAngle = 0;
	

	//Initialize camera settings
	camera.Init(Vector3(40, 40, 40), Vector3(0, 0, 0), Vector3(0, 1, 0));

	Mtx44 projection;
	projection.SetToPerspective(45.f, 4.f / 3.f, 0.1f, 1000.f);
	projectionStack.LoadMatrix(projection);

	// Init VBO
	for (int i = 0; i < NUM_GEOMETRY; ++i)
	{
		meshList[i] = nullptr;
	}
	meshList[GEO_AXES] = MeshBuilder::GenerateAxes("reference", 1000, 1000, 1000);

	meshList[GEO_QUAD] = MeshBuilder::GenerateQuad("quad", Color(0.37647, 0.37647, 0.37647), 1.f);
	meshList[GEO_QUAD]->material.kAmbient.Set(0.5f, 0.5f, 0.5f);
	meshList[GEO_QUAD]->material.kDiffuse.Set(0.5f, 0.5f, 0.5f);
	meshList[GEO_QUAD]->material.kSpecular.Set(0.5f, 0.5f, 0.5f);
	meshList[GEO_QUAD]->material.kShininess = 1.f;

	meshList[GEO_RED_CUBE] = MeshBuilder::GenerateCube("redCube", Color(0.79215, 0.38823, 0.34510), 1.f);
	meshList[GEO_RED_CUBE]->material.kAmbient.Set(0.5f, 0.5f, 0.5f);
	meshList[GEO_RED_CUBE]->material.kDiffuse.Set(0.5f, 0.5f, 0.5f);
	meshList[GEO_RED_CUBE]->material.kSpecular.Set(0.5f, 0.5f, 0.5f);
	meshList[GEO_RED_CUBE]->material.kShininess = 1.f;

	meshList[GEO_YELLOW_CUBE] = MeshBuilder::GenerateCube("yellowCube", Color(1, 0.77647, 0.36078), 1.f);
	meshList[GEO_YELLOW_CUBE]->material.kAmbient.Set(0.5f, 0.5f, 0.5f);
	meshList[GEO_YELLOW_CUBE]->material.kDiffuse.Set(0.5f, 0.5f, 0.5f);
	meshList[GEO_YELLOW_CUBE]->material.kSpecular.Set(0.5f, 0.5f, 0.5f);
	meshList[GEO_YELLOW_CUBE]->material.kShininess = 1.f;

	meshList[GEO_RED_CYLINDER] = MeshBuilder::GenerateCylinder("redCylinder", Color(0.79215, 0.38823, 0.34510), 36, 10, 10);
	meshList[GEO_RED_CYLINDER]->material.kAmbient.Set(0.5f, 0.5f, 0.5f);
	meshList[GEO_RED_CYLINDER]->material.kDiffuse.Set(0.5f, 0.5f, 0.5f);
	meshList[GEO_RED_CYLINDER]->material.kSpecular.Set(0.5f, 0.5f, 0.5f);
	meshList[GEO_RED_CYLINDER]->material.kShininess = 1.f;

	meshList[GEO_YELLOW_CONE] = MeshBuilder::GenerateCone("yellowCone", Color(0.92157, 0.80783, 0.52157), 36, 1, 1);
	meshList[GEO_YELLOW_CONE]->material.kAmbient.Set(0.5f, 0.5f, 0.5f);
	meshList[GEO_YELLOW_CONE]->material.kDiffuse.Set(1.f, 1.f, 1.f);
	meshList[GEO_YELLOW_CONE]->material.kSpecular.Set(0.5f, 0.5f, 0.5f);
	meshList[GEO_YELLOW_CONE]->material.kShininess = 1.f;

	meshList[GEO_RED_PYRAMID] = MeshBuilder::GenerateCone("redPyramid", Color(0.79215, 0.38823, 0.34510), 4, 1, 1);
	meshList[GEO_RED_PYRAMID]->material.kAmbient.Set(0.5f, 0.5f, 0.5f);
	meshList[GEO_RED_PYRAMID]->material.kDiffuse.Set(0.5f, 0.5f, 0.5f);
	meshList[GEO_RED_PYRAMID]->material.kSpecular.Set(0.5f, 0.5f, 0.5f);
	meshList[GEO_RED_PYRAMID]->material.kShininess = 1.f;

	meshList[GEO_SPHERE] = MeshBuilder::GenerateSphere("LEGsphere", Color(0.35294, 0.54117, 0.48627), 10, 36, 1);
	meshList[GEO_SPHERE]->material.kAmbient.Set(0.5f, 0.5f, 0.5f);
	meshList[GEO_SPHERE]->material.kDiffuse.Set(1.f, 1.f, 1.f);
	meshList[GEO_SPHERE]->material.kSpecular.Set(0.5f, 0.5f, 0.5f);
	meshList[GEO_SPHERE]->material.kShininess = 1.f;

	meshList[GEO_YELLOW_SPHERE] = MeshBuilder::GenerateSphere("yellowSphere", Color(0.92157, 0.80783, 0.52157), 10, 36, 1);
	meshList[GEO_YELLOW_SPHERE]->material.kAmbient.Set(0.5f, 0.5f, 0.5f);
	meshList[GEO_YELLOW_SPHERE]->material.kDiffuse.Set(1.f, 1.f, 1.f);
	meshList[GEO_YELLOW_SPHERE]->material.kSpecular.Set(0.5f, 0.5f, 0.5f);
	meshList[GEO_YELLOW_SPHERE]->material.kShininess = 1.f;

	meshList[GEO_HEMISPHERE] = MeshBuilder::GenerateHemisphere("yellowHemisphere", Color(0.92157, 0.80783, 0.52157), 10, 20, 1);
	meshList[GEO_HEMISPHERE]->material.kAmbient.Set(0.5f, 0.5f, 0.5f);
	meshList[GEO_HEMISPHERE]->material.kDiffuse.Set(1.f, 1.f, 1.f);
	meshList[GEO_HEMISPHERE]->material.kSpecular.Set(0.5f, 0.5f, 0.5f);
	meshList[GEO_HEMISPHERE]->material.kShininess = 1.f;

	meshList[GEO_WHITE_HEMISPHERE] = MeshBuilder::GenerateHemisphere("whiteHemisphere", Color(1, 1, 1), 10, 20, 1);
	meshList[GEO_WHITE_HEMISPHERE]->material.kAmbient.Set(0.5f, 0.5f, 0.5f);
	meshList[GEO_WHITE_HEMISPHERE]->material.kDiffuse.Set(0.5f, 0.5f, 0.5f);
	meshList[GEO_WHITE_HEMISPHERE]->material.kSpecular.Set(1.f, 1.f, 1.f);
	meshList[GEO_WHITE_HEMISPHERE]->material.kShininess = 1.f;

	meshList[GEO_BLUE_HEMISPHERE] = MeshBuilder::GenerateHemisphere("blueHemisphere", Color(0.44314, 0.74902, 0.67843), 10, 20, 1);
	meshList[GEO_BLUE_HEMISPHERE]->material.kAmbient.Set(0.5f, 0.5f, 0.5f);
	meshList[GEO_BLUE_HEMISPHERE]->material.kDiffuse.Set(0.5f, 0.5f, 0.5f);
	meshList[GEO_BLUE_HEMISPHERE]->material.kSpecular.Set(0.5f, 0.5f, 0.5f);
	meshList[GEO_BLUE_HEMISPHERE]->material.kShininess = 1.f;

	meshList[GEO_BLACK_HEMISPHERE] = MeshBuilder::GenerateHemisphere("blackHemisphere", Color(0, 0, 0), 10, 20, 1);
	meshList[GEO_BLACK_HEMISPHERE]->material.kAmbient.Set(0.5f, 0.5f, 0.5f);
	meshList[GEO_BLACK_HEMISPHERE]->material.kDiffuse.Set(0.5f, 0.5f, 0.5f);
	meshList[GEO_BLACK_HEMISPHERE]->material.kSpecular.Set(0.5f, 0.5f, 0.5f);
	meshList[GEO_BLACK_HEMISPHERE]->material.kShininess = 1.f;

	meshList[GEO_RED_TORUS] = MeshBuilder::GenerateTorus2("redTorus", Color(0.79215, 0.38823, 0.34510), 20, 20, 2, 1);
	meshList[GEO_RED_TORUS]->material.kAmbient.Set(0.5f, 0.5f, 0.5f);
	meshList[GEO_RED_TORUS]->material.kDiffuse.Set(0.5f, 0.5f, 0.5f);
	meshList[GEO_RED_TORUS]->material.kSpecular.Set(0.5f, 0.5f, 0.5f);
	meshList[GEO_RED_TORUS]->material.kShininess = 1.f;

	meshList[GEO_BLACK_CUBE] = MeshBuilder::GenerateCube("BlackCube", Color(0, 0, 0), 1);
	meshList[GEO_BLACK_CUBE]->material.kAmbient.Set(0.5f, 0.5f, 0.5f);
	meshList[GEO_BLACK_CUBE]->material.kDiffuse.Set(0.5f, 0.5f, 0.5f);
	meshList[GEO_BLACK_CUBE]->material.kSpecular.Set(0.5f, 0.5f, 0.5f);
	meshList[GEO_BLACK_CUBE]->material.kShininess = 0.f;

	meshList[GEO_L_CONNECTOR_TORUS] = MeshBuilder::GenerateTorus2("noseRing", Color(0.55686, 0.49019, 0.42353), 20, 20, 2, 1);
	meshList[GEO_L_CONNECTOR_TORUS]->material.kAmbient.Set(0.5f, 0.5f, 0.5f);
	meshList[GEO_L_CONNECTOR_TORUS]->material.kDiffuse.Set(0.5f, 0.5f, 0.5f);
	meshList[GEO_L_CONNECTOR_TORUS]->material.kSpecular.Set(0.5f, 0.5f, 0.5f);
	meshList[GEO_L_CONNECTOR_TORUS]->material.kShininess = 1.f;

	meshList[GEO_LIGHTBALL] = MeshBuilder::GenerateSphere("lightball", Color(1, 1, 1), 10, 20);

	walking = false;
	walkTemp = 0;

	swayTemp = 0;
	lanternAngle = 0;

	blinking = true;
	eyeLidAngle = -120;
	blinkTemp = 0;
	blinkTemp1 = 0;
	eyebrowY = 1.2;

	bodyX = 0;
	bodyY= 6.25;
	bodyZ = 0;

	noseAngle = 100;
	noseAngleX = 0;

	lLegAngle = 0;

	rLegAngle = -5;


	lArmAngle = 30;
	rArmAngle = 30;

	timer = 0;
	timerTemp = 0;

	direction = "";
}

void Assignment1::Update(double dt)
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

	//Reset model & animation
	if (Application::IsKeyPressed('V'))
	{
		walking = false;
		walkTemp = 0;

		swayTemp = 0;
		lanternAngle = 0;

		blinking = true;
		eyeLidAngle = -120;
		blinkTemp = 0;
		blinkTemp1 = 0;
		eyebrowY = 1.2;

		bodyX = 0;
		bodyY = 6.25;
		bodyZ = 0;

		noseAngle = 100;
		noseAngleX = 0;

		lLegAngle = 0;
		rLegAngle = -5;

		lArmAngle = 30;
		rArmAngle = 30;

		timer = 0;
		timerTemp = 0;

		direction = "";

		lanternX = 0;
		lanternY = 7.5;
		lanternZ = 6.8;
	}

	//Lantern light update
	light[1].position.Set(camera.position.x, camera.position.y, camera.position.z);

	//Blinking
	if (blinking)
	{
		if (blinkTemp1 == 3)
		{
			blinking = false;
			blinkTemp1 = 0;
		}
		else if (blinkTemp == 0)
		{
			eyeLidAngle -= 2;
			eyebrowY += 0.00125;
			if (eyeLidAngle < -120)
			{
				blinkTemp = 1;
				blinkTemp1++;
			}
		}
		else if (blinkTemp == 1)
		{
			eyeLidAngle += 2;
			eyebrowY -= 0.00125;
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
		lanternAngle += 0.5;
		lanternX -= 0.015;
		noseAngleX -= 0.075;
		if (lanternAngle >= 20)
		{
			swayTemp = 1;
		}
	}
	else if(swayTemp == 1)
	{
		lanternAngle -= 0.5;
		lanternX += 0.015;
		noseAngleX += 0.075;
		if (lanternAngle <= -20)
		{
			swayTemp = 0;
		}
	}

	//Walking
	if (walking)
	{
		if (walkTemp == 0)
		{
			lLegAngle -= 1;
			rLegAngle += 1;
			rArmAngle += 0.5;
			lArmAngle -= 0.5;
			noseAngle -= 0.125;
			if (lLegAngle <= -30)
			{
				walkTemp = 1;
			}
		}
		else if (walkTemp == 1)
		{
			lLegAngle += 1;
			rLegAngle -= 1;
			rArmAngle -= 0.5;
			lArmAngle += 0.5;
			noseAngle += 0.125;
			if (lLegAngle >= 30)
			{
				walkTemp = 0;
			}
		}
		if (direction == "forward")
		{
			bodyZ += 0.05;
			lanternZ += 0.05;
		}
		else if (direction == "backward")
		{
			bodyZ -= 0.05;
			lanternZ -= 0.05;
		}
	}

	timer += 0.016667;

	//Animation
	if (timerTemp == 0)
	{
		if (timer > 5)
		{
			walking = true;
			direction = "forward";
			timerTemp++;
		}
	}
	else if (timerTemp == 1)
	{
		if (timer > 10)
		{
			walking = false;
			timerTemp++;
		}
	}
	else if (timerTemp == 2)
	{
		if (timer > 15)
		{
			walking = true;
			direction = "backward";
			timerTemp++;
		}
	}
	else if (timerTemp == 3)
	{
		if (timer > 20)
		{
			walking = false;
			timerTemp++;
		}
	}
	else if (timerTemp == 4)
	{

	}

	if (int(timer) % 5 == 0)
		blinking = true;

	camera.Update(dt);
}

void Assignment1::Render()
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

	modelStack.LoadIdentity();
	
	RenderMesh(meshList[GEO_AXES], false);

	modelStack.PushMatrix();
	{
		modelStack.Translate(light[0].position.x, light[0].position.y, light[0].position.z);
		RenderMesh(meshList[GEO_LIGHTBALL], false);
	}
	modelStack.PopMatrix();

	/*modelStack.PushMatrix();
	{
		modelStack.Translate(light[1].position.x, light[1].position.y, light[1].position.z);
		RenderMesh(meshList[GEO_LIGHTBALL], false);
	}
	modelStack.PopMatrix();*/

	//Body
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
			RenderMesh(meshList[GEO_HEMISPHERE], true);

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
						RenderMesh(meshList[GEO_HEMISPHERE], true);
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
						RenderMesh(meshList[GEO_HEMISPHERE], true);
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
				RenderMesh(meshList[GEO_SPHERE], true);

				//Foot
				modelStack.PushMatrix();
				{
					modelStack.Scale(5, 1, 5);
					modelStack.Translate(0, -1.2, -0.2);
					modelStack.Rotate(35, 1, 0, 0);

					modelStack.Scale(0.2, 1, 0.2);
					modelStack.Scale(0.8, 0.5, 0.8);
					RenderMesh(meshList[GEO_SPHERE], true);
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
				RenderMesh(meshList[GEO_SPHERE], true);

				//Foot
				modelStack.PushMatrix();
				{
					modelStack.Scale(5, 1, 5);
					modelStack.Translate(0, -1.2, -0.2);
					modelStack.Rotate(35, 1, 0, 0);

					modelStack.Scale(0.2, 1, 0.2);
					modelStack.Scale(0.8, 0.5, 0.8);
					RenderMesh(meshList[GEO_SPHERE], true);
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
	//Body

	//1
	modelStack.PushMatrix();
	{
		modelStack.LoadIdentity();
		modelStack.Translate(0, 0, 0);
		modelStack.Rotate(-90, 1, 0, 0);
		modelStack.Scale(100, 100, 100);
		RenderMesh(meshList[GEO_QUAD], true);
	}
	modelStack.PopMatrix();
	//1
	
	//Background
	modelStack.PushMatrix();
	{
		modelStack.LoadIdentity();

		modelStack.Translate(-15, 5, -15);
		modelStack.Rotate(45, 0, 1, 0);
		
		modelStack.Scale(20, 20, 20);
		RenderMesh(meshList[GEO_RED_PYRAMID], true);

		modelStack.Scale(1.5, 1.5, 1.5);
		modelStack.Translate(1, 0, 1); 
		RenderMesh(meshList[GEO_RED_PYRAMID], true);

	}
	modelStack.PopMatrix();
	//Background
	
}

void Assignment1::Exit()
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

void Assignment1::RenderMesh(Mesh* mesh, bool enableLight)
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
	mesh->Render();
}
