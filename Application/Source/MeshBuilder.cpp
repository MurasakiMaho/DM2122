#include "MeshBuilder.h"
#include <GL\glew.h>
#include <vector>

//Texturing for sphere not fixed

Mesh* MeshBuilder::GenerateAxes(const std::string &meshName, float lengthX, float lengthY, float lengthZ)
{
	Vertex v;
	std::vector<Vertex> vertex_buffer_data;
	std::vector<GLuint> index_buffer_data;

	//x-axis
	v.pos.Set(-lengthX, 0, 0);	v.color.Set(1, 0, 0);	vertex_buffer_data.push_back(v);
	v.pos.Set(lengthX, 0, 0);	v.color.Set(1, 0, 0);	vertex_buffer_data.push_back(v);
	//y-axis
	v.pos.Set(0, -lengthY, 0);	v.color.Set(0, 1, 0);	vertex_buffer_data.push_back(v);
	v.pos.Set(0, lengthY, 0);	v.color.Set(0, 1, 0);	vertex_buffer_data.push_back(v);
	//z-axis
	v.pos.Set(0, 0, -lengthZ);	v.color.Set(0, 0, 1);	vertex_buffer_data.push_back(v);
	v.pos.Set(0, 0, lengthZ);	v.color.Set(0, 0, 1);	vertex_buffer_data.push_back(v);

	index_buffer_data.push_back(0);
	index_buffer_data.push_back(1);
	index_buffer_data.push_back(2);
	index_buffer_data.push_back(3);
	index_buffer_data.push_back(4);
	index_buffer_data.push_back(5);

	Mesh *mesh = new Mesh(meshName);

	glBindBuffer(GL_ARRAY_BUFFER, mesh->vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, vertex_buffer_data.size() * sizeof(Vertex), &vertex_buffer_data[0], GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh->indexBuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, index_buffer_data.size() * sizeof(GLuint), &index_buffer_data[0], GL_STATIC_DRAW);

	mesh->indexSize = index_buffer_data.size();
	mesh->mode = Mesh::DRAW_LINES;

	return mesh;
}

Mesh* MeshBuilder::GenerateQuad(const std::string &meshName, Color color, float length)
{
	Vertex v;
	std::vector<Vertex> vertex_buffer_data;
	std::vector<GLuint> index_buffer_data;

	v.pos.Set(0.5f * length, 0.5f * length, 0.f);	v.color = color; v.normal.Set(0, 0, 1);	 
	v.texCoord.Set(0, 0); //top left
	vertex_buffer_data.push_back(v);
	v.pos.Set(-0.5f * length, 0.5f * length, 0.f);	v.color = color; v.normal.Set(0, 0, 1);	 
	v.texCoord.Set(1, 0); //bottom right
	vertex_buffer_data.push_back(v);
	v.pos.Set(-0.5f * length, -0.5f * length, 0.f);	v.color = color; v.normal.Set(0, 0, 1);	
	v.texCoord.Set(1, 1); //top right
	vertex_buffer_data.push_back(v);
	v.pos.Set(0.5f * length, -0.5f * length, 0.f);	v.color = color; v.normal.Set(0, 0, 1);	 
	v.texCoord.Set(0, 1); //bottom left 
	
	vertex_buffer_data.push_back(v);

	
	
	
	

	//tri1
	index_buffer_data.push_back(0);
	index_buffer_data.push_back(1);
	index_buffer_data.push_back(2);
	//tri2
	index_buffer_data.push_back(0);
	index_buffer_data.push_back(2);
	index_buffer_data.push_back(3);

	Mesh* mesh = new Mesh(meshName);

	glBindBuffer(GL_ARRAY_BUFFER, mesh->vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, vertex_buffer_data.size() * sizeof(Vertex), &vertex_buffer_data[0], GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh->indexBuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, index_buffer_data.size() * sizeof(GLuint), &index_buffer_data[0], GL_STATIC_DRAW);

	mesh->indexSize = index_buffer_data.size();
	mesh->mode = Mesh::DRAW_TRIANGLES;

	return mesh;
}

