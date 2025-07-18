#include<cstdio>
#include<vector>
#include <unistd.h>
#include <limits.h>
#include <algorithm>

#include<glad/glad.h>
#include<GLFW/glfw3.h>

#include<g3d/renderable.hxx>
#include<g3d/model.hxx>
#include<g3d/vertex.hxx>

namespace Models {

Model* createCube(int w, int h, int d) {

	std::vector<Vertex> vertices = {
		{{0.5f, 0.5f, 0.5f}, {0, 1, 0}, {0,0}, {1,1,1,1}},
		{{-0.5f, 0.5f, 0.5f}, {0, 1, 0}, {0,0}, {0,1,0,1}},
		{{0.5f, 0.5f, -0.5f}, {0, 1, 0}, {0,0}, {1,0,0,1}},
		{{-0.5f, 0.5f, -0.5f}, {0, 1, 0}, {0,0}, {0,1,0,1}},

		{{0.5f, -0.5f, 0.5f}, {0, -1, 0}, {0,0}, {0,0,1,1}},
                {{-0.5f, -0.5f, 0.5f}, {0, -1, 0}, {0,0}, {1,0,0,1}},
                {{0.5f, -0.5f, -0.5f}, {0, -1, 0}, {0,0}, {0,0,1,1}},
                {{-0.5f, -0.5f, -0.5f}, {0, -1, 0}, {0,0}, {1,0,0,1}}
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

	unsigned int VBO, EBO;

	Model *ret = new Model();
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

	ret->active_vertex_attr_arrs = VERTEX_ATTR_ARR1 | VERTEX_ATTR_ARR2 | VERTEX_ATTR_ARR3 | VERTEX_ATTR_ARR4;

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	return ret;
}

Model* loadObjModel(std::istream* in) {
	char cwd[PATH_MAX];
	getcwd(cwd, sizeof(cwd));

	Model *m = new Model();
	std::vector<glm::vec3> positions;
	std::vector<glm::vec2> texcoords;
	std::vector<glm::vec3> normals;

	std::vector<Vertex> vertices;
	std::vector<uint32_t> indices;

	std::string str;

	while (*in >> str) {
		if (str == "v") {
			float x, y, z;
			*in >> x >> y >> z;
			positions.emplace_back(x, y, z);
		} else if(str == "vt") {
			float u, v;
			*in >> u >> v;
			texcoords.emplace_back(u, v);
		} else if(str == "vn") {
			float x, y, z;
                        *in >> x >> y >> z;
                        normals.emplace_back(x, y, z);
		} else if(str == "f") {
			std::string faceStr;
			for(int i=0; i < 3; i++) {
				int posi=0, texi=0, nori=0;
				size_t firstSlash = faceStr.find('/');
		                size_t secondSlash = faceStr.find('/', firstSlash + 1);
				posi = std::stoi(faceStr.substr(0, firstSlash)) - 1;

				if(secondSlash != std::string::npos) {
					if (secondSlash > firstSlash + 1)
						texi = std::stoi(faceStr.substr(firstSlash + 1, secondSlash - firstSlash - 1)) - 1;
					if (secondSlash + 1 < faceStr.size())
						nori = std::stoi(faceStr.substr(secondSlash + 1)) - 1;
				}

				Vertex v;
				v.pos = positions[posi];
				v.texCoord = (texi >= 0 && texi < texcoords.size()) ? texcoords[texi] : glm::vec2(0.0f);
				v.norm = (nori >= 0 && nori < normals.size()) ? normals[nori] : glm::vec3(0.0f);

				auto it = std::find(vertices.begin(), vertices.end(), v);
				if (it != vertices.end()) {
					indices.push_back(static_cast<uint32_t>(std::distance(vertices.begin(), it)));
				} else {
					vertices.push_back(v);
					indices.push_back(vertices.size() - 1);
				}
				
			}
		} else {
		        std::getline(*in, str); // satırın geri kalanını atla
		}
	}

	unsigned int VBO, EBO;

	Model *ret = new Model();
        glGenVertexArrays(1, &ret->VAO);
        glGenBuffers(1, &VBO);
        glGenBuffers(1, &EBO);

	glBindVertexArray(ret->VAO); // Use the buffer

        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * vertices.size(), vertices.data(), GL_STATIC_DRAW);

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
        ret->indexCount = sizeof(indices) / sizeof(int);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(uint32_t) * indices.size(), indices.data(), GL_STATIC_DRAW);

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

        ret->active_vertex_attr_arrs = VERTEX_ATTR_ARR1 | VERTEX_ATTR_ARR2 | VERTEX_ATTR_ARR3;

        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindVertexArray(0);

	return m;
}

}
