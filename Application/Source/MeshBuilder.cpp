#include "MeshBuilder.h"
#include <GL\glew.h>

#include "Vertex.h"
#include <vector>

/******************************************************************************/
/*!
\brief
Generate the vertices of a reference Axes; Use red for x-axis, green for y-axis, blue for z-axis
Then generate the VBO/IBO and store them in Mesh object

\param meshName - name of mesh
\param lengthX - x-axis should start at -lengthX / 2 and end at lengthX / 2
\param lengthY - y-axis should start at -lengthY / 2 and end at lengthY / 2
\param lengthZ - z-axis should start at -lengthZ / 2 and end at lengthZ / 2

\return Pointer to mesh storing VBO/IBO of reference axes
*/
/******************************************************************************/
Mesh* MeshBuilder::GenerateAxes(const std::string &meshName, float lengthX, float lengthY, float lengthZ)
{
	Vertex v;
	std::vector<Vertex> vertex_buffer_data;
	std::vector<unsigned> index_buffer_data;

	v.pos.Set(-10 * lengthX, 0.f, 0.f);	v.color.Set(1, 0, 0);	vertex_buffer_data.push_back(v);
	v.pos.Set(10 * lengthX, 0.f, 0.f);	v.color.Set(1, 0, 0);	vertex_buffer_data.push_back(v);
	v.pos.Set(0.f, -10 * lengthY, 0.f);	v.color.Set(0, 1, 0);	vertex_buffer_data.push_back(v);
	v.pos.Set(0.f, 10 * lengthY, 0.f);	v.color.Set(0, 1, 0);	vertex_buffer_data.push_back(v);
	v.pos.Set(0.f, 0.f, -10 * lengthZ);	v.color.Set(0, 0, 1);	vertex_buffer_data.push_back(v);
	v.pos.Set(0.f, 0.f, 10 * lengthZ);	v.color.Set(0, 0, 1);	vertex_buffer_data.push_back(v);

	for (int i = 0; i < 6; i++)
		index_buffer_data.push_back(i);

	Mesh* mesh = new Mesh(meshName);
	glBindBuffer(GL_ARRAY_BUFFER, mesh->vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, vertex_buffer_data.size() *
		sizeof(Vertex), &vertex_buffer_data[0], GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh->indexBuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, index_buffer_data.size()
		* sizeof(GLuint), &index_buffer_data[0], GL_STATIC_DRAW);
	mesh->mode = Mesh::DRAW_LINES;
	mesh->indexSize = index_buffer_data.size();
	return mesh;
}

/******************************************************************************/
/*!
\brief
Generate the vertices of a quad; Use random color for each vertex
Then generate the VBO/IBO and store them in Mesh object

\param meshName - name of mesh
\param lengthX - width of quad
\param lengthY - height of quad

\return Pointer to mesh storing VBO/IBO of quad
*/
/******************************************************************************/
Mesh* MeshBuilder::GenerateQuad(const std::string &meshName, Color color, float lengthX, float lengthY)
{
	Vertex v;
	std::vector<Vertex> vertex_buffer_data;
	std::vector<unsigned> index_buffer_data;

	v.pos.Set(0.5f * lengthX, 0.5f * lengthY, 0.f);		v.color = color;	vertex_buffer_data.push_back(v);
	v.pos.Set(-0.5f * lengthX, 0.5f * lengthY, 0.f);	v.color = color;	vertex_buffer_data.push_back(v);
	v.pos.Set(-0.5f * lengthX, -0.5f * lengthY, 0.f);	v.color = color;	vertex_buffer_data.push_back(v);
	v.pos.Set(0.5f * lengthX, 0.5f * lengthY, 0.f);		v.color = color;	vertex_buffer_data.push_back(v);
	v.pos.Set(-0.5f * lengthX, -0.5f * lengthY, 0.f);	v.color = color;	vertex_buffer_data.push_back(v);
	v.pos.Set(0.5f * lengthX, -0.5f * lengthY, 0.f);	v.color = color;	vertex_buffer_data.push_back(v);

	for (int i = 0; i < 6; i++)
		index_buffer_data.push_back(i);

	Mesh* mesh = new Mesh(meshName);
	glBindBuffer(GL_ARRAY_BUFFER, mesh->vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, vertex_buffer_data.size() *
		sizeof(Vertex), &vertex_buffer_data[0], GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh->indexBuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, index_buffer_data.size()
		* sizeof(GLuint), &index_buffer_data[0], GL_STATIC_DRAW);
	mesh->mode = Mesh::DRAW_TRIANGLES;
	mesh->indexSize = index_buffer_data.size();
	return mesh;
}

