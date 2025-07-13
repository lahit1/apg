#pragma once

#include<glm/glm.hpp>

#define vec3 glm::vec3
#define mat4 glm::mat4

struct Camera {

	mat4 matrix;

	float depth;

	vec3 pos, rot; // rot can be just a vec2 with manual calculations, may be i do it later ;)

	void rotate(vec3 rotation, float scalex, float scaley, float scalez); // euler rotations
	void update();
};
