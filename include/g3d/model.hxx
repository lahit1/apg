#pragma once

#include<glad/glad.h>
#include<GLFW/glfw3.h>
#include<g3d/renderable.hxx>
#include<g3d/material.hxx>
#include<glm/glm.hpp>

#include<istream>


#ifndef VERTEX_ATTR_ARR1

#define VERTEX_ATTR_ARR1 0b1
#define VERTEX_ATTR_ARR2 0b10
#define VERTEX_ATTR_ARR3 0b100
#define VERTEX_ATTR_ARR4 0b1000
#define VERTEX_ATTR_ARR5 0b10000
#define VERTEX_ATTR_ARR6 0b10000
#define VERTEX_ATTR_ARR7 0b10000
#define VERTEX_ATTR_ARR8 0b10000


#endif

struct Model : public Renderable {
	unsigned int VAO; // Buffer array (Vertices data)
	size_t indexCount;

	Material material;

	uint8_t active_vertex_attr_arrs;

	glm::mat4 matrix = glm::mat4(1);
};


namespace Models {

Model* createCube(int w, int h, int d);

Model* loadObjModel(std::istream* in);

}
