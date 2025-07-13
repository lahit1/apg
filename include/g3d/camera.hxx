#pragma once

#include<glm/glm.hpp>

#define LIMIT_X_ANGLE glm::radians(75)

#define vec3 glm::vec3
#define mat4 glm::mat4

struct Camera {

	vec3 pos, dist;
	mat4 rot, view;

	float rotx;

	void rotate(float radians, vec2 scale); // Scale relative to screen cursor position and screen size
	void updateView();
	void updateProjection();
};
