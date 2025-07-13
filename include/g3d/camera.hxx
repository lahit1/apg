#pragma once

#include<glm/glm.hpp>

#define LIMIT_X_ANGLE glm::radians(75)
#define vec2 glm::vec2
#define vec3 glm::vec3
#define mat4 glm::mat4

struct Camera {

	vec3 pos;
	mat4 rot, view, dist;

	float rotx; // rot can be just a vec2 with manual calculations, may be i do it later ;)

	void rotate(float radians, vec2 scale); // Scale relative to screen cursor position and screen size
	void updateView();
	void updateProjection();
};
