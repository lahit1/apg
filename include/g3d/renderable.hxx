#pragma once

struct Renderable {
	Renderable* next_r;

	virtual ~Renderable();
};
