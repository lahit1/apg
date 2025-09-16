#pragma once

#include<memory>
#include<ape/g3d/renderable.hxx>
#include<glm/glm.hpp>

struct Mesh : public Renderable {
	unsigned int VAO=0; // Buffer array (Vertices data)
	size_t indexCount=0;
	glm::mat4 matrix = glm::mat4(1);

	void render(std::shared_ptr<Program> pr) override;
};


namespace Meshes {

std::shared_ptr<Mesh> createCube(int w, int h, int d);

}