Mesh* MeshBuilder::GenerateCube(const std::string &meshName, Color color, float length)
{
	Vertex v;
	std::vector<Vertex> vertex_buffer_data;
	std::vector<GLuint> index_buffer_data;

	//Left
	v.pos.Set(-0.5f * length, -0.5f * length, -0.5f * length);	v.color = color; v.normal.Set(0, 0, 1);	vertex_buffer_data.push_back(v);
	v.pos.Set(-0.5f * length, -0.5f * length, 0.5f * length);	v.color = color; v.normal.Set(0, 0, 1);	vertex_buffer_data.push_back(v);
	v.pos.Set(-0.5f * length, 0.5f * length, 0.5f * length);	v.color = color; v.normal.Set(0, 0, 1);	vertex_buffer_data.push_back(v);
	
	v.pos.Set(-0.5f * length, -0.5f * length, -0.5f * length);	v.color = color; v.normal.Set(0, 0, 1);	vertex_buffer_data.push_back(v);
	v.pos.Set(-0.5f * length, 0.5f * length, 0.5f * length);	v.color = color; v.normal.Set(0, 0, 1);	vertex_buffer_data.push_back(v);
	v.pos.Set(-0.5f * length, 0.5f * length, -0.5f * length);	v.color = color; v.normal.Set(0, 0, 1);	vertex_buffer_data.push_back(v);

	//Back
	v.pos.Set(0.5f * length, 0.5f * length, -0.5f * length);	v.color = color; v.normal.Set(0, 0, 1);	vertex_buffer_data.push_back(v);
	v.pos.Set(-0.5f * length, -0.5f * length, -0.5f * length);	v.color = color; v.normal.Set(0, 0, 1);	vertex_buffer_data.push_back(v);
	v.pos.Set(-0.5f * length, 0.5f * length, -0.5f * length);	v.color = color; v.normal.Set(0, 0, 1);	vertex_buffer_data.push_back(v);

	v.pos.Set(0.5f * length, 0.5f * length, -0.5f * length);	v.color = color; v.normal.Set(0, 0, 1);	vertex_buffer_data.push_back(v);
	v.pos.Set(0.5f * length, -0.5f * length, -0.5f * length);	v.color = color; v.normal.Set(0, 0, 1);	vertex_buffer_data.push_back(v);
	v.pos.Set(-0.5f * length, -0.5f * length, -0.5f * length);	v.color = color; v.normal.Set(0, 0, 1);	vertex_buffer_data.push_back(v);

	//Bottom
	v.pos.Set(0.5f * length, -0.5f * length, 0.5f * length);	v.color = color; v.normal.Set(0, -1, 0);	vertex_buffer_data.push_back(v);
	v.pos.Set(-0.5f * length, -0.5f * length, 0.5f * length);	v.color = color; v.normal.Set(0, -1, 0);	vertex_buffer_data.push_back(v);
	v.pos.Set(-0.5f * length, -0.5f * length, -0.5f * length);	v.color = color; v.normal.Set(0, -1, 0);	vertex_buffer_data.push_back(v);

	v.pos.Set(0.5f * length, -0.5f * length, 0.5f * length);	v.color = color; v.normal.Set(0, -1, 0);	vertex_buffer_data.push_back(v);
	v.pos.Set(-0.5f * length, -0.5f * length, -0.5f * length);	v.color = color; v.normal.Set(0, -1, 0);	vertex_buffer_data.push_back(v);
	v.pos.Set(0.5f * length, -0.5f * length, -0.5f * length);	v.color = color; v.normal.Set(0, -1, 0);	vertex_buffer_data.push_back(v);
	
	//Front
	v.pos.Set(-0.5f * length, 0.5f * length, 0.5f * length);	v.color = color; v.normal.Set(0, 0, 1); v.texCoord.Set(0, 1);	vertex_buffer_data.push_back(v);
	v.pos.Set(-0.5f * length, -0.5f * length, 0.5f * length);	v.color = color; v.normal.Set(0, 0, 1); v.texCoord.Set(0, 0);	vertex_buffer_data.push_back(v);
	v.pos.Set(0.5f * length, -0.5f * length, 0.5f * length);	v.color = color; v.normal.Set(0, 0, 1); v.texCoord.Set(1, 0);	vertex_buffer_data.push_back(v);

	v.pos.Set(0.5f * length, 0.5f * length, 0.5f * length);		v.color = color; v.normal.Set(0, 0, 1); v.texCoord.Set(1, 1);	vertex_buffer_data.push_back(v);
	v.pos.Set(-0.5f * length, 0.5f * length, 0.5f * length);	v.color = color; v.normal.Set(0, 0, 1); v.texCoord.Set(0, 1);	vertex_buffer_data.push_back(v);
	v.pos.Set(0.5f * length, -0.5f * length, 0.5f * length);	v.color = color; v.normal.Set(0, 0, 1); v.texCoord.Set(0, 0);	vertex_buffer_data.push_back(v);
	
	//Right
	v.pos.Set(0.5f * length, 0.5f * length, 0.5f * length);		v.color = color; v.normal.Set(0, 0, 1);	vertex_buffer_data.push_back(v);
	v.pos.Set(0.5f * length, -0.5f * length, -0.5f * length);	v.color = color; v.normal.Set(0, 0, 1);	vertex_buffer_data.push_back(v);
	v.pos.Set(0.5f * length, 0.5f * length, -0.5f * length);	v.color = color; v.normal.Set(0, 0, 1);	vertex_buffer_data.push_back(v);

	v.pos.Set(0.5f * length, -0.5f * length, -0.5f * length);	v.color = color; v.normal.Set(0, 0, 1);	vertex_buffer_data.push_back(v);
	v.pos.Set(0.5f * length, 0.5f * length, 0.5f * length);		v.color = color; v.normal.Set(0, 0, 1);	vertex_buffer_data.push_back(v);
	v.pos.Set(0.5f * length, -0.5f * length, 0.5f * length);	v.color = color; v.normal.Set(0, 0, 1);	vertex_buffer_data.push_back(v);

	//Top
	v.pos.Set(0.5f * length, 0.5f * length, 0.5f * length);		v.color = color; v.normal.Set(0, 0, 1);	vertex_buffer_data.push_back(v);
	v.pos.Set(-0.5f * length, 0.5f * length, -0.5f * length);	v.color = color; v.normal.Set(0, 0, 1);	vertex_buffer_data.push_back(v);
	v.pos.Set(-0.5f * length, 0.5f * length, 0.5f * length);	v.color = color; v.normal.Set(0, 0, 1);	vertex_buffer_data.push_back(v);
		
	v.pos.Set(0.5f * length, 0.5f * length, 0.5f * length);		v.color = color; v.normal.Set(0, 0, 1);	vertex_buffer_data.push_back(v);
	v.pos.Set(0.5f * length, 0.5f * length, -0.5f * length);	v.color = color; v.normal.Set(0, 0, 1);	vertex_buffer_data.push_back(v);
	v.pos.Set(-0.5f * length, 0.5f * length, -0.5f * length);	v.color = color; v.normal.Set(0, 0, 1);	vertex_buffer_data.push_back(v);

	
	
	

	for (unsigned i = 0; i < 36; ++i)
	{
		index_buffer_data.push_back(i);
	}

	Mesh *mesh = new Mesh(meshName);

	glBindBuffer(GL_ARRAY_BUFFER, mesh->vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, vertex_buffer_data.size() * sizeof(Vertex), &vertex_buffer_data[0], GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh->indexBuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, index_buffer_data.size() * sizeof(GLuint), &index_buffer_data[0], GL_STATIC_DRAW);

	mesh->indexSize = index_buffer_data.size();
	mesh->mode = Mesh::DRAW_TRIANGLES;

	return mesh;
}

