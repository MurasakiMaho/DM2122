#ifndef MESH_BUILDER_H
#define MESH_BUILDER_H

#include "Mesh.h"
#include "Vertex.h"
#include <myMath.h>

class MeshBuilder
{
public:
	static Mesh* GenerateAxes(const std::string &meshName, float lengthX, float lengthY, float lengthZ);
	static Mesh* GenerateQuad(const std::string& meshName, Color color, float length = 1.f);
	static Mesh* GenerateCube(const std::string &meshName, Color color, float length = 1.f);
	static Mesh* GenerateCircle(const std::string& meshName, Color color,unsigned numSlices = 36, float radius = 1.f);
	static Mesh* GenerateRing(const std::string& meshName, Color color, unsigned numSlices = 36, float radius = 1.f);
	static Mesh* GenerateCylinder(const std::string& meshName, Color color, unsigned numSlices = 36, float radius = 1.f, float height = 1.f);
	static Mesh* GenerateCone(const std::string& meshName, Color color, unsigned numSlices, float radius, float height);
	static Mesh* GenerateSphere(const std::string& meshName, Color color, unsigned numStacks = 10, unsigned numSlices = 36, float radius = 1.f);
	static Mesh* GenerateHemisphere(const std::string& meshName, Color color, unsigned numStacks, unsigned numSlices, float radius);
	static Mesh* GenerateTorus2(const std::string& meshName, Color color, unsigned numStack, unsigned numSlice, float outerR, float innerR);
	static Mesh* GenerateQuarterTorus2(const std::string& meshName, Color color, unsigned numStack, unsigned numSlice, float outerR, float innerR);
};

#endif