/******************************************************************************/
/*!
\brief
Generate the vertices of a cube; Use random color for each vertex
Then generate the VBO/IBO and store them in Mesh object

\param meshName - name of mesh
\param lengthX - width of cube
\param lengthY - height of cube
\param lengthZ - depth of cube

\return Pointer to mesh storing VBO/IBO of cube
*/
/******************************************************************************/
Mesh* MeshBuilder::GenerateCube(const std::string &meshName, Color color, float lengthX, float lengthY, float lengthZ)
{
	Vertex v;
	std::vector<Vertex> vertex_buffer_data;
	std::vector<unsigned> index_buffer_data;

	v.pos.Set(0.5f * lengthX, 0.5f * lengthY, 0.5f * lengthZ);		v.color = color;	vertex_buffer_data.push_back(v);
	v.pos.Set(-0.5f * lengthX, 0.5f * lengthY, 0.5f * lengthZ);	v.color = color;	vertex_buffer_data.push_back(v);
	v.pos.Set(-0.5f * lengthX, -0.5f * lengthY, 0.5f * lengthZ);	v.color = color;	vertex_buffer_data.push_back(v);
	v.pos.Set(0.5f * lengthX, 0.5f * lengthY, 0.5f * lengthZ);		v.color = color;	vertex_buffer_data.push_back(v);
	v.pos.Set(-0.5f * lengthX, -0.5f * lengthY, 0.5f * lengthZ);	v.color = color;	vertex_buffer_data.push_back(v);
	v.pos.Set(0.5f * lengthX, -0.5f * lengthY, 0.5f * lengthZ);	v.color = color;	vertex_buffer_data.push_back(v);

	v.pos.Set(0.5f, 0.5f, -0.5f);		v.color.Set(1, 0, 0);	vertex_buffer_data.push_back(v);
	v.pos.Set(0.5f, 0.5f, 0.5f);	v.color.Set(1, 0, 0);	vertex_buffer_data.push_back(v);
	v.pos.Set(0.5f, -0.5f, 0.5f);	v.color.Set(1, 0, 0);	vertex_buffer_data.push_back(v);
	v.pos.Set(0.5f, 0.5f, -0.5f);		v.color.Set(1, 0, 0);	vertex_buffer_data.push_back(v);
	v.pos.Set(0.5f, 0.5f, -0.5f);	v.color.Set(1, 0, 0);	vertex_buffer_data.push_back(v);
	v.pos.Set(0.5f, -0.5f, -0.5f);	v.color.Set(1, 0, 0);	vertex_buffer_data.push_back(v);

	v.pos.Set(0.5f, 0.5f, 0.f);		v.color.Set(1, 0, 0);	vertex_buffer_data.push_back(v);
	v.pos.Set(-0.5f, 0.5f, 0.f);	v.color.Set(1, 0, 0);	vertex_buffer_data.push_back(v);
	v.pos.Set(-0.5f, -0.5f, 0.f);	v.color.Set(1, 0, 0);	vertex_buffer_data.push_back(v);
	v.pos.Set(0.5f, 0.5f, 0.f);		v.color.Set(1, 0, 0);	vertex_buffer_data.push_back(v);
	v.pos.Set(-0.5f, -0.5f, 0.f);	v.color.Set(1, 0, 0);	vertex_buffer_data.push_back(v);
	v.pos.Set(0.5f, -0.5f, 0.f);	v.color.Set(1, 0, 0);	vertex_buffer_data.push_back(v);

	v.pos.Set(0.5f, 0.5f, 0.f);		v.color.Set(1, 0, 0);	vertex_buffer_data.push_back(v);
	v.pos.Set(-0.5f, 0.5f, 0.f);	v.color.Set(1, 0, 0);	vertex_buffer_data.push_back(v);
	v.pos.Set(-0.5f, -0.5f, 0.f);	v.color.Set(1, 0, 0);	vertex_buffer_data.push_back(v);
	v.pos.Set(0.5f, 0.5f, 0.f);		v.color.Set(1, 0, 0);	vertex_buffer_data.push_back(v);
	v.pos.Set(-0.5f, -0.5f, 0.f);	v.color.Set(1, 0, 0);	vertex_buffer_data.push_back(v);
	v.pos.Set(0.5f, -0.5f, 0.f);	v.color.Set(1, 0, 0);	vertex_buffer_data.push_back(v);

	v.pos.Set(0.5f, 0.5f, 0.f);		v.color.Set(1, 0, 0);	vertex_buffer_data.push_back(v);
	v.pos.Set(-0.5f, 0.5f, 0.f);	v.color.Set(1, 0, 0);	vertex_buffer_data.push_back(v);
	v.pos.Set(-0.5f, -0.5f, 0.f);	v.color.Set(1, 0, 0);	vertex_buffer_data.push_back(v);
	v.pos.Set(0.5f, 0.5f, 0.f);		v.color.Set(1, 0, 0);	vertex_buffer_data.push_back(v);
	v.pos.Set(-0.5f, -0.5f, 0.f);	v.color.Set(1, 0, 0);	vertex_buffer_data.push_back(v);
	v.pos.Set(0.5f, -0.5f, 0.f);	v.color.Set(1, 0, 0);	vertex_buffer_data.push_back(v);

	v.pos.Set(0.5f, 0.5f, 0.f);		v.color.Set(1, 0, 0);	vertex_buffer_data.push_back(v);
	v.pos.Set(-0.5f, 0.5f, 0.f);	v.color.Set(1, 0, 0);	vertex_buffer_data.push_back(v);
	v.pos.Set(-0.5f, -0.5f, 0.f);	v.color.Set(1, 0, 0);	vertex_buffer_data.push_back(v);
	v.pos.Set(0.5f, 0.5f, 0.f);		v.color.Set(1, 0, 0);	vertex_buffer_data.push_back(v);
	v.pos.Set(-0.5f, -0.5f, 0.f);	v.color.Set(1, 0, 0);	vertex_buffer_data.push_back(v);
	v.pos.Set(0.5f, -0.5f, 0.f);	v.color.Set(1, 0, 0);	vertex_buffer_data.push_back(v);

	for (int i = 0; i < 6; i++)
		index_buffer_data.push_back(i);

	Mesh* mesh = new Mesh(meshName); 
	glBindBuffer(GL_ARRAY_BUFFER, mesh->vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, vertex_buffer_data.size() *sizeof(Vertex), &vertex_buffer_data[0], GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh->indexBuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, index_buffer_data.size()* sizeof(GLuint), &index_buffer_data[0], GL_STATIC_DRAW);
	mesh->mode = Mesh::DRAW_TRIANGLES;
	mesh->indexSize = index_buffer_data.size();
	return mesh;
}