Mesh* MeshBuilder::GenerateCircle(const std::string& meshName, Color color, unsigned numSlices, float radius)
{
	Vertex v;
	std::vector<Vertex> vertex_buffer_data;
	std::vector<GLuint> index_buffer_data;

	float radianPerSlice = Math::TWO_PI / numSlices;

	for (unsigned slice = 0; slice < numSlices + 1; ++slice)
	{
		float theta = slice * radianPerSlice;
		float x = radius * cosf(theta);
		float y = 0;
		float z = radius * sinf(theta);

		v.pos.Set(x, y, z);		v.color = color;	v.normal.Set(0, 0, 1);	vertex_buffer_data.push_back(v);
		v.pos.Set(0, 0, 0);		v.color = color;	v.normal.Set(0, 0, 1);	vertex_buffer_data.push_back(v);
	}
	for (unsigned slice = 0; slice < numSlices + 1; ++slice)
	{
		index_buffer_data.push_back(slice * 2 + 0);
		index_buffer_data.push_back(slice * 2 + 1);
	}

	Mesh* mesh = new Mesh(meshName);

	glBindBuffer(GL_ARRAY_BUFFER, mesh->vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, vertex_buffer_data.size() * sizeof(Vertex), &vertex_buffer_data[0], GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh->indexBuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, index_buffer_data.size() * sizeof(GLuint), &index_buffer_data[0], GL_STATIC_DRAW);

	mesh->indexSize = index_buffer_data.size();
	mesh->mode = Mesh::DRAW_TRIANGLE_STRIP;

	return mesh;
}

