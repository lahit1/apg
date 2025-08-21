#include<cstdio>
#include<vector>
#include<array>
#include <unistd.h>
#include <limits.h>
#include <algorithm>

#include<glad/glad.h>
#include<GLFW/glfw3.h>

#include<g3d/renderable.hxx>
#include<g3d/mesh.hxx>
#include<g3d/vertex.hxx>

void Mesh::render() {
	glBindVertexArray(VAO);
	glDrawElements(GL_TRIANGLES, indexCount, GL_UNSIGNED_INT, 0);
}

namespace Meshes {

std::shared_ptr<Mesh> createCube(int w, int h, int d) {

	std::vector<Vertex> vertices = {
		{{w/2.f, h/2.f, d/2.f}, {0, 1, 0}, {0,0}, {1,1,1,1}},
		{{-w/2.f, h/2.f, d/2.f}, {0, 1, 0}, {0,0}, {0,1,0,1}},
		{{w/2.f, h/2.f, -d/2.f}, {0, 1, 0}, {0,0}, {1,0,0,1}},
		{{-w/2.f, h/2.f, -d/2.f}, {0, 1, 0}, {0,0}, {0,1,0,1}},

		{{w/2.f, -h/2.f, d/2.f}, {0, -1, 0}, {0,0}, {0,0,1,1}},
                {{-w/2.f, -h/2.f, d/2.f}, {0, -1, 0}, {0,0}, {1,0,0,1}},
                {{w/2.f, -h/2.f, -d/2.f}, {0, -1, 0}, {0,0}, {0,0,1,1}},
                {{-w/2.f, -h/2.f, -d/2.f}, {0, -1, 0}, {0,0}, {1,0,0,1}}
	};

	int indices[] = {
			0, 4, 1, // front
			1, 5, 4,

			0, 1, 2, // top
			2, 3, 1,

			2, 6, 3, // back
			3, 7, 6,

			0, 4, 2, // right
			2, 6, 4,

			4, 5, 6, // bottom
			6, 7, 5,

			3, 7, 1, // left
			1, 5, 3
			};

	unsigned int VBO=0, EBO=0;

	std::shared_ptr<Mesh> ret = std::make_shared<Mesh>();
	glGenVertexArrays(1, &ret->VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	glBindVertexArray(ret->VAO); // Use the buffer

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * vertices.size(), vertices.data(), GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	ret->indexCount = sizeof(indices) / sizeof(int);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);


	// Set pointer
	glVertexAttribPointer(0, // layout = 0
				3,  // vec3
				GL_FLOAT,
				GL_FALSE,
				sizeof(Vertex), // sizeof(Vertex)
				(void*)offsetof(Vertex, pos)); // ofset of position per vertex

	glVertexAttribPointer(1, // layout = 1
                                3,  // vec3
                                GL_FLOAT,
                                GL_FALSE,
                                sizeof(Vertex), // sizeof(Vertex)
                                (void*)offsetof(Vertex, norm)); // ofset of normal per vertex

	glVertexAttribPointer(2, // layout = 2
                                2,  // vec2
                                GL_FLOAT,
                                GL_FALSE,
                                sizeof(Vertex), // sizeof(Vertex)
                                (void*)offsetof(Vertex, texCoord)); // ofset of normal per vertex

	glVertexAttribPointer(3, // layout = 3
                                4,  // vec2
                                GL_FLOAT,
                                GL_FALSE,
                                sizeof(Vertex), // sizeof(Vertex)
                                (void*)offsetof(Vertex, color)); // ofset of normal per vertex

	glEnableVertexAttribArray(0);
        glEnableVertexAttribArray(1);
        glEnableVertexAttribArray(2);
        glEnableVertexAttribArray(3);

	glBindVertexArray(0);

	return ret;
}

}

