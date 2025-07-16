#pragma once

#include<glad/glad.h>
#include<GLFW/glfw3.h>
#include<g3d/renderable.hxx>
#include<g3d/material.hxx>
#include<glm/glm.hpp>

#define mat4 glm::mat4


struct Model : public Renderable {
	unsigned int VAO; // Buffer array (Vertices data)
	size_t indexCount;

	Material material;

	mat4 matrix = mat4(1);
};


namespace Models {

Model* createCube(int w, int h, int d);

}