//undone
Mesh* MeshBuilder::GenerateRing(const std::string& meshName, Color color, unsigned numSlices, float radius)
{
	Vertex v;
	std::vector<Vertex> vertex_buffer_data;
	std::vector<GLuint> index_buffer_data;

	float radianPerSlice = Math::TWO_PI / numSlices;

	v.pos.Set(0.f, 0.f, 0.f);		v.color = color;	vertex_buffer_data.push_back(v);
	for (unsigned slice = 0; slice < numSlices + 1; ++slice)
	{
		float theta = slice * radianPerSlice; // every iteration +
		float x = radius * cosf(theta);
		float y = 0;
		float z = radius * sinf(theta);

		v.pos.Set(x, y, z);	v.color = color;	vertex_buffer_data.push_back(v);
	}
	for (unsigned slice = 0; slice < numSlices + 1; ++slice)
	{
		index_buffer_data.push_back(slice + 1);
		index_buffer_data.push_back(0);
	}

	Mesh* mesh = new Mesh(meshName);

	glBindBuffer(GL_ARRAY_BUFFER, mesh->vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, vertex_buffer_data.size() * sizeof(Vertex), &vertex_buffer_data[0], GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh->indexBuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, index_buffer_data.size() * sizeof(GLuint), &index_buffer_data[0], GL_STATIC_DRAW);

	mesh->indexSize = index_buffer_data.size();
	mesh->mode = Mesh::DRAW_TRIANGLE_STRIP;

	return mesh;
}

Mesh* MeshBuilder::GenerateCylinder(const std::string& meshName, Color color, unsigned numSlices, float radius, float height)
{
	Vertex v;
	std::vector<Vertex> vertex_buffer_data;
	std::vector<GLuint> index_buffer_data;

	float radianPerSlice = Math::TWO_PI / numSlices;

	//bottom
	unsigned startIndex = 0;
	for (unsigned slice = 0; slice < numSlices + 1; ++slice)
	{
		float theta = slice * radianPerSlice;
		float x = radius * cosf(theta);
		float y = -height * 0.5f;
		float z = radius * sinf(theta);

		v.pos.Set(x, y, z);		v.color = color;	v.normal.Set(0, -1, 0);	vertex_buffer_data.push_back(v);
		v.pos.Set(0, y, 0);		v.color = color;	v.normal.Set(0, -1, 0); vertex_buffer_data.push_back(v);
	}
	for (unsigned slice = 0; slice < numSlices + 1; ++slice)
	{
		index_buffer_data.push_back(startIndex + slice * 2 + 1);
		index_buffer_data.push_back(startIndex + slice * 2 + 0);
	}
	startIndex = vertex_buffer_data.size();
	//curve
	for (unsigned slice = 0; slice < numSlices + 1; ++slice)
	{
		float theta = slice * radianPerSlice;
		float x = radius * cosf(theta);
		float z = radius * sinf(theta);

		v.pos.Set(x, -height * 0.5f, z);		v.color = color;	v.normal.Set(x, 0, z);	vertex_buffer_data.push_back(v);
		v.pos.Set(x, height * 0.5f, z);		v.color = color;	v.normal.Set(x, 0, z);	vertex_buffer_data.push_back(v);
	}
	for (unsigned slice = 0; slice < numSlices + 1; ++slice)
	{
		index_buffer_data.push_back(startIndex + slice * 2 + 0);
		index_buffer_data.push_back(startIndex + slice * 2 + 1);
	}
	startIndex = vertex_buffer_data.size();
	//top
	for (unsigned slice = 0; slice < numSlices + 1; ++slice)
	{
		float theta = slice * radianPerSlice;
		float x = radius * cosf(theta);
		float y = height * 0.5f;
		float z = radius * sinf(theta);

		v.pos.Set(x, y, z);		v.color = color;	v.normal.Set(0, 1, 0);	vertex_buffer_data.push_back(v);
		v.pos.Set(0, y, 0);		v.color = color;	v.normal.Set(0, 1, 0);	vertex_buffer_data.push_back(v);
	}
	for (unsigned slice = 0; slice < numSlices + 1; ++slice)
	{
		index_buffer_data.push_back(startIndex + slice * 2 + 0);
		index_buffer_data.push_back(startIndex + slice * 2 + 1);
	}
	

	Mesh* mesh = new Mesh(meshName);

	glBindBuffer(GL_ARRAY_BUFFER, mesh->vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, vertex_buffer_data.size() * sizeof(Vertex), &vertex_buffer_data[0], GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh->indexBuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, index_buffer_data.size() * sizeof(GLuint), &index_buffer_data[0], GL_STATIC_DRAW);

	mesh->indexSize = index_buffer_data.size();
	mesh->mode = Mesh::DRAW_TRIANGLE_STRIP;

	return mesh;
}

