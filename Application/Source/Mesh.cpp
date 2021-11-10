
#include "Mesh.h"
#include "GL\glew.h"

#include "Vertex.h"

/******************************************************************************/
/*!
\brief
Default constructor - generate VBO/IBO here

\param meshName - name of mesh
*/
/******************************************************************************/
Mesh::Mesh(const std::string &meshName)
	: name(meshName)
	, mode(DRAW_TRIANGLES)


{
	glGenBuffers(1, &vertexBuffer);
	glGenBuffers(1, &indexBuffer);
}

/******************************************************************************/
/*!
\brief
Destructor - delete VBO/IBO here
*/
/******************************************************************************/
Mesh::~Mesh()
{
	glDeleteBuffers(1, &vertexBuffer);
	glDeleteBuffers(1, &indexBuffer);
}

/******************************************************************************/
/*!
\brief
OpenGL render code
*/
/******************************************************************************/
void Mesh::Render()
{
	glEnableVertexAttribArray(0);	// 1st attribute buffer : vertices
	glEnableVertexAttribArray(1);	// 2nd attribute buffer : colours

	glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)sizeof(Position));
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer);
	if (mode == DRAW_LINES)
		glDrawElements(GL_LINES, 6, GL_UNSIGNED_INT, 0);
	else if (mode == DRAW_TRIANGLE_STRIP)
		glDrawElements(GL_TRIANGLE_STRIP, 6, GL_UNSIGNED_INT, 0);
	else
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
}