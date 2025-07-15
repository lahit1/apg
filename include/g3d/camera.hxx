#pragma once

#include<glm/glm.hpp>

#define LIMIT_X_ANGLE glm::radians(75.0f)

#define vec2 glm::vec2
#define vec3 glm::vec3
#define mat4 glm::mat4


constexpr vec3 zaxis{0, 0, 1};
constexpr vec3 yaxis{0, 1, 0};
constexpr vec3 xaxis{1, 0, 0};

struct Camera {

	Camera();

	vec3 pos = vec3(0,0,0), dist = vec3(0,0,5), up = yaxis;
	mat4 view, proj, vp;

	float fov = glm::radians(45.0f);
	float aspect = 4.0f / 3.0f;
	float nearPlane = 0.1f;
	float farPlane = 100.0f;

	void rotate(float radians, vec2 scale); // Scale relative to screen cursor position and screen size
	void updateView();
	void updateProjection();
	void updateVP();
};
