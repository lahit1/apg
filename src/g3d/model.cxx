#include <g3d/model.hxx>
#include <g3d/vertex.hxx>

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

void Model::render() {
	Material* mat = material;
	for(auto ufor : mat->uniforms_f)
		if(ufor.first)
			ufor.second.binder_funcfv(ufor.first, 1, ufor.second.value);

	int i;
	for(auto tex : mat->textures)
		if(tex.first) {
			glUniform1i(tex.first, i);
			tex.second.bind(i++);
		}

	for(Mesh* m: meshes)
		m->render();
}

namespace Models {
Model* loadObjModel(std::istream* in) {
    char cwd[PATH_MAX];
    if (getcwd(cwd, sizeof(cwd)) == nullptr) {
        std::cerr << "Warning: Could not get current working directory" << std::endl;
    }

    std::vector<glm::vec3> positions;
    std::vector<glm::vec2> texcoords;
    std::vector<glm::vec3> normals;

    std::vector<Vertex> currentVertices;
    std::vector<uint32_t> currentIndices;
    
    std::unordered_map<std::string, std::pair<std::vector<Vertex>, std::vector<uint32_t>>> meshes;
    std::string currentMeshName = "default";

    std::string str;

    while (*in >> str) {
        if (str == "v") {
            float x, y, z;
            *in >> x >> y >> z;
            positions.emplace_back(x, y, z);
        } else if (str == "vt") {
            float u, v;
            *in >> u >> v;
            texcoords.emplace_back(u, v);
        } else if (str == "vn") {
            float x, y, z;
            *in >> x >> y >> z;
            normals.emplace_back(x, y, z);
        } else if (str == "o" || str == "g") {
            // Save current mesh if it has data
            if (!currentVertices.empty() || !currentIndices.empty()) {
                meshes[currentMeshName] = {currentVertices, currentIndices};
                currentVertices.clear();
                currentIndices.clear();
            }
            
            // Get new mesh name
            std::string meshName;
            std::getline(*in, meshName);
            
            // Trim whitespace
            meshName.erase(0, meshName.find_first_not_of(" \t"));
            meshName.erase(meshName.find_last_not_of(" \t") + 1);
            
            if (meshName.empty()) {
                meshName = (str == "o") ? "object_" + std::to_string(meshes.size()) 
                                       : "group_" + std::to_string(meshes.size());
            }
            
            currentMeshName = meshName;
        } else if (str == "f") {
            std::vector<std::string> faceTokens;
            std::string faceStr;
            
            // Read the entire face line
            std::string line;
            std::getline(*in, line);
            std::istringstream lineStream(line);
            
            while (lineStream >> faceStr) {
                faceTokens.push_back(faceStr);
            }

            if (faceTokens.size() < 3) continue;

            // Triangle fan approach: v0-v1-v2, v0-v2-v3, ...
            for (size_t i = 1; i + 1 < faceTokens.size(); ++i) {
                std::array<std::string, 3> triStrs = {faceTokens[0], faceTokens[i], faceTokens[i + 1]};
                for (const auto& token : triStrs) {
                    int posi = -1, texi = -1, nori = -1;
                    size_t firstSlash = token.find('/');
                    size_t secondSlash = token.find('/', firstSlash + 1);

                    try {
                        posi = std::stoi(token.substr(0, firstSlash)) - 1;
                    } catch (...) {
                        posi = -1;
                    }

                    if (secondSlash != std::string::npos) {
                        if (secondSlash > firstSlash + 1) {
                            try {
                                texi = std::stoi(token.substr(firstSlash + 1, secondSlash - firstSlash - 1)) - 1;
                            } catch (...) {
                                texi = -1;
                            }
                        }
                        if (secondSlash + 1 < token.size()) {
                            try {
                                nori = std::stoi(token.substr(secondSlash + 1)) - 1;
                            } catch (...) {
                                nori = -1;
                            }
                        }
                    }

                    Vertex v;
                    v.pos = (posi >= 0 && static_cast<size_t>(posi) < positions.size()) ? positions[posi] : glm::vec3(0.0f);
                    v.texCoord = (texi >= 0 && static_cast<size_t>(texi) < texcoords.size()) ? texcoords[texi] : glm::vec2(0.0f);
                    v.norm = (nori >= 0 && static_cast<size_t>(nori) < normals.size()) ? normals[nori] : glm::vec3(0.0f);

                    // Use std::find with the overloaded == operator
                    auto it = std::find(currentVertices.begin(), currentVertices.end(), v);
                    if (it != currentVertices.end()) {
                        currentIndices.push_back(static_cast<uint32_t>(std::distance(currentVertices.begin(), it)));
                    } else {
                        currentVertices.push_back(v);
                        currentIndices.push_back(static_cast<uint32_t>(currentVertices.size() - 1));
                    }
                }
            }
        } else {
            std::getline(*in, str); // skip the rest of the line
        }
    }

    // Save the last mesh
    if (!currentVertices.empty() || !currentIndices.empty()) {
        meshes[currentMeshName] = {currentVertices, currentIndices};
    }

    // Create model
    Model* model = new Model();

    // Create a mesh for each object/group
    for (const auto& meshData : meshes) {
        const auto& vertices = meshData.second.first;
        const auto& indices = meshData.second.second;

        if (vertices.empty() || indices.empty()) {
            continue;
        }

        Mesh* mesh = new Mesh();
        unsigned int VBO = 0, EBO = 0;

        glGenVertexArrays(1, &mesh->VAO);
        glGenBuffers(1, &VBO);
        glGenBuffers(1, &EBO);

        glBindVertexArray(mesh->VAO);

        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * vertices.size(), vertices.data(), GL_STATIC_DRAW);

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
        mesh->indexCount = indices.size();
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(uint32_t) * indices.size(), indices.data(), GL_STATIC_DRAW);

        // Set vertex attributes
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, pos));
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, norm));
        glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, texCoord));

        glEnableVertexAttribArray(0);
        glEnableVertexAttribArray(1);
        glEnableVertexAttribArray(2);

        glBindVertexArray(0);

        // Clean up buffers
        glDeleteBuffers(1, &VBO);
        glDeleteBuffers(1, &EBO);

        // Add mesh to model using both methods
        model->meshes.push_back(mesh);
        model->namedMeshes[meshData.first] = mesh;
        
        std::cout << "Loaded mesh: " << meshData.first 
                  << " (vertices: " << vertices.size() 
                  << ", indices: " << indices.size() << ")" << std::endl;
    }

    if (model->meshes.empty()) {
        std::cerr << "Warning: No meshes found in OBJ file" << std::endl;
    }

    return model;
}
}
