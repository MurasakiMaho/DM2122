#include "Scene1.h"
#include "GL\glew.h"

#include "shader.hpp"


Scene1::Scene1()
{
}

Scene1::~Scene1()
{
}

void Scene1::Init()
{
	// Init VBO here

	// Set BG colour to dark blue
	glClearColor(0.0f, 0.0f, 0.4f, 0.0f);

	//Generate a default VAO
	glGenVertexArrays(1, &m_vertexArrayID);
	glBindVertexArray(m_vertexArrayID);

	//Generate buffers
	glGenBuffers(NUM_GEOMETRY, &m_vertexBuffer[0]);
	glGenBuffers(NUM_GEOMETRY, &m_colorBuffer[0]);


	// Set current active buffer
	glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer[GEO_TRIANGLE_1]);
	
	// An array of 3 vectors which represents 3 vertices
	static const GLfloat vertex_buffer_data[] =
	{	
		0, 1, 0,
		0, -1, 0,
		1, 0, 0
	};

	// Transfer vertices to OpenGL
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertex_buffer_data), vertex_buffer_data, GL_STATIC_DRAW);

	glBindBuffer(GL_ARRAY_BUFFER, m_colorBuffer[GEO_TRIANGLE_1]);

	// An array of 3 vectors which represents the colours of the 3 vertices
	static const GLfloat color_buffer_data[] = 
	{
		0.0f, 0.0f, 0.0f,	//colour of vertex 1
		0.0f, 0.0f, 0.0f,	//colour of vertex 2
		1, 0.0f, 0.0f	//colour of vertex 3
	};

	glBufferData(GL_ARRAY_BUFFER, sizeof(color_buffer_data), color_buffer_data, GL_STATIC_DRAW);

	// 2nd

	// Set current active buffer
	glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer[GEO_TRIANGLE_2]);
	

	static const GLfloat vertex_buffer_data_2[] =
	{
		-1, 0, -0.5,
		0, 1, -0.5,
		0, -1, -0.5
	};

	// Transfer vertices to OpenGL
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertex_buffer_data_2), vertex_buffer_data_2, GL_STATIC_DRAW);

	glBindBuffer(GL_ARRAY_BUFFER, m_colorBuffer[GEO_TRIANGLE_2]);

	static const GLfloat color_buffer_data_2[] =
	{
		1, 0.0f, 0.0f,
		0.0f, 0.0f, 0.0f,
		0.0f, 0.0f, 0.0f
	};

	glBindBuffer(GL_ARRAY_BUFFER, m_colorBuffer[GEO_TRIANGLE_2]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(color_buffer_data_2), color_buffer_data_2, GL_STATIC_DRAW);

	// 3rd
	
	glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer[GEO_TRIANGLE_3]);
	
	static const GLfloat vertex_buffer_data_3[] =
	{
		-1, 1, 0,
		-0.3333, 0.6666, 0,
		-0.6666, 0.3333, 0
	};
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertex_buffer_data), vertex_buffer_data_3, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, m_colorBuffer[GEO_TRIANGLE_3]);

	static const GLfloat color_buffer_data_3[] =
	{
		1.000, 0.388, 0.278,	//colour of vertex 1
		0.0f, 0.0f, 0.0f,	//colour of vertex 2
		0.0f, 0.0f, 0.0f	//colour of vertex 3
	};
	glBufferData(GL_ARRAY_BUFFER, sizeof(color_buffer_data), color_buffer_data_3, GL_STATIC_DRAW);

	// 4th
	glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer[GEO_TRIANGLE_4]);

	static const GLfloat vertex_buffer_data_4[] =
	{
		1, 1, 0,
		0.3333, 0.6666, 0,
		0.6666, 0.3333, 0
	};
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertex_buffer_data), vertex_buffer_data_4, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, m_colorBuffer[GEO_TRIANGLE_4]);

	static const GLfloat color_buffer_data_4[] =
	{
		1.000, 0.388, 0.278,	//colour of vertex 1
		0.0f, 0.0f, 0.0f,	//colour of vertex 2
		0.0f, 0.0f, 0.0f	//colour of vertex 3
	};
	glBufferData(GL_ARRAY_BUFFER, sizeof(color_buffer_data), color_buffer_data_4, GL_STATIC_DRAW);

	// 5th
	glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer[GEO_TRIANGLE_5]);

	static const GLfloat vertex_buffer_data_5[] =
	{
		0.288, 0.222, 0,
		0.216, 0.09, 0,
		0.116, 0.10, 0
	};
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertex_buffer_data), vertex_buffer_data_5, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, m_colorBuffer[GEO_TRIANGLE_5]);

	static const GLfloat color_buffer_data_5[] =
	{
		0.580, 0.000, 0.827,	//colour of vertex 1
		0.0f, 0.0f, 0.0f,	//colour of vertex 2
		0.0f, 0.0f, 0.0f	//colour of vertex 3
	};
	glBufferData(GL_ARRAY_BUFFER, sizeof(color_buffer_data), color_buffer_data_5, GL_STATIC_DRAW);

	// 6th
	glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer[GEO_TRIANGLE_6]);

	static const GLfloat vertex_buffer_data_6[] =
	{
		-0.288, 0.222, 0,
		-0.216, 0.09, 0,
		-0.116, 0.10, 0
	};
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertex_buffer_data), vertex_buffer_data_6, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, m_colorBuffer[GEO_TRIANGLE_6]);

	static const GLfloat color_buffer_data_6[] =
	{
		0.580, 0.000, 0.827,	//colour of vertex 1
		0.0f, 0.0f, 0.0f,	//colour of vertex 2
		0.0f, 0.0f, 0.0f	//colour of vertex 3
	};
	glBufferData(GL_ARRAY_BUFFER, sizeof(color_buffer_data), color_buffer_data_6, GL_STATIC_DRAW);

	// 7th
	glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer[GEO_TRIANGLE_7]);

	static const GLfloat vertex_buffer_data_7[] =
	{
		-0.488, -0.222, 0,
		0, -0.45, 0,
		0, -0.40, 0
	};
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertex_buffer_data), vertex_buffer_data_7, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, m_colorBuffer[GEO_TRIANGLE_7]);

	static const GLfloat color_buffer_data_7[] =
	{
		0.0f, 0.0f, 0.0f,	//colour of vertex 1
		1, 1, 1,	//colour of vertex 2
		1, 1, 1	//colour of vertex 3
	};
	glBufferData(GL_ARRAY_BUFFER, sizeof(color_buffer_data), color_buffer_data_7, GL_STATIC_DRAW);

	// 8th
	glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer[GEO_TRIANGLE_8]);

	static const GLfloat vertex_buffer_data_8[] =
	{
		0.488, -0.222, 0,
		0, -0.45, 0,
		0, -0.40, 0
	};
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertex_buffer_data), vertex_buffer_data_8, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, m_colorBuffer[GEO_TRIANGLE_8]);

	static const GLfloat color_buffer_data_8[] =
	{
		0.0f, 0.0f, 0.0f,	//colour of vertex 1
		1, 1, 1,	//colour of vertex 2
		1, 1, 1	//colour of vertex 3
	};
	glBufferData(GL_ARRAY_BUFFER, sizeof(color_buffer_data), color_buffer_data_8, GL_STATIC_DRAW);

	// Load vertex and fragment shaders
	m_programID = LoadShaders("Shader//SimpleVertexShader.vertexshader", "Shader//SimpleFragmentShader.fragmentshader");
	//Use our shader
	glUseProgram(m_programID);
}

