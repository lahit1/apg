#pragma once

#include<glad/glad.h>
#include<GLFW/glfw3.h>
#include<g3d/renderable.hxx>
#include<g3d/material.hxx>
#include<glm/glm.hpp>

#include<istream>

struct Mesh : public Renderable {
	unsigned int VAO=0; // Buffer array (Vertices data)
	size_t indexCount=0;

	Material material;

	glm::mat4 matrix = glm::mat4(1);
};


namespace Meshes {

Mesh* createCube(int w, int h, int d);

Mesh* loadObjMesh(std::istream* in);
Mesh* loadObjTrianglesMesh(std::istream* in);

}
