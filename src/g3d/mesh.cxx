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

namespace Meshes {

Mesh* createCube(int w, int h, int d) {

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

	Mesh *ret = new Mesh();
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

//	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	return ret;
}

Mesh* loadObjMesh(std::istream* in) {
        char cwd[PATH_MAX];
        getcwd(cwd, sizeof(cwd));

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
                    std::vector<std::string> faceTokens;
                    std::string faceStr;
                    while (in->peek() != '\n' && *in >> faceStr) {
                        faceTokens.push_back(faceStr);
                    }

                    if (faceTokens.size() < 3) continue;

                    // Triangle fan approach: v0-v1-v2, v0-v2-v3, ...
                    for (size_t i = 1; i + 1 < faceTokens.size(); ++i) {
                        std::array<std::string, 3> triStrs = {faceTokens[0], faceTokens[i], faceTokens[i + 1]};
                        for (const auto& token : triStrs) {
                            int posi = 0, texi = 0, nori = 0;
                            size_t firstSlash = token.find('/');
                            size_t secondSlash = token.find('/', firstSlash + 1);

                            posi = std::stoi(token.substr(0, firstSlash)) - 1;

                            if (secondSlash != std::string::npos) {
                                if (secondSlash > firstSlash + 1)
                                    texi = std::stoi(token.substr(firstSlash + 1, secondSlash - firstSlash - 1)) - 1;
                                if (secondSlash + 1 < token.size())
                                    nori = std::stoi(token.substr(secondSlash + 1)) - 1;
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
                    }
                } else {
                        std::getline(*in, str); // satırın geri kalanını atla
                }
        }

        unsigned int VBO=0, EBO=0;

        Mesh *ret = new Mesh();
        glGenVertexArrays(1, &ret->VAO);
        glGenBuffers(1, &VBO);
        glGenBuffers(1, &EBO);

        glBindVertexArray(ret->VAO); // Use the buffer

        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * vertices.size(), vertices.data(), GL_STATIC_DRAW);

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
        ret->indexCount = indices.size();
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

        glEnableVertexAttribArray(0);
        glEnableVertexAttribArray(1);
        glEnableVertexAttribArray(2);

//        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindVertexArray(0);

        return ret;
}



Mesh* loadObjTrianglesMesh(std::istream* in) {
	char cwd[PATH_MAX];
	getcwd(cwd, sizeof(cwd));

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
		    std::vector<std::string> faceTokens;
		    std::string faceStr;
		    while (in->peek() != '\n' && *in >> faceStr) {
		        faceTokens.push_back(faceStr);
		    }
	
		    if (faceTokens.size() < 3) continue;
	
		    // Triangle fan approach: v0-v1-v2, v0-v2-v3, ...
		    for (size_t i = 1; i + 1 < faceTokens.size(); ++i) {
		        std::array<std::string, 3> triStrs = {faceTokens[0], faceTokens[i], faceTokens[i + 1]};
		        for (const auto& token : triStrs) {
		            int posi = 0, texi = 0, nori = 0;
		            size_t firstSlash = token.find('/');
		            size_t secondSlash = token.find('/', firstSlash + 1);
	
		            posi = std::stoi(token.substr(0, firstSlash)) - 1;
	
		            if (secondSlash != std::string::npos) {
		                if (secondSlash > firstSlash + 1)
		                    texi = std::stoi(token.substr(firstSlash + 1, secondSlash - firstSlash - 1)) - 1;
		                if (secondSlash + 1 < token.size())
		                    nori = std::stoi(token.substr(secondSlash + 1)) - 1;
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
		    }
		} else {
		        std::getline(*in, str); // satırın geri kalanını atla
		}
	}

	unsigned int VBO=0, EBO=0;

	Mesh *ret = new Mesh();
        glGenVertexArrays(1, &ret->VAO);
        glGenBuffers(1, &VBO);
        glGenBuffers(1, &EBO);

	glBindVertexArray(ret->VAO); // Use the buffer

        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * vertices.size(), vertices.data(), GL_STATIC_DRAW);

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
        ret->indexCount = indices.size();
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

	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);

//        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindVertexArray(0);

	return ret;
}

}

