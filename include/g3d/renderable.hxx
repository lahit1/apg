#pragma once

struct Renderable {
	Renderable* next_r;

	virtual ~Renderable() = 0;

	virtual void render() = 0;
};
