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
	m_parameters[U_NUMLIGHTS] = glGetUniformLocation(m_programID, "numLights");
	glUseProgram(m_programID);
	
	light[0].type = Light::LIGHT_POINT;
	light[0].position.Set(0, 20, 0);
	light[0].color.Set(1, 1, 1);
	light[0].power = 1;
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

	//variable to rotate geometry
	rotateAngle = 0;

	//Initialize camera settings
	camera.Init(Vector3(20, 20, 20), Vector3(0, 0, 0), Vector3(0, 1, 0));

	Mtx44 projection;
	projection.SetToPerspective(45.f, 4.f / 3.f, 0.1f, 1000.f);
	projectionStack.LoadMatrix(projection);

	// Init VBO
	for (int i = 0; i < NUM_GEOMETRY; ++i)
	{
		meshList[i] = nullptr;
	}
	meshList[GEO_AXES] = MeshBuilder::GenerateAxes("reference", 1000, 1000, 1000);

	meshList[GEO_QUAD] = MeshBuilder::GenerateQuad("quad", Color(0, 1, 1), 1.f);
	meshList[GEO_QUAD]->material.kAmbient.Set(0.5f, 0.5f, 0.5f);
	meshList[GEO_QUAD]->material.kDiffuse.Set(0.5f, 0.5f, 0.5f);
	meshList[GEO_QUAD]->material.kSpecular.Set(0.5f, 0.5f, 0.5f);
	meshList[GEO_QUAD]->material.kShininess = 1.f;

	meshList[GEO_CUBE] = MeshBuilder::GenerateCube("cube", Color(1, 0, 0), 1.f);
	meshList[GEO_CUBE]->material.kAmbient.Set(0.5f, 0.5f, 0.5f);
	meshList[GEO_CUBE]->material.kDiffuse.Set(0.5f, 0.5f, 0.5f);
	meshList[GEO_CUBE]->material.kSpecular.Set(0.5f, 0.5f, 0.5f);
	meshList[GEO_CUBE]->material.kShininess = 1.f;

	meshList[GEO_CIRCLE] = MeshBuilder::GenerateCircle("circle", Color(0, 1, 1), 20, 1.f);

	meshList[GEO_WHITE_CIRCLE] = MeshBuilder::GenerateCircle("whiteCircle", Color(1, 1, 1), 20, 1.f);
	meshList[GEO_WHITE_CIRCLE]->material.kAmbient.Set(0.5f, 0.5f, 0.5f);
	meshList[GEO_WHITE_CIRCLE]->material.kDiffuse.Set(0.5f, 0.5f, 0.5f);
	meshList[GEO_WHITE_CIRCLE]->material.kSpecular.Set(0.5f, 0.5f, 0.5f);
	meshList[GEO_WHITE_CIRCLE]->material.kShininess = 1.f;

	meshList[GEO_RING] = MeshBuilder::GenerateRing("ring", Color(0, 1, 1), 20, 1.f);

	meshList[GEO_CYLINDER] = MeshBuilder::GenerateCylinder("cylinder", Color(1, 0, 0), 36, 10, 10);
	meshList[GEO_CYLINDER]->material.kAmbient.Set(0.5f, 0.5f, 0.5f);
	meshList[GEO_CYLINDER]->material.kDiffuse.Set(0.5f, 0.5f, 0.5f);
	meshList[GEO_CYLINDER]->material.kSpecular.Set(0.5f, 0.5f, 0.5f);
	meshList[GEO_CYLINDER]->material.kShininess = 1.f;

	meshList[GEO_BLUE_CYLINDER] = MeshBuilder::GenerateCylinder("blueCylinder", Color(0.22353, 0.49412, 0.82745), 36, 1, 1);
	meshList[GEO_BLUE_CYLINDER]->material.kAmbient.Set(0.5f, 0.5f, 0.5f);
	meshList[GEO_BLUE_CYLINDER]->material.kDiffuse.Set(0.5f, 0.5f, 0.5f);
	meshList[GEO_BLUE_CYLINDER]->material.kSpecular.Set(0.5f, 0.5f, 0.5f);
	meshList[GEO_BLUE_CYLINDER]->material.kShininess = 1.f;

	meshList[GEO_CONE] = MeshBuilder::GenerateCone("cone", Color(1, 0, 0), 36, 1, 1);
	meshList[GEO_CONE]->material.kAmbient.Set(0.5f, 0.5f, 0.5f);
	meshList[GEO_CONE]->material.kDiffuse.Set(0.5f, 0.5f, 0.5f);
	meshList[GEO_CONE]->material.kSpecular.Set(0.5f, 0.5f, 0.5f);
	meshList[GEO_CONE]->material.kShininess = 1.f;

	meshList[GEO_YELLOW_CONE] = MeshBuilder::GenerateCone("yellowCone", Color(0.92157, 0.80783, 0.52157), 36, 1, 1);
	meshList[GEO_YELLOW_CONE]->material.kAmbient.Set(0.5f, 0.5f, 0.5f);
	meshList[GEO_YELLOW_CONE]->material.kDiffuse.Set(0.5f, 0.5f, 0.5f);
	meshList[GEO_YELLOW_CONE]->material.kSpecular.Set(0.5f, 0.5f, 0.5f);
	meshList[GEO_YELLOW_CONE]->material.kShininess = 1.f;

	meshList[GEO_SPHERE] = MeshBuilder::GenerateSphere("sphere", Color(1, 0, 0), 10, 36, 1);
	meshList[GEO_SPHERE]->material.kAmbient.Set(0.5f, 0.5f, 0.5f);
	meshList[GEO_SPHERE]->material.kDiffuse.Set(0.5f, 0.5f, 0.5f);
	meshList[GEO_SPHERE]->material.kSpecular.Set(0.5f, 0.5f, 0.5f);
	meshList[GEO_SPHERE]->material.kShininess = 1.f;

	meshList[GEO_BLUE_SPHERE] = MeshBuilder::GenerateSphere("blueSphere", Color(0.22353, 0.49412, 0.82745), 10, 36, 1);
	meshList[GEO_BLUE_SPHERE]->material.kAmbient.Set(0.5f, 0.5f, 0.5f);
	meshList[GEO_BLUE_SPHERE]->material.kDiffuse.Set(0.5f, 0.5f, 0.5f);
	meshList[GEO_BLUE_SPHERE]->material.kSpecular.Set(0.5f, 0.5f, 0.5f);
	meshList[GEO_BLUE_SPHERE]->material.kShininess = 1.f;

	meshList[GEO_GOLD_SPHERE] = MeshBuilder::GenerateSphere("goldSphere", Color(0.65098, 0.54118, 0.21569), 10, 36, 1);
	meshList[GEO_GOLD_SPHERE]->material.kAmbient.Set(0.5f, 0.5f, 0.5f);
	meshList[GEO_GOLD_SPHERE]->material.kDiffuse.Set(0.5f, 0.5f, 0.5f);
	meshList[GEO_GOLD_SPHERE]->material.kSpecular.Set(0.5f, 0.5f, 0.5f);
	meshList[GEO_GOLD_SPHERE]->material.kShininess = 1.f;

	meshList[GEO_YELLOW_SPHERE] = MeshBuilder::GenerateSphere("yellowSphere", Color(0.92157, 0.80783, 0.52157), 10, 36, 1);
	meshList[GEO_YELLOW_SPHERE]->material.kAmbient.Set(0.5f, 0.5f, 0.5f);
	meshList[GEO_YELLOW_SPHERE]->material.kDiffuse.Set(0.5f, 0.5f, 0.5f);
	meshList[GEO_YELLOW_SPHERE]->material.kSpecular.Set(0.5f, 0.5f, 0.5f);
	meshList[GEO_YELLOW_SPHERE]->material.kShininess = 1.f;

	meshList[GEO_HEMISPHERE] = MeshBuilder::GenerateHemisphere("hemisphere", Color(0.92157, 0.80783, 0.52157), 10, 20, 1);
	meshList[GEO_HEMISPHERE]->material.kAmbient.Set(0.5f, 0.5f, 0.5f);
	meshList[GEO_HEMISPHERE]->material.kDiffuse.Set(0.5f, 0.5f, 0.5f);
	meshList[GEO_HEMISPHERE]->material.kSpecular.Set(0.5f, 0.5f, 0.5f);
	meshList[GEO_HEMISPHERE]->material.kShininess = 1.f;

	meshList[GEO_WHITE_HEMISPHERE] = MeshBuilder::GenerateHemisphere("whiteHemisphere", Color(1, 1, 1), 10, 20, 1);
	meshList[GEO_WHITE_HEMISPHERE]->material.kAmbient.Set(0.5f, 0.5f, 0.5f);
	meshList[GEO_WHITE_HEMISPHERE]->material.kDiffuse.Set(0.5f, 0.5f, 0.5f);
	meshList[GEO_WHITE_HEMISPHERE]->material.kSpecular.Set(0.5f, 0.5f, 0.5f);
	meshList[GEO_WHITE_HEMISPHERE]->material.kShininess = 1.f;

	meshList[GEO_BLUE_HEMISPHERE] = MeshBuilder::GenerateHemisphere("blueHemisphere", Color(0.44314, 0.74902, 0.67843), 10, 20, 1);
	meshList[GEO_BLUE_HEMISPHERE]->material.kAmbient.Set(0.5f, 0.5f, 0.5f);
	meshList[GEO_BLUE_HEMISPHERE]->material.kDiffuse.Set(0.5f, 0.5f, 0.5f);
	meshList[GEO_BLUE_HEMISPHERE]->material.kSpecular.Set(0.5f, 0.5f, 0.5f);
	meshList[GEO_BLUE_HEMISPHERE]->material.kShininess = 1.f;

	meshList[GEO_BLACK_HEMISPHERE] = MeshBuilder::GenerateHemisphere("blueHemisphere", Color(0, 0, 0), 10, 20, 1);
	meshList[GEO_BLACK_HEMISPHERE]->material.kAmbient.Set(0.5f, 0.5f, 0.5f);
	meshList[GEO_BLACK_HEMISPHERE]->material.kDiffuse.Set(0.5f, 0.5f, 0.5f);
	meshList[GEO_BLACK_HEMISPHERE]->material.kSpecular.Set(0.5f, 0.5f, 0.5f);
	meshList[GEO_BLACK_HEMISPHERE]->material.kShininess = 1.f;

	meshList[GEO_RED_TORUS] = MeshBuilder::GenerateTorus2("redTorus", Color(0.73725, 0.27059, 0.25490), 20, 20, 2, 1);
	meshList[GEO_RED_TORUS]->material.kAmbient.Set(0.5f, 0.5f, 0.5f);
	meshList[GEO_RED_TORUS]->material.kDiffuse.Set(0.5f, 0.5f, 0.5f);
	meshList[GEO_RED_TORUS]->material.kSpecular.Set(0.5f, 0.5f, 0.5f);
	meshList[GEO_RED_TORUS]->material.kShininess = 1.f;

	meshList[GEO_WHITE_TORUS] = MeshBuilder::GenerateTorus2("whiteTorus", Color(0.89804, 0.89804, 0.89804), 20, 20, 2, 1);
	meshList[GEO_WHITE_TORUS]->material.kAmbient.Set(0.5f, 0.5f, 0.5f);
	meshList[GEO_WHITE_TORUS]->material.kDiffuse.Set(0.5f, 0.5f, 0.5f);
	meshList[GEO_WHITE_TORUS]->material.kSpecular.Set(0.5f, 0.5f, 0.5f);
	meshList[GEO_WHITE_TORUS]->material.kShininess = 1.f;

	meshList[GEO_QUARTERTORUS] = MeshBuilder::GenerateQuarterTorus2("quartertorus", Color(1, 0, 0), 20, 20, 2, 1);
	meshList[GEO_QUARTERTORUS]->material.kAmbient.Set(0.5f, 0.5f, 0.5f);
	meshList[GEO_QUARTERTORUS]->material.kDiffuse.Set(0.5f, 0.5f, 0.5f);
	meshList[GEO_QUARTERTORUS]->material.kSpecular.Set(0.5f, 0.5f, 0.5f);
	meshList[GEO_QUARTERTORUS]->material.kShininess = 1.f;

	meshList[GEO_LIGHTBALL] = MeshBuilder::GenerateSphere("lightball", Color(1, 1, 1), 10, 20);

	
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


	rotateAngle += (float)(10 * dt);

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


	//Body incomplete

	//Body
	modelStack.PushMatrix();
	{
		modelStack.Translate(0, 5, 0);
		modelStack.Rotate(0, 0, 0, 1);
		modelStack.Scale(4, 3, 4);
		RenderMesh(meshList[GEO_BLUE_HEMISPHERE], true);


		modelStack.Scale(0.25, 0.33333, 0.25);
		modelStack.Translate(0, 0, 0);
		modelStack.Rotate(180, 0, 0, 1);
		modelStack.Scale(4, 4, 4);
		RenderMesh(meshList[GEO_BLUE_HEMISPHERE], true);

		//Head
		modelStack.PushMatrix();
		{
			modelStack.Rotate(-180, 0, 0, 1);
			modelStack.Scale(0.25, 0.25, 0.25);
			modelStack.Translate(0, 1, 0);
			modelStack.Rotate(0, 0, 0, 1);
			modelStack.Scale(3.5, 6, 3.5);
			RenderMesh(meshList[GEO_HEMISPHERE], true);

			//Nose
			modelStack.PushMatrix();
			{
				modelStack.Scale(0.28571, 0.16667, 0.28571);
				modelStack.Translate(0, 4.3, 2.4);
				modelStack.Rotate(100, 100, 0, 1);
				modelStack.Scale(1.5, 4, 1.5);
				RenderMesh(meshList[GEO_YELLOW_SPHERE], true);

				modelStack.PushMatrix();
				{
					modelStack.Rotate(0, 0, 0, 1);
					modelStack.Translate(0, 1.1, 0);
					modelStack.Scale(0.8, 1, 0.8);
					RenderMesh(meshList[GEO_YELLOW_CONE], true);

					//Lanturn
					/*modelStack.PushMatrix();
					{
						modelStack.Rotate(0, 0, 0, 1);
						modelStack.Translate(0, 1.1, 0);
						modelStack.Scale(0.8, 1, 0.8);
						RenderMesh(meshList[GEO_YELLOW_CONE], true);
					}
					modelStack.PopMatrix();*/
					//Lanturn
				}
				modelStack.PopMatrix();
			}
			modelStack.PopMatrix();
			//Nose

			//Eyes
			modelStack.PushMatrix();
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
						modelStack.Rotate(0, 90, 90, 1);
						modelStack.Rotate(45, 45, 0, 1);
						modelStack.Translate(0, 0.6, 0);
						modelStack.Scale(0.5, 0.5, 0.5);
						RenderMesh(meshList[GEO_BLACK_HEMISPHERE], true);
					}
					modelStack.PopMatrix();
					//Pupil
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
				}
				modelStack.PopMatrix();
				//Right
			}
			modelStack.PopMatrix();
			//Eyes

		}
		modelStack.PopMatrix();
		//Head

		////1
		//modelStack.PushMatrix();
		//{
		//	modelStack.LoadIdentity();
		//	modelStack.Translate(0, 0, 0);
		//	modelStack.Rotate(-90, 1, 0, 0);
		//	modelStack.Scale(100, 100, 100);
		//	RenderMesh(meshList[GEO_QUAD], true);
		//}
		//modelStack.PopMatrix();
		////1

	}
	modelStack.PopMatrix();
	//Body

	
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
