#pragma once

#include<glm/glm.hpp>

constexpr glm::vec3 zaxis{0, 0, 1};
constexpr glm::vec3 yaxis{0, 1, 0};
constexpr glm::vec3 xaxis{1, 0, 0};

struct Camera {

	Camera();

	glm::vec3 pos = glm::vec3(0,0,0), dist = glm::vec3(0, 0, 5), up = yaxis;
	glm::mat4 view, proj, vp;

	float fov = glm::radians(45.0f);
	float aspect = 4.0f / 3.0f;
	float nearPlane = 0.1f;
	float farPlane = 100.0f;

	void updateView();
	void updateProjection();
	void updateVP();
};
