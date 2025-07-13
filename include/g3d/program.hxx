#pragma once

#include<g3d/shader.hxx>

struct Program {
	unsigned int ptr;
	inline void attach(Shader* s) {
        	glAttachShader(ptr, s->ptr);
	}

	inline void link() {
        	glLinkProgram(ptr);
	}
	inline void use() {
		glUseProgram(ptr);
	};
};

namespace Programs {

Program* create();

}