void Scene1::Update(double dt)
{
}

void Scene1::Render()
{
	// Render VBO here

	// Clear buffer colour every frame
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER);

	
	glEnableVertexAttribArray(0);	// 1st attribute buffer : vertices
	glEnableVertexAttribArray(1);	// 2nd attribute buffer : colours

	glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer[GEO_TRIANGLE_1]);
	glVertexAttribPointer
	(
		0,			// attribute. Must match the layout in the shader. Usually0 is for vertex
		3,			// size
		GL_FLOAT,	// type
		GL_FALSE,	// normalized?
		0,			// stride
		0			// array buffer offset	
	);
	glBindBuffer(GL_ARRAY_BUFFER, m_colorBuffer[GEO_TRIANGLE_1]);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glDrawArrays(GL_TRIANGLES, 0, 3);

	glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer[GEO_TRIANGLE_2]);
	glVertexAttribPointer(0,3, GL_FLOAT, GL_FALSE, 0, 0);
	glBindBuffer(GL_ARRAY_BUFFER, m_colorBuffer[GEO_TRIANGLE_2]);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glDrawArrays(GL_TRIANGLES, 0, 3);	// Starting from vertex 0; 3 vertices = 1 triangle

	glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer[GEO_TRIANGLE_3]);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glBindBuffer(GL_ARRAY_BUFFER, m_colorBuffer[GEO_TRIANGLE_3]);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glDrawArrays(GL_TRIANGLES, 0, 3);

	glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer[GEO_TRIANGLE_4]);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glBindBuffer(GL_ARRAY_BUFFER, m_colorBuffer[GEO_TRIANGLE_4]);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glDrawArrays(GL_TRIANGLES, 0, 3);

	glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer[GEO_TRIANGLE_5]);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glBindBuffer(GL_ARRAY_BUFFER, m_colorBuffer[GEO_TRIANGLE_5]);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glDrawArrays(GL_TRIANGLES, 0, 3);

	glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer[GEO_TRIANGLE_6]);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glBindBuffer(GL_ARRAY_BUFFER, m_colorBuffer[GEO_TRIANGLE_6]);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glDrawArrays(GL_TRIANGLES, 0, 3);

	glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer[GEO_TRIANGLE_7]);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glBindBuffer(GL_ARRAY_BUFFER, m_colorBuffer[GEO_TRIANGLE_7]);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glDrawArrays(GL_TRIANGLES, 0, 3);

	glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer[GEO_TRIANGLE_8]);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glBindBuffer(GL_ARRAY_BUFFER, m_colorBuffer[GEO_TRIANGLE_8]);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glDrawArrays(GL_TRIANGLES, 0, 3);


	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
}

void Scene1::Exit()
{
	// Cleanup VBO here

	glDeleteBuffers(NUM_GEOMETRY, &m_vertexBuffer[0]);
	glDeleteBuffers(NUM_GEOMETRY, &m_colorBuffer[0]);
	glDeleteVertexArrays(1, &m_vertexArrayID);

	glDeleteProgram(m_programID);
}