Mesh* MeshBuilder::GenerateCone(const std::string& meshName, Color color, unsigned numSlices, float radius, float height)
{
	Vertex v;
	std::vector<Vertex> vertex_buffer_data;
	std::vector<GLuint> index_buffer_data;

	float radianPerSlice = Math::TWO_PI / numSlices;

	//bottom
	unsigned startIndex = 0;
	for (unsigned slice = 0; slice < numSlices + 1; ++slice)
	{
		float theta = slice * radianPerSlice;
		float x = radius * cosf(theta);
		float y = -height * 0.5f;
		float z = radius * sinf(theta);

		v.pos.Set(x, y, z);		v.color = color;	v.normal.Set(0, -1, 0);	vertex_buffer_data.push_back(v);
		v.pos.Set(0, y, 0);		v.color = color;	v.normal.Set(0, -1, 0); vertex_buffer_data.push_back(v);
	}
	for (unsigned slice = 0; slice < numSlices + 1; ++slice)
	{
		index_buffer_data.push_back(startIndex + slice * 2 + 1);
		index_buffer_data.push_back(startIndex + slice * 2 + 0);
	}
	startIndex = vertex_buffer_data.size();
	//curve
	for (unsigned slice = 0; slice < numSlices + 1; ++slice)
	{
		float theta = slice * radianPerSlice;
		float x = cosf(theta);
		float z = sinf(theta);
	
		v.pos.Set(radius * x, -height * 0.5f, radius * z);
		v.color = color;	
		if (numSlices != 4)
			v.normal.Set(height * x, radius, height * z);
		else
			v.normal.Set(0, 1, 0);

		vertex_buffer_data.push_back(v);

		v.pos.Set(0, height * 0.5f, 0);
		v.color = color;	

		if (numSlices != 4)
			v.normal.Set(height * x, radius, height * z);
		else
			v.normal.Set(0, 1, 0);

		vertex_buffer_data.push_back(v);
	}
	for (unsigned slice = 0; slice < numSlices + 1; ++slice)
	{
		index_buffer_data.push_back(startIndex + slice * 2 + 0);
		index_buffer_data.push_back(startIndex + slice * 2 + 1);
	}

	Mesh* mesh = new Mesh(meshName);

	glBindBuffer(GL_ARRAY_BUFFER, mesh->vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, vertex_buffer_data.size() * sizeof(Vertex), &vertex_buffer_data[0], GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh->indexBuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, index_buffer_data.size() * sizeof(GLuint), &index_buffer_data[0], GL_STATIC_DRAW);

	mesh->indexSize = index_buffer_data.size();
	mesh->mode = Mesh::DRAW_TRIANGLE_STRIP;

	return mesh;
}

Mesh* MeshBuilder::GenerateSphere(const std::string& meshName, Color color, unsigned numStacks, unsigned numSlices, float radius)
{
	Vertex v;
	std::vector<Vertex> vertex_buffer_data;
	std::vector<GLuint> index_buffer_data;

	float degreePerStack = 180.f / numStacks;
	float degreePerSlice = 360.f / numSlices;

	for (unsigned stack = 0; stack < numStacks + 1; ++stack)
	{
		float phi = -90.f + stack * degreePerStack;
		for (unsigned slice = 0; slice < numSlices + 1; ++slice)
		{
			float theta = slice * degreePerSlice;
			float x = cosf(Math::DegreeToRadian(phi)) * cosf(Math::DegreeToRadian(theta));
			float y = sinf(Math::DegreeToRadian(phi));
			float z = cosf(Math::DegreeToRadian(phi)) * sinf(Math::DegreeToRadian(theta));

			v.pos.Set(radius * x, radius * y, radius * z);
			v.color = color; 
			v.normal.Set(radius * x, radius * y, radius * z);
			//v.texCoord.Set(slice - 1, stack - 1);
			vertex_buffer_data.push_back(v);
		}
	}
	for (unsigned stack = 0; stack < numStacks; ++stack)
	{
		for (unsigned slice = 0; slice < numSlices + 1; ++slice)
		{
			index_buffer_data.push_back(stack * (numSlices + 1) + slice);
			index_buffer_data.push_back((stack + 1) * (numSlices + 1) + slice);
		}
	}

	Mesh* mesh = new Mesh(meshName);

	glBindBuffer(GL_ARRAY_BUFFER, mesh->vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, vertex_buffer_data.size() * sizeof(Vertex), &vertex_buffer_data[0], GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh->indexBuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, index_buffer_data.size() * sizeof(GLuint), &index_buffer_data[0], GL_STATIC_DRAW);

	mesh->indexSize = index_buffer_data.size();
	mesh->mode = Mesh::DRAW_TRIANGLE_STRIP;

	return mesh;
}

