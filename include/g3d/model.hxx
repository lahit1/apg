#include <g3d/mesh.hxx>
#include <g3d/material.hxx>
#include <glm/glm.hpp>


class Model : Renderable {

	Mesh *first=nullptr, *last=nullptr, *current=nullptr;

	public:

	Material mat;

	glm::mat4 matrix = glm::mat4(1);

	inline void addChild(Mesh *r) {
		if(last == nullptr)
			first = last = r;
		else {
			last->next_r = r;
			last = r;
		}
	};

	inline void reset() {
		current = first;
	}

	inline bool isAvailable() {
		return current != nullptr;
	}

	inline Mesh* next() {
		if(current == nullptr) return current;
		Mesh *ret = current;
		current = static_cast<Mesh*>(current->next_r);
		return ret;
	}
};
