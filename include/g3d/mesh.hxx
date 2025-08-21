#pragma once

#include<g3d/renderable.hxx>

struct Mesh : public Renderable {
	unsigned int VAO=0; // Buffer array (Vertices data)
	size_t indexCount=0;

	void render() override;
};


namespace Meshes {

Mesh* createCube(int w, int h, int d);

}