Mesh* MeshBuilder::GenerateHemisphere(const std::string& meshName, Color color, unsigned numStacks, unsigned numSlices, float radius)
{
	Vertex v;
	std::vector<Vertex> vertex_buffer_data;
	std::vector<GLuint> index_buffer_data;

	float degreePerStack = 90.f / numStacks;
	float degreePerSlice = 360.f / numSlices;


	//bottom
	unsigned startIndex;
	startIndex = vertex_buffer_data.size();
	for (unsigned slice = 0; slice < numSlices + 1; ++slice)
	{
		float theta = slice * degreePerSlice;
		float x = radius * cosf(Math::DegreeToRadian(theta));
		float z = radius * sinf(Math::DegreeToRadian(theta));

		v.pos.Set(x, 0, z);		v.color = color;	v.normal.Set(0, -1, 0);	vertex_buffer_data.push_back(v);
		v.pos.Set(0, 0, 0);		v.color = color;	v.normal.Set(0, -1, 0); vertex_buffer_data.push_back(v);
	}
	for (unsigned slice = 0; slice < numSlices + 1; ++slice)
	{
		index_buffer_data.push_back(startIndex + slice * 2 + 1);
		index_buffer_data.push_back(startIndex + slice * 2 + 0);
	}

	//Curve
	startIndex = vertex_buffer_data.size();
	for (unsigned stack = 0; stack < numStacks + 1; ++stack)
	{
		float phi = 0.f + stack * degreePerStack;
		for (unsigned slice = 0; slice < numSlices + 1; ++slice)
		{
			float theta = slice * degreePerSlice;
			float x = radius * cosf(Math::DegreeToRadian(phi)) * cosf(Math::DegreeToRadian(theta));
			float y = radius * sinf(Math::DegreeToRadian(phi));
			float z = radius * cosf(Math::DegreeToRadian(phi)) * sinf(Math::DegreeToRadian(theta));

			v.pos.Set(x, y, z);		v.color = color; v.normal.Set(x, y, z);	vertex_buffer_data.push_back(v);
		}
	}
	for (unsigned stack = 0; stack < numStacks; ++stack)
	{
		for (unsigned slice = 0; slice < numSlices + 1; ++slice)
		{
			index_buffer_data.push_back(startIndex + stack * (numSlices + 1) + slice);
			index_buffer_data.push_back(startIndex + (stack + 1) * (numSlices + 1) + slice);
		}
	}

	Mesh* mesh = new Mesh(meshName);

	glBindBuffer(GL_ARRAY_BUFFER, mesh->vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, vertex_buffer_data.size() * sizeof(Vertex), &vertex_buffer_data[0], GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh->indexBuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, index_buffer_data.size() * sizeof(GLuint), &index_buffer_data[0], GL_STATIC_DRAW);

	mesh->indexSize = index_buffer_data.size();
	mesh->mode = Mesh::DRAW_TRIANGLE_STRIP;

	return mesh;
}

