#pragma once

#include<glm/glm.hpp>

struct Vertex {
	glm::vec3 pos, norm;
	glm::vec2 texCoord;
	glm::vec4 color; // rgba

	inline bool operator==(const Vertex& other) const {
	        return pos == other.pos &&
        	       norm == other.norm &&
	               texCoord == other.texCoord &&
        	       color == other.color;
	}
};
