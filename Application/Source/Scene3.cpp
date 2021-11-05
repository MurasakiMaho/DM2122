#include "Scene3.h"
#include "GL\glew.h"

#include "shader.hpp"


Scene3::Scene3()
{
}

Scene3::~Scene3()
{
}

void Scene3::Init()
{
	rotateAngle = -20;
	translateX = 1;
	translateY = 0;
	scaleAll = 0.01;
	translateFoxY = 0;

	// Init VBO here

	// Set BG colour to dark blue
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

	//Generate a default VAO
	glGenVertexArrays(1, &m_vertexArrayID);
	glBindVertexArray(m_vertexArrayID);

	//Generate buffers
	glGenBuffers(NUM_GEOMETRY, &m_vertexBuffer[0]);
	glGenBuffers(NUM_GEOMETRY, &m_colorBuffer[0]);

	//sky
	// Set current active buffer
	glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer[GEO_TRIANGLE_1]);

	// An array of 3 vectors which represents 3 vertices
	static const GLfloat vertex_buffer_data[] =
	{
		-2, 0, 0,
		2, 0, 0,
		0, -2, 0
	};

	// Transfer vertices to OpenGL
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertex_buffer_data), vertex_buffer_data, GL_STATIC_DRAW);

	glBindBuffer(GL_ARRAY_BUFFER, m_colorBuffer[GEO_TRIANGLE_1]);

	// An array of 3 vectors which represents the colours of the 3 vertices
	static const GLfloat color_buffer_data[] =
	{
		0.1176,0.5647,1,
		0.1176,0.5647,1,
		0.0980, 0.0980, 0.4784
	};

	glBufferData(GL_ARRAY_BUFFER, sizeof(color_buffer_data), color_buffer_data, GL_STATIC_DRAW);

	for (int i = 0; i < 1; i++)
	{
		// Set current active buffer
		glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer[GEO_TRIANGLE_2]);

		static const GLfloat vertex_buffer_data_2[] =
		{
			-2, 0, 0,
			2, 0, 0,
			0, 2, 0
		};

		// Transfer vertices to OpenGL
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertex_buffer_data_2), vertex_buffer_data_2, GL_STATIC_DRAW);

		glBindBuffer(GL_ARRAY_BUFFER, m_colorBuffer[GEO_TRIANGLE_2]);

		static const GLfloat color_buffer_data_2[] =
		{
			0.1176,0.5647,1,
			0.1176,0.5647,1,
			//0.0980, 0.0980, 0.4784
			//0.1804,0.1333,0.5412
			//0.1333,0.0824,0.3412
			//0.0471,0.0313,0.1686
			1,1,1
		};

		glBindBuffer(GL_ARRAY_BUFFER, m_colorBuffer[GEO_TRIANGLE_2]);
		glBufferData(GL_ARRAY_BUFFER, sizeof(color_buffer_data_2), color_buffer_data_2, GL_STATIC_DRAW);

		//// 3rd 

		//glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer[GEO_TRIANGLE_3]);

		//static const GLfloat vertex_buffer_data_3[] =
		//{
		//	2, 2, 0,
		//	-2, 2, 0,
		//	0, 0, 0
		//};
		//glBufferData(GL_ARRAY_BUFFER, sizeof(vertex_buffer_data), vertex_buffer_data_3, GL_STATIC_DRAW);
		//glBindBuffer(GL_ARRAY_BUFFER, m_colorBuffer[GEO_TRIANGLE_3]);

		//static const GLfloat color_buffer_data_3[] =
		//{
		//	0.1176,0.5647,1,
		//0.1176,0.5647,1,
		//	//0.2941,0,0.5098,
		////0.2941,0,0.5098,
		//0.0980, 0.0980, 0.4784
		//};
		//glBufferData(GL_ARRAY_BUFFER, sizeof(color_buffer_data), color_buffer_data_3, GL_STATIC_DRAW);

		//// 4th right road
		//glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer[GEO_TRIANGLE_4]);

		//static const GLfloat vertex_buffer_data_4[] =
		//{
		//	-2, 2, 0,
		//	-2, -2, 0,
		//	0,0, 0
		//};
		//glBufferData(GL_ARRAY_BUFFER, sizeof(vertex_buffer_data), vertex_buffer_data_4, GL_STATIC_DRAW);
		//glBindBuffer(GL_ARRAY_BUFFER, m_colorBuffer[GEO_TRIANGLE_4]);

		//static const GLfloat color_buffer_data_4[] =
		//{
		//	0.1176,0.5647,1,
		//	//0.2941,0,0.5098,
		//	//0.2941,0,0.5098,
		//0.1176,0.5647,1,
		//0.0980, 0.0980, 0.4784
		//};
		//glBufferData(GL_ARRAY_BUFFER, sizeof(color_buffer_data), color_buffer_data_4, GL_STATIC_DRAW);

	}

	//road
	//left geo tri 5,6
	for (int i = 0; i < 1; i++)
	{
		// 5th
		glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer[GEO_TRIANGLE_5]);

		static const GLfloat vertex_buffer_data_5[] =
		{
			-1, -1, 0,
			0, -1, 0,
			0, 0, 0
		};
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertex_buffer_data), vertex_buffer_data_5, GL_STATIC_DRAW);
		glBindBuffer(GL_ARRAY_BUFFER, m_colorBuffer[GEO_TRIANGLE_5]);

		static const GLfloat color_buffer_data_5[] =
		{

			1, 0.549, 0,
		1, 0.549, 0,
		1, 0.647, 0,
		};
		glBufferData(GL_ARRAY_BUFFER, sizeof(color_buffer_data), color_buffer_data_5, GL_STATIC_DRAW);

		// 6th
		glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer[GEO_TRIANGLE_6]);

		static const GLfloat vertex_buffer_data_6[] =
		{

			1, -1, 0,
			0, -1, 0,
			0, 0, 0
		};
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertex_buffer_data), vertex_buffer_data_6, GL_STATIC_DRAW);
		glBindBuffer(GL_ARRAY_BUFFER, m_colorBuffer[GEO_TRIANGLE_6]);

		static const GLfloat color_buffer_data_6[] =
		{

			1, 0.549, 0,
			1, 0.549, 0,
			1, 0.647, 0
		};
		glBufferData(GL_ARRAY_BUFFER, sizeof(color_buffer_data), color_buffer_data_6, GL_STATIC_DRAW);
	}
	//right geo tri 7,8
	for (int i = 0; i < 1; i++)
	{
		// 7th
		glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer[GEO_TRIANGLE_7]);

		static const GLfloat vertex_buffer_data_7[] =
		{
			-0.6666, -1, 0,
			0, -1, 0,
			0, 0, 0
		};
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertex_buffer_data), vertex_buffer_data_7, GL_STATIC_DRAW);
		glBindBuffer(GL_ARRAY_BUFFER, m_colorBuffer[GEO_TRIANGLE_7]);

		static const GLfloat color_buffer_data_7[] =
		{
			0.7215, 0.5254, 0.043,
			0.7215, 0.5254, 0.043,
			0.8549, 0.6470, 0.1255
		};
		glBufferData(GL_ARRAY_BUFFER, sizeof(color_buffer_data), color_buffer_data_7, GL_STATIC_DRAW);

		// 8th
		glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer[GEO_TRIANGLE_8]);

		static const GLfloat vertex_buffer_data_8[] =
		{
			0.6666, -1, 0,
			 0, -1, 0,
			0, 0, 0
		};
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertex_buffer_data), vertex_buffer_data_8, GL_STATIC_DRAW);
		glBindBuffer(GL_ARRAY_BUFFER, m_colorBuffer[GEO_TRIANGLE_8]);

		static const GLfloat color_buffer_data_8[] =
		{
			0.7215, 0.5254, 0.043,
			0.7215, 0.5254, 0.043,
			0.8549, 0.6470, 0.1255
		};
		glBufferData(GL_ARRAY_BUFFER, sizeof(color_buffer_data), color_buffer_data_8, GL_STATIC_DRAW);
	}
	//land
	for (int i = 0; i < 1; i++)
	{
	// 9th
	glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer[GEO_TRIANGLE_9]);

	static const GLfloat vertex_buffer_data_9[] =
	{
		-1, -1, 0,
		-1, 0, 0,
		0, 0, 0
	};
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertex_buffer_data), vertex_buffer_data_9, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, m_colorBuffer[GEO_TRIANGLE_9]);

	static const GLfloat color_buffer_data_9[] =
	{

		1, 0.549, 0,
	1, 0.549, 0,
	1, 0.647, 0,
	};
	glBufferData(GL_ARRAY_BUFFER, sizeof(color_buffer_data), color_buffer_data_9, GL_STATIC_DRAW);

	//10th
	glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer[GEO_TRIANGLE_10]);

	static const GLfloat vertex_buffer_data_10[] =
	{

		1, -1, 0,
		1, 0, 0,
		0, 0, 0
	};
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertex_buffer_data), vertex_buffer_data_10, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, m_colorBuffer[GEO_TRIANGLE_10]);

	static const GLfloat color_buffer_data_10[] =
	{

		1, 0.549, 0,
		1, 0.549, 0,
		1, 0.647, 0
	};
	glBufferData(GL_ARRAY_BUFFER, sizeof(color_buffer_data), color_buffer_data_10, GL_STATIC_DRAW);
}
	//tree geo tri 11 to 14
	for (int i = 0; i < 1; i++)
	{
		//9
		glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer[GEO_TRIANGLE_11]);

		// An array of 3 vectors which represents 3 vertices
		static const GLfloat vertex_buffer_data_11[] =
		{
			0.1, -1, 0,
			-0.1, -1, 0,
			0, 0.7, 0
			
		};

		// Transfer vertices to OpenGL
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertex_buffer_data_11), vertex_buffer_data_11, GL_STATIC_DRAW);

		glBindBuffer(GL_ARRAY_BUFFER, m_colorBuffer[GEO_TRIANGLE_11]);

		// An array of 3 vectors which represents the colours of the 3 vertices
		static const GLfloat color_buffer_data_11[] =
		{
			0.5451,0.2701,0.0745,
			0.5451,0.2701,0.0745,
			0.6274,0.3215,0.1764
			
		};

		glBufferData(GL_ARRAY_BUFFER, sizeof(color_buffer_data_11), color_buffer_data_11, GL_STATIC_DRAW);

		glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer[GEO_TRIANGLE_12]);

		//10
		// An array of 3 vectors which represents 3 vertices
		static const GLfloat vertex_buffer_data_12[] =
		{
			0, 0.7, 0,
			0, 0.7, 0,
			-0.1, -1, 0
			
		};

		// Transfer vertices to OpenGL
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertex_buffer_data_12), vertex_buffer_data_12, GL_STATIC_DRAW);

		glBindBuffer(GL_ARRAY_BUFFER, m_colorBuffer[GEO_TRIANGLE_12]);

		// An array of 3 vectors which represents the colours of the 3 vertices
		static const GLfloat color_buffer_data_12[] =
		{
			0.6274,0.3215,0.1764,
			0.6274,0.3215,0.1764,
			0.5451,0.2701,0.0745
		};

		glBufferData(GL_ARRAY_BUFFER, sizeof(color_buffer_data_12), color_buffer_data_12, GL_STATIC_DRAW);

		//11
		glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer[GEO_TRIANGLE_13]);

		// An array of 3 vectors which represents 3 vertices
		static const GLfloat vertex_buffer_data_13[] =
		{
			
			0.3, -0.5, 0,
			-0.3, -0.5, 0,
			0, 0.1, 0
		};

		// Transfer vertices to OpenGL
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertex_buffer_data_13), vertex_buffer_data_13, GL_STATIC_DRAW);

		glBindBuffer(GL_ARRAY_BUFFER, m_colorBuffer[GEO_TRIANGLE_13]);

		// An array of 3 vectors which represents the colours of the 3 vertices
		static const GLfloat color_buffer_data_13[] =
		{
			0.8039,0.5215,0.2470,
			0.8039,0.5215,0.2470,
			0.8235,0.4117,0.1176
		};

		glBufferData(GL_ARRAY_BUFFER, sizeof(color_buffer_data_13), color_buffer_data_13, GL_STATIC_DRAW);

		glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer[GEO_TRIANGLE_14]);

		//12
		// An array of 3 vectors which represents 3 vertices
		static const GLfloat vertex_buffer_data_14[] =
		{
			0.2, 0, 0,
			-0.2, 0, 0,
			0, 0.7, 0
		};

		// Transfer vertices to OpenGL
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertex_buffer_data_14), vertex_buffer_data_14, GL_STATIC_DRAW);

		glBindBuffer(GL_ARRAY_BUFFER, m_colorBuffer[GEO_TRIANGLE_14]);

		// An array of 3 vectors which represents the colours of the 3 vertices
		static const GLfloat color_buffer_data_14[] =
		{
			0.8235,0.4117,0.1176,
			0.8235,0.4117,0.1176,
			0.8039,0.5215,0.2470
		};

		glBufferData(GL_ARRAY_BUFFER, sizeof(color_buffer_data_14), color_buffer_data_14, GL_STATIC_DRAW);
	}
	//fox head geo tri 15 to 20
	for (int i = 0; i < 1; i++)
	{
		//15
		glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer[GEO_TRIANGLE_15]);

		// An array of 3 vectors which represents 3 vertices
		static const GLfloat vertex_buffer_data_15[] =
		{
			-0.1, 0, 0,
			0.1, 0, 0,
			0, -0.4, 0

		};

		// Transfer vertices to OpenGL
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertex_buffer_data_15), vertex_buffer_data_15, GL_STATIC_DRAW);

		glBindBuffer(GL_ARRAY_BUFFER, m_colorBuffer[GEO_TRIANGLE_15]);

		// An array of 3 vectors which represents the colours of the 3 vertices
		static const GLfloat color_buffer_data_15[] =
		{
			/*0.8235,0.4117,0.1176,
			0.8235,0.4117,0.1176,
			0.8039,0.5215,0.2470*/
			0.6706,0.4588,0.1412,
			0.6706,0.4588,0.1412,
			0.8039,0.5215,0.2470

		};

		glBufferData(GL_ARRAY_BUFFER, sizeof(color_buffer_data_15), color_buffer_data_15, GL_STATIC_DRAW);

		glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer[GEO_TRIANGLE_16]);

		//16
		// An array of 3 vectors which represents 3 vertices
		static const GLfloat vertex_buffer_data_16[] =
		{
			-0.025, -0.3, 0,
			0.025, -0.3, 0,
			0, -0.4, 0

		};

		// Transfer vertices to OpenGL
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertex_buffer_data_16), vertex_buffer_data_16, GL_STATIC_DRAW);

		glBindBuffer(GL_ARRAY_BUFFER, m_colorBuffer[GEO_TRIANGLE_16]);

		// An array of 3 vectors which represents the colours of the 3 vertices
		static const GLfloat color_buffer_data_16[] =
		{
			/*0.6274,0.3215,0.1764,
			0.6274,0.3215,0.1764,
			0.5451,0.2701,0.0745*/
			0,0,0,0,0,0,0,0,0
		};

		glBufferData(GL_ARRAY_BUFFER, sizeof(color_buffer_data_16), color_buffer_data_16, GL_STATIC_DRAW);

		//17 ears
		glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer[GEO_TRIANGLE_17]);

		// An array of 3 vectors which represents 3 vertices
		static const GLfloat vertex_buffer_data_17[] =
		{

			-0.1, 0, 0,
			-0.05, 0, 0,
			-0.075, 0.1, 0
		};

		// Transfer vertices to OpenGL
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertex_buffer_data_17), vertex_buffer_data_17, GL_STATIC_DRAW);

		glBindBuffer(GL_ARRAY_BUFFER, m_colorBuffer[GEO_TRIANGLE_17]);

		// An array of 3 vectors which represents the colours of the 3 vertices
		static const GLfloat color_buffer_data_17[] =
		{
			0.6706,0.4588,0.1412,
			0.6706,0.4588,0.1412,
			0.8235,0.4117,0.1176
		};

		glBufferData(GL_ARRAY_BUFFER, sizeof(color_buffer_data_17), color_buffer_data_17, GL_STATIC_DRAW);

		glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer[GEO_TRIANGLE_18]);

		//18 ears
		// An array of 3 vectors which represents 3 vertices
		static const GLfloat vertex_buffer_data_18[] =
		{
			0.1, 0, 0,
			0.05, 0, 0,
			0.075, 0.1, 0
		};

		// Transfer vertices to OpenGL
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertex_buffer_data_18), vertex_buffer_data_18, GL_STATIC_DRAW);

		glBindBuffer(GL_ARRAY_BUFFER, m_colorBuffer[GEO_TRIANGLE_18]);

		// An array of 3 vectors which represents the colours of the 3 vertices
		static const GLfloat color_buffer_data_18[] =
		{
			0.6706,0.4588,0.1412,
			0.6706,0.4588,0.1412,
			0.8039,0.5215,0.2470
		};

		glBufferData(GL_ARRAY_BUFFER, sizeof(color_buffer_data_18), color_buffer_data_18, GL_STATIC_DRAW);

		//19
		glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer[GEO_TRIANGLE_19]);

		// An array of 3 vectors which represents 3 vertices
		static const GLfloat vertex_buffer_data_19[] =
		{

			-0.03, -0.1, 0,
			-0.07, -0.06, 0,
			-0.02, -0.1, 0
		};

		// Transfer vertices to OpenGL
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertex_buffer_data_19), vertex_buffer_data_19, GL_STATIC_DRAW);

		glBindBuffer(GL_ARRAY_BUFFER, m_colorBuffer[GEO_TRIANGLE_19]);

		// An array of 3 vectors which represents the colours of the 3 vertices
		static const GLfloat color_buffer_data_19[] =
		{
			0,0,0,0,0,0,0,0,0
		};

		glBufferData(GL_ARRAY_BUFFER, sizeof(color_buffer_data_19), color_buffer_data_19, GL_STATIC_DRAW);

		glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer[GEO_TRIANGLE_20]);

		//20
		// An array of 3 vectors which represents 3 vertices
		static const GLfloat vertex_buffer_data_20[] =
		{
			0.03, -0.1, 0,
			0.07, -0.06, 0,
			0.02, -0.1, 0
		};

		// Transfer vertices to OpenGL
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertex_buffer_data_20), vertex_buffer_data_20, GL_STATIC_DRAW);

		glBindBuffer(GL_ARRAY_BUFFER, m_colorBuffer[GEO_TRIANGLE_20]);

		// An array of 3 vectors which represents the colours of the 3 vertices
		static const GLfloat color_buffer_data_20[] =
		{
			0,0,0,0,0,0,0,0,0
		};

		glBufferData(GL_ARRAY_BUFFER, sizeof(color_buffer_data_20), color_buffer_data_20, GL_STATIC_DRAW);
	}
	// fox legs geo tri 21 to 24
	for (int i = 0; i < 1; i++)
	{
		//21
		glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer[GEO_TRIANGLE_21]);

		// An array of 3 vectors which represents 3 vertices
		static const GLfloat vertex_buffer_data_21[] =
		{
			-0.075, -0.1, 0,
			-0.025, -0.3, 0,
			-0.08, -0.5, 0,

		};

		// Transfer vertices to OpenGL
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertex_buffer_data_21), vertex_buffer_data_21, GL_STATIC_DRAW);

		glBindBuffer(GL_ARRAY_BUFFER, m_colorBuffer[GEO_TRIANGLE_21]);

		// An array of 3 vectors which represents the colours of the 3 vertices
		static const GLfloat color_buffer_data_21[] =
		{
			/*0.8235,0.4117,0.1176,
			0.8235,0.4117,0.1176,
			0.8039,0.5215,0.2470*/
			0.6706,0.4588,0.1412,
			0.6706,0.4588,0.1412,
			0.8039,0.5215,0.2470

		};

		glBufferData(GL_ARRAY_BUFFER, sizeof(color_buffer_data_21), color_buffer_data_21, GL_STATIC_DRAW);

		glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer[GEO_TRIANGLE_22]);

		//22
		// An array of 3 vectors which represents 3 vertices
		static const GLfloat vertex_buffer_data_22[] =
		{
			0.075, -0.1, 0,
			0.025, -0.3, 0,
			0.08, -0.5, 0,

		};

		// Transfer vertices to OpenGL
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertex_buffer_data_22), vertex_buffer_data_22, GL_STATIC_DRAW);

		glBindBuffer(GL_ARRAY_BUFFER, m_colorBuffer[GEO_TRIANGLE_22]);

		// An array of 3 vectors which represents the colours of the 3 vertices
		static const GLfloat color_buffer_data_22[] =
		{
			0.6706,0.4588,0.1412,
			0.6706,0.4588,0.1412,
			0.8039,0.5215,0.2470
		};

		glBufferData(GL_ARRAY_BUFFER, sizeof(color_buffer_data_22), color_buffer_data_22, GL_STATIC_DRAW);

		//17 ears
		glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer[GEO_TRIANGLE_23]);

		// An array of 3 vectors which represents 3 vertices
		static const GLfloat vertex_buffer_data_23[] =
		{

			-0.1, 0, 0,
			-0.05, 0, 0,
			-0.075, 0.1, 0
		};

		// Transfer vertices to OpenGL
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertex_buffer_data_23), vertex_buffer_data_23, GL_STATIC_DRAW);

		glBindBuffer(GL_ARRAY_BUFFER, m_colorBuffer[GEO_TRIANGLE_23]);

		// An array of 3 vectors which represents the colours of the 3 vertices
		static const GLfloat color_buffer_data_23[] =
		{
			0.6706,0.4588,0.1412,
			0.6706,0.4588,0.1412,
			0.8235,0.4117,0.1176
		};

		glBufferData(GL_ARRAY_BUFFER, sizeof(color_buffer_data_23), color_buffer_data_23, GL_STATIC_DRAW);

		glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer[GEO_TRIANGLE_24]);

		//18 ears
		// An array of 3 vectors which represents 3 vertices
		static const GLfloat vertex_buffer_data_24[] =
		{
			0.1, 0, 0,
			0.05, 0, 0,
			0.075, 0.1, 0
		};

		// Transfer vertices to OpenGL
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertex_buffer_data_24), vertex_buffer_data_24, GL_STATIC_DRAW);

		glBindBuffer(GL_ARRAY_BUFFER, m_colorBuffer[GEO_TRIANGLE_24]);

		// An array of 3 vectors which represents the colours of the 3 vertices
		static const GLfloat color_buffer_data_24[] =
		{
			0.6706,0.4588,0.1412,
			0.6706,0.4588,0.1412,
			0.8039,0.5215,0.2470
		};

		glBufferData(GL_ARRAY_BUFFER, sizeof(color_buffer_data_24), color_buffer_data_24, GL_STATIC_DRAW);

	}
	//sun
	for (int i = 0; i < 1; i++)
	{
		//25
		glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer[GEO_TRIANGLE_25]);

		// An array of 3 vectors which represents 3 vertices
		static const GLfloat vertex_buffer_data_25[] =
		{

			0.4,0.5,0,
			0.4,0,0,
			0,0,0
		};

		// Transfer vertices to OpenGL
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertex_buffer_data_25), vertex_buffer_data_25, GL_STATIC_DRAW);

		glBindBuffer(GL_ARRAY_BUFFER, m_colorBuffer[GEO_TRIANGLE_25]);

		// An array of 3 vectors which represents the colours of the 3 vertices
		static const GLfloat color_buffer_data_25[] =
		{
			0.9215,0.6706,0.2039,
			0.9215,0.7882,0.2029,
			0.9215,0.6706,0.2039,
		};

		glBufferData(GL_ARRAY_BUFFER, sizeof(color_buffer_data_25), color_buffer_data_25, GL_STATIC_DRAW);

		glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer[GEO_TRIANGLE_26]);

		//26
		// An array of 3 vectors which represents 3 vertices
		static const GLfloat vertex_buffer_data_26[] =
		{
			0.4,0.5,0,
			0,0.5,0,
			0,0,0
		};

		// Transfer vertices to OpenGL
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertex_buffer_data_26), vertex_buffer_data_26, GL_STATIC_DRAW);

		glBindBuffer(GL_ARRAY_BUFFER, m_colorBuffer[GEO_TRIANGLE_26]);

		// An array of 3 vectors which represents the colours of the 3 vertices
		static const GLfloat color_buffer_data_26[] =
		{
			0.9215,0.6706,0.2039,
			0.9215,0.7882,0.2029,
			0.9215,0.6706,0.2039,
		};

		glBufferData(GL_ARRAY_BUFFER, sizeof(color_buffer_data_26), color_buffer_data_26, GL_STATIC_DRAW);
	}

	// Load vertex and fragment shaders
	m_programID = LoadShaders("Shader//TransformVertexShader.vertexshader", "Shader//SimpleFragmentShader.fragmentshader");
	//Use our shader
	glUseProgram(m_programID);

	//Get a handle for our "MVP" uniform
	m_parameters[U_MVP] = glGetUniformLocation(m_programID, "MVP");
	/*m_parameters[U_MVP_1] = glGetUniformLocation(m_programID, "MVP");
	m_parameters[U_MVP_2] = glGetUniformLocation(m_programID, "MVP");*/
}

