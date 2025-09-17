#pragma once

#include <glm/glm.hpp>
#include <ape/g3d/keyframe.hxx>

#include <vector>

struct BoneAnimation {
	std::vector<KeyFrame> keyframes;

	glm::mat4 interpolate(float current_time);
};
