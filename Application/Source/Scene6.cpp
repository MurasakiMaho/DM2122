#include "Scene6.h"
#include "GL\glew.h"

#include "shader.hpp"
#include "Mtx44.h"

#include "Application.h"
#include "MeshBuilder.h"

Scene6::Scene6()
{
}

Scene6::~Scene6()
{
}

void Scene6::Init()
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
	m_programID = LoadShaders( "Shader//TransformVertexShader.vertexshader", "Shader//SimpleFragmentShader.fragmentshader" );
	// Get a handle for our "MVP" uniform
	m_parameters[U_MVP] = glGetUniformLocation(m_programID, "MVP");
	// Use our shader
	glUseProgram(m_programID);
	
	//variable to rotate geometry
	rotateAngle = 0;

	//Initialize camera settings
	camera.Init(Vector3(40, 30, 30), Vector3(0, 0, 0), Vector3(0, 1, 0));

	Mtx44 projection;
	projection.SetToPerspective(45.f, 4.f / 3.f, 0.1f, 1000.f);
	projectionStack.LoadMatrix(projection);

	// Init VBO
	for (int i = 0; i < NUM_GEOMETRY; ++i)
	{
		meshList[i] = nullptr;
	}
	meshList[GEO_AXES] = MeshBuilder::GenerateAxes("reference", 1000, 1000, 1000);
	meshList[GEO_QUAD] = MeshBuilder::GenerateQuad("quad", Color(1, 1, 0), 1.f);
	meshList[GEO_CUBE] = MeshBuilder::GenerateCube("cube", Color(1, 0, 0), 1.f);
	meshList[GEO_CIRCLE] = MeshBuilder::GenerateCircle("circle", Color(0, 1, 1), 20, 1.f);
	meshList[GEO_RING] = MeshBuilder::GenerateRing("ring", Color(0, 1, 1), 20, 1.f);
	meshList[GEO_SPHERE] = MeshBuilder::GenerateSphere("sphere", Color(0, 1, 1), 10, 20);
}

void Scene6::Update(double dt)
{
	if(Application::IsKeyPressed('1')) //enable back face culling
		glEnable(GL_CULL_FACE);
	if(Application::IsKeyPressed('2')) //disable back face culling
		glDisable(GL_CULL_FACE);
	if(Application::IsKeyPressed('3'))
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL); //default fill mode
	if(Application::IsKeyPressed('4'))
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); //wireframe mode

	rotateAngle += (float)(10 * dt);

	camera.Update(dt);
}

void Scene6::Render()
{
	// Render VBO here
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	//Temp variables
	Mtx44 MVP;

	viewStack.LoadIdentity();
	viewStack.LookAt(
		camera.position.x, camera.position.y, camera.position.z,
		camera.target.x, camera.target.y, camera.target.z,
		camera.up.x, camera.up.y, camera.up.z);
	modelStack.LoadIdentity();
	MVP = projectionStack.Top() * viewStack.Top() * modelStack.Top();

	glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]);
	meshList[GEO_AXES]->Render();

	//1 sun
	modelStack.PushMatrix();
	{
		modelStack.LoadIdentity();
		modelStack.Translate(3, 2, 0);
		modelStack.Rotate(0, 0, 0, 1);
		modelStack.Scale(2, 2, 2);
		MVP = projectionStack.Top() * viewStack.Top() * modelStack.Top();
		glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]);
		meshList[GEO_SPHERE]->Render();


		//2 planet
		{
			modelStack.PushMatrix();
			modelStack.Rotate(-rotateAngle, 0, 0, 1);
			modelStack.Translate(3, 0, 0);
			modelStack.Scale(0.5, 0.5, 0.5);
			MVP = projectionStack.Top() * viewStack.Top() * modelStack.Top();
			glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]);
			meshList[GEO_SPHERE]->Render();

			//3 moon
			modelStack.PushMatrix();
			{
				modelStack.Rotate(4 * rotateAngle, 0, 0, 1);
				modelStack.Translate(2, 0, 0);
				modelStack.Scale(0.5, 0.5, 0.5);
				MVP = projectionStack.Top() * viewStack.Top() * modelStack.Top();
				glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]);
				meshList[GEO_SPHERE]->Render();
			}
			modelStack.PopMatrix();
			//3
		}
		modelStack.PopMatrix();
		//2

		//2 second planet
		modelStack.PushMatrix();
		{
			modelStack.Rotate(-rotateAngle + 15, 0, 0, 1);
			modelStack.Translate(-5, 0, 0);
			modelStack.Scale(0.75, 0.75, 0.75);
			MVP = projectionStack.Top() * viewStack.Top() * modelStack.Top();
			glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]);
			meshList[GEO_SPHERE]->Render();

			//3 ring
			modelStack.PushMatrix();
			{
				modelStack.Rotate(rotateAngle, 90, 0, 0);
				modelStack.Translate(0, 0, 0);
				modelStack.Scale(1.5, 1.5, 1.5);
				MVP = projectionStack.Top() * viewStack.Top() * modelStack.Top();
				glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]);
				meshList[GEO_CIRCLE]->Render();
			}
			modelStack.PopMatrix();
			//3
		}
		modelStack.PopMatrix();
		//2
	}

	modelStack.PopMatrix();
	//1

}

void Scene6::Exit()
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
