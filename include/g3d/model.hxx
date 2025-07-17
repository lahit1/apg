#pragma once

#include<glad/glad.h>
#include<GLFW/glfw3.h>
#include<g3d/renderable.hxx>
#include<g3d/material.hxx>
#include<glm/glm.hpp>

#include<istream>

struct Model : public Renderable {
	unsigned int VAO; // Buffer array (Vertices data)
	size_t indexCount;

	Material material;

	glm::mat4 matrix = glm::mat4(1);
};


namespace Models {

Model* createCube(int w, int h, int d);

Model* loadObjModel(std::istream in);

}