Mesh* MeshBuilder::GenerateTorus2(const std::string& meshName, Color color, unsigned numStack, unsigned numSlice, float outerR, float innerR) 
{
	Vertex v;
	std::vector<Vertex> vertex_buffer_data;
	std::vector<GLuint> index_buffer_data;

	float radianPerStack = Math::TWO_PI / numStack;
	float radianPerSlice = Math::TWO_PI / numSlice;
	float x1, z1; //y1 is always zero
	float x2, y2, z2;
	for(unsigned stack = 0; stack < numStack + 1; stack++)
	{
		for(unsigned slice = 0; slice < numSlice + 1; slice++) 
		{
			z1 = outerR * cos(stack * radianPerStack);x1 = outerR * sin(stack * radianPerStack);
			z2 = (outerR + innerR * cos(slice * radianPerSlice)) * cos(stack * radianPerStack);
			y2 = innerR * sin(slice * radianPerSlice);
			x2 = (outerR + innerR * cos(slice * radianPerSlice)) * sin(stack * radianPerStack);

			v.pos.Set(x2, y2, z2);	v.color = color; v.normal.Set(x2 - x1, y2, z2 - z1);	vertex_buffer_data.push_back(v);
		}
	}for (unsigned stack = 0; stack < numStack; stack++) 
	{ 
		for (unsigned slice = 0; slice < numSlice + 1; slice++)
		{ 
		index_buffer_data.push_back((numSlice + 1) * stack + slice + 0);
		index_buffer_data.push_back((numSlice + 1) * (stack + 1) + slice + 0);
		} 
	}

	Mesh* mesh = new Mesh(meshName);

	glBindBuffer(GL_ARRAY_BUFFER, mesh->vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, vertex_buffer_data.size() * sizeof(Vertex), &vertex_buffer_data[0], GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh->indexBuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, index_buffer_data.size() * sizeof(GLuint), &index_buffer_data[0], GL_STATIC_DRAW);

	mesh->indexSize = index_buffer_data.size();
	mesh->mode = Mesh::DRAW_TRIANGLE_STRIP;

	return mesh;
}

Mesh* MeshBuilder::GenerateQuarterTorus2(const std::string& meshName, Color color, unsigned numStack, unsigned numSlice, float outerR, float innerR)
{
	Vertex v;
	std::vector<Vertex> vertex_buffer_data;
	std::vector<GLuint> index_buffer_data;

	float radianPerStack = Math::HALF_PI / numStack;
	float radianPerSlice = Math::TWO_PI / numSlice;
	float x1, z1; //y1 is always zero
	float x2, y2, z2;
	for (unsigned stack = 0; stack < numStack + 1; stack++)
	{
		for (unsigned slice = 0; slice < numSlice + 1; slice++)
		{
			z1 = outerR * cos(stack * radianPerStack); x1 = outerR * sin(stack * radianPerStack);
			z2 = (outerR + innerR * cos(slice * radianPerSlice)) * cos(stack * radianPerStack);
			y2 = innerR * sin(slice * radianPerSlice);
			x2 = (outerR + innerR * cos(slice * radianPerSlice)) * sin(stack * radianPerStack);

			v.pos.Set(x2, y2, z2);	v.color = color; v.normal.Set(x2 - x1, y2, z2 - z1);	vertex_buffer_data.push_back(v);
		}
	}for (unsigned stack = 0; stack < numStack; stack++)
	{
		for (unsigned slice = 0; slice < numSlice + 1; slice++)
		{
			index_buffer_data.push_back((numSlice + 1) * stack + slice + 0);
			index_buffer_data.push_back((numSlice + 1) * (stack + 1) + slice + 0);
		}
	}

	Mesh* mesh = new Mesh(meshName);

	glBindBuffer(GL_ARRAY_BUFFER, mesh->vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, vertex_buffer_data.size() * sizeof(Vertex), &vertex_buffer_data[0], GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh->indexBuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, index_buffer_data.size() * sizeof(GLuint), &index_buffer_data[0], GL_STATIC_DRAW);

	mesh->indexSize = index_buffer_data.size();
	mesh->mode = Mesh::DRAW_TRIANGLE_STRIP;

	return mesh;
}

Mesh* MeshBuilder::GenerateOBJ(const std::string& meshName, const std::string& file_path)
{
	//Read vertices, texcoords & normals from OBJ
	std::vector<Position> vertices;
	std::vector<TexCoord> uvs;
	std::vector<Vector3> normals;
	bool success = LoadOBJ(file_path.c_str(), vertices, uvs, normals);
	if (!success)
		return NULL;
	//Index the vertices, texcoords & normals properly
	std::vector<Vertex> vertex_buffer_data;
	std::vector<GLuint> index_buffer_data;
	IndexVBO(vertices, uvs, normals, index_buffer_data, vertex_buffer_data);
	//Create the mesh and call glBindBuffer, glBufferData
	//Use triangle list and remember to set index size

	Mesh* mesh = new Mesh(meshName);

	glBindBuffer(GL_ARRAY_BUFFER, mesh->vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, vertex_buffer_data.size() * sizeof(Vertex), &vertex_buffer_data[0], GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh->indexBuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, index_buffer_data.size() * sizeof(GLuint), &index_buffer_data[0], GL_STATIC_DRAW);

	mesh->indexSize = index_buffer_data.size();
	mesh->mode = Mesh::DRAW_TRIANGLES;

	return mesh;
}

