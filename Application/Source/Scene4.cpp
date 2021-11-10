#include "Scene4.h"
#include "GL\glew.h"

#include "shader.hpp"
#include "Application.h"
#include "MeshBuilder.h"


Scene4::Scene4()
{
}

Scene4::~Scene4()
{
}

void Scene4::Init()
{
	rotateAngle = -20;
	translateX = 1;
	scaleAll = 1;

	//Camera
	camera.Init(Vector3(4, 3, 3), Vector3(0, 0, 0), Vector3(0, 1, 0));

	// Init VBO here
	// Set BG colour to dark blue
	glClearColor(0.0f, 0.0f, 0.4f, 0.0f);
	// Enable depth test
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);

	//Generate a default VAO
	glGenVertexArrays(1, &m_vertexArrayID);
	glBindVertexArray(m_vertexArrayID);

	meshList[GEO_AXES] = MeshBuilder::GenerateAxes("reference",1000, 1000, 1000);
	meshList[GEO_QUAD] = MeshBuilder::GenerateQuad("quad", 1, 1);
	meshList[GEO_CUBE] = MeshBuilder::GenerateCube("cube", 1, 1,1);


	// Load vertex and fragment shaders
	m_programID = LoadShaders("Shader//TransformVertexShader.vertexshader", "Shader//SimpleFragmentShader.fragmentshader");
	//Use our shader
	glUseProgram(m_programID);

	//Get a handle for our "MVP" uniform
	m_parameters[U_MVP] = glGetUniformLocation(m_programID, "MVP");
	/*m_parameters[U_MVP_1] = glGetUniformLocation(m_programID, "MVP");
	m_parameters[U_MVP_2] = glGetUniformLocation(m_programID, "MVP");*/
}

void Scene4::Update(double dt)
{
	rotateAngle += (float)(10 * dt);
	translateX += (float)(5 * dt);
	scaleAll += (float)(2 * dt);

	if (Application::IsKeyPressed('1'))
		glEnable(GL_CULL_FACE); 
	if (Application::IsKeyPressed('2'))
		glDisable(GL_CULL_FACE);
	if (Application::IsKeyPressed('3'))
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL); //default fill mode
	if (Application::IsKeyPressed('4'))
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); //wireframe mode

	camera.Update(dt);
}

void Scene4::Render()
{

	// Clear buffer colour every frame
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	Mtx44 translate, rotate, scale;
	Mtx44 model;
	Mtx44 view;
	Mtx44 projection;
	Mtx44 MVP;

	translate.SetToIdentity();
	rotate.SetToIdentity();
	scale.SetToIdentity();
	model.SetToIdentity();

	view.SetToLookAt(
		camera.position.x,	 camera.position.y,  camera.position.z, 
		camera.target.x,	 camera.target.y,    camera.target.y,
		camera.up.x,		 camera.up.y,		 camera.up.z
	);

	projection.SetToPerspective(45.0f, 4.0f / 3.0f, 0.1f, 1000.0f); //FOV, Aspect Ratio, Near Plane, Far Plane

	scale.SetToScale(1, 1, 1);
	rotate.SetToRotation(0, 0, 0, 1);
	translate.SetToTranslation(0, 0, 0);
	model.SetToIdentity();
	model = translate * rotate * scale;
	MVP = projection * view * model;
	glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]);

	meshList[GEO_AXES]->Render();

	translate.SetToIdentity();
	rotate.SetToIdentity();
	scale.SetToIdentity();
	model.SetToIdentity();

	scale.SetToScale(1, 1, 1);
	rotate.SetToRotation(rotateAngle, 0, 0, 1);
	translate.SetToTranslation(0, 0, 0);
	model.SetToIdentity();
	model = translate * rotate * scale;
	MVP = projection * view * model;
	glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]);
	meshList[GEO_QUAD]->Render();
	//meshList[GEO_CUBE]->Render();

	translate.SetToIdentity();
	rotate.SetToIdentity();
	scale.SetToIdentity();
	model.SetToIdentity();

	
}

void Scene4::Exit()
{
	glDeleteVertexArrays(1, &m_vertexArrayID);

	glDeleteProgram(m_programID);
}