void Scene3::Update(double dt)
{
	rotateAngle += (float)(50 * dt);

	if (translateX < -27)
		translateX = 27;
	translateX -= (float)(7.5 * dt);

	if (translateY > 0)
		translateY = -20;
	translateY += (float)(5 * dt);


	scaleAll += (float)(3 * dt);
	if (scaleAll > 40) scaleAll = 0.01;
	
	translateFoxY -= (float)(2 * dt);
	if (translateFoxY < -27) translateFoxY = 0;

	//translateLeftTreeX -= (float)(20 * dt);
	//translateLeftTreeY -= (float)(20 * dt);
	//treeScale += (float)(10 * dt);
	//if (translateLeftTreeY < -20)
	//{
	//	translateLeftTreeX = -3;
	//	translateLeftTreeY = 2;
	//	treeScale = 5;
	//}
}

void Scene3::Render()
{
	//Try trees moving toward pov


	// Clear buffer colour every frame
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	Mtx44 translate, rotate, scale;
	Mtx44 model;
	Mtx44 view;
	Mtx44 projection;
	Mtx44 MVP;

	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);

	projection.SetToOrtho(-20, 20, -20, 20, -20, 20); //Our world is a cube defined by this boundaries

	//sky
	for (int i = 0; i < 1; i++)
	{
		translate.SetToIdentity();
			rotate.SetToIdentity();
			scale.SetToIdentity();
			model.SetToIdentity();
			view.SetToIdentity(); //no need camera for now, set at world's origin
			
			scale.SetToScale(20, 20, 20);
			rotate.SetToRotation(rotateAngle, 0, 0, 1);
			translate.SetToTranslation(0, 0, 0);
			model = translate * rotate * scale;
			MVP = projection * view * model;
			glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]);

			glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer[GEO_TRIANGLE_1]);
			glVertexAttribPointer
			(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
			glBindBuffer(GL_ARRAY_BUFFER, m_colorBuffer[GEO_TRIANGLE_1]);
			glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);
			glDrawArrays(GL_TRIANGLES, 0, 3);

			glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer[GEO_TRIANGLE_2]);
			glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
			glBindBuffer(GL_ARRAY_BUFFER, m_colorBuffer[GEO_TRIANGLE_2]);
			glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);
			glDrawArrays(GL_TRIANGLES, 0, 3);	// Starting from vertex 0; 3 vertices = 1 triangle

			/*glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer[GEO_TRIANGLE_3]);
			glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
			glBindBuffer(GL_ARRAY_BUFFER, m_colorBuffer[GEO_TRIANGLE_3]);
			glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);
			glDrawArrays(GL_TRIANGLES, 0, 3);

			glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer[GEO_TRIANGLE_4]);
			glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
			glBindBuffer(GL_ARRAY_BUFFER, m_colorBuffer[GEO_TRIANGLE_4]);
			glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);
			glDrawArrays(GL_TRIANGLES, 0, 3);*/
	}
	//road 
	for (int i = 0; i < 1;i++)
	{
		translate.SetToIdentity();
		rotate.SetToIdentity();
		scale.SetToIdentity();
		model.SetToIdentity();
		view.SetToIdentity(); //no need camera for now, set at world's origin
		
		scale.SetToScale(20, 20, 20);
		rotate.SetToRotation(0, 0, 0, 1);
		translate.SetToTranslation(0, 0, 0);
		model = translate * rotate * scale;
		MVP = projection * view * model;
		glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]);

		glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer[GEO_TRIANGLE_5]);
		glVertexAttribPointer
		(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
		glBindBuffer(GL_ARRAY_BUFFER, m_colorBuffer[GEO_TRIANGLE_5]);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);
		glDrawArrays(GL_TRIANGLES, 0, 3);

		glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer[GEO_TRIANGLE_6]);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
		glBindBuffer(GL_ARRAY_BUFFER, m_colorBuffer[GEO_TRIANGLE_6]);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);
		glDrawArrays(GL_TRIANGLES, 0, 3);	// Starting from vertex 0; 3 vertices = 1 triangle

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
	}
	//land
	for (int i = 0; i < 1; i++)
	{
		translate.SetToIdentity();
		rotate.SetToIdentity();
		scale.SetToIdentity();
		model.SetToIdentity();

		scale.SetToScale(20, 20, 20);
		rotate.SetToRotation(0, 0, 0, 1);
		translate.SetToTranslation(0, 0, 0);
		model = translate * rotate * scale;
		MVP = projection * view * model;
		glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]);

		glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer[GEO_TRIANGLE_9]);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
		glBindBuffer(GL_ARRAY_BUFFER, m_colorBuffer[GEO_TRIANGLE_9]);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);
		glDrawArrays(GL_TRIANGLES, 0, 3);

		glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer[GEO_TRIANGLE_10]);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
		glBindBuffer(GL_ARRAY_BUFFER, m_colorBuffer[GEO_TRIANGLE_10]);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);
		glDrawArrays(GL_TRIANGLES, 0, 3);
	}
	//tree 1
	for (int i = 0; i < 1; i++)
	{
		translate.SetToIdentity();
		rotate.SetToIdentity();
		scale.SetToIdentity();
		model.SetToIdentity();

		scale.SetToScale(5, 5, 5);
		rotate.SetToRotation(0, 0, 0, 1);
		translate.SetToTranslation(-3,2, 0);
		model = translate * rotate * scale;
		MVP = projection * view * model;
		glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]);

		glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer[GEO_TRIANGLE_11]);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
		glBindBuffer(GL_ARRAY_BUFFER, m_colorBuffer[GEO_TRIANGLE_11]);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);
		glDrawArrays(GL_TRIANGLES, 0, 3);

		glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer[GEO_TRIANGLE_12]);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
		glBindBuffer(GL_ARRAY_BUFFER, m_colorBuffer[GEO_TRIANGLE_12]);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);
		glDrawArrays(GL_TRIANGLES, 0, 3);

		glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer[GEO_TRIANGLE_13]);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
		glBindBuffer(GL_ARRAY_BUFFER, m_colorBuffer[GEO_TRIANGLE_13]);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);
		glDrawArrays(GL_TRIANGLES, 0, 3);

		glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer[GEO_TRIANGLE_14]);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
		glBindBuffer(GL_ARRAY_BUFFER, m_colorBuffer[GEO_TRIANGLE_14]);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);
		glDrawArrays(GL_TRIANGLES, 0, 3);
	}
	//tree 2
	for (int i = 0; i < 1; i++)
	{
		translate.SetToIdentity();
		rotate.SetToIdentity();
		scale.SetToIdentity();
		model.SetToIdentity();

		scale.SetToScale(7, 7, 7);
		rotate.SetToRotation(0, 0, 0, 1);
		translate.SetToTranslation(-6, 0, 0);
		model = translate * rotate * scale;
		MVP = projection * view * model;
		glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]);

		glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer[GEO_TRIANGLE_11]);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
		glBindBuffer(GL_ARRAY_BUFFER, m_colorBuffer[GEO_TRIANGLE_11]);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);
		glDrawArrays(GL_TRIANGLES, 0, 3);

		glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer[GEO_TRIANGLE_12]);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
		glBindBuffer(GL_ARRAY_BUFFER, m_colorBuffer[GEO_TRIANGLE_12]);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);
		glDrawArrays(GL_TRIANGLES, 0, 3);

		glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer[GEO_TRIANGLE_13]);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
		glBindBuffer(GL_ARRAY_BUFFER, m_colorBuffer[GEO_TRIANGLE_13]);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);
		glDrawArrays(GL_TRIANGLES, 0, 3);

		glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer[GEO_TRIANGLE_14]);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
		glBindBuffer(GL_ARRAY_BUFFER, m_colorBuffer[GEO_TRIANGLE_14]);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);
		glDrawArrays(GL_TRIANGLES, 0, 3);
	}
	//tree 3
	for (int i = 0; i < 1; i++)
	{
		translate.SetToIdentity();
		rotate.SetToIdentity();
		scale.SetToIdentity();
		model.SetToIdentity();

		scale.SetToScale(10, 10, 10);
		rotate.SetToRotation(0, 0, 0, 1);
		translate.SetToTranslation(-10, -3, 0);
		model = translate * rotate * scale;
		MVP = projection * view * model;
		glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]);

		glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer[GEO_TRIANGLE_11]);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
		glBindBuffer(GL_ARRAY_BUFFER, m_colorBuffer[GEO_TRIANGLE_11]);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);
		glDrawArrays(GL_TRIANGLES, 0, 3);

		glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer[GEO_TRIANGLE_12]);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
		glBindBuffer(GL_ARRAY_BUFFER, m_colorBuffer[GEO_TRIANGLE_12]);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);
		glDrawArrays(GL_TRIANGLES, 0, 3);

		glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer[GEO_TRIANGLE_13]);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
		glBindBuffer(GL_ARRAY_BUFFER, m_colorBuffer[GEO_TRIANGLE_13]);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);
		glDrawArrays(GL_TRIANGLES, 0, 3);

		glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer[GEO_TRIANGLE_14]);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
		glBindBuffer(GL_ARRAY_BUFFER, m_colorBuffer[GEO_TRIANGLE_14]);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);
		glDrawArrays(GL_TRIANGLES, 0, 3);
	}
	//tree 4
	for (int i = 0; i < 1; i++)
	{
		translate.SetToIdentity();
		rotate.SetToIdentity();
		scale.SetToIdentity();
		model.SetToIdentity();

		scale.SetToScale(15, 15, 15);
		rotate.SetToRotation(0, 0, 0, 1);
		translate.SetToTranslation(-17, -8, 0);
		model = translate * rotate * scale;
		MVP = projection * view * model;
		glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]);

		glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer[GEO_TRIANGLE_11]);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
		glBindBuffer(GL_ARRAY_BUFFER, m_colorBuffer[GEO_TRIANGLE_11]);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);
		glDrawArrays(GL_TRIANGLES, 0, 3);

		glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer[GEO_TRIANGLE_12]);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
		glBindBuffer(GL_ARRAY_BUFFER, m_colorBuffer[GEO_TRIANGLE_12]);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);
		glDrawArrays(GL_TRIANGLES, 0, 3);

		glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer[GEO_TRIANGLE_13]);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
		glBindBuffer(GL_ARRAY_BUFFER, m_colorBuffer[GEO_TRIANGLE_13]);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);
		glDrawArrays(GL_TRIANGLES, 0, 3);

		glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer[GEO_TRIANGLE_14]);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
		glBindBuffer(GL_ARRAY_BUFFER, m_colorBuffer[GEO_TRIANGLE_14]);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);
		glDrawArrays(GL_TRIANGLES, 0, 3);
	}
	//tree 5
	for (int i = 0; i < 1; i++)
	{
		translate.SetToIdentity();
		rotate.SetToIdentity();
		scale.SetToIdentity();
		model.SetToIdentity();

		scale.SetToScale(5, 5, 5);
		rotate.SetToRotation(0, 0, 0, 1);
		translate.SetToTranslation(3, 2, 0);
		model = translate * rotate * scale;
		MVP = projection * view * model;
		glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]);

		glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer[GEO_TRIANGLE_11]);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
		glBindBuffer(GL_ARRAY_BUFFER, m_colorBuffer[GEO_TRIANGLE_11]);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);
		glDrawArrays(GL_TRIANGLES, 0, 3);

		glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer[GEO_TRIANGLE_12]);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
		glBindBuffer(GL_ARRAY_BUFFER, m_colorBuffer[GEO_TRIANGLE_12]);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);
		glDrawArrays(GL_TRIANGLES, 0, 3);

		glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer[GEO_TRIANGLE_13]);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
		glBindBuffer(GL_ARRAY_BUFFER, m_colorBuffer[GEO_TRIANGLE_13]);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);
		glDrawArrays(GL_TRIANGLES, 0, 3);

		glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer[GEO_TRIANGLE_14]);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
		glBindBuffer(GL_ARRAY_BUFFER, m_colorBuffer[GEO_TRIANGLE_14]);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);
		glDrawArrays(GL_TRIANGLES, 0, 3);
	}
	//tree 2
	for (int i = 0; i < 1; i++)
	{
		translate.SetToIdentity();
		rotate.SetToIdentity();
		scale.SetToIdentity();
		model.SetToIdentity();

		scale.SetToScale(7, 7, 7);
		rotate.SetToRotation(0, 0, 0, 1);
		translate.SetToTranslation(6, 0, 0);
		model = translate * rotate * scale;
		MVP = projection * view * model;
		glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]);

		glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer[GEO_TRIANGLE_11]);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
		glBindBuffer(GL_ARRAY_BUFFER, m_colorBuffer[GEO_TRIANGLE_11]);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);
		glDrawArrays(GL_TRIANGLES, 0, 3);

		glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer[GEO_TRIANGLE_12]);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
		glBindBuffer(GL_ARRAY_BUFFER, m_colorBuffer[GEO_TRIANGLE_12]);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);
		glDrawArrays(GL_TRIANGLES, 0, 3);

		glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer[GEO_TRIANGLE_13]);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
		glBindBuffer(GL_ARRAY_BUFFER, m_colorBuffer[GEO_TRIANGLE_13]);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);
		glDrawArrays(GL_TRIANGLES, 0, 3);

		glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer[GEO_TRIANGLE_14]);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
		glBindBuffer(GL_ARRAY_BUFFER, m_colorBuffer[GEO_TRIANGLE_14]);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);
		glDrawArrays(GL_TRIANGLES, 0, 3);
	}
	//tree 3
	for (int i = 0; i < 1; i++)
	{
		translate.SetToIdentity();
		rotate.SetToIdentity();
		scale.SetToIdentity();
		model.SetToIdentity();

		scale.SetToScale(10, 10, 10);
		rotate.SetToRotation(0, 0, 0, 1);
		translate.SetToTranslation(10, -3, 0);
		model = translate * rotate * scale;
		MVP = projection * view * model;
		glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]);

		glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer[GEO_TRIANGLE_11]);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
		glBindBuffer(GL_ARRAY_BUFFER, m_colorBuffer[GEO_TRIANGLE_11]);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);
		glDrawArrays(GL_TRIANGLES, 0, 3);

		glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer[GEO_TRIANGLE_12]);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
		glBindBuffer(GL_ARRAY_BUFFER, m_colorBuffer[GEO_TRIANGLE_12]);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);
		glDrawArrays(GL_TRIANGLES, 0, 3);

		glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer[GEO_TRIANGLE_13]);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
		glBindBuffer(GL_ARRAY_BUFFER, m_colorBuffer[GEO_TRIANGLE_13]);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);
		glDrawArrays(GL_TRIANGLES, 0, 3);

		glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer[GEO_TRIANGLE_14]);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
		glBindBuffer(GL_ARRAY_BUFFER, m_colorBuffer[GEO_TRIANGLE_14]);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);
		glDrawArrays(GL_TRIANGLES, 0, 3);
	}
	//tree 4
	for (int i = 0; i < 1; i++)
	{
		translate.SetToIdentity();
		rotate.SetToIdentity();
		scale.SetToIdentity();
		model.SetToIdentity();

		scale.SetToScale(15, 15, 15);
		rotate.SetToRotation(0, 0, 0, 1);
		translate.SetToTranslation(17, -8, 0);
		model = translate * rotate * scale;
		MVP = projection * view * model;
		glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]);

		glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer[GEO_TRIANGLE_11]);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
		glBindBuffer(GL_ARRAY_BUFFER, m_colorBuffer[GEO_TRIANGLE_11]);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);
		glDrawArrays(GL_TRIANGLES, 0, 3);

		glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer[GEO_TRIANGLE_12]);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
		glBindBuffer(GL_ARRAY_BUFFER, m_colorBuffer[GEO_TRIANGLE_12]);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);
		glDrawArrays(GL_TRIANGLES, 0, 3);

		glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer[GEO_TRIANGLE_13]);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
		glBindBuffer(GL_ARRAY_BUFFER, m_colorBuffer[GEO_TRIANGLE_13]);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);
		glDrawArrays(GL_TRIANGLES, 0, 3);

		glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer[GEO_TRIANGLE_14]);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
		glBindBuffer(GL_ARRAY_BUFFER, m_colorBuffer[GEO_TRIANGLE_14]);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);
		glDrawArrays(GL_TRIANGLES, 0, 3);
	}
	//fox
	for (int i = 0; i < 1; i++)
	{
		translate.SetToIdentity();
		rotate.SetToIdentity();
		scale.SetToIdentity();
		model.SetToIdentity();

		scale.SetToScale(scaleAll, scaleAll, scaleAll);
		rotate.SetToRotation(0, 0, 0, 1);
		translate.SetToTranslation(0, translateFoxY, 0);
		model = translate * rotate * scale;
		MVP = projection * view * model;
		glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]);

		glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer[GEO_TRIANGLE_15]);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
		glBindBuffer(GL_ARRAY_BUFFER, m_colorBuffer[GEO_TRIANGLE_15]);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);
		glDrawArrays(GL_TRIANGLES, 0, 3);

		glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer[GEO_TRIANGLE_16]);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
		glBindBuffer(GL_ARRAY_BUFFER, m_colorBuffer[GEO_TRIANGLE_16]);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);
		glDrawArrays(GL_TRIANGLES, 0, 3);

		glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer[GEO_TRIANGLE_17]);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
		glBindBuffer(GL_ARRAY_BUFFER, m_colorBuffer[GEO_TRIANGLE_17]);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);
		glDrawArrays(GL_TRIANGLES, 0, 3);

		glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer[GEO_TRIANGLE_18]);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
		glBindBuffer(GL_ARRAY_BUFFER, m_colorBuffer[GEO_TRIANGLE_18]);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);
		glDrawArrays(GL_TRIANGLES, 0, 3);

		glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer[GEO_TRIANGLE_19]);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
		glBindBuffer(GL_ARRAY_BUFFER, m_colorBuffer[GEO_TRIANGLE_19]);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);
		glDrawArrays(GL_TRIANGLES, 0, 3);

		glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer[GEO_TRIANGLE_20]);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
		glBindBuffer(GL_ARRAY_BUFFER, m_colorBuffer[GEO_TRIANGLE_20]);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);
		glDrawArrays(GL_TRIANGLES, 0, 3);

		glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer[GEO_TRIANGLE_21]);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
		glBindBuffer(GL_ARRAY_BUFFER, m_colorBuffer[GEO_TRIANGLE_21]);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);
		glDrawArrays(GL_TRIANGLES, 0, 3);

		glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer[GEO_TRIANGLE_22]);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
		glBindBuffer(GL_ARRAY_BUFFER, m_colorBuffer[GEO_TRIANGLE_22]);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);
		glDrawArrays(GL_TRIANGLES, 0, 3);
	}
	//sun
	for (int i = 0; i < 1; i++)
	{
		translate.SetToIdentity();
		rotate.SetToIdentity();
		scale.SetToIdentity();
		model.SetToIdentity();

		scale.SetToScale(10, 10, 10);
		rotate.SetToRotation(rotateAngle, rotateAngle, rotateAngle, 1);
		translate.SetToTranslation(translateX, 15, 0);
		model = translate * rotate * scale;
		MVP = projection * view * model;
		glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]);

		glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer[GEO_TRIANGLE_25]);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
		glBindBuffer(GL_ARRAY_BUFFER, m_colorBuffer[GEO_TRIANGLE_25]);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);
		glDrawArrays(GL_TRIANGLES, 0, 3);

		glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer[GEO_TRIANGLE_26]);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
		glBindBuffer(GL_ARRAY_BUFFER, m_colorBuffer[GEO_TRIANGLE_26]);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);
		glDrawArrays(GL_TRIANGLES, 0, 3);

		
	}

	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
}

void Scene3::Exit()
{
	// Cleanup VBO here

	glDeleteBuffers(NUM_GEOMETRY, &m_vertexBuffer[0]);
	glDeleteBuffers(NUM_GEOMETRY, &m_colorBuffer[0]);
	glDeleteVertexArrays(1, &m_vertexArrayID);

	glDeleteProgram(m_programID);
}
