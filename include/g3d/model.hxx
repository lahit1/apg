#pragma once

#include <g3d/mesh.hxx>
#include <g3d/material.hxx>
#include <glm/glm.hpp>
#include <unordered_map>

struct Model;

namespace Models {
	Model* loadObjModel(std::istream* in);	
}

struct Model : Renderable {

	std::vector<Mesh*> meshes;
	std::unordered_map<std::string, Mesh*> namedMeshes;

	Material* material;

	glm::mat4 matrix = glm::mat4(1);

	~Model() {
		for (Mesh* mesh : meshes)
			delete mesh;
		meshes.clear();
		namedMeshes.clear();
	}

	inline void addChild(Mesh *r) {
		meshes.push_back(r);
	};

	inline void addChild(Mesh *r, std::string name) {
		meshes.push_back(r);
		namedMeshes[name] = r;
	}


	inline bool loadFromObj(std::istream* in) {
		Model* loadedModel = Models::loadObjModel(in);
		if (loadedModel && !loadedModel->meshes.empty()) {
			for (Mesh* mesh : loadedModel->meshes)
				this->meshes.push_back(mesh);

			for (const auto& pair : loadedModel->namedMeshes)
				this->namedMeshes[pair.first] = pair.second;

			loadedModel->meshes.clear();
			loadedModel->namedMeshes.clear();
			delete loadedModel;

			return true;
		}
		return false;
	}

	void render() override;
};
