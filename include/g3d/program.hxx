#pragma once

#include<g3d/shader.hxx>

struct Program;

namespace Programs {

	inline const char* mvpULoc = "mvpU";

	Program* create();
}

struct Program {

	GLuint mvpULoc_ptr;

	unsigned int ptr;
	inline void attach(Shader* s) {
        	glAttachShader(ptr, s->ptr);
	}

	inline void link() {
        	glLinkProgram(ptr);
		mvpULoc_ptr = glGetUniformLocation(ptr, Programs::mvpULoc);
	}
};
