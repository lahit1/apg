#pragma once

#include<glm/glm.hpp>

#define LIMIT_X_ANGLE glm::radians(75)

#define vec2 glm::vec2
#define vec3 glm::vec3
#define mat4 glm::mat4

struct Camera {

	vec3 pos, dist;
	mat4 rot, view, proj, vp;
	float rotx;

	float fov = glm::radians(45.0f);
	float aspect = 4 / 3;
	float nearPlane = 0.1f;
	float farPlane = 100.0f;

	void rotate(float radians, vec2 scale); // Scale relative to screen cursor position and screen size
	void updateView();
	void updateProjection();
	void updateVP();
};
