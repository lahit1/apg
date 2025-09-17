#include <ape/g3d/model.hxx>
#include <ape/g3d/vertex.hxx>

#include <unistd.h>
#include <algorithm>
#include <fstream>
#include <iostream>
#include <vector>
#include <array>
#include <string>
#include <cstring>
#include <sstream>
#include <unordered_map>

void Model::render(std::shared_ptr<Program> pr) {
	std::shared_ptr<Material> mat = material;
	for(auto ufor : mat->uniforms_f)
		if(ufor.first)
			ufor.second.binder_funcfv(ufor.first, 1, ufor.second.value);

	int i;
	for(auto tex : mat->textures)
		if(tex.first) {
			glUniform1i(tex.first, i);
			tex.second->bind(i++);
		}


	float dt = 1./60; // Debug value

	for(Animation ani: animations) {
		ani.act(dt);
		for(auto bani: ani.boneanimations) {
			auto meshp = namedMeshes.find(bani.first);
			if(meshp == namedMeshes.end()) continue;
			meshp->second->matrix = bani.second.interpolate(ani.current_time);
		}
	}

	for(std::shared_ptr<Mesh> m: meshes) {
		glm::mat4 mmat = m->matrix * matrix;
	        glUniformMatrix4fv(pr->modelULoc_ptr(), 1, GL_FALSE, glm::value_ptr(mmat));
	        glUniformMatrix4fv(pr->normalULoc_ptr(), 1, GL_FALSE, glm::value_ptr(glm::transpose(glm::inverse(mmat))));

		m->render(pr);
	}
}

namespace Models {
std::shared_ptr<Model> loadObjModel(std::istream* in) {
    std::vector<glm::vec3> positions;
    std::vector<glm::vec2> texcoords;
    std::vector<glm::vec3> normals;

    std::vector<Vertex> vertices;
    std::vector<uint32_t> indices;

    auto parseFaceToken = [](const std::string &token, int &posi, int &texi, int &nori) {
        posi = texi = nori = -1;
        size_t firstSlash = token.find('/');
        size_t secondSlash = token.find('/', firstSlash + 1);

        // position
        if (firstSlash != std::string::npos)
            posi = std::stoi(token.substr(0, firstSlash)) - 1;
        else
            posi = std::stoi(token) - 1;

        // texcoord
        if (firstSlash != std::string::npos && firstSlash + 1 < token.size()) {
            if (secondSlash != std::string::npos && secondSlash > firstSlash + 1)
                texi = std::stoi(token.substr(firstSlash + 1, secondSlash - firstSlash - 1)) - 1;
            else
                texi = std::stoi(token.substr(firstSlash + 1)) - 1;
        }

        // normal
        if (secondSlash != std::string::npos && secondSlash + 1 < token.size())
            nori = std::stoi(token.substr(secondSlash + 1)) - 1;
    };

    std::string line;
    while (std::getline(*in, line)) {
        std::istringstream ss(line);
        std::string prefix;
        ss >> prefix;

        if (prefix == "v") {
            float x, y, z; ss >> x >> y >> z;
            positions.emplace_back(x, y, z);
        } else if (prefix == "vt") {
            float u, v; ss >> u >> v;
            texcoords.emplace_back(u, v);
        } else if (prefix == "vn") {
            float x, y, z; ss >> x >> y >> z;
            normals.emplace_back(x, y, z);
        } else if (prefix == "f") {
            std::vector<std::string> tokens;
            std::string token;
            while (ss >> token) tokens.push_back(token);

            for (size_t i = 1; i + 1 < tokens.size(); ++i) {
                std::array<std::string, 3> tri = {tokens[0], tokens[i], tokens[i + 1]};
                for (auto &t : tri) {
                    int pi, ti, ni;
                    parseFaceToken(t, pi, ti, ni);

                    Vertex v;
                    v.pos = (pi >= 0 && pi < (int)positions.size()) ? positions[pi] : glm::vec3(0.0f);
                    v.texCoord = (ti >= 0 && ti < (int)texcoords.size()) ? texcoords[ti] : glm::vec2(0.0f);
		    v.texCoord.y = 1.0f - v.texCoord.y;
                    v.norm = (ni >= 0 && ni < (int)normals.size()) ? normals[ni] : glm::vec3(0.0f);

                    auto it = std::find(vertices.begin(), vertices.end(), v);
                    if (it != vertices.end())
                        indices.push_back((uint32_t)std::distance(vertices.begin(), it));
                    else {
                        vertices.push_back(v);
                        indices.push_back((uint32_t)(vertices.size() - 1));
                    }
                }
            }
        }
    }

    auto model = std::make_shared<Model>();
    auto mesh = std::make_shared<Mesh>();

    unsigned int VBO, EBO;
    glGenVertexArrays(1, &mesh->VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(mesh->VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * vertices.size(), vertices.data(), GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(uint32_t) * indices.size(), indices.data(), GL_STATIC_DRAW);
    mesh->indexCount = indices.size();

    // Attribute locations: pos=0, normal=1, texCoord=2
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, pos));
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, norm));
    glEnableVertexAttribArray(1);

    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, texCoord));
    glEnableVertexAttribArray(2);

    glBindVertexArray(0);

    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);

    model->meshes.push_back(mesh);
    return model;
}
}
