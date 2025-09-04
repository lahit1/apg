#pragma once

#include<memory>
#include<ape/g3d/renderable.hxx>

struct Mesh : public Renderable {
	unsigned int VAO=0; // Buffer array (Vertices data)
	size_t indexCount=0;

	void render() override;
};


namespace Meshes {

std::shared_ptr<Mesh> createCube(int w, int h, int d);

}
