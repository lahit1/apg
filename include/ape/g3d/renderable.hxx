#pragma once

#include <ape/g/program.hxx>
#include <memory>

struct Renderable {
	Renderable* next_r;

	virtual ~Renderable() = 0;

	virtual void render(std::shared_ptr<Program> pr) = 0;
};
