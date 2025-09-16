#pragma once

#include <ape/g3d/mesh.hxx>
#include <ape/g3d/material.hxx>
#include <glm/glm.hpp>
#include <unordered_map>
#include <memory>

struct Model;

namespace Models {
	std::shared_ptr<Model> loadObjModel(std::istream* in);	
}

struct Model : Renderable {

	std::vector<std::shared_ptr<Mesh>> meshes;
	std::unordered_map<std::string, std::shared_ptr<Mesh>> namedMeshes;

	std::shared_ptr<Material> material;

	glm::mat4 matrix = glm::mat4(1);

	~Model() {
		meshes.clear();
		namedMeshes.clear();
	}

	inline void addChild(std::shared_ptr<Mesh> r) {
		meshes.push_back(r);
	};

	inline void addChild(std::shared_ptr<Mesh> r, std::string name) {
		meshes.push_back(r);
		namedMeshes[name] = r;
	}


	inline bool loadFromObj(std::istream* in) {
		std::shared_ptr<Model> loadedModel = Models::loadObjModel(in);
		if (loadedModel && !loadedModel->meshes.empty()) {
			for (std::shared_ptr<Mesh> mesh : loadedModel->meshes)
				this->meshes.push_back(mesh);

			for (const auto& pair : loadedModel->namedMeshes)
				this->namedMeshes[pair.first] = pair.second;

			loadedModel->meshes.clear();
			loadedModel->namedMeshes.clear();

			return true;
		}
		return false;
	}

	void render(std::shared_ptr<Program> pr) override;
};
