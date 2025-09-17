#pragma once

#include <unordered_map>
#include <ape/g3d/boneanimation.hxx>
#include <string>

enum {

	AMODE_ONCE = 0,
	AMODE_REPEAT

};

struct Animation {
	float duration;
	float current_time;

	char amode = 1;

	bool pmode = true;

	std::unordered_map<std::string, BoneAnimation> boneanimations;

	void act(float dt);

	inline void play() {
		pmode = 1;
	}

	inline void stop() {
		pmode = 0;
		current_time = 0;
	}

	inline void pause() {
		pmode = 0;
	}
};