Mesh* MeshBuilder::GenerateText(const std::string& meshName, unsigned numRow, unsigned numCol)
{
	Vertex v;
	std::vector<Vertex> vertex_buffer_data;
	std::vector<GLuint> index_buffer_data;

	float width = 1.f / numCol;
	float height = 1.f / numRow;
	unsigned offset = 0;
	for (unsigned row = 0; row < numRow; ++row)
	{
		for (unsigned col = 0; col < numCol; ++col)
		{
			//example (1.f/16,11.f/16)
			//Task: Add 4 vertices into vertex_buffer_data
			v.pos.Set(0.5f, 0.5f, 0.f);	v.normal.Set(0, 0, 1);
			v.texCoord.Set((col + 1.0f) * width, (numRow - row) * height); //v0
			vertex_buffer_data.push_back(v);
			v.pos.Set(-0.5f, 0.5f, 0.f); v.normal.Set(0, 0, 1);
			v.texCoord.Set(col * width, (numRow - row) * height); //v1
			vertex_buffer_data.push_back(v);
			v.pos.Set(-0.5f, -0.5f, 0.f);	v.normal.Set(0, 0, 1);
			v.texCoord.Set(col * width, (numRow - 1.0f - row) * height); //v2
			vertex_buffer_data.push_back(v);
			v.pos.Set(0.5f, -0.5f, 0.f); v.normal.Set(0, 0, 1);
			v.texCoord.Set((col + 1.0f) * width, (numRow - 1.0f - row) * height); //v3
			vertex_buffer_data.push_back(v);

			//Task: Add 6 indices into index_buffer_data
			//tri1
			index_buffer_data.push_back(offset + 0);
			index_buffer_data.push_back(offset + 1);
			index_buffer_data.push_back(offset + 2);
			//tri2
			index_buffer_data.push_back(offset + 0);
			index_buffer_data.push_back(offset + 2);
			index_buffer_data.push_back(offset + 3);
			offset += 4;
		}
	}

	Mesh* mesh = new Mesh(meshName);

	glBindBuffer(GL_ARRAY_BUFFER, mesh->vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, vertex_buffer_data.size() * sizeof(Vertex), &vertex_buffer_data[0], GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh->indexBuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, index_buffer_data.size() * sizeof(GLuint), &index_buffer_data[0], GL_STATIC_DRAW);

	mesh->indexSize = index_buffer_data.size();
	mesh->mode = Mesh::DRAW_TRIANGLES;

	return mesh;
}

Mesh* MeshBuilder::GenerateOBJMTL(const std::string& meshName, const std::string& file_path, const std::string& mtl_path)
{
	//Read vertices, texcoords & normals from OBJ
	std::vector<Position> vertices;
	std::vector<TexCoord> uvs;
	std::vector<Vector3> normals;
	std::vector<Material> materials;
	bool success = LoadOBJMTL(file_path.c_str(), mtl_path.c_str(), vertices, uvs, normals, materials);
	if (!success)
		return NULL;
	//Index the vertices, texcoords & normals properly
	std::vector<Vertex> vertex_buffer_data;
	std::vector<GLuint> index_buffer_data;
	IndexVBO(vertices, uvs, normals, index_buffer_data, vertex_buffer_data);

	Mesh* mesh = new Mesh(meshName);
	for (Material& material : materials)
		mesh->materials.push_back(material);

	glBindBuffer(GL_ARRAY_BUFFER, mesh->vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, vertex_buffer_data.size() * sizeof(Vertex), &vertex_buffer_data[0], GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh->indexBuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, index_buffer_data.size() * sizeof(GLuint), &index_buffer_data[0], GL_STATIC_DRAW);

	mesh->indexSize = index_buffer_data.size();
	mesh->mode = Mesh::DRAW_TRIANGLES;

	return mesh;
}



